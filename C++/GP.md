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
+ 1.1-1 构造函数：
```cpp
string(); // string str
string(const char* str); || string(const string& str); //string str2(str1);
string(int n , char c); //string str(n , 'a');
```
+ 1.1-2 赋值：
```cpp
/*overload operator*/
string& operator=(const char* s); || string& operator=(const string& s); //将字符串s 赋给当前字符串
string& operator=(char c); //将字符c 赋给当前字符串
/*function of string , 写法：str.assign() */
string& assign(const char* s , int n); //将字符串s前n个字符 赋给当前字符串
string& assign(const string& s); || string& assign(const char* s); //将字符串s 赋给当前字符串
string& assign(int n , char c); //用n个字符c赋给当前字符串
```
+ 1.1-3 拼接/截取：
```cpp
/*overload operator ， str1 += "vkk"*/
string& operator+=(const char* s); || string& operator+=(const string& s); 
string& operator+=(char c);
/*function of string , 写法：str.append() */
string& append(const char* s , int n); // 将字符串s前n个字符 接到当前字符串末
string& append(const string& s); || string& append(const char* s); // 将字符串s 接到当前字符串末
string& append(const string& s , int pos , int n); // 字符串s中从pos开始的n个字符接到字符串的结尾

/*function of string , 写法：str.substr() */
string& substr(int pos , int n) const //从pos开始，截取n个字符
```
+ 1.1-4查找：
```cpp
/*function of string , 写法：str.find() */
int find(const char* str, int pos = 0) const; || int find(const string& str, int pos = 0) const; // 查找 str 第一次出现位置，从 pos 开始查找
int find(const char* s, int pos, int n) const; // 从 pos 位置查找 字符串s 的前 n 个字符第一次位置
int find(const char c, int pos = 0) const; // 查找字符 c 第一次出现位置
/*function of string , 写法：str.rfind() */
int rfind(const string& str, int pos = npos) const; || int rfind(const char* str, int pos = npos) const; // 查找 str 最后一次位置，从 pos 开始查找
int rfind(const char* s, int pos, int n) const; // 从 pos 查找 s 的前 n 个字符最后一次位置
int rfind(const char c, int pos = 0) const; // 查找字符 c 最后一次出现位置
```
+ 1.1-5 替换：
```cpp
/*function of string , 写法：str.replace() */
string& replace(int pos, int n, const string& str); || string& replace(int pos, int n, const char* s); // 替换从 pos 开始的 n 个字符为字符串 s(n长度的字符串整个被replace为字符串s)
```
+ 1.1-6 比较（按字符的ASCII码进行比较）：
> 1. `=` : return 0;
> 2. `>` : return 1;
> 3. `<` : return -1;
```cpp
/*overload operator , ==/!=/</>/... */
/*function of string , 写法：str.compare() */
int compare(const char* s) const; || int compare(const string& s) const; //与字符串s比较
```
+ 1.1-7 存取：
```cpp
/*overload operator ， str1[] */
char& operator[](int n);
/*function of string , 写法：str.at() */
char& at(int n); //获取字符
```
+ 1.1-8 插入/删除：
```cpp
/*function of string , 写法：str.insert() */
string& replace(int pos, const char* s); || string& replace(int pos, const string& s); //插入字符串s
string& replace(int pos, int n, char c); //从指定位置pos开始插入n个字符c
/*function of string , 写法：str.erase() */
string& erase(int pos, int n = npos); // 删除从pos开始的n个字符
```
+ 扩展：输入/输出(不属于string容器的)：
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

#### 1.2 vector(单端数组)
+ 1.2-1 构造函数
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
vector<T> vec ; // 默认构造函数
vector<T> vec(n,elem); // 将n个elem赋给vec
vector<T> vec2(vec1.begin() , vec1.end()); // 将vec1的[begin(),end())的元素拷贝给vec2
vector<T> vec2(const vector& vec1); // 拷贝构造 vector<T> vec(vec1)
}
```
+ 1.2-2 赋值：
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
vector<T> vec1 {1,2,3}
vector<T> vec2;
vec2 = vec1; // operator=
vec2.assign(vec1.begin(),vec1.end());  
vec2.assign(n , elem);
}  
```
+ 1.2-3 容量/大小
```cpp
vector<T> vec;
vec.empty();
vec.capacity(); // 容量
vec.size(); // 大小
vec.resize(int n ，elem); // 重新指定大小为n,如果容器变长以elem填充(没写elem,以0填充)，如果变短删除末尾的数
```
+ 1.2-4 插入/删除
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
vector<T> vec {1，2，3，4，5};
vec.push_back(elem); // 尾部插入elem
vec.pop_back(); 
vec.insert(vec.begin() , n , elem) // 从vec的vec.begin()插入n个elem;(没n默认1个) 
vec.erase(vec.begin() , vec.begin()+3); // 从vec.begin()删到vec.begin()+3,可以只有vec.begin()(删一个)
vec.clear();
}
```
+ 1.2-5 存取
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
vector<T> vec {1,2,3,4};
vector<T> vec1 = vec[0] // operator[]
vec.at(int idx); // 返回[idx]元素 
vec.front(); // 返回第一个元素(0)
vec.back(); // 返回最后一个元素
}
```
+ 1.2-6 互换
```cpp
/* swap()的巧用->收缩内存空间 */
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vec {10, 20, 30, 40, 50};
    vec.push_back(60);
    vec.push_back(70);
    vec.erase(vec.begin() + 2, vec.end()); // 保留10,20，size=2, capacity=7（假设扩容后）
    cout << "删除后：size=" << vec.size() << ", capacity=" << vec.capacity() << endl;

    // 步骤1：创建临时 vector，仅包含原 vec 的有效元素（capacity=2）
    vector<int> temp_vec(vec.begin(), vec.end()); 
    cout << "临时vec：size=" << temp_vec.size() << ", capacity=" << temp_vec.capacity() << endl; // size=2, cap=2

    // 步骤2：交换原 vec 和临时 vec
    vec.swap(temp_vec); 
    // 交换后：原vec的size=2, cap=2；temp_vec的size=2, cap=7（冗余内存转移到temp_vec）

    cout << "收缩后：size=" << vec.size() << ", capacity=" << vec.capacity() << endl; // size=2, cap=2

    return 0;
}
```
+ 1.2-7 预留空间
```cpp
reserve(int len); // 开辟空间，但是数据没初始化
```
***

#### 1.3 deque(双端数组)
+ 1.3-1 构造函数
+ 1.3-2 赋值
+ 1.3-3 大小
+ 1.3-4 插入/删除
```cpp
deque<T> deq;
deq.pop_front();
deq.push_front(n);
```
+ 1.3-5 存取

**以上内容（1.3-1到1.3-5）均可参考`vector`容器**
+ 1.3-6 排序
```cpp
sort(iterator beg , iterator end);
```
***

#### 1.4 list
+ 基本概念：双向循环(指针有两个`prev`/`next`)链表，由***数据域***与***指针域***组成，因此数据并非连续的,是由指针指向的。
+ 1.4-1 构造函数/赋值
+ 1.4-2 大小/交换

**以上内容（1.4-1到1.4-2）可参考`vector`/`deque`容器**
+ 1.4-3 插入/删除

**此内容可参考`deque`容器对应内容,都有双向可增删的特点**
```cpp
#include<iostream>
#include<list>
#include <algorithm>

int main(){
list<int> lis {1,2,3,4};
list<int> lis2 {5,6,7,8};
list<int>::iterator it = lis.begin();
lis.insert(++it , n , elem); // 在从++it指向的位置插入n个(可以略去n,默认1)数据elem
lis.insert(--it , lis2.begin() , lis2.end()); 
lis.erase(++it); // 删除迭代器指向位置的元素
lis.erase(lis.begin() , lis.end());
lis.clear();
lis.remove(elem); // 删去所有value=elem的元素
}
```
+ 1.4-5 存取
```cpp
/* 无operator[] / at();  itreator只可以"++";"--" */
list<int> lis {1,2,3,4}; 
lis.front(); // 返回第一个元素 
lis.back(); 
```
+ 1.4-6 反转/排序
**此内容可参考`algorithm`**
```cpp
lis.reverse();
lis.sort(); // 与deque不同，"()"为空,进阶可以参考下面的Algorithm内容
```
***

#### 1.5 set
+ 特点：自动排序，无法插入重复元素(二叉树)
+ 1.5-1 构造/赋值
+ 1.5-2 大小/交换
+ 1.5-3 插入/删除
+ 1.5-4 查找/统计
+ 1.5-5 排序

**以上内容（1.5-1 ~ 1.5-5）逻辑上可以适当参考`map`容器,二者都与红黑树有关**
***

#### 1.6 map
+ 简介：map中元素都是pair，pair中都第一个元素为key(键值)，起索引作用，第二个元素为value(实值)。所有元素都会根据键值自动排序
+ 本质：关联式容器，底层结构用二叉树实现
+ 1.6-1 构造/赋值
```cpp
map<int,int> m1 = {(1,10),(2,20),(3,30)}; //  默认构造
map<int,int> m2(m1); // 拷贝构构造
map<int,int>m3;
m3 = m2; // operator=
```
+ 1.6-2 大小/交换
```cpp
map<int,int> m1 {(1,10),(2,20),(3,30),(4,40)};
m1.size();
m1.empty();
map<int,int> m2;
m2.swap(m1);
```
+ 1.6-3 插入/删除
```cpp
map<int,int> m1 {(1,10),(2,20),(3,30),(4,40)};
/* insert() */
m1.insert(pair<int,int>(5,55)); 
m1.insert(make_pair(6,65));
m1.insert(map<int,int>::value_type(7,66));
m1[0] = 11; //如果没有value，但是用的话，会创建value=0的元素(建议用于索引，不建议插入)
/* 删除 */
m1.erase(m1.begin(),m1.end()-2); // m1.begin()/m1.end()-2 -> key的值(可以只传第一个参)
m1.clear();
```
+ 1.6-4 查找/统计
```cpp
map<int,int> m1 {(1,22),(2,23),(3,44)};
map<int,int>::iterator pos = m1.find(key); // 返回iterator
m1.count(key); // return 1/0 -> key具有唯一性
```
+ 1.6-5 排序
利用仿函数(参考下面的Functors)
```cpp
#include<map>
/* 降序 */
class Mycompare{
public:
    bool operator()(int v1 , int v2){
        return v1 > v2 ;
    }
}
int main(){
    map<int,int,Mycompare> m1;
    m1.insert(make_pair(1,10));
    m1.insert(make_pair(2,20));
    m1.insert(make_pair(3,30));
    m1.insert(make_pair(4,40));
    m1.insert(make_pair(5,50));

    for(map<int,int,Mycompare>::interator it = m1.begin() ; it != m.end() ; it++){
        cout << "key:" << it->first << "value:" << (*it).second << endl;
    }
}
```
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
    /* 1. 默认排序：升序（依赖元素的'<'运算符），仅支持随机访问迭代器 */
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
+ 函数对象是 “重载了函数操作符的类",调用时像函数一样(e.g:`greater<int>()`)，核心用于定制算法的逻辑。重载函数操作符`()`，行为类似函数的调用，也称为仿函数
#### 4.1 遍历
+ 4.1-1 `for_each`
+ 4.1-2 `transform`
+ 4.1-3 `find`
#### 4.2 查找
+ 4.2-1 `find_if`
+ 4.2-2 `adjacent_find`
+ 4.2-3 `binary_search`
+ 4.2-4 `count`
+ 4.2-5 `count_if`
#### 4.3 排序
+ 4.3-1 `sort`
+ 4.3-2 `random_shuffle`
+ 4.3-3 `merge`
+ 4.3-1 `reverse`
#### 4.4 拷贝/替换
+ 4.4-1 `copy`
+ 4.4-2 `replace`
+ 4.4-3 `replace_if`
+ 4.4-4 `swap`
#### 4.5 算术生成
+ 4.5-1 `accumulate`
+ 4.5-2 `fill`
#### 4.6 集合
+ 4.6-1 `set_intersection`
+ 4.6-2 `set_union`
+ 4.6-1 `set_difference`
### 5. Adapters
### 6. Allocators
