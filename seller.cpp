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
  string this_good_name;
  cout << "请输入商品名称：";
  cin >> this_good_name;
  string this_good_price;
  cout << "请输入商品价格：";
  cin >> this_good_price;
  string this_good_stock;
  cout << "请输入商品数量：";
  cin >> this_good_stock;
  string this_good_information;
  cout << "请输入商品描述：";
  cin >> this_good_information;
  cout << endl;

  //判断用户输入是否合法

  //Todo:判断价格是否为大于0的一位小数

  //Todo:判断数量是否为大于0的整数

}

void Seller::change_good(User &user) {
  ;
}