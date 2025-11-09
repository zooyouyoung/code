#include<iostream>
using namespace std;
#include<vector>
#include<limits>//用于numeric_limits

/*创建图书类*/
class Book
{
public:
    string bookName;
    string writerName;
    int bookPrice;
    bool bookLended;
};

/*界面functions*/
void WebPage()
{
    cout << "********************************" << endl;
    cout << "******** 0.终止程序操作 ********" << endl;
    cout << "******** 1.图书入库操作 ********" << endl;
    cout << "******** 2.图书借阅操作 ********" << endl;
    cout << "******** 3.图书归还操作 ********" << endl;
    cout << "******** 4.图书查询操作 ********" << endl;
    cout << "********************************" << endl;
    cout << "请输入所要执行的操作(0/1/2/3/4): " ;
}

/*控制系统等待和清屏*/
void pause_clear()
{
    cout << "即将返回目录，请按任意键继续..." << endl;
    cin.ignore(numeric_limits<streamsize>::max() , '\n');
    cin.get();
    system("clear");
}

/*入库functions*/
void cinBook(vector<Book>& book)
{
    string book_name , writer_name ;
    int book_price;
    bool book_lended = 0;

    cout << "请按照要求输入书本信息" << endl;
    cout << "请输入书名:" << " ";
    cin >> book_name;
    cout << "请输入作者" << " ";
    cin >> writer_name;
    cout << "请输入价格" << " ";
    cin >> book_price;

    Book agent_book;
    agent_book.bookName = book_name;
    agent_book.writerName = writer_name;
    agent_book.bookPrice = book_price;
    agent_book.bookLended = false;
    book.push_back(agent_book);

    cout << "《" << book_name << "》" << "入库成功" ;
}

/*借书functions*/
void getBook(vector<Book>& book)
{
    string book_name;
    if(book.empty())
    {
        cout << "书库中暂无图书" << endl;
        return ;
    }
    cout << "*********** 图书列表 ***********" << endl;
    for(int i = 0 ; i < book.size() ; i++)
    {
        cout << (i+1) << "." << "书名：《" << book[i].bookName << "》" << "\t" << "借阅状态：" << (book[i].bookLended ?  "借出" : "未借出" ) << endl;
    }
    cout << "********************************" << endl;
    cout << "请选择要借阅的书：";
    flag:
    cin >> book_name;
    bool borrowed = false;
    for(auto& elem : book)
    {
        if((book_name == elem.bookName) && (!elem.bookLended))
        {
            cout << "《" << book_name << "》" << "借阅成功" << endl;
            elem.bookLended = true ;
            borrowed = true;
            break;
        }
    }
    if(!borrowed)
    {
        cout << "《" << book_name << "》" << "未入库或已被借出." << endl;
        cout << "请重新输入：" ;
        goto flag;
    }   
}

/*归还functions*/
void backBook(vector<Book>& book)
{
    string book_name;
    cout << "********* 借阅图书列表 *********" << endl;
    for(int i = 0 ; i < book.size() ; i++)
    {
        if(book[i].bookLended)
        {
            cout << (i+1) << "." << "书名：《" << book[i].bookName << "》" << "\t" << "借阅状态：" << (book[i].bookLended ?  "借出" : "未借出" ) << endl;
        }
    }
    cout << "********************************" << endl;
    cout << "请选择要归还的书：" ;
    flag:
    cin >> book_name;
    bool lended = false;
    for(auto& elem : book)
    {
        if((book_name == elem.bookName) && (elem.bookLended))
        {
            cout << "《" << book_name << "》" << "归还成功" << endl;
            elem.bookLended = false ;
            lended = true;
            break;
        }
    }
    if(!lended)
    {
        cout << "《" << book_name << "》" << "未入库或未被借出." << endl;
        cout << "请重新输入：" ;
        goto flag;
    }   
}

/*查询functions*/
void findBook(vector<Book>& book)
{
    if(book.empty())
    {
        cout << "书库中暂无图书" << endl;
        return ;
    }
    cout << "*********** 图书列表 ***********" << endl;
    for(int i = 0 ; i < book.size() ; i++)
    {
        cout << i+1 << "." << "书名：" << "《" << book[i].bookName << "》" << endl;
    }
    cout << "********************************" << endl;
    string book_name;
    cout << "请输入要查询的书：" ;
    cin >> book_name;
    for(auto& elem : book)
    {
        if(elem.bookName == book_name)
        {
            int choice = 0 , choose = 0;
            cout << "书本存在，请选择要查询的内容：" << endl;
            flag:
            cout << "1->作者   2->价格   3->借阅状态" << endl;
            cin >> choice;
            switch(choice)
            {
                case 1:
                    cout << "作者：" << elem.writerName << endl;
                    break;
                case 2:
                    cout << "价格：" << elem.bookPrice << endl;
                    break;
                case 3:
                    cout << "借阅状态：" << (elem.bookLended ? "借出" : "未借出")  << endl;
                    break;
            }
            cout << "是否继续查询书本相关信息(1/0)" << endl;
            cin >> choose ;
            if(choose == 0)
            {
                return ;
            }
            if(choose == 1)
            {
                cout << "请选择要查询的内容：" << endl;
                goto flag;
            }
        }
    }
    cout << "书本未入库，请选择其它书本" << endl;
}


int main()
{
    vector<Book> book;
    while(1)
    {
        int select;
        WebPage();
        cin >> select;
        int n = 0;
        cout << endl;
        switch(select)
        {
            /*退出**********************/
            case 0:
                system("clear");
                return 0;
                break;

            /*入库**********************/
            case 1:
                if(book.size() < n)
                book.resize(n);
                cinBook(book);
                n++;
                pause_clear();
                break;

            /*借阅**********************/
            case 2:
                getBook(book);
                pause_clear();
                break;        

            /*归还**********************/
            case 3:
                backBook(book);
                pause_clear();
                break;

            /*查询**********************/
            case 4:
                findBook(book);
                pause_clear();
                break;
                
            /**************************/
            default:
                system("clear");
                cout << "请仔细阅读目录，输入恰当内容(0/1/2/3/4)" << endl;
                break;
        }
    }
}