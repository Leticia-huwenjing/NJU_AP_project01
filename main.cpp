#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <iomanip>
#include "admin.h"
#include "buyer.h"
#include "data.h"
#include "seller.h"
#include "sql.h"
#include "user.h"
#include "file.h"
#include "utfwidth.h"
using namespace std;

vector<every_user> store_users;
vector<commodity> store_goods;
vector<order> store_orders;
vector<deposit> store_recharge;

void main_manu(){
  cout << "==========================================" << endl;
  cout << "1.管理员登录 2.用户注册 3.用户登录 4.退出程序" << endl;
  cout << "==========================================" << endl << endl;
  cout << "请输入操作：";
}

int admin_mod(){ //0正常退出，1登录失败
  Manager admin;
  bool log_res = admin.log_in();
  int opt=0;
  while(log_res){
    admin.admin_manu();
    cin >> opt;
    while(!cin || getchar()!='\n'){
      cout << "输入不合法！请重新输入：";
      cin.clear();
      while(getchar()!='\n');
      cin >> opt;
    }

    switch (opt) {
      case 1:{
        admin.view_goods();
        break;
      }
      case 2:{
        admin.search_goods();
        break;
      }
      case 3:{
        admin.remove_good();
        break;
      }
      case 4:{
        admin.view_orders();
        break;
      }
      case 5:{
        admin.view_users();
        break;
      }
      case 6:{
        admin.ban_user();
        break;
      }
      case 7:{
        return 0;
      }
      default: {
        cout << "请输入1-7之间的整数！" << endl;
        break;
      }
    }
  }
  return 1;
}

void register_module(){
  cout << "请输入用户名：";
  string test_name;
  getline(cin, test_name);
  if(test_name.find(' ') != string::npos){
    cout << "***************" << endl;
    cout << "您的输入不合法！" << endl;
    cout << "***************" << endl << endl;
    return ;
  }
  cout << "请输入密码：";
  string test_password;
  getline(cin, test_password);
  if(test_password.find(' ') != string::npos){
    cout << "***************" << endl;
    cout << "您的输入不合法！" << endl;
    cout << "***************" << endl << endl;
    return ;
  }
  User user(test_name, test_password);
  user.register_account(user);
}

int buyer_mod(Buyer &buyer, User &user){
  int opt=0;
  while(true){
    buyer.menu();
    cin >> opt;
    while(!cin || getchar()!='\n'){
      cout <<"输入不合法！请重新输入：";
      cin.clear();
      while(getchar()!='\n');
      cin >> opt;
    }

    switch (opt) {
      case 1:{
        buyer.view_goods(user);
        break;
      }
      case 2:{
        buyer.buy_good(user);
        break;
      }
      case 3:{
        buyer.search_good(user);
        break;
      }
      case 4:{
        buyer.view_orders(user);
        break;
      }
      case 5:{
        buyer.good_detail(user);
        break;
      }
      case 6:{
        return 0;
      }
      default: {
        cout << "请输入1-6之间的整数！" << endl;
        break;
      }
    }
  }
}

int seller_mod(Seller &seller, User &user){
  int opt=0;
  while(true){
    seller.menu();
    cin >> opt;
    while(!cin || getchar()!='\n'){
      cout <<"输入不合法！请重新输入：";
      cin.clear();
      while(getchar() != '\n');
      cin >> opt;
    }

    switch (opt) {
      case 1:{
        seller.sell_good(user);
        break;
      }
      case 2:{
        seller.view_goods(user);
        break;
      }
      case 3:{
        seller.change_good(user);
        break;
      }
      case 4:{
        seller.remove_good(user);
        break;
      }
      case 5:{
        seller.view_orders(user);
        break;
      }
      case 6:{
        return 0;
      }
      default: {
        cout << "请输入1-6之间的整数！" << endl;
        break;
      }
    }
  }
}

int person_mod(User &user){
  int opt=0;
  while(true){
    user.information_manu();
    cin >> opt;
    while(!cin || getchar()!='\n'){
      cout << "输入不合法!请重新输入：";
      cin.clear();
      while(getchar()!='\n');
      cin >> opt;
    }

    switch (opt) {
      case 1:{
        user.see_information(user);
        break;
      }
      case 2:{
        user.change(user);
        break;
      }
      case 3:{
        user.recharge(user);
        break;
      }
      case 4:{
        return 0;
      }
      default: {
        cout << "请输入1-4之间的整数！" << endl;
        break;
      }
    }
  }
}


int user_module(){ //0正常退出，1登录失败
  cout << "请输入用户名：";
  string test_name;
  cin >> test_name;
  cout << "请输入密码：";
  string test_password;
  cin >> test_password;
  User user(test_name, test_password);
  if(user.log_in(user)) {
    while (true) {
      user.user_manu();
      int opt = 0;
      cin >> opt;
      while (!cin || getchar() != '\n') {
        cout << "输入不合法!请重新输入：";
        cin.clear();
        while (getchar() != '\n');
        cin >> opt;
      }

      switch (opt) {
        case 1: {
          Buyer buyer;
          buyer_mod(buyer, user);
          break;
        }
        case 2: {
          Seller seller;
          seller_mod(seller, user);
          break;
        }
        case 3: {
          person_mod(user);
          break;
        }
        case 4: {
          return 0;
        }
        default: {
          cout << "请输入1-4之间的整数！" << endl;
          break;
        }
      }
    }
  }
  return 1;
}

int main()
{
  init();
  read();
  int opt=0;
  while (true)
  {
    main_manu();
    cin >> opt;
    while(!cin || getchar()!='\n'){
      cout << "输入不合法!请重新输入：";
      cin.clear();
      while(getchar()!='\n');
      cin >> opt;
    }

    switch (opt)
    {
      case 1:{
        admin_mod();
        break;
      }
      case 2:{
        register_module();
        break;
      }
      case 3:{
        user_module();
        break;
      }
      case 4:return 0;
      default: {
        cout << "请输入1-4之间的整数！" << endl;
        break;
      }
    }
  }
}