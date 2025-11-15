# BASIC
## 一、 *头文件*
#### 1.`<iostream>` : input/output;
#### 2.`<cstdio>` : including：scanf()/printf()/...(c语言的all);
#### 3.`<iomanip>`与常用函数 ：
##### 3.1 小数精度与格式控制（最常用）
- `setprecision(int n)` ：核心控制 “数字精度”，需搭配`fixed`/`scientific`使用，否则控制 “有效数字总数(小数点前后)”
- `fixed` ：固定小数格式（强制按 “整数.小数” 形式输出），常与 setprecision 搭配控制小数位数
- `scientific` ：科学计数法格式(如 3.14e+00),适合极大/极小的数，同样需搭配`setprecision()`控制精度
```cpp
double num = 3.14159;
cout << setprecision(3) << num; // 无fixed，控制有效数字：输出3.14
cout << fixed << setprecision(3) << num; // 搭配fixed，控制小数位：输出3.142
cout << scientific << setprecision(3) << num; // 科学计数法+3位小数：输出3.142e+00
/*C*/
printf("%n.g",num); //控制 n 位有效数字（对应无 fixed 的 setprecision (n)）
printf("%.nf",num); //固定 n 位小数（对应 C++ fixed+setprecision (n)）
printf("%.ne",num); //科学计数法 + n 位小数（对应 scientific+setprecision (n)）
```
- `resetiosflags(fixed | scientific)`：重置小数格式，恢复默认的 “有效数字” 模式（取消`fixed`或`scientific`的效果）
```cpp
cout << fixed << setprecision(2) << 123.456; // 输出123.46
cout << resetiosflags(ios::fixed) << setprecision(3) << 123.456; // 重置后，输出123（3位有效数字）

printf("%.2f\n", 123.456); // 先输出 123.46（2 位小数）
printf("%g\n", 123.456); // 再用`%g`覆盖，输出 123.456（默认有效数字）
```
##### 3.2 输出对齐控制（排版常用）与 填充字符控制（配合对齐 / 宽度）
- `setw(int n)`：设置 “下一个输出项” 的宽度(**默认右对齐**)
- `left` ：设置**“后续输出”**左对齐（配合 setw 使用，覆盖默认右对齐）
- `right` ：重置为默认的右对齐（取消 left 效果）
- `setfill(char c)` ：设置 “输出宽度不足时” 的填充字符（默认填充空格），需配合 setw 使用才生效
```cpp
cout << left << setw(5) << "A" << setw(5) << "B"; // 左对齐：输出"A    B    "
cout << right << setw(5) << "C"; // 重置右对齐：输出"    C"
cout << setw(5) << setfill('*') << 123; //宽度5、右对齐、不足用'*'填充：输出"**123"
cout << left << setw(5) << setfill('#') << 123; //左对齐、宽度5、填充'#'：输出"123##"

printf("%5d\n", 123); // 右对齐，输出 "  123"(默认)
printf("%-5d\n", 123); // '-'左对齐，输出 "123  "
printf("%05d\n", 123); // 0 填充，输出 "00123"
```
##### 3.3 进制转换控制（配合整数输出）
- `oct` ：将后续整数输出为八进制（默认带前缀 0，如 25 输出 031）
- `hex` ：将后续整数输出为十六进制（默认带前缀 0x，小写；配合 uppercase 可转大写）
- `dec` ：重置为默认的十进制输出（取消 oct/hex 效果）
```cpp
int num = 25;
cout << oct << num; // 八进制：031
cout << hex << num; // 十六进制小写：0x19
cout << uppercase << hex << num; // 十六进制大写：0X19
cout << dec << num; // 重置十进制：25
```
- C语言中靠`printf`格式符直接指定 : `%o`（八进制）、`%x`（十六进制小写）、`%X`（十六进制大写）、`%d`（十进制）
```c
scanf("%o/%x/%d", &num)
```
#### 4. `<algorithm>`(提供算法，配合容器和数组使用) : 
- 排序:`std::sort()` // sort(nums.begin(), nums.end())
- 反转:`std::reverse()` // reverse(s.begin(), s.end())
- 查找:`std::find()` // find(nums.begin(), nums.end(), 5)
#### 5. `<cmath>`/`<climits>`/`<cstdlib>`(数值相关: 常量、绝对值、类型转换)
##### 5.1 `<climits>` ：
+ 5.1-1 `std::INT_MAX`（int 最大值）
+ 5.1-2 `std::INT_MIN`（int 最小值）
+ 5.1-3 `std::UINT_MAX`（unsigned int 最大值）
##### 5.2 `<cmath>` :
+ 5.2-1 `int std::abs(int x)` // 整数绝对值
+ 5.2-2 `double std::fabs(double x)` // 小数绝对值
+ 5.2-3 `double std::sqrt(double x)` // 平方根
+ 5.2-4 `double std::pow(double x , double y)` // x^y
##### 5.3 `<cstdlib>` :
+ 5.3-1 `int std::atoi(const char* c)` // 字符串转整数 
+ 5.3-2 `std::system("pause/cls")`

## 二、 *数据*
#### 1. 基本数据
|数据类型|关键字|字节|数据范围|易错点|
|:---:|:-----:|:-:|---------------|--------------|
|布尔型|`bool`|1|true(非0,本质存1)/false(0)|输出时 cout 会把 true->1/false->0|
|字符型|`char`/`signed char`|1|-128 ~ 127 ( -2⁷ ~ 2⁷-1) / 0~255(0 ~ 2⁸-1)|存储单个字符的本质是存**ASCII码**|
|短整型|`short`/`unsigned short`|2|-32768 ~ 32767 (-2¹⁵ ~ 2¹⁵-1) / 0 ~ 65535 (0 ~ 2¹⁶-1)|存储小范围整数，节省内存|
|整型|`int`/`unsigned int`|4|-2³¹ ~ 2³¹ - 1 / 0 ~ 2³² - 1|string::size()、vector::size()`retrne size_t`本质是unsigned int/long|
|长整型|`long`/`unsigned long`|4(32)/8(64)|32位: -2¹⁴⁷⁴⁸³⁶⁴⁸ ~ 2¹⁴⁷⁴⁸³⁶⁴⁷ / 0 ~ 2³² - 1    ; 64位：-2⁶³ ~ 2⁶³ - 1 / 0 ~ 2⁶⁴ - 1||
|长长整型|`long long`/`unsigned long long`|8|-2⁶³ ~ 2⁶³ - 1 /  0 ~ 2⁶⁴ - 1|必须 C++11 及以上编译器支持,整数常量需加后缀`LL`|
|单精度浮点型|`float`|4|±3.4×10³⁸(精度:约**6~7** 位有效数字)|小数常量默认是`double`，需加后缀`f`(3.14f),否则按 double 处理|
|双精度浮点型|`double`|8|±1.7×10³⁰⁸(精度:约**15~17**位有效数字)|精度比 float 高，多数场景用它|
#### 2. 复合数据
+ **数组** (`int arr[5]; / int arr[][3];`)
1. 基础类型字节数 × 数组长度,存储批量*同类型数据*
2. 长度固定，不能动态修改（需动态扩容用 vector）
3. 范围：下标从**0 ~ len-1**，越界访问会出错
+ **指针** (`int* p; / char* ch;`)	
1. 32位平台4字节',64位平台8字节,存储 "变量/数组/函数"的内存地址，实现**间接访问**字节数与 “指向的类型” 无关，只和平台位数有关
2. 未初始化的指针（野指针）不能访问，会导致程序崩溃
+ **引用** (`int& ref = num;`)
1. 本质: "变量的别名"，无独立字节数(编译器优化),**作为函数参数，避免拷贝(如修改实参、提升效率)**
2. 必须**初始化**(不能先定义再赋值),一旦绑定变量，不能再绑定其他变量(区别于指针)
+ **结构体** (`struct Student{};`)
1. 所有成员字节数之和(可能因 “内存对齐” 略有增加),存储不同类型数据(基本/复合数据)的组合
2. 字节数需考虑 **"内存对齐"**（如 struct {char c; int i;} 字节数是 8，不是 5）

## 三、*基础结构*
#### 1. 顺序
#### 2. 选择
##### 2.1 `switch`
```cpp
switch(choice)
{
case choice1:
  break;
case choice2:
  break;
case choice3:
  break;
case choice4:
  break;
default:
  break;
}
```
##### 2.2 `if`/`else if`/`else`
#### 3. 循环
##### 3.1 `for`
```cpp
for(int i = 0 , j = 10 ; i < n ; i++ , j--){}
for(auto &c : str){} //需要修改原始值的是时候用'&'，若仅需遍历输出可以不加（但是会拷贝）
for(const int &a : arr){} //只读不改，避免拷贝
```
##### 3.2 `while`/`do while`
#### 4. 跳转
##### 4.1 `break`
作用：跳出当前循环
##### 4.2 `continue`
作用：结束当前次的循环，进入下与一次循环
##### 4.3 `goto`
作用：
##### 4.4 `return`
作用：跳出当前函数，若函数有返回值则返回函数值








