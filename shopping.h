//
// Created by 胡文菁 on 2022/3/20.
//

#ifndef MAIN_CPP__SHOPPING_H_
#define MAIN_CPP__SHOPPING_H_

#include <iostream>
#include "user.h"
#include "buyer.h"
using namespace std;

class Cart{
 public:
  void cart_menu();
  void add_cart(User &user);
  void rm_cart(User &user);
  void buy_all(User &user, Buyer &buyer);
  void see_cart(User &user);

 private:
  string user_id;
};


#endif //MAIN_CPP__SHOPPING_H_
