//
// Created by 胡文菁 on 2022/2/26.
//

#ifndef MAIN_CPP__FILE_H_
#define MAIN_CPP__FILE_H_

#include "data.h"
#include <vector>
#include <fstream>

extern vector<every_user> store_users;
extern vector<commodity> store_goods;
extern vector<order> store_orders;
extern vector<deposit> store_recharge;

using namespace std;
//读取
void read();
void read_users();
void read_goods();
void read_orders();
void read_recharge();

//写入
void write_users();
void write_goods();
void write_orders();
void write_recharge();

#endif //MAIN_CPP__FILE_H_
