## 1. *What is Markdown ？*
**Markdown**是一种轻量级**标记语言**，它以纯文本形式(*易读、易写、易更改*)编写文档，并最终以HTML格式发布。    
**Markdown**也可以理解为将以MARKDOWN语法编写的语言转换成HTML内容的工具。    

## 2 *Why we use Markdown ？*
+ 它是易读（看起来舒服）、易写（语法简单）、易更改**纯文本**。处处体现着**极简主义**的影子。
+ 兼容HTML，可以转换为HTML格式发布。
+ 跨平台使用。
+ 越来越多的网站支持Markdown。
+ 更方便清晰地组织你的电子邮件。（Markdown-here, Airmail）

## 3. *How to use ？*
如果不算**扩展**，Markdown的语法绝对**简单**到让你爱不释手。

Markdown语法主要分为如下几大部分：
**标题**，**段落**，**区块引用**，**代码区块**，**强调**，**列表**，**分割线**，**链接**，**图片**，**反斜杠 `\`**，**符号 '`' **

### 3.1 标题(两种形式)  
1）使用`=`和`-`标记一级和二级标题

代码:
> 一级标题   
> `=========`   
> 二级标题    
> `---------`

效果：
> 一级标题   
> =========   
> 二级标题
> ---------  

2）使用`#`，可表示1-6级标题

代码：
> \# 一级标题   
> \## 二级标题   
> \### 三级标题   
> \#### 四级标题   
> \##### 五级标题   
> \###### 六级标题    

效果：
> # 一级标题   
> ## 二级标题   
> ### 三级标题   
> #### 四级标题   
> ##### 五级标题   
> ###### 六级标题

### 3.2 段落
段落的前后要有空行，所谓的空行是指没有文字内容。  
若想在段内强制换行的方式是使用**两个以上空格加上回车**（引用中换行省略回车）

### 3.3 区块引用
在段落的每行或者只在第一行使用符号`>`,还可使用多个嵌套引用

代码：
> \> 区块引用  
> \>> 嵌套引用  

效果：
> 区块引用  
>> 嵌套引用

### 3.4 代码区块
代码区块的建立是在每行加上4个空格或者一个制表符（如同写代码一样）

普通段落：

void main()    
{    
    printf("Hello, Markdown.");    
}    

代码区块：

    void main()
    {
        printf("Hello, Markdown.");
    }

**注意**:需要和普通段落之间存在空行

### 3.5 强调
在强调内容两侧分别加上`*`或者`_`

代码：
> \*斜体\*，\_斜体\_    
> \*\*粗体\*\*，\_\_粗体\_\_

效果：
> *斜体*，_斜体_    
> **粗体**，__粗体__

### 3.6 列表
使用`·`、`+`、或`-`标记无序列表

代码：
> \-（+\*） 第一项
> \-（+\*） 第二项
> \- （+\*）第三项

**注意**：标记后面最少有一个_空格_或_制表符_。若不在引用区块中，必须和前方段落之间存在空行

效果：
> + 第一项
> + 第二项
> + 第三项

有序列表的标记方式是将上述的符号换成数字,并辅以`.`

代码：
> 1 . 第一项   
> 2 . 第二项    
> 3 . 第三项    

效果：
> 1. 第一项
> 2. 第二项
> 3. 第三项

### 3.7 分割线
分割线最常使用就是三个或以上`*`，还可以使用`-`和`_`  

### 3.8 链接
链接可以由两种形式生成：**行内式**和**参考式**    
**行内式**：
> \[younghz的Markdown库\]\(https:://github.com/younghz/Markdown "Markdown"\)。

效果：
> [younghz的Markdown库](https:://github.com/younghz/Markdown "Markdown")。

**参考式**：
> \[younghz的Markdown库1\]\[1\]    
> \[younghz的Markdown库2\]\[2\]    
> \[1\]:https:://github.com/younghz/Markdown "Markdown"    
> \[2\]:https:://github.com/younghz/Markdown "Markdown"    

效果：
> [younghz的Markdown库1][1]    
> [younghz的Markdown库2][2]

[1]: https:://github.com/younghz/Markdown "Markdown"
[2]: https:://github.com/younghz/Markdown "Markdown"

**注意**：上述的`[1]:https:://github.com/younghz/Markdown "Markdown"`不出现在区块中。

### 3.9 图片
添加图片的形式和链接相似，只需在链接的基础上前方加一个`！`
### 3.10 反斜杠`\`
相当于**反转义**作用。使符号成为普通符号
### 3.11 符号'`'
起到标记作用

代码：
>\`ctrl+a\`

效果：
>`ctrl+a`    

## 4. *Who use it ?*
Markdown的使用者：
+ **GitHub**
+ 简书
+ Stack Overflow
+ Apollo
+ Moodle
+ Reddit
+ 等等

## 5.扩展(HTML):
Markdown的语法不能完全满足开发，但好在Markdown支持HTML,以下列举一些Markdown中高频使用的HTML语法

### 5.1文本样式（改色、改字体、组合样式）
```cpp
<!-- 1. <font>标签：快速改颜色、大小、字体 -->
<font color="red" size="3">红色3号字（size取值1-7，默认3）</font>
<font color="#0066CC" face="微软雅黑">蓝色、微软雅黑字体（#0066CC为精准色号）</font>
<font color="green" size="4">绿色4号字（适合标注关键提示）</font>
 
<!-- 2. <span>标签：灵活组合多样式（颜色+加粗+斜体） -->
<span style="color:orange; font-weight:bold">橙色加粗的重点标题</span>
<span style="color:gray; font-style:italic">灰色斜体的注释说明</span>
<span style="color:blue; font-weight:bold; font-size:16px">蓝色加粗16号字的核心提示</span>
```
### 5.2 标题对齐类（控制标题居中 / 右对齐）
```cpp
<!-- 居中的二级标题（适配项目功能模块标题，如“一、程序主界面”） -->
<h2 style="text-align:center">二、图书录入功能运行示例</h2>
<!-- 居中的三级标题（适配子模块标题，如“1. 输入操作说明”） -->
<h3 style="text-align:center">1. 输入操作步骤</h3>
<!-- 右对齐的四级标题（适合标注文档落款、补充说明） -->
<h4 style="text-align:right">—— 图书馆管理系统项目文档</h4>
```
### 5.3 图片控制类（控尺寸、居中、加边框）
```cpp
<!-- 1. 基础款：50%宽度（适配运行截图，避免图片过大） -->
<img src="images/main_menu.png" alt="程序主菜单截图" width="50%">
<!-- 2. 固定尺寸款：400像素宽（尺寸统一，排版更整齐） -->
<img src="images/add_book_success.png" alt="图书录入成功截图" width="400">
<!-- 3. 美观款：居中+50%宽度+灰色边框（提升截图质感） -->
<img src="images/book_borrow.png" alt="图书借阅功能截图" width="50%" style="display:block; margin:0 auto; border:1px solid #ccc">
<!-- 4. 备用款：加载失败显示替代文字（避免图片失效后空白） -->
<img src="images/book_return.png" alt="图书归还功能截图（加载失败请检查路径）" width="50%">
```
### 5.4 文本对齐类（控制普通段落对齐）
```cpp
<!-- 居中的说明段落（适合标注截图备注、整体提示） -->
<p style="text-align:center">注：所有截图均为程序实际运行效果，点击图片可查看原图。</p>
<!-- 右对齐的段落（适合文档结尾、版本说明） -->
<p style="text-align:right">版本：v1.0 | 更新时间：2025年</p>
<!-- 左对齐的段落（默认左对齐，可用于强调关键注意事项） -->
<p style="text-align:left; color:red">注意：运行前需注释掉`pause_clear()`中的`system("clear")`函数，避免界面被清空。</p>
```
### 5.5 分割线美化类（分隔文档模块）
```cpp
<!-- 粗红色分割线（分隔大模块，如“运行结果”与“提交文件说明”） -->
<hr style="border:2px solid red; width:80%">
<!-- 细蓝色分割线（分隔小模块，如“图书录入”与“图书借阅”功能） -->
<hr style="border:1px solid blue; width:70%">
<!-- 浅灰色细分割线（低调分隔，不抢内容注意力） -->
<hr style="border:1px solid #eee; width:90%">
```
### 5.6 列表补充类（列表项居中)
```cpp
<!-- 居中的无序列表（适合展示提交文件清单、核心功能列表） -->
<ul style="text-align:center; list-style-position:inside;">
  <li>提交文件1：library_manager.cpp（项目核心C++代码）</li>
  <li>提交文件2：README.md（项目说明文档，含运行结果与截图）</li>
  <li>提交文件3：images文件夹（存放所有程序运行截图）</li>
  <li>提交文件4：CMakeLists.txt（项目编译配置文件）</li>
</ul>

<!-- 居中的有序列表（适合展示程序操作步骤） -->
<ol style="text-align:center; list-style-position:inside;">
  <li>启动程序，查看主菜单功能选项</li>
  <li>输入“1”，执行图书信息录入操作</li>
  <li>按提示输入图书编号、名称、作者、库存，完成录入</li>
  <li>查看“图书录入成功”提示，确认功能正常</li>
</ol>
```

## 6. 尝试一下
+ **Chrome**下的插件诸如`stackedit`与`markdown-here`等非常方便，也不用担心平台受限。
+ **在线**的dillinger.io评价也不错 
+ **Linux**下的ReText不错。    

**当然，最终境界永远都是笔下是语法,自己的技术**

****
**注意**：不同的Markdown解释器或工具对相应语法（扩展语法）的解释效果不尽相同，具体可参见工具的使用说明。
虽然有人想出面搞一个所谓的标准化的Markdown，[没想到还惹怒了健在的创始人John Gruber]
(http://blog.codinghorror.com/standard-markdown-is-now-common-markdown/ )。
****
以上基本是所有traditonal markdown的语法。

## 其它：
列表的使用(非traditonal markdown)：

用`|`表示表格纵向边界，表头和表内容用`-`隔开，并可用`:`进行对齐设置，两边都有`:`则表示居中，若不加`:`则默认左对齐。

|代码库                              |链接                                |
|:------------------------------------:|------------------------------------|
|MarkDown                              |[https://github.com/younghz/Markdown](https://github.com/younghz/Markdown "Markdown")|
|MarkDownCopy                              |[https://github.com/younghz/Markdown](https://github.com/younghz/Markdown "Markdown")|


关于其它扩展语法可参见具体工具的使用说明。
