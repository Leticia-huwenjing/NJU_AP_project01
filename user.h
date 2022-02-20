//
// Created by 胡文菁 on 2022/2/19.
//

#ifndef PROJECT01__USER_H_
#define PROJECT01__USER_H_

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
class User{
 public:
  void user_manu();
  void information_manu();
  void change(User &user);
  void see_information(User &user);
  void recharge(User &user);
  bool log_in();
  bool register_account();
  friend istream &operator>>(istream &input, User &user); //Todo:事后删除

 private:
  bool is_alive;
  string id;
  string name;
  string password;
  string tel;
  string address;
  double money;
};
#endif //PROJECT01__USER_H_
