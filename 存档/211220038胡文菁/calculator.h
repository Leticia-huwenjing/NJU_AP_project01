//
// Created by 胡文菁 on 2022/2/19.
//

#ifndef PROJECT01__CALCULATOR_H_
#define PROJECT01__CALCULATOR_H_

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cmath>
#include "user.h"
using namespace std;

bool point_valid(string notation);//接受原始表达式，判断如果有小数点，小数点左右是否有空格
bool blank_valid(string notation);//接受原始表达式，判断空格是否合法，一个空格的前后不能都是数字，负号与数字之间不应该有空格，比如，1 2 3即为不合法，-  7不合法
string edit(string notation);//去除表达式中所有的空格
bool add_valid(string notation);//保证加号是双元操作符
bool sub_valid(string notation);//保证减号是双元操作符
bool multi_valid(string notation);//保证乘号是双元操作符
bool div_valid(string notation);//保证除号是双元操作符
bool mul_valid(string notation);//保证无隐藏乘号
bool operator_valid(string notation);//保证无连续操作符
bool bracket_valid(string notation);//保证括号匹配且不存在空括号
bool decimal_valid(string notation);//保证不出现0. .0
bool digit_valid(string notation);//保证只有一位小数
string is_valid(string notation);//此时输入的表达式不含有空格,如果不合法，返回不合法原因，如果合法，返回"合法"
int priority(string str);

string simplify(string notation); //化简计算表达式，合并成交数量一致的交易

string convert(string notation);//将中缀表达式转为逆波兰表达式,在逆波兰表达式中，将&当作负号
string calculate(string notation);//计算逆波兰表达式,返回除零错误
string calculator(string notation);//总计算器接口

#endif //PROJECT01__CALCULATOR_H_
