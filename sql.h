//
// Created by 胡文菁 on 2022/2/19.
//

#ifndef PROJECT01__SQL_H_
#define PROJECT01__SQL_H_

#include <iostream>
using namespace std;
void mysql(string instruction);
void insert(string table_name);
void insert_user(string x1, string x2, string x3, string x4, string x5, string x6);
void insert_good(string x1, string x2, string x3, string x4, string x5, string x6, string x7, string x8);
void insert_order(string x1, string x2, string x3, string x4, string x5, string x6, string x7);
void update(string table_name, string column, string value, string edit_column, string edit_value);
void select_admin(string table, string column, string value);
void select_buyer(string table, string column, string value);
void select_all(string user, string table);//buyer,seller,admin
#endif //PROJECT01__SQL_H_
