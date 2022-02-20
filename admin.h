//
// Created by 胡文菁 on 2022/2/19.
//

#ifndef PROJECT01__ADMIN_H_
#define PROJECT01__ADMIN_H_

#include <iostream>
#include <iomanip>
using namespace std;

class Manager{
 public:
  void admin_manu(); //管理员菜单
  bool log_in(); //管理员登录
  void view_goods(string command); //管理员查看商品功能,该函数解析command
  void view_orders(string command); //管理员查看全部订单功能,该函数解析command
  void search_goods(); //管理员搜索商品功能，该函数生成command并传给解析函数
  void remove_good(); //管理员下架商品功能，该函数生成command并传给解析函数
  void view_users(string command);  //管理员查看用户功能，该函数解析command
  void ban_user(); //管理员封禁用户功能，该函数生成command并传给解析函数

 private:
  string name = "admin";
  string password = "123456";
};

#endif //PROJECT01__ADMIN_H_
