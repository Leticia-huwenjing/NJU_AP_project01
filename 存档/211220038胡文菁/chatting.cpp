//
// Created by 胡文菁 on 2022/3/20.
//

#include "chatting.h"
void Chatting::chat_menu(){
  cout << "\033[34m=======================================================" << endl;
  cout << "1.用户留言 2.查看新留言 3.查看留言记录 4.退出留言系统" << endl;
  cout << "=======================================================" << endl;
  cout << endl;
  cout << "请输入操作：\033[0m";
}


void Chatting::add_message(User &user){
  cout << "请输入您想留言的用户ID：";
  string receiver_id;
  getline(cin, receiver_id);
  bool is_alive = false;
  int len = store_users.size();
  for(int i = 0; i < len; i++){
    if(store_users[i].user_id == receiver_id){
      if(store_users[i].condition == "正常"){
        is_alive = true;
      }
      break;
    }
  }
  if(!is_alive){
    cout << "\033[31m******************" << endl;
    cout << "您输入的用户非法！" << endl;
    cout << "******************\033[0m" << endl;
  }
  else{
    cout << "请输入您的留言：";
    string information;
    getline(cin, information);
    message this_message;
    this_message.sender_id = user.id;
    this_message.receiver_id = receiver_id;
    this_message.info = information;
    this_message.date = sql_date();
    int p = this_message.date.rfind(':');
    this_message.date = this_message.date.erase(p);
    this_message.condition = "未被查看";
    store_message.push_back(this_message);
    cout << "\033[01;32m留言成功！\033[0m" << endl;
    write_message();
  }
  cout << endl;
}


void Chatting::see_new_message(User &user){
  bool is_message = false;
  int len = store_message.size();
  for(int i = 0; i < len; i++){
    if(store_message[i].receiver_id == user.id && store_message[i].condition == "未被查看"){
      is_message = true;
      break;
    }
  }
  if(!is_message){
    cout << "\033[31m***********************" << endl;
    cout << "您没有尚未查看的新留言！" << endl;
    cout << "***********************\033[0m" << endl;
  }
  else{
    cout << "\033[32m您收到了新的留言！\033[0m" << endl;
    for(int i = 0; i < len; i++){
      if(store_message[i].receiver_id == user.id && store_message[i].condition == "未被查看"){
        cout << "********************************" << endl;
        cout << "发送用户ID：" << store_message[i].sender_id << endl;
        cout << "发送时间：" << store_message[i].date << endl;
        cout << "发送内容：" << store_message[i].info << endl;
        cout << "********************************" << endl;
        cout << endl;
        store_message[i].condition = "已被查看";
      }
    }
    write_message();
  }
  cout << endl;
}


void Chatting::see_message_history(User &user){
  cout << "请选择查看记录方式（1.查看全部 2.查看某一用户）：";
  int opt=0;
  cin >> opt;
  while(!cin || getchar()!='\n'){
    cout << "\033[31m输入不合法!请重新输入：\033[0m";
    cin.clear();
    while(getchar()!='\n');
    cin >> opt;
  }
  switch (opt) {
    case 1:{
      bool is_send = false;
      int len = store_message.size();
      for(int i = 0; i < len; i++){
        if(store_message[i].sender_id == user.id){
          is_send = true;
          break;
        }
      }
      if(!is_send){
        cout << "\033[31m您尚未发出留言！\033[0m" << endl;
      }
      else {
        cout << "\033[33m您发出的留言记录如下：\033[0m" << endl;
        for(int i = 0; i < len; i++){
          if(store_message[i].sender_id == user.id){
            cout << "***********************" << endl;
            cout << "接受用户ID：" << store_message[i].receiver_id << endl;
            cout << "留言时间：" << store_message[i].date << endl;
            cout << "留言内容：" << store_message[i].info << endl;
            cout << "***********************" << endl;
          }
        }
      }
      cout << endl;

      bool is_receive = false;
      for(int i = 0; i < len; i++){
        if(store_message[i].receiver_id == user.id){
          is_receive = true;
          break;
        }
      }
      if(!is_receive){
        cout << "\033[31m您尚未收到留言！\033[0m" << endl;
      }
      else{
        cout << "\033[33m您收到的留言如下：\033[0m" << endl;
        for(int i = 0; i < len; i++){
          if(store_message[i].receiver_id == user.id){
            cout << "***********************" << endl;
            cout << "发出用户ID：" << store_message[i].sender_id << endl;
            cout << "留言时间：" << store_message[i].date << endl;
            cout << "留言内容：" << store_message[i].info << endl;
            cout << "***********************" << endl;
            store_message[i].condition = "已被查看";
          }
        }
        write_message();
      }
      cout << endl;
      break;
    }
    case 2:{
      cout << "请输入您想查看的用户：";
      string other_id;
      getline(cin, other_id);
      if(other_id.find(' ') != string::npos){
        cout << "\033[31m****************" << endl;
        cout << "您的输入不合法！" << endl;
        cout << "****************\033[0m" << endl << endl;
        return ;
      }

      //收拾离谱输入
      bool res = true;
      int i;
      if(other_id.size() != 4 || other_id[0] != 'U' || !(other_id[1] >= '0' && other_id[1] <= '9'
          && other_id[2] >= '0' && other_id[2] <= '9' && other_id[3] >= '0' && other_id[3] <= '9')){
        res = false;
        cout << "\033[31m****************" << endl;
        cout << "您的输入不合法！" << endl;
        cout << "****************\033[0m" << endl;
      }

        //处理用户不存在
      else{
        bool is_alive = false;
        int len = store_users.size();
        for(i = 0; i < len; i++){
          if(store_users[i].user_id == other_id){
            is_alive = true;
            break;
          }
        }
        if(!is_alive){
          res = false;
          cout << "\033[31m************" << endl;
          cout << "用户不存在！" << endl;
          cout << "************\033[0m" << endl;
        }
      }

      if(res){
        int len = store_message.size();
        bool is_send = false;
        for(int x = 0; x < len; x++){
          if(store_message[x].sender_id == user.id && store_message[x].receiver_id == other_id){
            is_send = true;
            break;
          }
        }
        if(!is_send){
          cout << "\033[31m您尚未向该用户发送留言！\033[0m" << endl;
        }
        else{
          cout << "\033[33m您对该用户的留言如下：\033[0m" << endl;
          for(int x = 0; x < len; x++){
            if(store_message[x].sender_id == user.id && store_message[x].receiver_id == other_id){
              cout << "*************************" << endl;
              cout << "留言时间：" << store_message[x].date << endl;
              cout << "留言内容：" << store_message[x].info << endl;
              cout << "留言状态：" << store_message[x].condition << endl;
              cout << "*************************" << endl;
            }
          }
        }
        cout << endl;

        bool is_receive = false;
        for(int x = 0; x < len; x++){
          if(store_message[x].receiver_id == user.id && store_message[x].sender_id == other_id){
            is_receive = true;
            break;
          }
        }
        if(!is_receive) {
          cout << "\033[31m您尚未收到该用户的留言！\033[0m" << endl;
        }
        else{
          cout << "\033[33m您收到该用户的留言如下：\033[0m" << endl;
          for(int x = 0; x < len; x++){
            if(store_message[x].receiver_id == user.id && store_message[x].sender_id == other_id){
              cout << "*************************" << endl;
              cout << "留言时间：" << store_message[x].date << endl;
              cout << "留言内容：" << store_message[x].info << endl;
              cout << "留言状态：" << store_message[x].condition << endl;
              cout << "*************************" << endl;
            }
          }
        }
      }
      break;
    }
    default:{
      cout << "\033[31m请输入1-2之间的整数！\033[0m" << endl;
      break;
    }
  }
  cout << endl;
}