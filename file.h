//
// Created by 胡文菁 on 2022/2/26.
//

#ifndef MAIN_CPP__FILE_H_
#define MAIN_CPP__FILE_H_

#include "data.h"
#include <vector>
#include <fstream>
using namespace std;
//读取
void read(vector<every_user>&store_users, vector<commodity>&store_goods, vector<order>&store_orders);
void read_users(vector<every_user>&store_users);
void read_goods(vector<commodity>&store_goods);
void read_orders(vector<order>&store_orders);

//写入
void write_users(vector<every_user>&store_users);
void write_goods(vector<commodity>&store_goods);
void write_orders(vector<order>&store_orders);

#endif //MAIN_CPP__FILE_H_
