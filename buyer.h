//
// Created by 胡文菁 on 2022/2/19.
//

#ifndef PROJECT01__BUYER_H_
#define PROJECT01__BUYER_H_

#include "user.h"
class Buyer : public User{
 public:
  void menu(); //买家界面初始化
  void view_goods(); //买家查看商品列表
  void search_good(); //买家搜索在售商品
  void view_orders(User &user); //买家查看自己购买物品的历史订单
  void buy_good(User &user); //买家购买商品
  void good_detail(); //查看商品详细信息
};
#endif //PROJECT01__BUYER_H_
