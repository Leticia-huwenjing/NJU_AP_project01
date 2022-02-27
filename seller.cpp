//
// Created by 胡文菁 on 2022/2/19.
//

#include "seller.h"
void Seller::menu() {
  cout << "========================================================================" << endl;
  cout << "1.发布商品 2.查看发布商品 3.修改商品信息 4.下架商品 5.查看历史订单 6.返回用户主界面" << endl;
  cout << "========================================================================" << endl;
  cout << endl;
  cout << "请输入操作：";
}

void Seller::view_goods(User &user) {
  string manipulator = "seller";
  string instruction = "SELECT * FROM commodity";
  mysql(instruction, manipulator, user);
}

void Seller::remove_good(User &user) {
  ;
}

void Seller::view_orders(User &user) {
  string manipulator = "seller";
  string instruction = "SELECT * FROM order";
  mysql(instruction, manipulator, user);
}

void Seller::sell_good(User &user) {
  ;
}

void Seller::change_good(User &user) {
  ;
}