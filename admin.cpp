//
// Created by 胡文菁 on 2022/2/19.
//

#include "admin.h"
void Manager::admin_manu() {
  cout << "===========================================================================" << endl;
  cout << "1.查看所有商品 2.搜索商品 3.下架商品 4.查看所有订单 5.查看所有用户 6.封禁用户 7.注销" << endl;
  cout << "===========================================================================" << endl;
  cout << endl;
  cout << "请输入操作：";
}

bool Manager::log_in() {
  bool res = false;
  cout << "请输入管理员姓名：";
  string test_name;
  cin >> test_name;
  cout << "请输入密码：";
  string test_password;
  cin >> test_password;
  if(name == test_name){
    if(password == test_password){
      res = true;
      cout << endl;
      cout << "-----登录成功-----" << endl;
      cout << endl;
    }
    else{
      cout << endl;
      cout << "-----密码错误，登录失败，返回主菜单-----" << endl;
      cout << endl;
    }
  }
  else{
    cout << endl;
    cout << "-----姓名错误，登录失败，返回主菜单-----" << endl;
    cout << endl;
  }
  return res;
}

void Manager::view_goods(string command) {
  ;
}

void Manager::view_orders(string command) {
  ;
}

void Manager::search_goods() {
  ;
}

void Manager::remove_good() {
  ;
}

void Manager::view_users(string command) {
  ;
}

void Manager::ban_user() {
  ;
}