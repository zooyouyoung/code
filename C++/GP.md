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


### 2. Algorithms
### 3. Iterators
### 4. Functors
### 5. Adapters
### 6. Allocators
