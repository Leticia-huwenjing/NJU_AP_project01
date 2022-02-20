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
  User(string name_,string password_,bool is_alive_=true,string id_="U",string tel_="",string address_="",double money_=0);
  void user_manu();
  void information_manu();
  void change(User &user);
  void see_information(User &user);
  void recharge(User &user);
  bool log_in(User &user);
  bool register_account();

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
