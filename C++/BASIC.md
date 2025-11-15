# BASICS 

## 一、 Precessing
### *Macro*
#### 1. `#include<>/#include""`
#### 2. `#define`(宏定义)
+ 作用：定义**无参/带参宏**，实现文本替换
+ 格式：`#define PI 3.14`、`#define ADD(a,b) (a)+(b)`(a,b要"()")
#### 3. `#undef`
+ 作用：取消之前定义的宏，之后代码中该宏名不再生效（避免宏污染后续代码）
+ 格式：#undef 宏名（无替换文本，直接取消）
#### 4. `#ifdef`/`#ifndef`/`#else`/`#endif`
+ 作用：根据**宏是否已定义**，决定某段代码是否参与编译（仅保留满足条件的代码，其他代码预处理时直接删除，减少最终可执行文件大小）
+ 格式：

(1) `#ifdef 宏名`（宏已定义，则编译代码）
```cpp
#define DEBUG // 定义DEBUG宏（开启调试模式）
int main() {
    int a = 10;
    // 条件编译：若DEBUG已定义，编译以下代码（调试时打印变量）
    #ifdef DEBUG
        cout << "调试模式：a=" << a << endl; // 会编译，输出a=10
    #else
        cout << "发布模式" << endl; // 不编译
    #endif // 结束条件编译
    return 0;
}
```
(2) `#ifndef 宏名`（宏未定义，则编译代码，常用于防止头文件重复包含）
```cpp
// 自定义头文件 my_header.h
#ifndef MY_HEADER_H // 若MY_HEADER_H未定义，(if no define)则进入
#define MY_HEADER_H // 定义MY_HEADER_H，下次再包含时会跳过
#define MAX 200
void func();

#endif // 结束条件编译
return 0;
```
#### 5. `#if`/`#elif`/`#else`/`#endif`(数值条件编译,按数值条件决定是否编译)
+ 作用：判断 “数值表达式” 的真假（非 0 为真，0 为假），决定代码是否编译（比 #ifdef 更灵活，支持数值比较）
+ 格式：`#if 数值表达式`（表达式必须是编译期常量，不能是运行时变量）
```cpp
#define VERSION 3 // 定义版本号（编译期常量）
int main() {
    #if VERSION == 1
        cout << "版本1：基础功能" << endl;
    #elif VERSION == 2
        cout << "版本2：新增查询功能" << endl;
    #elif VERSION == 3
        cout << "版本3：新增修改和删除功能" << endl; // 编译后输出这句
    #else
        cout << "未知版本" << endl;
    #endif // 结束条件编译
    return 0;
}
```
#### 6. `#error`
+ 作用：强制报错，检测非法条件 
+ 格式：`#error 错误提示信息`(错误提示信息不加"")
#### 7. predefined macros
|预定义宏|核心作用|类型|代码实例（输出效果）|
|:---:|--------|:----:|--------|
|`__FILE__`|返回当前源文件的 “完整路径 + 文件名”|字符串常量|cout << __FILE__ → D:\code\test.cpp|
|`__LINE__`|返回当前代码所在的 “行号”|整数常量|cout << __LINE__ → 8（假设代码在第 8 行）|
|`__DATE__`|返回编译时的 “日期”|字符串常量|cout << __DATE__ → Oct 26 2024|
|`__TIME__`|返回编译时的 “时间”|字符串常量|cout << __TIME__ → 15:30:45|
|`__cplusplus`|返回 C++ 标准版本号（判断编译器是否支持 C++xx）|整数常量|cout << __cplusplus → 201703（C++17）|

+ **注意** : 预定义宏的值是 “编译期确定” ，不是运行时动态变化的
### *Header Files*
#### 1.`<iostream>` : input/output;
#### 2.`<cstdio>` : including：scanf()/printf()/...(c语言的all);
#### 3. `<algorithm>`(提供算法，配合容器和数组使用) : 
- 排序:`std::sort()` // sort(nums.begin(), nums.end())
- 反转:`std::reverse()` // reverse(s.begin(), s.end())
- 查找:`std::find()` // find(nums.begin(), nums.end(), 5)
#### 4. `<cmath>`/`<climits>`/`<cstdlib>`(数值相关: 常量、绝对值、类型转换)
##### 4.1 `<climits>` ：
+ 4.1-1 `std::INT_MAX`（int 最大值）
+ 4.1-2 `std::INT_MIN`（int 最小值）
+ 4.1-3 `std::UINT_MAX`（unsigned int 最大值）
##### 4.2 `<cmath>` :
+ 4.2-1 `int std::abs(int x)` // 整数绝对值
+ 4.2-2 `double std::fabs(double x)` // 小数绝对值
+ 4.2-3 `double std::sqrt(double x)` // 平方根
+ 4.2-4 `double std::pow(double x , double y)` // x^y
##### 4.3 `<cstdlib>` :
+ 4.3-1 `int std::atoi(const char* c)` // 字符串转整数 
+ 4.3-2 `std::system("pause/cls")`
#### 5.`<iomanip>`与常用函数 ：
##### 5.1 小数精度与格式控制（最常用）
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
##### 5.2 输出对齐控制（排版常用）与 填充字符控制（配合对齐 / 宽度）
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
##### 5.3 进制转换控制（配合整数输出）
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


## 二、 Datas
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


## 三、Control Flow
#### 1. 顺序
#### 2. 选择
##### 2.1 `switch`
```cpp
/* switch与enum的使用 */
int main() {
    // 定义枚举：表示“订单状态”，每个枚举值对应一个整数（默认0开始，可自定义）
    enum OrderStatus {
        PENDING = 1,  // 待支付（自定义值1）
        PAID = 2,     // 已支付
        SHIPPED = 3,  // 已发货
        DELIVERED = 4 // 已送达
    };
    OrderStatus status; // 定义枚举类型变量
    cout << "请输入订单状态（1.待支付 2.已支付 3.已发货 4.已送达）：" << endl;
    cin >> (int)status; // 枚举需强转为int接收输入
    switch (status) {
        case PENDING: cout << "订单状态：待支付，需尽快付款！" << endl; break;
        case PAID: cout << "订单状态：已支付，等待发货！" << endl; break;
        case SHIPPED: cout << "订单状态：已发货，预计3天送达！" << endl; break;
        case DELIVERED: cout << "订单状态：已送达，感谢使用！" << endl; break;
        default: cout << "状态输入错误！" << endl; break;
    }
    return 0;
}
```
##### 2.2 `if`/`else if`/`else`
......
#### 3. 循环
##### 3.1 `for`
```cpp
for(int i = 0 , j = 10 ; i < n ; i++ , j--){}
for(auto &c : str){} //需要修改原始值的是时候用'&'，若仅需遍历输出可以不加（但是会拷贝）
for(const int &a : arr){} //只读不改，避免拷贝
```
##### 3.2 `while`/`do while`
```cpp
while(1/true){};
while(cin >> str){};
while(int n = 0 ; n < 12){}; // while(循环变量的定义+初始化)"C++17 及以上支持",变量仅在循环范围内有效(避免污染外部代码)
```
+ **注意** : 表达式不能是 “非整数型”：e.g:switch(3.14)（double）、switch("abc")（string),都会编译报错，只能用`int`、`char`、`enum`等整数型
#### 4. 跳转
##### 4.1 `break`
作用：跳出当前循环
##### 4.2 `continue`
作用：结束当前次的循环，进入下与一次循环
##### 4.3 `goto`
作用：在当前函数中，从当前位置跳转到标记位置(风险高，逻辑易混乱)
```cpp
flag:
...
goto flag;
```
##### 4.4 `return`
作用：跳出当前函数，若函数有返回值则返回函数值

## 四、Functions
### 1. 函数的定义与调用
```cpp
void name(){} // 方式1：无参无返
int name(){return 0;} // 方式2：无参有返
void name(int a , int b , ...){} // 方式3：有参无返
string name(char* ch){return "";} // 方式4：有参有返
```
### 2. 函数核心特性
#### 2.1 函数声明与定义分离(方便维护)
+ 声明：告诉编译器 “函数存在及格式”，写在 main 前或头文件中；
+ 定义：提供 “函数具体实现”，写在`main`后或单独的`.cpp`文件中
```cpp
#include <iostream>
using namespace std;
/* 函数声明（关键：返回值、函数名、参数类型/顺序必须和定义一致）*/
int max_val(int a, int b); // 参数名a/b可省略，写成int max_val(int, int);
int main() {
    cout << "max(25,18)=" << max_val(25, 18) << endl;
    return 0;
}

/* 函数定义（实现逻辑，参数名可和声明一致或重新命名）*/
int max_val(int x, int y) {
    return x > y ? x : y;
}
```
#### 2.2 默认参数（简化常用场景的调用）
+ 定义：声明时给参数加 “默认值”，默认参数必须放在"**参数列表末尾**"
+ 调用：可传入全部实参（覆盖默认值），也可省略默认参数的实参（用默认值）；
+ **注意**：默认值仅能在 “声明中写”，定义中不能重复写
```cpp
#include <iostream>
using namespace std;

/* 函数声明：默认参数必须在尾部 */
int calculate_total(int count, int price = 10);
int main() {
    // 调用方式1：省略默认参数
    cout << "5件商品总价：" << calculate_total(5) << endl;
    // 调用方式2：传入全部实参，覆盖默认值
    cout << "5件商品（单价15）总价：" << calculate_total(5, 15) << endl;
    return 0;
}

/* 函数定义：参数price不能再写默认值（否则报错）*/
int calculate_total(int count, int price) {
    return count * price;
}
```
#### 2.3 函数重载
+ 定义：多个函数 “*函数名相同*”，但"*参数列表不同*"（参数个数不同、参数类型不同、参数顺序不同）
+ **注意**：仅返回值不同，不能构成重载
```cpp
```
#### 2.4 函数模板
+ 定义：用 template <typename T> 定义 “类型占位符 T”，函数的参数、返回值用 T 代替，无需为不同类型写多个重载函数
+ 调用：自动推导类型（根据实参），或手动指定类型（避免歧义）
```cpp
```
### 3. 函数进阶用法
#### 3.1 递归函数（函数调用自身，解决 “分治” 问题）
+ 定义：函数体内调用自身，必须有 “终止条件”（否则无限递归，栈溢出崩溃）
+ 场景：阶乘、斐波那契数列、二叉树遍历
代码实例：计算 n 的阶乘（n! = n*(n-1)*...*1）
```cpp
#include <iostream>
using namespace std;
// 递归函数：计算n的阶乘
int factorial(int n) {
    if (n == 1) {
        return 1;
    }
    // 递归逻辑：n! = n * (n-1)!
    return n * factorial(n - 1);
}
int main() {return 0;}
```
#### 3.2 内联函数（inline，提升简单函数的执行效率）
+ 定义：在函数声明/定义前加`inline`关键字，编译器会将 “函数调用” 替换为“函数体代码”
+ **注意**：仅适合 “逻辑简单、代码量少” 的函数（如加法、比较），复杂函数（多循环/多分支）加`inline`无效（编译器会忽略）
```cpp
#include <iostream>
using namespace std;
// 内联函数：简单比较逻辑，加inline提升效率
inline int min_val(int a, int b) {
    return a < b ? a : b;
}
int main() {
    // 调用时，编译器会替换为：cout << (3 < 5 ? 3 : 5) << endl;
    cout << "min(3,5)=" << min_val(3, 5) << endl;
    return 0;
}
```
#### 3.3 函数指针（指向函数的指针，存储函数地址）
+ 定义：格式为 “返回值类型 (* 指针名)(参数类型列表)”，指针指向 “返回值和参数匹配” 的函数
+ 场景：动态切换函数（如根据条件调用不同的计算函数）、回调函数。
```cpp
#include <iostream>
using namespace std;
// 两个普通函数（返回值、参数类型一致，可被同一函数指针指向）
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int main() {
    // 1. 定义函数指针：指向“返回int、接收两个int参数”的函数
    int (*func_ptr)(int, int);
    // 2. 指针指向add函数（函数名即函数地址，无需&）
    func_ptr = add;
    cout << "10+20=" << func_ptr(10, 20) << endl;
    // 3. 指针指向sub函数（切换指向的函数）
    func_ptr = sub;
    cout << "10-20=" << func_ptr(10, 20) << endl;
    return 0;
}
```
