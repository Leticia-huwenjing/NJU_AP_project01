//
// Created by 胡文菁 on 2022/2/26.
//

#include "file.h"

//文件初始化
void init(){
  string file_user = "/home/huwenjing/project01/user.txt";
  string file_commodity = "/home/huwenjing/project01/commodity.txt";
  string file_commands = "/home/huwenjing/project01/commands.txt";
  string file_order = "/home/huwenjing/project01/order.txt";
  string file_recharge = "/home/huwenjing/project01/recharge.txt";
  string file_cart = "/home/huwenjing/project01/shoppingCart.txt";
  string file_message = "/home/huwenjing/project01/chatting.txt";

  ifstream ifs_user(file_user);
  if(!ifs_user){
    ofstream ofs_user(file_user);
    ofs_user << "用户ID,用户名,密码,联系方式,地址,钱包余额,用户状态";
    ofs_user.close();
  }
  else{
    ifs_user.close();
  }

  ifstream ifs_commidity(file_commodity);
  if(!ifs_commidity){
    ofstream ofs_commodity(file_commodity);
    ofs_commodity << "商品ID,名称,价格,数量,描述,卖家ID,上架时间,商品状态";
    ofs_commodity.close();
  }
  else{
    ifs_commidity.close();
  }

  ifstream ifs_commands(file_commands);
  if(!ifs_commands){
    ofstream ofs_commands(file_commands);
    ofs_commands.close();
  }
  else{
    ifs_commands.close();
  }

  ifstream ifs_order(file_order);
  if(!ifs_order){
    ofstream ofs_order(file_order);
    ofs_order << "订单ID,商品ID,交易单价,数量,交易时间,卖家ID,买家ID";
    ofs_order.close();
  }
  else{
    ifs_order.close();
  }

  ifstream ifs_recharge(file_recharge);
  if(!ifs_recharge){
    ofstream ofs_recharge(file_recharge);
    ofs_recharge << "用户ID,充值金额";
    ofs_recharge.close();
  }
  else{
    ifs_recharge.close();
  }

  ifstream ifs_cart(file_cart);
  if(!ifs_cart){
    ofstream ofs_cart(file_cart);
    ofs_cart << "用户ID,商品ID,商品数量,商品状态";
    ofs_cart.close();
  }
  else{
    ifs_cart.close();
  }

  ifstream ifs_chat(file_message);
  if(!ifs_chat){
    ofstream ofs_chat(file_message);
    ofs_chat << "发送者ID,接受者ID,内容,发送时间,留言状态";
    ofs_chat.close();
  }
  else{
    ifs_chat.close();
  }
}

//读取
void read() {
  read_users();
  read_goods();
  read_orders();
  read_recharge();
  read_cart();
  read_message();
}

void read_users(){
  ifstream ifs("/home/huwenjing/project01/user.txt");
  string line;
  getline(ifs, line);
  while(getline(ifs,line)){
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
    string this_id = line.erase(4);
    string this_tel = without_password.erase(third_);
    string this_address = without_tel.erase(fourth_);
    string this_money = without_address.erase(fifth_);
    every_user cur_user;
    cur_user.user_id = this_id;
    cur_user.user_name = this_name;
    cur_user.password = this_password;
    cur_user.tel = this_tel;
    cur_user.address = this_address;
    cur_user.money = this_money;
    cur_user.condition = this_condition;
    store_users.push_back(cur_user);
  }
  ifs.close();
}

void read_goods(){
  ifstream ifs("/home/huwenjing/project01/commodity.txt");
  string line;
  getline(ifs, line);
  while(getline(ifs,line)){
    string without_id = line.substr(5); //除去id
    unsigned long first_,second_,third_,fourth_,fifth_,sixth_;
    first_ = without_id.find(',');
    string without_name = without_id.substr(first_+1);
    second_ = without_name.find(',');
    string without_price = without_name.substr(second_+1);
    third_ = without_price.find(',');
    string without_stock = without_price.substr(third_+1);
    fourth_ = without_stock.find(',');
    string without_information = without_stock.substr(fourth_+1);
    fifth_ = without_information.find(',');
    string without_seller = without_information.substr(fifth_+1);
    sixth_ = without_seller.find(',');
    string this_condition = without_seller.substr(sixth_+1);

    string this_id = line.erase(4);
    string this_name = without_id.erase(first_);
    string this_price = without_name.erase(second_);
    string this_stock = without_price.erase(third_);
    string this_information = without_stock.erase(fourth_);
    string this_seller = without_information.erase(fifth_);
    string this_time = without_seller.erase(sixth_);

    commodity good;
    good.good_id = this_id;
    good.good_name = this_name;
    good.good_price = this_price;
    good.stock = this_stock;
    good.information = this_information;
    good.seller_id = this_seller;
    good.time = this_time;
    good.condition = this_condition;

    store_goods.push_back(good);
  }
  ifs.close();
}

void read_orders(){
  ifstream ifs("/home/huwenjing/project01/order.txt");
  string line;
  getline(ifs, line);
  while(getline(ifs,line)) {
    string without_order_id = line.substr(5); //除去id
    unsigned long first_, second_, third_, fourth_, fifth_;
    first_ = without_order_id.find(',');
    string without_good_id = without_order_id.substr(first_ + 1);
    second_ = without_good_id.find(',');
    string without_price = without_good_id.substr(second_ + 1);
    third_ = without_price.find(',');
    string without_amount = without_price.substr(third_ + 1);
    fourth_ = without_amount.find(',');
    string without_time = without_amount.substr(fourth_ + 1);
    fifth_ = without_time.find(',');
    string this_buyer_id = without_time.substr(fifth_ + 1);

    string this_order_id = line.erase(4);
    string this_good_id = without_order_id.erase(first_);
    string this_price = without_good_id.erase(second_);
    string this_amount = without_price.erase(third_);
    string this_time = without_amount.erase(fourth_);
    string this_seller_id = without_time.erase(fifth_);

    order order;
    order.order_id = this_order_id;
    order.good_id = this_good_id;
    order.per_price = this_price;
    order.amount = this_amount;
    order.time = this_time;
    order.seller_id = this_seller_id;
    order.buyer_id = this_buyer_id;

    store_orders.push_back(order);
  }
  ifs.close();
}

void read_recharge(){
  ifstream ifs("/home/huwenjing/project01/recharge.txt");
  string line;
  getline(ifs, line);
  while(getline(ifs,line)){
    string money = line.substr(5);
    string user_id = line.erase(4);

    deposit this_deposit;
    this_deposit.user_id = user_id;
    this_deposit.money = money;

    store_recharge.push_back(this_deposit);
  }
  ifs.close();
}

void read_cart(){
  ifstream ifs("/home/huwenjing/project01/shoppingCart.txt");
  string line;
  getline(ifs, line);
  while(getline(ifs, line)){
    string good = line.substr(5);
    string user_id = line.erase(4);
    string amount_and_condition = good.substr(5);
    string good_id = good.erase(4);
    int p = amount_and_condition.find(',');
    string good_condition = amount_and_condition.substr(p+1);
    string good_amount = amount_and_condition.erase(p);

    commodity this_commodity;
    this_commodity.good_id = good_id;
    this_commodity.stock = good_amount;
    this_commodity.condition = good_condition;

    bool res = false;
    for(int i = 0; i < store_cart.size(); i++){
      if(store_cart[i].user_id == user_id){
        store_cart[i].shoppingCart.push_back(this_commodity);
        res = true;
        break;
      }
    }

    if(!res){
      cart this_cart;
      this_cart.user_id = user_id;
      this_cart.shoppingCart.push_back(this_commodity);
      store_cart.push_back(this_cart);
    }
  }
  ifs.close();
}

void read_message(){
  ifstream ifs("/home/huwenjing/project01/chatting.txt");
  string line;
  getline(ifs, line);
  while(getline(ifs, line)){
    string without_sender = line.substr(5);
    string sender_id = line.erase(4);
    string without_receiver = without_sender.substr(5);
    string receiver_id = without_sender.erase(4);
    int p1 = without_receiver.find(',');
    string without_info= without_receiver.substr(p1+1);
    string information = without_receiver.erase(p1);
    int p2 = without_info.find(',');
    string condition = without_info.substr(p2+1);
    string time = without_info.erase(p2);
    message this_message;
    this_message.sender_id = sender_id;
    this_message.receiver_id = receiver_id;
    this_message.info = information;
    this_message.date = time;
    this_message.condition = condition;
    store_message.push_back(this_message);
  }
  ifs.close();
}

void write_users(){
  ofstream ofs("/home/huwenjing/project01/user.txt");
  ofs << "用户ID,用户名,密码,联系方式,地址,钱包余额,用户状态";
  int len = store_users.size();
  for(int i = 0; i < len; i++){
    ofs << endl
        << store_users[i].user_id << "," << store_users[i].user_name << "," << store_users[i].password << ","
        << store_users[i].tel << "," << store_users[i].address << "," << store_users[i].money << ","
        << store_users[i].condition;
  }
  ofs.close();
}

void write_goods(){
  ofstream ofs("/home/huwenjing/project01/commodity.txt");
  ofs << "商品ID,名称,价格,数量,描述,卖家ID,上架时间,商品状态";
  int len = store_goods.size();
  for(int i = 0; i < len; i++){
    ofs << endl
        << store_goods[i].good_id << "," << store_goods[i].good_name << "," << store_goods[i].good_price << ","
        << store_goods[i].stock << "," << store_goods[i].information << "," << store_goods[i].seller_id << ","
        << store_goods[i].time << "," << store_goods[i].condition;
  }
  ofs.close();
}

void write_orders(){
  ofstream ofs("/home/huwenjing/project01/order.txt");
  ofs << "订单ID,商品ID,交易单价,数量,交易时间,卖家ID,买家ID";
  int len = store_orders.size();
  for(int i = 0; i < len; i++){
    ofs << endl
        << store_orders[i].order_id << "," << store_orders[i].good_id << "," << store_orders[i].per_price << ","
        << store_orders[i].amount << "," << store_orders[i].time << "," << store_orders[i].seller_id << ","
        << store_orders[i].buyer_id;
  }
  ofs.close();
}

void write_recharge(){
  ofstream ofs("/home/huwenjing/project01/recharge.txt");
  ofs << "用户ID,充值金额";
  int len = store_recharge.size();
  for(int i = 0; i < len; i++){
    ofs << endl
        << store_recharge[i].user_id << "," << store_recharge[i].money;
  }
  ofs.close();
}

void write_cart(){
  ofstream ofs("/home/huwenjing/project01/shoppingCart.txt");
  ofs<< "用户ID,商品ID,商品数量,商品状态";
  int len = store_cart.size();
  for(int i = 0; i < len; i++){
    int cart_len = store_cart[i].shoppingCart.size();
    for(int j = 0; j < cart_len; j++){
      ofs << endl
          << store_cart[i].user_id << "," << store_cart[i].shoppingCart[j].good_id  << ","
          << store_cart[i].shoppingCart[j].stock << "," << store_cart[i].shoppingCart[j].condition;
    }
  }
  ofs.close();
}

void write_message(){
  ofstream ofs("/home/huwenjing/project01/chatting.txt");
  ofs << "发送者ID,接受者ID,内容,发送时间,留言状态";
  int len = store_message.size();
  for(int i = 0; i < len; i++){
    ofs << endl
        << store_message[i].sender_id << "," << store_message[i].receiver_id << ","
        << store_message[i].info << "," << store_message[i].date << ","
        << store_message[i].condition;
  }
  ofs.close();
}