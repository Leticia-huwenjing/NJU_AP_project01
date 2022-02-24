//
// Created by 胡文菁 on 2022/2/19.
//

#include "calculator.h"

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cmath>
using namespace std;

bool point_valid(string notation){
  bool res = true;
  while(!notation.empty() && notation.find('.') != string::npos){
    int len = notation.size();
    unsigned long i = notation.find('.');
    if(i == 0 || i == len-1 || notation[i-1] == ' ' || notation[i+1] == ' '){
      res = false;
      break;
    }
    notation = notation.substr(i+1);
  }
  return res;
} //接受原始表达式，判断如果有小数点，小数点左右是否有空格

bool blank_valid(string notation){
  bool res = true;
  string copy;
  while(!notation.empty() && notation.find(' ') != string::npos) {
    int len = notation.size();
    unsigned long i = notation.find(' ');
    if (i != 0 && i != len - 1 && notation[i - 1] >= '0' && notation[i - 1] <= '9'
        && notation[i + 1] >= '0' && notation[i + 1] <= '9') {
      res = false;
      break;
    }
    notation = notation.substr(i + 1);
  }
  return res;
}//接受原始表达式，判断空格是否合法，一个空格的前后不能都是数字，负号与数字之间不应该有空格，比如，1 2 3即为不合法，-  7不合法

string edit(string notation){
  string res;
  int len = notation.size();
  for(int i = 0; i < len; i++){
    if(notation[i] != ' '){
      res.append(notation.substr(i, 1));
    }
  }
  return res;
}  //去除表达式中所有的空格

bool add_valid(string notation){
  bool res = true;
  while(!notation.empty() && notation.find('+') != string::npos) {
    int len = notation.size();
    unsigned long i = notation.find('+');
    if (i == 0 || i == len - 1) {
      res = false;
      break;
    }
    else if(notation[i-1] != ')' && (notation[i-1] < '0' || notation[i-1] > '9')){
      res = false;
      break;
    }
    else if(notation[i+1] != '(' && (notation[i+1] < '0' || notation[i+1] > '9')){
      res = false;
      break;
    }
    notation = notation.substr(i+1);
  }
  return res;
} //保证加号是双元操作符

bool sub_valid(string notation){
  bool res = true;
  while(!notation.empty() && notation.find('-') != string::npos) {
    int len = notation.size();
    unsigned long i = notation.find('-');
    if(i == 0){
      notation = notation.substr(i+1);
      continue;
    }
    else if (i == len-1) {
      res = false;
      break;
    }
    else if(notation[i-1] != '(' && notation[i-1] != ')' && (notation[i-1] < '0' || notation[i-1] > '9')){
      res = false;
      break;
    }
    notation = notation.substr(i+1);
  }
  return res;
} //保证减号是双元操作符

bool multi_valid(string notation){
  bool res = true;
  while(!notation.empty() && notation.find('*') != string::npos) {
    int len = notation.size();
    unsigned long i = notation.find('*');
    if (i == 0 || i == len - 1) {
      res = false;
      break;
    }
    else if(notation[i-1] != ')' && (notation[i-1] < '0' || notation[i-1] > '9')){
      res = false;
      break;
    }
    else if(notation[i+1] != '(' && (notation[i+1] < '0' || notation[i+1] > '9')){
      res = false;
      break;
    }
    notation = notation.substr(i+1);
  }
  return res;
} //保证乘号是双元操作符

bool div_valid(string notation){
  bool res = true;
  while(!notation.empty() && notation.find('/') != string::npos) {
    int len = notation.size();
    unsigned long i = notation.find('/');
    if (i == 0 || i == len - 1) {
      res = false;
      break;
    }
    else if(notation[i-1] != ')' && (notation[i-1] < '0' || notation[i-1] > '9')){
      res = false;
      break;
    }
    else if(notation[i+1] != '(' && (notation[i+1] < '0' || notation[i+1] > '9')){
      res = false;
      break;
    }
    notation = notation.substr(i+1);
  }
  return res;
} //保证除号是双元操作符

bool mul_valid(string notation){
  bool res = true;
  string copy;
  copy.assign(notation);
  while(!notation.empty() && notation.find('(') != string::npos){
    int len = notation.size();
    unsigned long i = notation.find('(');
    if(i != 0 && notation[i-1] != '+' && notation[i-1] != '-' && notation[i-1] != '*' && notation[i-1] != '/'){
      res = false;
      break;
    }
    notation = notation.substr(i+1);
  }

  if(res){
    while(!copy.empty() && copy.find(')') != string::npos) {
      int len = copy.size();
      unsigned long i = copy.find(')');
      if(i != len-1 && copy[i+1] != '+' && copy[i+1] != '-' && copy[i+1] != '*' && copy[i+1] != '/' && copy[i+1]!= ')'){
        res = false;
        break;
      }
      copy = copy.substr(i+1);
    }
  }
  return res;
} //保证无隐藏乘号

bool operator_valid(string notation){
  bool res = true;
  while(notation.size()>1){
    if((notation[0] == '+' || notation[0] == '-' || notation[0] == '*' || notation[0] == '/') &&
        (notation[1] == '+' || notation[1] == '-'|| notation[1] == '*' || notation[1] == '/')){
      res = false;
      break;
    }
    notation = notation.substr(1);
  }
  return res;
} //保证无连续操作符

bool bracket_valid(string notation){
  bool res = true;
  bool flag = false;
  stack<string> stack;
  int len = notation.size();
  for(int i = 0; i < len; i++){
    if(notation[i] == '('){
      stack.push("(");
    }
    else if(notation[i] == ')'){
      if(stack.empty()){
        res = false;
        break;
      }
      stack.pop();
    }
    else{
      flag = true;
    }
  }
  if(!stack.empty()){
    res = false;
  }
  return (res && flag);
} //保证括号匹配且不存在空括号

bool decimal_valid(string notation){
  bool res = true;
  int len = notation.size();
  for(int i = 0; i < len; i++){
    if(notation[i] == '.'){
      if(i == 0 || i == len-1){
        res = false;
        break;
      }
      else{
        if(notation[i-1] < '0' || notation[i-1] > '9' || notation[i+1] < '0' || notation[i+1] > '9'){
          res = false;
          break;
        }
      }
    }
  }
  return res;
} //保证不出现0. .0

bool digit_valid(string notation){
  bool res = true;
  int len = notation.size();
  for(int i = 0; i < len; i++){
    if(notation[i] == '.'){
      if(i == 0 || i == len-1){
        res = false;
        break;
      }
      else{
        if(i+1 < len-1){
          if(notation[i+2] >= '0' && notation[i+2] <= '9'){
            res = false;
            break;
          }
        }
      }
    }
  }
  return res;
} //保证只有一位小数

string is_valid(string notation){
  string res="合法";
  //+1 +(2+3) 加号不算做一元操作符
  if(!add_valid(notation)){
    res = "加号不可以进行一元操作！";
  }
  else if(!sub_valid(notation)){
    res = "减号不可以进行一元操作！";
  }
  else if(!multi_valid(notation)){
    res = "乘号不可以进行一元操作！";
  }
  else if(!div_valid(notation)){
    res = "除号不可以进行一元操作！";
  }
    //()) 括号不匹配或者存在空括号
  else if(!bracket_valid(notation)){
    res = "括号不匹配/存在空括号";
  }
    //2(1+1) 不能使用隐藏乘号(意味着在中间的前括号的前面必须是操作符，后括号的后面也必须是操作符
  else if(!mul_valid(notation)){
    res = "不可以使用隐藏乘号！";
  }
    //-1*-1 不能出现连续操作符
  else if(!operator_valid(notation)){
    res = "不可以出现连续操作符！";
  }
    //0. .0 不能出现点的左右只有一位数字
  else if(!decimal_valid(notation)){
    res = "小数点左右必须均为数字！";
  }
    //0.01 不能出现两位及以上小数
  else if(!digit_valid(notation)){
    res = "计算器只支持一位小数计算！";
  }
  return res;
} //此时输入的表达式不含有空格,如果不合法，返回不合法原因，如果合法，返回"合法"

int priority(string str){
  if(str == "&")
    return 3;
  else if(str == "*" || str == "/")
    return 2;
  else if(str == "+" || str == "-")
    return 1;
}

string convert(string notation){
  string res;
  stack<string> stack;
  int len = notation.size();
  int i = 0;
  while(i < len){
    if(notation[i] >='0' && notation[i] <= '9'){
      if(i+1 < len){
        res.append(notation.substr(i, 1));
        i++;
        while(i+1 < len && (notation[i] == '.' || (notation[i] >= '0' && notation[i] <= '9'))){
          res.append(notation.substr(i, 1));
          i++;
        }
        if(i == len-1){
          if(notation[i] >= '0' && notation[i] <= '9') {
            res.append(notation.substr(i, 1));
            res.append(" ");
            i++;
          }
          else{
            res.append(" ");
          }
        }
        else{
          res.append(" ");
        }
      }
      else{
        res.append(notation.substr(i, 1));
        res.append(" ");
        i++;
      }
    } //cur是操作数
    else if(notation[i] == '('){
      stack.push("(");
      i++;
    }
    else if(notation[i] == '+' || notation[i] == '-' || notation[i] == '*'|| notation[i] == '/'){
      if((i == 0 || notation[i-1] == '(') && notation[i] == '-'){
        notation[i] = '&';
      }
      string cur(1, notation[i]);
      while(true) {
        if (stack.empty() || stack.top() == "(") {
          stack.push(cur);
          i++;
          break;
        }
        else if (priority(cur) > priority(stack.top())) {
          stack.push(cur);
          i++;
          break;
        }
        else {
          res.append(stack.top());
          stack.pop();
        }
      }
    }
    else{
      while(stack.top() != "("){
        res.append(stack.top());
        stack.pop();
      }
      i++;
      stack.pop();
    }
  }
  while(!stack.empty()){
    res.append(stack.top());
    stack.pop();
  }
  return res;
} //将中缀表达式转为逆波兰表达式,在逆波兰表达式中，将&当作负号

string calculate(string notation){
  string res;
  int len = notation.size();
  vector<double> store;
  int i = 0;
  while(i < len){
    if(notation[i] >= '0' && notation[i] <= '9') {
      string cur;
      string tmp;
      while (notation[i] == '.' || (notation[i] >= '0' && notation[i] <= '9')) {
        tmp.assign(1, notation[i]);
        cur.append(tmp);
        i++;
      }
      double ans = stod(cur);
      store.push_back(ans);
      i++;
    }
    else{
      int length = store.size();
      if(notation[i] == '&'){
        store[length-1] = -store[length-1];
      }
      else if(notation[i] == '+'){
        store[length-2] = store[length-2]+store[length-1];
        store.erase(store.end()-1);
      }
      else if(notation[i] == '-'){
        store[length-2] = store[length-2]-store[length-1];
        store.erase(store.end()-1);
      }
      else if(notation[i] == '*'){
        store[length-2] = store[length-2]*store[length-1];
        store.erase(store.end()-1);
      }
      else if(notation[i] == '/'){
        if(fabs(store[length-1]-0.0) < 1e-13){
          res = "除数为0！";
          return res;
        }
        else{
          store[length-2] = store[length-2]/store[length-1];
          store.erase(store.end()-1);
        }
      }
      i++;
    }

  }
  res = to_string(store[0]);
  //处理四舍五入
  int size = res.size();
  if (res.find('.') != string::npos){
    int p = res.find('.');
    if(size-p-1 > 1){
      if((res[p+2]-'0') > 4) {
        vector<int> vector;
        for (int m = 0; m <= p + 2; m++) {
          if(res[m] != '.') {
            vector.push_back(res[m] - '0');
          }
        }
        vector[p+1]++;
        for(int m = p+1; m >= 1; m--){
          if(vector[m] >= 10){
            vector[m]%=10;
            vector[m-1]++;
          }
        }
        if(vector[0] >= 10){
          string ans("1");
          vector[0] %=10;
          for(int m = 0; m < p+1; m++){
            ans.append(to_string(vector[m]));
            if(m == p-1){
              ans.append(".");
            }
          }
          return ans;
        }
        else{
          string ans;
          for(int m = 0; m < p+1; m++){
            ans.append(to_string(vector[m]));
            if(m == p-1){
              ans.append(".");
            }
          }
          return ans;
        }
      }
      else{
        res.erase(p+2);
      }
    }
  }
  return res;
} //计算逆波兰表达式,返回除零错误


string calculator(string notation){
  string res = "合法";
  if(!point_valid(notation)){
    res = "小数点不合法！";
  }
  else if(!blank_valid(notation)){
    res = "空格前后不能均为数字/负号与数字之间存在空格";
  }
  else{
    notation = edit(notation); //notation已不含有空格
    if(is_valid(notation) != "合法"){
      res = is_valid(notation);
    }
    else{
      res = calculate(convert(notation));
    }
  }
  return res;
} //总计算器接口
