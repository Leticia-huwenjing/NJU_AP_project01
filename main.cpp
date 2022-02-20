#include <iostream>
#include "admin.h"
#include "buyer.h"
#include "calculator.h"
#include "data.h"
#include "seller.h"
#include "sql.h"
#include "user.h"
using namespace std;

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
        string command1("SELECT * FROM commodity");
        admin.view_goods(command1);
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
        string command4("SELECT * FROM order");
        admin.view_orders(command4);
        break;
      }
      case 5:{
        string command5("SELECT * FROM user");
        admin.view_users(command5);
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

void register_account(){
  User user;
  user.register_account();
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
        string command1("SELECT * FROM commodity");
        buyer.view_goods(command1);
        break;
      }
      case 2:{
        buyer.buy_good(user);
        break;
      }
      case 3:{
        buyer.search_good();
        break;
      }
      case 4:{
        string command4("SELECT * FROM order");
        buyer.view_orders(command4);
        break;
      }
      case 5:{
        buyer.good_detail();
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
        string command2("SELECT * FROM commodity");
        seller.view_goods(command2);
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
        string command5("SELECT * FROM order");
        seller.view_orders(command5);
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
  User user;
  cin >> user; //Todo:更改用户初始化
  while(user.log_in()){
    user.user_manu();
    int opt=0;
    cin >> opt;
    while(!cin || getchar()!='\n'){
      cout << "输入不合法!请重新输入：";
      cin.clear();
      while(getchar()!='\n');
      cin >> opt;
    }

    switch (opt) {
      case 1:{
        Buyer buyer;
        buyer_mod(buyer, user);
        break;
      }
      case 2:{
        Seller seller;
        seller_mod(seller, user);
        break;
      }
      case 3:{
        person_mod(user);
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
  return 1;
}

int main()
{
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
        register_account();
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