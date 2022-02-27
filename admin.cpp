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

void Manager::view_goods() {
  string manipulator = "admin";
  string instruction = "SELECT * FROM commodity";
  string fake_name = "";
  string fake_password = "";
  User user(fake_name,fake_password);
  mysql(instruction, manipulator, user);
}

void Manager::view_orders() {
  string manipulator = "admin";
  string instruction = "SELECT * FROM order";
  string fake_name = "";
  string fake_password = "";
  User user(fake_name,fake_password);
  mysql(instruction, manipulator, user);
}

void Manager::search_goods() {
  string fake_name = "";
  string fake_password = "";
  User user(fake_name,fake_password);
  string manipulator = "admin";
  string instruction = "SELECT * FROM commodity WHERE 名称 CONTAINS ";
  cout << "请输入商品名称：";
  string this_name;
  cin >> this_name;
  instruction.append(this_name);
  mysql(instruction, manipulator, user);
}

void Manager::remove_good() {
  string fake_name = "";
  string fake_password = "";
  User user(fake_name,fake_password);
  //Todo:管理员下架
}

void Manager::view_users() {
  string manipulator = "admin";
  string instruction = "SELECT * FROM user";
  string fake_name = "";
  string fake_password = "";
  User user(fake_name,fake_password);
  mysql(instruction, manipulator, user);
}

void Manager::ban_user() {
  string fake_name = "";
  string fake_password = "";
  User user(fake_name,fake_password);
  //Todo:管理员封禁
}