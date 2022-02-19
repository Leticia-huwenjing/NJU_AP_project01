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

int admin_mod(){
  Manager admin;
  bool log_res = admin.log_in();
  char opt;
  while(log_res){
    admin.admin_manu();
    cin >> opt;
    switch (opt) {
      case '1':{
        admin.view_goods();
        break;
      }
      case '2':{
        admin.search_goods();
        break;
      }
      case '3':{
        admin.remove_good();
        break;
      }
      case '4':{
        admin.view_orders();
        break;
      }
      case '5':{
        admin.view_users();
        break;
      }
      case '6':{
        admin.ban_user();
        break;
      }
      case '7':{
        return 0;
      }
      default: {
        cout << "Not A Valid Request!" << endl;
        break;
      }
    }
  }
  return 0;
}

void register_account(){
  User user;
  user.register_account();
}

int buyer_mod(Buyer &buyer, User &user){
  char opt;
  while(true){
    buyer.menu();
    cin >> opt;
    switch (opt) {
      case '1':{
        buyer.view_goods();
        break;
      }
      case '2':{
        buyer.buy_good(user);
        break;
      }
      case '3':{
        buyer.search_good();
        break;
      }
      case '4':{
        buyer.view_orders(user);
        break;
      }
      case '5':{
        buyer.good_detail();
        break;
      }
      case '6':{
        return 0;
      }
      default: {
        char c;
        while(c=getchar() != '\n');
        cout << "Not A Valid Request!" << endl;
        break;
      }
    }
  }
}

int seller_mod(Seller &seller, User &user){
  char opt;
  while(true){
    seller.menu();
    cin >> opt;
    switch (opt) {
      case '1':{
        seller.sell_good(user);
        break;
      }
      case '2':{
        seller.view_goods(user);
        break;
      }
      case '3':{
        seller.change_good(user);
        break;
      }
      case '4':{
        seller.remove_good(user);
        break;
      }
      case '5':{
        seller.view_orders(user);
        break;
      }
      case '6':{
        return 0;
      }
      default: {
        char c;
        while(c=getchar() != '\n');
        cout << "Not A Valid Request!" << endl;
        break;
      }
    }
  }
}

int person_mod(User &user){
  char opt;
  while(true){
    user.information_manu();
    cin >> opt;
    switch (opt) {
      case '1':{
        user.see_information(user);
        break;
      }
      case '2':{
        user.change(user);
        break;
      }
      case '3':{
        user.recharge(user);
        break;
      }
      case '4':{
        return 0;
      }
      default: {
        char c;
        while(c=getchar() != '\n');
        cout << "Not A Valid Request!" << endl;
        break;
      }
    }
  }
}


int user_module(){
  User user;
  cin >> user; //Todo:更改用户初始化
  while(user.log_in()){
    user.user_manu();
    char opt;
    cin >> opt;
    switch (opt) {
      case '1':{
        Buyer buyer;
        buyer_mod(buyer, user);
        break;
      }
      case '2':{
        Seller seller;
        seller_mod(seller, user);
        break;
      }
      case '3':{
        person_mod(user);
        break;
      }
      case '4':{
        return 0;
      }
      default: {
        char c;
        while(c=getchar() != '\n');
        cout << "Not A Valid Request!" << endl;
        break;
      }
    }
  }
  return 0;
}

int main()
{
  char opt;
  while (true)
  {
    main_manu();
    cin >> opt;
    switch (opt)
    {
      case '1':{
        admin_mod();
        break;
      }
      case '2':{
        register_account();
        break;
      }
      case '3':{
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