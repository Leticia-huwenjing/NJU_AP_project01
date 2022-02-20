//
// Created by 胡文菁 on 2022/2/19.
//

#ifndef PROJECT01__SELLER_H_
#define PROJECT01__SELLER_H_

#include "user.h"
class Seller : public User{
 public:
  void menu(); //卖家界面初始化
  void view_goods(string command); //卖家查看自己发布的商品,该函数解析command
  void remove_good(User &user); //卖家下架自己发布的商品,该函数生成command并传给解析函数
  void view_orders(string command); //卖家查看自己的历史订单,该函数解析command
  void sell_good(User &user); //卖家发布商品,该函数生成command并传给解析函数
  void change_good(User &user); //卖家修改商品信息，该函数生成command并传给解析函数

};

#endif //PROJECT01__SELLER_H_
