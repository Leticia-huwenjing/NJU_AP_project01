//
// Created by 胡文菁 on 2022/2/19.
//

#ifndef PROJECT01__CALCULATOR_H_
#define PROJECT01__CALCULATOR_H_

#include <iostream>
#include "user.h"
using namespace std;
string calculator(string edited_notation); //返回表达式的值或表达式不合法的原因
string edit(string notation); //将中缀表达式转化为逆波兰表达式
string generate(User &user); //产生中缀表达式
#endif //PROJECT01__CALCULATOR_H_
