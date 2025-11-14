# STL
### 1. Container
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
