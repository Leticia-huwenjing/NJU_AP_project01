#include <iostream>
#include "admin.h"
#include "buyer.h"
#include "calculator.h"
#include "data.h"
#include "seller.h"
#include "sql.h"
#include "user.h"
using namespace std;

char opt;

void main_manu(){
  cout << "==========================================" << endl;
  cout << "1.管理员登录 2.用户注册 3.用户登录 4.退出程序" << endl;
  cout << "==========================================" << endl << endl;
  cout << "请输入操作：";
}

void admin_mod(){
  ;
}

void register_account(){
  ;
}

void user_module(){
  ;
}

int main()
{
  while (true)
  {
    main_manu();
    cin >> opt;
    switch (opt)
    {
      case '1':{
        char c;
        while(c=getchar() != '\n');
        admin_mod();
        break;
      }
      case '2':{
        char c;
        while(c=getchar() != '\n');
        register_account();
        break;
      }
      case '3':{
        char c;
        while(c=getchar() != '\n');
        user_module();
        break;
      }
      case '4':return 0;
      default: {
        char c;
        while(c=getchar() != '\n');
        cout << "Not A Valid Request!" << endl;
        break;
      }
    }
  }
}