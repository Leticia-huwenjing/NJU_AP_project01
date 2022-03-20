//
// Created by 胡文菁 on 2022/3/20.
//

#ifndef MAIN_CPP__CHATTING_H_
#define MAIN_CPP__CHATTING_H_

#include <iostream>
#include "user.h"
using namespace std;


class Chatting{
 public:
  void chat_menu();
  void write_message(User &user);
  void see_new_message(User &user);
  void see_message_history(User &user);
 private:
  string user_id;
};


#endif //MAIN_CPP__CHATTING_H_
