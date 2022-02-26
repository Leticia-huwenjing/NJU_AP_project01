//
// Created by 胡文菁 on 2022/2/19.
//

#include "user.h"

User::User(string& name_, string& password_, bool is_alive_, string id_, string tel_, string address_, string money_) {
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
  cout << "情选择修改的属性（1.用户名 2.联系方式 3.地址）：";
  int opt=0;
  cin >> opt;
  while(!cin || getchar()!='\n'){
    cout << "输入不合法!请重新输入：";
    cin.clear();
    while(getchar()!='\n');
    cin >> opt;
  }
  switch (opt) {
    case 1:{
      cout << "请输入修改后的用户名：";
      string new_name;
      cin >> new_name;
      //判断是否重名
      break;
    }
    case 2:{
      cout << "请输入修改后的联系方式：";
      string new_tel;
      cin >> new_tel;
      user.tel = new_tel;
      break;
    }
    case 3: {
      cout << "请输入修改后的地址：";
      string new_address;
      cin >> new_address;
      user.address = new_address;
      break;
    }
    default:{
      cout << "请输入1-3之间的整数！" << endl;
      break;
    }
  }
  //将修改后的结果写入文件
}

void User::see_information(User &user) {
  cout << "*******************" << endl;
  cout << "用户名：" << user.name << endl;
  cout << "联系方式：" << user.tel << endl;
  cout << "地址：" << user.address << endl;
  cout << "钱包余额：" << user.money << endl;
  cout << "*******************" << endl;
  cout << endl;
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

    string this_condition = without_address.substr(fifth_+1);
    string this_name = without_id.erase(first_);
    string this_password = without_name.erase(second_);

    if(this_name == user.name && this_password == user.password){
      res = true;
      if(this_condition == "正常"){
        alive = true;
        string this_id = line.erase(4);
        string this_tel = without_password.erase(third_);
        string this_address = without_tel.erase(fourth_);
        string this_money = without_address.erase(fifth_);
        user.id = this_id;
        user.is_alive = true;
        user.name = this_name;
        user.password = this_password;
        user.tel = this_tel;
        user.address = this_address;
        user.money = this_money;
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

void User::register_account(User &user) {
  bool res = true;
  ifstream ifs("/Users/huwenjing/project01/user.txt");
  string line;
  getline(ifs, line);
  while(getline(ifs, line) && line.size()>4) {
    string without_id = line.substr(5); //除去id
    unsigned long first_;
    first_ = without_id.find(',');
    string this_name = without_id.erase(first_);

    if(this_name == user.name){
      res = false;
      break;
    }
  }
  ifs.close();

  if(res){ //
    string last_id = line.erase(4);
    int cnt = 100*(last_id[1]-'0') + 10*(last_id[2]-'0') + (last_id[3]-'0')+1;
    string new_ID;
    stringstream ss;
    ss << cnt;
    ss >> new_ID;
    while(new_ID.size()<3){
      new_ID = "0"+new_ID;
    }
    user.id += new_ID;
    cout << "****** 创建成功！请补充信息 ******" << endl;
    cout << "请输入你的联系方式：";
    cin >> user.tel;
    cout << "请输入你的地址：";
    cin >> user.address;
    user.money = "0.0";
    user.is_alive = true;
    cout << "****** 信息补充成功！即将返回主菜单... ******" << endl;

    ofstream ofs("/Users/huwenjing/project01/user.txt", ios::app);
    ofs << endl << user.id << "," << user.name << "," << user.password << "," << user.tel << "," << user.address << "," << user.money << "," << "正常";
    ofs.close();
  }
  else{
    cout << "****** 用户名重复，创建失败！即将返回主菜单... ******" << endl;
  }
}