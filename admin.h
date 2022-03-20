//
// Created by 胡文菁 on 2022/2/19.
//

#ifndef PROJECT01__ADMIN_H_
#define PROJECT01__ADMIN_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "file.h"
#include "sql.h"
#include "user.h"
using namespace std;

class Manager{
 public:
  void admin_manu(); //管理员菜单
  bool log_in(); //管理员登录
  void view_goods(); //管理员查看商品功能
  void view_orders(); //管理员查看全部订单功能
  void search_goods(); //管理员搜索商品功能
  void remove_good(); //管理员下架商品功能
  void view_users();  //管理员查看用户功能
  void ban_user(); //管理员封禁用户功能

 private:
  string name = "admin";
  string password = "123456";
};

#endif //PROJECT01__ADMIN_H_
