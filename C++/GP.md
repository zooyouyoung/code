# Generic Programming

## 一、Template/Class
### 1. Function Template(函数模板)
+ 定义格式 ：`template <typename T1, typename T2,...>` `(typename`<=>`class`)
+ 关键特性：使用时自动推导类型,也可手动指定类型(避免推导歧义)
+ 避坑点：自动推导仅看 “函数参数”，与返回值无关。若参数类型不一致，推导会失败(需手动指定类型)
```cpp
template <typename T, typename U> 
T print_info(T id, U name)
{ 
    cout << "ID：" << id << "，姓名：" << name << endl;
    return id;
}
```
### 2. Class Template(类模板)
+ 定义格式：`template <typename T,...>` 紧跟类定义，类内成员
+ 关键特性：使用时必须手动指定类型(无法像函数模板一样自动推导)
+ 避坑点：类模板的 “成员函数” 若在类外定义，需重新写`template <typename T,...>`声明，否则编译器无法识别`T`
```cpp
template <typename T> 
class Student
{
private:
    T id;
    string name;
public:
    Student(T id_val, string name_val); 
    void show_info();
};
/* 成员函数类外定义：必须重新写 template <typename T>，否则识别不了T */
template <typename T> 
Student<T>::Student(T id_val, string name_val)
{
    id = id_val;
    name = name_val;
}
template <typename T> 
void Student<T>::show_info()
{ 
    cout << "学号：" << id << "，姓名：" << name << endl;
}
int main(){return 0;}
```
### 3. 模板的进阶特征
#### 1. Template Specialization(模板特化)
为特殊类型定制逻辑
+ 作用：当模板对某类 “特殊类型”(如string、指针)的逻辑不适用时，为该类型单独写定制代码(比如通用比较函数,对`string`不能比地址，需比字符串内容)
+ 分类：（1）**全特化**(为所有类型占位符指定具体类型)；（2）**偏特化**(仅为部分类型占位符指定具体类型，类模板专属，函数模板不支持偏特化)
```cpp
// 1. 通用模板：比较任意类型（默认比值/地址）
template <typename T> 
bool is_equal(T a, T b) {
    cout << "通用模板调用：";
    return a == b;
}

// 2. 全特化：为 T=string 定制逻辑（比较字符串内容，而非地址）
template <> // 全特化标志：空的 template 括号
bool is_equal<string>(string a, string b) { // 明确指定 T=string
    cout << "string 特化模板调用：";
    return a == b; // string 类重载了 ==，直接比内容
}

// 3. 全特化：为 T=const char*（C风格字符串）定制逻辑
template <> 
bool is_equal<const char*>(const char* a, const char* b) {
    cout << "const char* 特化模板调用：";
    return strcmp(a, b) == 0; // 用 strcmp 比内容，避免比地址
}

int main() {
    cout << is_equal(10, 10) << endl;          // 通用模板，输出1（true）
    cout << is_equal("apple", "apple") << endl;// const char* 特化，输出1
    cout << is_equal(string("banana"), string("banana")) << endl; // string 特化，输出1
    return 0;
}
```
#### 2. Non-type Template Parameters(非类型模板参数)
用 “值” 作为模板参数
+ 作用：模板参数不仅可以是 “类型`typename T`”，还可以是 “固定值(如`int` `char`、枚举),使用时传入具体值，适合“**固定长度 / 固定阈值**”的通用场景
+ 避坑点：非类型参数的 “值” 必须是 “编译期常量”(如字面量5,宏定义,`const`常量),不能是运行时才确定的值
```cpp
// 1. 模板参数：T（类型）、SIZE（非类型，int 值，数组长度）
template <typename T, int SIZE> 
class FixedArray {
private:
    T arr[SIZE]; // 数组长度为 SIZE（编译期确定，无需动态扩容）
public:
    void set_val(int idx, T val) {
        if (idx >= 0 && idx < SIZE) arr[idx] = val;
    }
    void print_arr() {
        for (int i = 0; i < SIZE; i++) cout << arr[i] << " ";
        cout << endl;
    }
};

int main() {
    // 2. 使用：传入类型 T=int、非类型参数 SIZE=3（数组长度3）
    FixedArray<int, 3> arr1;
    arr1.set_val(0, 10);
    arr1.set_val(1, 20);
    arr1.print_arr(); // 输出：10 20 0

    // 传入 T=double、SIZE=5（数组长度5）
    FixedArray<double, 5> arr2;
    arr2.set_val(0, 3.14);
    arr2.set_val(2, 5.67);
    arr2.print_arr(); // 输出：3.14 0 5.67 0 0
    return 0;
}
```
#### 3. Nested Template(模板的嵌套使用)
```cpp
vector<vector> point;
```

## 二、STL
### 1. Containers
```cpp
size()； //返回个数/长度
empty()； //判断是否为空
push_back(); //末尾添加
pop_back()； //末尾删除
```
***
#### 1.1 string
##### 1.1-1构造函数：
```cpp
string();
string(const char* str);
string(const string& str); //string str2(str1);
string(int n , char c); //string(n , 'a');
```
##### 1.1-2赋值：
```cpp
/*overload operator*/
string& operator=(const char* s); //将char*类型字符串 赋给当前字符串
string& operator=(const string& s); //将字符串s 赋给当前字符串
string& operator=(char c); //将字符c 赋给当前字符串
/*function of string , 写法：str.assign() */
string& assign(const char* s); //将char*类型字符串s 赋给当前字符串
string& assign(const char* s , int n); //将字符串s前n个字符 赋给当前字符串
string& assign(const string& s); //将字符串s 赋给当前字符串
string& assign(int n , char c); //用n个字符c赋给当前字符串
```
##### 1.1-3拼接/截取：
```cpp
/*overload operator ， str1 += "vkk"*/
string& operator+=(const char* s); 
string& operator+=(const string& s); 
string& operator+=(char c);
/*function of string , 写法：str.append() */
string& append(const char* s); //将char*类型字符串s 接到当前字符串末
string& append(const char* s , int n); //将字符串s前n个字符 接到当前字符串末
string& append(const string& s);
string& append(const string& s , int pos , int n); //字符串s中从pos开始的n个字符接到字符串的结尾

/*function of string , 写法：str.substr() */
string& substr(int pos , int n) const //从pos开始，截取n个字符
```
##### 1.1-4查找：
```cpp
/*function of string , 写法：str.find() */
int find(const string& str, int pos = 0) const; // 查找 str 第一次出现位置，从 pos 开始查找
int find(const char* s, int pos = 0) const; // 查找 s 第一次出现位置，从 pos 开始查找
int find(const char* s, int pos, int n) const; // 从 pos 位置查找 字符串s 的前 n 个字符第一次位置
int find(const char c, int pos = 0) const; // 查找字符 c 第一次出现位置
/*function of string , 写法：str.rfind() */
int rfind(const string& str, int pos = npos) const; // 查找 str 最后一次位置，从 pos 开始查找
int rfind(const char* s, int pos = npos) const; // 查找 s 最后一次出现位置，从 pos 开始查找
int rfind(const char* s, int pos, int n) const; // 从 pos 查找 s 的前 n 个字符最后一次位置
int rfind(const char c, int pos = 0) const; // 查找字符 c 最后一次出现位置
```
##### 1.1-5替换：
```cpp
/*function of string , 写法：str.replace() */
string& replace(int pos, int n, const string& str); // 替换从 pos 开始 n 个字符为字符串 str
string& replace(int pos, int n, const char* s); // 替换从 pos 开始的 n 个字符为字符串 s(n长度的字符串整个被replace为字符串s)
```
##### 1.1-6比较（按字符的ASCII码进行比较）：
1. `=` : return 0;
2. `>` : return 1;
3. `<` : return -1;
```cpp
/*overload operator , ==/!=/</>/... */
/*function of string , 写法：str.compare() */
int compare(const string& s) const; //与字符串s比较
int compare(const char* s) const;
```
##### 1.1-7存取：
```cpp
/*overload operator ， str1[] */
char& operator[](int n);
/*function of string , 写法：str.at() */
char& at(int n); //获取字符
```
##### 1.1-8插入/删除：
```cpp
/*function of string , 写法：str.insert() */
string& replace(int pos, const char* s); //插入字符串s
string& replace(int pos, const string& s); //插入字符串s
string& replace(int pos, int n, char c); //从指定位置pos开始插入n个字符c
/*function of string , 写法：str.erase() */
string& erase(int pos, int n = npos); // 删除从pos开始的n个字符
```
##### 扩展：输入/输出(不属于string容器的)：
```cpp
/* 输入包括空格，更加通用 */
cin.get(char& ch);
getchar(char& ch);
cin.getline(char* buf , int len);
cin.getline(cin , string& str);
getchar(char* buf);
/* 输出 */
putchar();
cout.put(char ch);
```
***
#### 1.2 vector
***
#### 1.3 deque
***
#### 1.4 list
***
#### 1.5 map
***
#### 1.6 set
***
### 2. Algorithms
+ `sort()`(排序)
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 自定义排序规则：降序（函数形式）
bool cmp_desc(int a, int b) {
    return a > b; // a>b时，a排在b前面（降序）
}
int main() {
    vector<int> vec = {3,1,4,1,5};
    /* 1. 默认排序：升序（依赖元素的'<'运算符） */
    sort(vec.begin(), vec.end());
    cout << "升序排序后：";
    for (int num : vec) cout << num << " "; // 输出：1 1 3 4 5
    /* 2. 自定义排序：降序（用cmp_desc函数） */
    sort(vec.begin(), vec.end(), cmp_desc);
    cout << "\n降序排序后：";
    for (int num : vec) cout << num << " "; // 输出：5 4 3 1 1
    /* 3. 用函数对象 "greater<int>()" */
    sort(vec.begin(), vec.end(), greater<int>());
    cout << "\n函数对象降序排序后：";
    for (int num : vec) cout << num << " "; // 输出：5 4 3 1 1

    return 0;
}
```
+ `find()`(查找)
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    vector<int> vec = {10,20,30};
    vector<int>::iterator it1 = find(vec.begin(), vec.end(), 20);
    if (it1 != vec.end()) {
        cout << "找到20，索引：" << it1 - vec.begin() << endl; 
    }
    
    vector<string> str_vec = {"apple", "banana", "orange"};
    auto it2 = find(str_vec.begin(), str_vec.end(), "banana");
    if (it2 != str_vec.end()) {
        cout << "找到字符串：" << *it2 << endl;
    }

    return 0;
}
```
+ `reverse()`(反转)
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    /* 1. 反转vector */
    vector<int> vec = {1,2,3,4,5};
    reverse(vec.begin(), vec.end());
    cout << "反转后vector：";
    for (int num : vec) cout << num << " "; // 输出：5 4 3 2 1
    /* 2. 反转string */
    string s = "hello";
    reverse(s.begin(), s.end());
    cout << "\n反转后string：" << s << endl; // 输出：olleh

    return 0;
}
```
+ `count()`(计数)
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> vec = {1,2,2,3,2,4};
    /* 统计2出现的次数 */
    int count_2 = count(vec.begin(), vec.end(), 2);
    cout << "元素2出现的次数：" << count_2 << endl; // 输出：3

    return 0;
}
```
+ `swap()`(交换): 
不交换容器对象本身的地址，仅交换内部存储数据的指针、大小等元信息
```cpp
#include <iostream>
#include <vector>
#include <list>
using namespace std;

int main() {
    /* 1. 随机访问迭代器（vector）：支持跳跃访问 */
    vector<int> vec = {1,2,3};
    vector<int>::iterator vec_it = vec.begin();
    vec_it += 2; // 跳跃2步，指向3（list迭代器不支持此操作）
    cout << "vector迭代器跳跃访问：" << *vec_it << endl; // 输出：3

    /* 2. 双向迭代器（list）：仅支持++/--，不支持跳跃 */
    list<int> lst = {10,20,30};
    list<int>::iterator lst_it = lst.begin();
    // lst_it += 2; // 报错！list迭代器无跳跃能力
    advance(lst_it, 2); // 需用advance函数移动2步，指向30
    cout << "list迭代器移动访问：" << *lst_it << endl; // 输出：30

    /* 3. 常量迭代器（const_iterator）：只读，不允许修改元素 */
    vector<int>::const_iterator const_vec_it = vec.begin();
    // *const_vec_it = 100; // 报错！常量迭代器不能修改元素
    cout << "常量迭代器只读访问：" << *const_vec_it << endl; // 输出：1

    return 0;
}
```
### 3. Iterators
迭代器本质是 “模拟指针的类”，统一了不同容器的遍历接口
#### 3.1 4种常用迭代器类型
|迭代器类型|核心功能|支持的容器|
|-----|--------|-----|
|输入迭代器|只读，只能向前遍历(++)，不支持(--)|所有容器(少用，算法内部用)|
|输出迭代器|只写，只能向前遍历(++)，不支持(--)|所有容器(少用，算法内部用)|
|双向迭代器|可读可写，支持向前(++)和向后(--)遍历|`list`、`map`、`set`|
|随机访问迭代器|可读可写，支持*双向遍历*和*跳跃访问*（+n、-n）|`vector`、`array`（最常用）|
```cpp
#include <iostream>
#include <vector>
#include <list>
using namespace std;

int main() {
    /* 1. 随机访问迭代器（vector）：支持跳跃访问 */
    vector<int> vec = {1,2,3};
    vector<int>::iterator vec_it = vec.begin();
    vec_it += 2; // 跳跃2步，指向3（list迭代器不支持此操作）
    cout << "vector迭代器跳跃访问：" << *vec_it << endl; // 输出：3

    /* 2. 双向迭代器（list）：仅支持++/--，不支持跳跃 */
    list<int> lst = {10,20,30};
    list<int>::iterator lst_it = lst.begin();
    // lst_it += 2; -> 报错！list迭代器无跳跃能力
    advance(lst_it, 2); // 需用advance函数移动2步，指向30
    cout << "list迭代器移动访问：" << *lst_it << endl; // 输出：30

    /* 3. 常量迭代器（const_iterator）：只读，不允许修改元素 */
    vector<int>::const_iterator const_vec_it = vec.begin();
    // *const_vec_it = 100; -> 报错！常量迭代器不能修改元素
    cout << "常量迭代器只读访问：" << *const_vec_it << endl; // 输出：1

    return 0;
}
```
### 4. Functors
### 5. Adapters
### 6. Allocators
