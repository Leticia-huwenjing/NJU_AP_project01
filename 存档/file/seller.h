//
// Created by 胡文菁 on 2022/2/19.
//

#ifndef PROJECT01__SELLER_H_
#define PROJECT01__SELLER_H_

#include "user.h"
#include "sql.h"
class Seller{
 public:
  void menu(); //卖家界面初始化
  void view_goods(User &user); //卖家查看自己发布的商品
  void remove_good(User &user); //卖家下架自己发布的商品
  void view_orders(User &user); //卖家查看自己的历史订单
  void sell_good(User &user); //卖家发布商品
  void change_good(User &user); //卖家修改商品信息
};

#endif //PROJECT01__SELLER_H_
