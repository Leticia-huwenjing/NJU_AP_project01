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
  cout << "请选择修改的属性（1.用户名 2.联系方式 3.地址）：";
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
      int len = store_users.size();
      bool res = true;
      for(int i = 0; i < len; i++){
        if(store_users[i].user_name == new_name){
          res = false;
          break;
        }
      }
      if(res){
        user.name = new_name;
        cout << "修改成功！" << endl;
      }
      else{
        cout << "存在重名,修改失败！" << endl;
      }
      break;
    }
    case 2:{
      cout << "请输入修改后的联系方式：";
      string new_tel;
      cin >> new_tel;
      user.tel = new_tel;
      cout << "修改成功！" << endl;
      break;
    }
    case 3: {
      cout << "请输入修改后的地址：";
      string new_address;
      cin >> new_address;
      user.address = new_address;
      cout << "修改成功！" << endl;
      break;
    }
    default:{
      cout << "请输入1-3之间的整数！" << endl;
      break;
    }
  }
  int length = store_users.size();
  for(int i = 0; i < length; i++){
    if(store_users[i].user_id == user.id){
      store_users[i].user_name = user.name;
      store_users[i].address = user.address;
      store_users[i].tel = user.tel;
      break;
    }
  }
  write_users();
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
  cout << "请输入充值金额：";
  string this_money;
  cin >> this_money;
  int len = this_money.size();
  for(int i = 0; i < len; i++){
    if(this_money[i] != '.' && !(this_money[i] >= '0' && this_money[i] <= '9')){
      cout << "输入不合法！" << endl;
      cin.clear();
      while(getchar()!='\n');
      return ;
    }
  }
  if(this_money.find('.') != string::npos){
    int p = this_money.find('.');
    if(len-p >= 3){
      cout << "充值失败！最多只能输入一位小数！" << endl;
      return ;
    }
  }
  else{
    this_money.append(".0");
  }

  string notation1; //充值金额计算
  notation1.append(this_money);
  int cnt1 = store_recharge.size();
  for(int i = 0; i < cnt1; i++){
    if(store_recharge[i].user_id == user.id){
      notation1.append("+");
      notation1.append(store_recharge[i].money);
    }
  }

  string notation2; //购买金额计算
  int cnt2 = store_orders.size();
  for(int i = 0; i < cnt2; i++){
    if(store_orders[i].buyer_id == user.id){
      notation2.append("-");
      notation2.append(store_orders[i].per_price);
      notation2.append("*");
      notation2.append(store_orders[i].amount);
    }
  }

  string notation3; //售出金额计算
  for(int i = 0; i < cnt2; i++){
    if(store_orders[i].seller_id == user.id){
      notation2.append("+");
      notation2.append(store_orders[i].per_price);
      notation2.append("*");
      notation2.append(store_orders[i].amount);
    }
  }

  string notation; //最后生成的总表达式
  notation.append(notation1);
  notation.append(notation2);
  notation.append(notation3);

  notation = simplify(notation); //化简表达式，生成括号

  user.money = calculator(notation);
  int cnt3 = store_users.size();
  for(int i = 0; i < cnt3; i++){
    if(store_users[i].user_id == user.id){
      store_users[i].money = user.money;
    }
  }
  write_users();

  deposit this_recharge;
  this_recharge.user_id = user.id;
  this_recharge.money = this_money;
  store_recharge.push_back(this_recharge);
  write_recharge();

  cout << "充值成功，当前余额：" << user.money << endl;
  cout << endl;
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

  if(res){
    string new_ID;
    if(line[0] != 'U'){
      new_ID = "U001";
      user.id = new_ID;
    }
    else {
      string last_id = line.erase(4);
      int cnt = 100 * (last_id[1] - '0') + 10 * (last_id[2] - '0') + (last_id[3] - '0') + 1;
      stringstream ss;
      ss << cnt;
      ss >> new_ID;
      while (new_ID.size() < 3) {
        new_ID = "0" + new_ID;
      }
      user.id += new_ID;
    }
    cout << "****** 创建成功！请补充信息 ******" << endl;
    cout << "请输入你的联系方式：";
    cin >> user.tel;
    cout << "请输入你的地址：";
    cin >> user.address;
    user.money = "0.0";
    user.is_alive = true;
    cout << "****** 信息补充成功！即将返回主菜单... ******" << endl;

    every_user this_user;
    this_user.user_id = user.id;
    this_user.user_name = user.name;
    this_user.password = user.password;
    this_user.tel = user.tel;
    this_user.address = user.address;
    this_user.money = user.money;
    this_user.condition = "正常";

    store_users.push_back(this_user);

    write_users();
  }
  else{
    cout << "****** 用户名重复，创建失败！即将返回主菜单... ******" << endl;
  }
}