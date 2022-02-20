//
// Created by 胡文菁 on 2022/2/19.
//

#ifndef PROJECT01__DATA_H_
#define PROJECT01__DATA_H_

#include <iostream>
using namespace std;

string user_title = "用户ID,用户名,密码,联系方式,地址,钱包余额";
string good_title = "商品ID,名称,价格,数量,描述,卖家ID,上架时间,商品状态";
string order_title = "订单ID,商品ID,交易单价,数量,交易时间,卖家ID,买家ID";
string command_file = "commands.txt";
string good_file = "commodity.txt";
string order_file = "order.txt";
string user_file = "user.txt";
string path = "/Users/huwenjing/project01/";


struct commodity{ //Todo:结构
  string condition;
  string good_id;
  string good_name;
  double good_price=0;
  int stock=0;
  string information;
  string time;
  string seller_id;
};

struct every_user{
  string user_id;
  string user_name;
  string password;
  string tel;
  string address;
  double money;
};

struct order{

};

#endif //PROJECT01__DATA_H_
