//
// Created by 胡文菁 on 2022/2/19.
//

#ifndef PROJECT01__DATA_H_
#define PROJECT01__DATA_H_

#include <iostream>
using namespace std;

struct commodity{
  string condition;
  string good_id;
  string good_name;
  string good_price="0";
  string stock="0";
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
  string money;
  string condition;
};

struct order{
  string order_id;
  string good_id;
  string per_price="0";
  string amount="0";
  string time;
  string seller_id;
  string buyer_id;
};

struct deposit{
  string user_id;
  string money;
};

#endif //PROJECT01__DATA_H_
