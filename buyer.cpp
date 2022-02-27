//
// Created by 胡文菁 on 2022/2/19.
//

#include "buyer.h"
void Buyer::menu() {
  cout << "=============================================================================" << endl;
  cout << "1.查看商品列表 2.购买商品 3.搜索商品 4.查看历史订单 5.查看商品详细信息 6.返回用户主界面" << endl;
  cout << "=============================================================================" << endl;
  cout << endl;
  cout << "请输入操作：";
}

void Buyer::view_goods(User &user) {
  string manipulator = "buyer";
  string instruction = "SELECT * FROM commodity";
  mysql(instruction, manipulator, user);
}

void Buyer::search_good(User &user) {
  string manipulator = "buyer";
  string instruction = "SELECT * FROM commodity WHERE 名称 CONTAINS ";
  cout << "请输入商品名称：";
  string this_name;
  cin >> this_name;
  instruction.append(this_name);
  mysql(instruction, manipulator, user);
}

void Buyer::view_orders(User &user) {
  string manipulator = "buyer";
  string instruction = "SELECT * FROM order";
  mysql(instruction, manipulator, user);
}

void Buyer::buy_good(User &user) {
  ;
}

void Buyer::good_detail(User &user) {
  string manipulator = "buyer";
  string instruction = "SELECT * FROM commodity WHERE 商品ID CONTAINS ";
  cout << "请输入您想要查看的商品ID：";
  string this_good_id;
  cin >> this_good_id;
  instruction.append(this_good_id);
  mysql(instruction, manipulator, user);
}