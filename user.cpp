//
// Created by 胡文菁 on 2022/2/19.
//

#include "user.h"

User::User(string name_, string password_, bool is_alive_, string id_, string tel_, string address_, double money_) {
  name = name_;
  password = password_;
  is_alive = is_alive_;
  id = id_;
  tel = tel_;
  address = address_;
  money = money_;
}

void User::user_manu() {
  cout << "===========================================" << endl;
  cout << "1.我是买家 2.我是卖家 3.个人信息管理 4.注销登录" << endl;
  cout << "===========================================" << endl;
  cout << endl;
  cout << "请输入操作：";
}

void User::information_manu() {
  cout << "=========================================" << endl;
  cout << "1.查看信息 2.修改信息 3.充值 4.返回用户主界面" << endl;
  cout << "=========================================" << endl;
  cout << endl;
  cout << "请输入操作：";
}

void User::change(User &user) {
  ;
}

void User::see_information(User &user) {
  ;
}

void User::recharge(User &user) {
  ;
}

bool User::log_in(User &user) {
  bool res = false;
  bool alive = false;
  ifstream ifs("/Users/huwenjing/project01/user.txt");
  string line;
  getline(ifs, line);
  while(getline(ifs, line)){
    string without_id = line.substr(5); //除去id
    unsigned long first_,second_,third_,fourth_,fifth_;
    first_ = without_id.find(',');
    string without_name = without_id.substr(first_+1);
    second_ = without_name.find(',');
    string without_password = without_name.substr(second_+1);
    third_ = without_password.find(',');
    string without_tel = without_password.substr(third_+1);
    fourth_ = without_tel.find(',');
    string without_address = without_tel.substr(fourth_+1);
    fifth_ = without_address.find(',');
    string condition = without_address.substr(fifth_+1);

    string this_name;
    this_name = without_id.erase(first_);
    string this_password;
    this_password = without_name.erase(second_);
    if(this_name == user.name && this_password == user.password){
      res = true;
      if(condition == "正常"){
        alive = true;
      }
      break;
    }
  }
  if(res&&alive) {
    cout << endl;
    cout << "-----登录成功-----" << endl;
    cout << endl;
  }
  else if(res){
    cout << endl;
    cout << "-----您已被封禁-----" << endl;
    cout << endl;
  }
  else{
    cout << endl;
    cout << "-----用户名或密码错误-----" << endl;
    cout << endl;
  }
  ifs.close();
  return res&&alive;
}

bool User::register_account() {
  return false;
}