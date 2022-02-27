//
// Created by 胡文菁 on 2022/2/19.
//

#ifndef PROJECT01__SQL_H_
#define PROJECT01__SQL_H_

#include <iostream>
#include "file.h"
#include "utfwidth.h"
#include "user.h"
using namespace std;

void mysql(string instruction, string& manipulator, User& user);
void insert(string instruction, string& manipulator, User& user);
void update(string instruction, string& manipulator, User& user);
void select(string instruction, string& manipulator, User& user);

//admin
void select_admin(string instruction);
void search_admin(string instruction); //select含有WHERE时
void update_good_admin(string instruction); //下架商品
void update_user_admin(string instruction); //封禁用户（需要调用下架商品）

//buyer
void select_buyer(string instruction, User& user);
void search_buyer(string instruction); //select含有WHERE时，查找商品or查看商品详细信息
void insert_buyer(string instruction, User& user); //增加订单
void update_buyer(string instruction, User& user);//购买商品

//seller
void select_seller(string instruction, User& user); //查看发布商品or查看历史订单
void insert_seller(string instruction, User& user); //上架商品
void update_seller(string instruction, User& user); //下架商品or修改商品属性

//计算发布时间
string date();
string sql_date();

#endif //PROJECT01__SQL_H_
