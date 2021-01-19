#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <iterator>
#include <cstddef>
#include <conio.h>   //即时输入
#include <cstdlib>   //清屏
#include <stdexcept> //异常处理
#include <fstream>   //文件io
#include <sstream>   //string io
#include <ctime>
#define CLEAN system("cls")
#define PAUSE system("pause")
using namespace std;

class book
{
    friend void book_to_text(vector<book> &books);
    friend void search_book(vector<book> &books);
    friend class user;
    friend class root;
    friend void find_all_book(vector<book> &books);
    friend void add_book(vector<book> &books);

private:
    string name;
    string isbn;
    string in_date;
    int book_number;

public:
    book() = default;
    book(const string &name, const string &isbn, const string &in_date, int &book_number) : name(name), isbn(isbn),
                                                                                            in_date(in_date), book_number(book_number){};
    bool compare(string &info);
};
class user
{
    friend user &check_account_user(vector<user> &users);
    friend void user_to_text(vector<user> &users);
    friend void find_all_user(vector<user> &users);
    friend void search_user(vector<user> &users);

private:
    string name;
    string phone;
    string password;
    int borrow_number;
    vector<string> borrow_book;
    vector<string> borrow_date;

public:
    user() = default;
    user(string &name, string &phone, string &password) : name(name), phone(phone), password(password), borrow_number(0), borrow_book({""}),
                                                          borrow_date({""}){};
    user(string &name, string &phone, string &password, int borrow_number, vector<string> &borrow_book, vector<string> &borrow_date) : name(name), phone(phone), password(password),
                                                                                                                                       borrow_number(borrow_number), borrow_book(borrow_book),
                                                                                                                                       borrow_date(borrow_date){};
    void loading_selection(char choose, vector<book> &books);
    void borrow_book_user(vector<book> &books);
    void return_book_user(vector<book> &books);
    bool compare(string &info);
    void find_user_info();
    void change_user_password();
};
class root
{
    friend root &check_account_root(vector<root> &roots);
    friend void root_to_text(vector<root> &roots);
    friend void find_all_root(vector<root> &roots);

private:
    string account;
    string password;

public:
    root() = default;
    root(string &account, string &password) : account(account), password(password){};
    void loading_selection(char choose, vector<book> &books, vector<user> &users, vector<root> &root);
    void change_root_password();
};

bool have_account();               //检验是否有账户*
bool is_user();                    //检验是否是用户*
char print_menu(bool identity);    //根据参数确定打印哪种菜单*
bool check_account(bool identity); //核对账号与密码*
user &creat_account_user();        //创建用户账户*
root &creat_account_root();        //创建管理员账户*
vector<user> &text_to_user();      //将文件数据导入内存中*
vector<root> &text_to_root();
vector<book> &text_to_book();
user &check_account_user(vector<user> &users); //检查用户密码*
root &check_account_root(vector<root> &roots); //检查管理员密码*
void user_to_text(vector<user> &users);        //将内存数据存入文件中*
void root_to_text(vector<root> &roots);
void book_to_text(vector<book> &books);
void search_book(vector<book> &books);
string get_time();
void find_all_book(vector<book> &books);
void find_all_user(vector<user> &users);
void find_all_root(vector<root> &roots);
void search_user(vector<user> &users);
void add_book(vector<book> &books);

int main(void)
{
    vector<user> &users = text_to_user();
    vector<root> &roots = text_to_root();
    vector<book> &books = text_to_book();
    bool haveaccount = have_account();
    bool isuser = is_user();
    if (!haveaccount)
    {
        if (isuser)
        {
            users.push_back(creat_account_user());
            user_to_text(users);
        }
        else
        {
            roots.push_back(creat_account_root());
            root_to_text(roots);
        }
    }
    if (isuser)
    {
        user &user_now = check_account_user(users);
        while (1)
        {
            char choose = print_menu(isuser);
            user_now.loading_selection(choose, books);
            user_to_text(users);
            book_to_text(books);
            PAUSE;
        }
    }
    else
    {
        root &root_now = check_account_root(roots);
        while (1)
        {
            char choose = print_menu(isuser);
            root_now.loading_selection(choose, books, users, roots);
            root_to_text(roots);
            book_to_text(books);
            PAUSE;
        }
    }
}
bool have_account()
{
    while (1)
    {
        cout << "登录&注册:\n1.登录   2.注册";
        char have = getch();
        if (have == '1')
        {
            return true;
        }
        else if (have == '2')
        {
            return false;
        }
        else
        {
            CLEAN;
            cout << "输入无效，请重新输入!\a" << endl;
        }
    }
}
bool is_user()
{
    CLEAN;
    while (1)
    {

        cout << "你的身份是?:\n1.用户   2.管理员";
        char have = getch();
        if (have == '1')
        {
            return true;
        }
        else if (have == '2')
        {
            return false;
        }
        else
        {
            CLEAN;
            cout << "输入无效，请重新输入!\a" << endl;
        }
    }
}
user &creat_account_user()
{
    CLEAN;
    string name, phone, password, password2;
    cout << "创建账户\n请输入账户名:";
    cin >> name;
    cout << "请输入手机号码:";
    cin >> phone;
    cout << "请输入密码:";
    cin >> password;
    cout << "请确认密码:";
    while (1)
    {
        cin >> password2;
        if (password != password2)
        {
            cout << "两次输入不一致!请重新输入:";
        }
        else
        {
            static user root_new(name, phone, password);
            cout << "创建成功!\n";
            PAUSE;
            return root_new;
        }
    }
}
root &creat_account_root()
{
    CLEAN;
    string account, password, password2;
    cout << "创建账户\n请输入账户号码:";
    cin >> account;
    cout << "请输入密码:";
    cin >> password;
    cout << "请确认密码:";
    while (1)
    {
        cin >> password2;
        if (password != password2)
        {
            cout << "两次输入不一致!请重新输入:";
        }
        else
        {
            static root root_new(account, password);
            cout << "创建成功!\n";
            PAUSE;
            return root_new;
        }
    }
}
vector<user> &text_to_user()
{
    static vector<user> users;
    fstream f_user_exist;
    f_user_exist.open("D:\\data\\user.txt");
    if (!f_user_exist)
    {
        fstream f_user("D:\\data\\user.txt", ios::app);
        f_user.close();
    }
    else
    {
        f_user_exist.close();
        fstream f_user("D:\\data\\user.txt", ios::in);
        string data_all;
        while (getline(f_user, data_all))
        {
            stringstream data_single;
            data_single << data_all;
            string name, phone, password;
            int borrow_number;
            vector<string> borrow_book;
            vector<string> borrow_date;
            string borrow_book_s;
            string borrow_date_s;
            data_single >> name >> phone >> password >> borrow_number;
            auto book_begin = borrow_book.begin();
            auto date_begin = borrow_date.begin();
            for (int count = 0; count < borrow_number; count++, book_begin++)
            {
                data_single >> borrow_book_s;
                borrow_book.push_back(borrow_book_s);
            }
            for (int count = 0; count < borrow_number; count++, date_begin++)
            {
                data_single >> borrow_date_s;
                borrow_date.push_back(borrow_date_s);
            }
            user user_new(name, phone, password, borrow_number, borrow_book, borrow_date);
            users.push_back(user_new);
        }
        f_user.close();
    }
    return users;
}
vector<root> &text_to_root()
{
    static vector<root> roots;
    fstream f_root_exist;
    f_root_exist.open("D:\\data\\root.txt");
    if (!f_root_exist)
    {
        fstream f_root("D:\\data\\root.txt", ios::app);
        f_root.close();
    }
    else
    {
        f_root_exist.close();
        fstream f_root("D:\\data\\root.txt", ios::in);
        string data_all;
        while (getline(f_root, data_all))
        {
            stringstream data_single;
            data_single << data_all;
            string account, password;
            while (data_single >> account >> password)
            {
                root root_new(account, password);
                roots.push_back(root_new);
            }
        }
        f_root.close();
    }
    return roots;
}
vector<book> &text_to_book()
{
    static vector<book> books;
    fstream f_book_exist;
    f_book_exist.open("D:\\data\\book.txt");
    if (!f_book_exist)
    {
        fstream f_book("D:\\data\\book.txt", ios::app);
        f_book.close();
    }
    else
    {
        f_book_exist.close();
        fstream f_book("D:\\data\\book.txt", ios::in);
        string data_all;
        while (getline(f_book, data_all))
        {
            stringstream data_single;
            data_single << data_all;
            string name, isbn, in_date;
            int book_number;
            while (data_single >> name >> isbn >> in_date >> book_number)
            {
                book book_new(name, isbn, in_date, book_number);
                books.push_back(book_new);
            }
        }
        f_book.close();
    }
    return books;
}
user &check_account_user(vector<user> &users)
{
    CLEAN;
    cout << "用户登录\n请输入用户名或手机号:";
    while (1)
    {
        string name, phone, password, name_phone;
        cin >> name_phone;
        cout << "请输入密码:";
        cin >> password;
        for (auto &check : users)
        {
            if (check.name == name_phone || check.phone == name_phone)
            {
                if (check.password == password)
                {
                    cout << "登陆成功" << endl;
                    PAUSE;
                    return check;
                }
            }
        }
        CLEAN;
        cout << "用户登录\n账号或密码错误!请重新输入\n请输入用户名或手机号:";
    }
}
root &check_account_root(vector<root> &roots)
{
    CLEAN;
    cout << "管理员登录\n请输入账号:";
    while (1)
    {
        string account, password;
        cin >> account;
        cout << "请输入密码:";
        cin >> password;
        for (auto &check : roots)
        {
            if (check.account == account && check.password == password)
            {
                cout << "登陆成功" << endl;
                PAUSE;
                return check;
            }
        }
        CLEAN;
        cout << "管理员登录\n账号或密码错误!请重新输入\n请输入账号:";
    }
}
void user_to_text(vector<user> &users)
{
    fstream f_user("D:\\data\\user.txt", ios::out);
    for (auto &user : users)
    {
        stringstream borrow_num;
        borrow_num << user.borrow_number;
        string borrow_number;
        borrow_num >> borrow_number;
        string add_user = "";
        add_user = add_user + user.name + " " + user.phone + " " + user.password + " " + borrow_number;
        for (auto &add_book : user.borrow_book)
        {
            add_user = add_user + " " + add_book;
        }
        for (auto &add_date : user.borrow_date)
        {
            add_user = add_user + " " + add_date;
        }
        add_user = add_user + "\n";
        f_user << add_user;
    }
    f_user.close();
}
void root_to_text(vector<root> &roots)
{
    fstream f_root("D:\\data\\root.txt", ios::out);
    for (auto &root : roots)
    {
        string add_root = "";
        add_root = add_root + root.account + " " + root.password;
        add_root = add_root + "\n";
        f_root << add_root;
    }
    f_root.close();
}
void book_to_text(vector<book> &books)
{
    fstream f_book("D:\\data\\book.txt", ios::out);
    for (auto &book : books)
    {
        stringstream book_num;
        book_num << book.book_number;
        string book_number;
        book_num >> book_number;
        string add_book = "";
        add_book = add_book + book.name + " " + book.isbn + " " + book.in_date + " " + book_number + "\n";
        f_book << add_book;
    }
    f_book.close();
}
char print_menu(bool identity)
{
    while (identity)
    {
        CLEAN;
        cout << "用户主界面\n1.搜索图书\n2.借阅图书\n3.归还图书\n4.浏览全部图书\n5.查询个人信息\n6.更改密码\n请输入选项:" << endl;
        char choose = getch();
        if (choose > '0' && choose < '7')
        {
            return choose;
        }
        else
        {
            CLEAN;
            cout << "输入无效!请重新输入" << endl;
            PAUSE;
        }
    }
    while (!identity)
    {
        CLEAN;
        cout << "管理员主界面\n1.浏览图书库信息\n2.浏览用户信息\n3.浏览管理员信息\n4.查询图书信息\n5.查询用户信息\n6.添加书籍\n7.更改密码\n请输入选项:" << endl;
        char choose = getch();
        if (choose > '0' && choose < '8')
        {
            return choose;
        }
        else
        {
            CLEAN;
            cout << "输入无效!请重新输入" << endl;
            PAUSE;
        }
    }
    return 'x';
}
void search_book(vector<book> &books)
{
    CLEAN;
    string find_book_info;
    cout << "请输入你要查询书籍的名称或ISBN:";
    cin >> find_book_info;
    for (auto &book : books)
    {
        if (book.compare(find_book_info))
        {
            cout << "为你找到:\n《" << book.name << "》 \nISBN:" << book.isbn << " \n入库日期:" << book.in_date << " \n图书存量:" << book.book_number << endl;
            return;
        }
        else
        {
            cout << "未查询到相关书籍" << endl;
            return;
        }
    }
    cout << "未查询到相关书籍" << endl;
}
bool book::compare(string &info)
{
    if (info == this->name || info == this->isbn)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void user::borrow_book_user(vector<book> &books)
{
    CLEAN;
    string borrow_book_info;
    cout << "请输入你要借阅的书籍的名称或ISBN:";
    cin >> borrow_book_info;
    for (auto &book : books)
    {
        if (book.compare(borrow_book_info))
        {
            cout << "为你找到:\n《" << book.name << "》 \nISBN:" << book.isbn << " \n入库日期:" << book.in_date << " \n图书存量:" << book.book_number << endl;
            if (book.book_number <= 0)
            {
                cout << "图书已无存量,不可借阅\a" << endl;
                return;
            }
            cout << "是否要借阅?(y/n)"<<endl;
            while (1)
            {
                char choose = getch();
                if (choose == 'y')
                {
                    book.book_number--;
                    this->borrow_number++;
                    (this->borrow_book).push_back(book.name);
                    (this->borrow_date).push_back(get_time());
                    cout << "\n借阅成功!请及时归还哦" << endl;
                    return;
                }
                else if (choose == 'n')
                {
                    cout << "您已取消借阅\a" << endl;
                    return;
                }
                else
                {
                    cout << "输入无效,请重新输入:\a" << endl;
                    continue;
                }
            }
            break;
        }
    }
    cout << "未查询到相关书籍\a" << endl;
    return;
}
void user::loading_selection(char choose, vector<book> &books)
{
    switch (choose)
    {
    case '1':
        search_book(books);
        break;
    case '2':
        this->borrow_book_user(books);
        break;
    case '3':
        this->return_book_user(books);
        break;
    case '4':
        find_all_book(books);
        break;
    case '5':
        this->find_user_info();
        break;
    case '6':
        this->change_user_password();
        break;
    }
}
void root::loading_selection(char choose, vector<book> &books, vector<user> &users, vector<root> &roots)
{
    switch (choose)
    {
    case '1':
        find_all_book(books);
        break;
    case '2':;
        find_all_user(users);
        break;
    case '3':;
        find_all_root(roots);
        break;
    case '4':
        search_book(books);
        break;
    case '5':
        search_user(users);
        break;
    case '6':
        add_book(books);
        break;
    case '7':
        this->change_root_password();
        break;
    }
}
string get_time()
{
    time_t now = time(0);
    char *dt = ctime(&now);
    string timer(dt);
    for (auto &ch : timer)
    {
        if (ch == ' ')
        {
            ch = '-';
        }
        if (ch == '\n')
        {
            ch = '.';
        }
    }
    return timer;
}
void user::return_book_user(vector<book> &books)
{
    CLEAN;
    string return_book_info;
    cout << "请输入你要归还的书籍的名称:";
    cin >> return_book_info;
    for (auto &user_book : this->borrow_book)
    {
        if (user_book == return_book_info)
        {
            cout << "是否要归还?(y/n)" << endl;
            while (1)
            {
                char choose = getch();
                if (choose == 'y')
                {
                    for (auto beg = (this->borrow_book).begin(), end = (this->borrow_book).end(); beg != end; beg++)
                    {
                        if (*beg == return_book_info)
                        {
                            (this->borrow_book).erase(beg);
                        }
                    }
                    for (auto &book_book : books)
                    {
                        if (book_book.compare(return_book_info))
                        {
                            book_book.book_number++;
                        }
                    }
                    cout << "归还成功!" << endl;
                    return;
                }
                else if (choose == 'n')
                {
                    cout << "您已取消归还\a" << endl;
                    return;
                }
                else
                {
                    cout << "输入无效,请重新输入:\a" << endl;
                }
            }
        }
    }
    cout << "未查找到相关书籍\a" << endl;
    return;
}
bool user::compare(string &info)
{
    for (auto &borrow_name : this->borrow_book)
    {
        if (borrow_name == info)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}
void find_all_book(vector<book> &books)
{
    CLEAN;
    cout << "图书仓库(名称/ISBN/入库日期/存量)" << endl;
    for (auto &book : books)
    {
        cout << "《" << book.name << "》  " << book.isbn << "  " << book.in_date << "  " << book.book_number << endl;
    }
}
void user::find_user_info()
{
    CLEAN;
    int count = 0;
    cout << "用户信息(账号/手机号)" << endl;
    cout << this->name << "  " << this->phone << endl;
    cout << "正在借阅的图书" << endl;
    for (auto borrow_books : this->borrow_book)
    {
        cout << borrow_books << "    " << (this->borrow_date)[count] << endl;
        count++;
    }
}
void user::change_user_password()
{
    CLEAN;
    cout << "修改密码" << endl;
    cout << "请输入旧密码:";
    string old_password;
    cin >> old_password;
    while (1)
    {
        if (old_password == this->password)
        {
            cout << "请输入新密码:";
            string new_password;
            cin >> new_password;
            cout << "请再次输入新密码:";
            while (1)
            {
                string new_password_2;
                cin >> new_password_2;
                if (new_password == new_password_2)
                {
                    this->password = new_password;
                    cout << "修改成功！" << endl;
                    break;
                }
                else
                {
                    cout << "两次密码输入不一致!请重新输入:\a";
                }
            }
        }
        else
        {
            cout << "密码输入有误!\a" << endl;
        }
        break;
    }
}
void find_all_user(vector<user> &users)
{
    CLEAN;
    cout << "用户信息" << endl;
    cout << "账号/手机号/密码/借阅本数" << endl;
    for (auto &user : users)
    {
        cout << user.name << "  " << user.phone << "  " << user.password << "  " << user.borrow_number << endl;
    }
}
void find_all_root(vector<root> &roots)
{
    CLEAN;
    cout << "管理员信息" << endl;
    cout << "账号/密码" << endl;
    for (auto &root : roots)
    {
        cout << root.account << "  " << root.password << endl;
    }
}
void search_user(vector<user> &users)
{
    CLEAN;
    string find_user_info;
    cout << "请输入你要查询用户的账号或手机号:";
    cin >> find_user_info;
    for (auto &user : users)
    {
        if (find_user_info == user.name || find_user_info == user.phone)
        {
            cout << "为你找到:" << user.name << " \n手机号:" << user.phone << " \n借阅数量:" << user.borrow_number << endl;
            int count = 0;
            for (auto &borrow_books : user.borrow_book)
            {
                cout << borrow_books;
                cout << "    " << user.borrow_date[count] << endl;
                count++;
            }
            return;
        }
        else
        {
            cout << "未查询到相关用户信息\a" << endl;
            return;
        }
    }
    cout << "未查询到任何用户信息\a" << endl;
}
void add_book(vector<book> &books)
{
    CLEAN;
    cout << "添加书籍" << endl;
    cout << "输入书籍名称:";
    string add_book_name;
    cin >> add_book_name;
    cout << "输入书籍ISBN号:";
    string add_book_isbn;
    cin >> add_book_isbn;
    cout << "输入添加本数:";
    int add_book_num;
    cin >> add_book_num;
    for (auto add_book_names : books)
    {
        if (add_book_names.compare(add_book_name))
        {
            add_book_names.book_number += add_book_num;
            cout << "添加成功" << endl;
            return;
        }
    }
    book book_new(add_book_name, add_book_isbn, get_time(), add_book_num);
    books.push_back(book_new);
    cout << "新增成功" << endl;
}
void root::change_root_password()
{
    CLEAN;
    cout << "修改密码" << endl;
    cout << "请输入旧密码:";
    string old_password;
    cin >> old_password;
    while (1)
    {
        if (old_password == this->password)
        {
            cout << "请输入新密码:";
            string new_password;
            cin >> new_password;
            cout << "请再次输入新密码:";
            while (1)
            {
                string new_password_2;
                cin >> new_password_2;
                if (new_password == new_password_2)
                {
                    this->password = new_password;
                    cout << "修改成功！" << endl;
                    return;
                }
                else
                {
                    cout << "两次密码输入不一致!请重新输入:\a";
                }
            }
        }
        else
        {
            cout << "密码输入有误!\a" << endl;
        }
        return;
    }
}
