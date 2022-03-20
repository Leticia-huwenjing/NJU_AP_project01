//
// Created by 胡文菁 on 2022/2/19.
//

#include "sql.h"

string date(){
  //计算发布时间
  time_t timep;
  struct tm *p;
  time(&timep); /*获得time_t结构的时间，UTC时间*/
  p = gmtime(&timep); /*转换为struct tm结构的UTC时间*/
  int year = 1900 + p->tm_year;
  int mon = 1+ p->tm_mon;
  int day = p->tm_mday;
  string this_year = to_string(year);
  string this_month = to_string(mon);
  string this_day = to_string(day);
  if(this_month.size() == 1){
    this_month = "0"+this_month;
  }
  if(this_day.size() == 1){
    this_day = "0"+this_day;
  }
  string date;
  date = this_year+"-"+this_month+"-"+this_day;
  return date;
}

string sql_date(){
  time_t timep;
  struct tm *p;
  time(&timep); /*获得time_t结构的时间，UTC时间*/
  p = gmtime(&timep); /*转换为struct tm结构的UTC时间*/
  int year = 1900 + p->tm_year;
  int mon = 1+ p->tm_mon;
  int day = p->tm_mday;
  int hour = 8+p->tm_hour;
  int min = p->tm_min;
  int sec = p->tm_sec;
  string this_year = to_string(year);
  string this_month = to_string(mon);
  string this_day = to_string(day);
  string this_hour = to_string(hour);
  string this_min = to_string(min);
  string this_sec = to_string(sec);
  if(this_month.size() == 1){
    this_month = "0"+this_month;
  }
  if(this_day.size() == 1){
    this_day = "0"+this_day;
  }
  if(this_hour.size() == 1){
    this_hour = "0"+this_hour;
  }
  if(this_min.size() == 1){
    this_min = "0"+this_min;
  }
  if(this_sec.size() == 1){
    this_sec = "0"+this_sec;
  }

  string date;
  date = this_year+"-"+this_month+"-"+this_day+" "+this_hour+":"+this_min+":"+this_sec+": ";
  return date;
}

void mysql(string instruction, string& manipulator, User& user){
  char opt = instruction[0];
  switch (opt) {
    case 'I':{
      insert(instruction, manipulator, user);
      break;
    }
    case 'U':{
      update(instruction, manipulator, user);
      break;
    }
    case 'S':{
      select(instruction, manipulator, user);
      break;
    }
    default:{
      cout << "指令合成失败！" << endl;
      break;
    }
  }
} //sql总接口

void insert(string instruction, string& manipulator, User& user){
  if(manipulator == "buyer"){
    insert_buyer(instruction, user);
  }
  else{
    insert_seller(instruction, user);
  }
}

void update(string instruction, string& manipulator, User& user){
  if(manipulator == "admin"){
    if(instruction.find("用户") != string::npos){
      update_user_admin(instruction);
    }
    else if(instruction.find("卖家") != string::npos){
      update_commodity_admin(instruction);
    }
    else{
      update_good_admin(instruction);
    }
  }
  else if(manipulator == "buyer"){
    update_buyer(instruction, user);
  }
  else{
    update_seller(instruction, user);
  }
}

void select(string instruction, string& manipulator, User& user){
  if(manipulator == "admin"){
    if(instruction.find("WHERE") != string::npos){
      search_admin(instruction);
    }
    else{
      select_admin(instruction);
    }
  }
  else if(manipulator == "buyer"){
    if(instruction.find("WHERE") != string::npos){
      search_buyer(instruction);
    }
    else{
      select_buyer(instruction, user);
    }
  }
  else{
    select_seller(instruction, user);
  }
}

void select_admin(string instruction){
  if(instruction.find("commodity") != string::npos){
    int len  = store_goods.size();
    if(len == 0){
      cout << "**************" << endl;
      cout << "当前没有商品！" << endl;
      cout << "**************" << endl;
    }
    else {
      cout
          << "*************************************************************************************************************************************"
          << endl;
      cout << left << setw_u8(20, "商品ID") << "商品ID"
           << left << setw_u8(20, "名称") << "名称"
           << left << setw_u8(20, "价格") << "价格"
           << left << setw_u8(20, "上架时间") << "上架时间"
           << left << setw_u8(20, "卖家ID") << "卖家ID"
           << left << setw_u8(20, "数量") << "数量"
           << left << setw_u8(20, "商品状态") << "商品状态" << endl;

      for (int i = 0; i < len; i++) {
        cout << left << setw_u8(20, store_goods[i].good_id) << store_goods[i].good_id
             << left << setw_u8(20, store_goods[i].good_name) << store_goods[i].good_name
             << left << setw_u8(20, store_goods[i].good_price) << store_goods[i].good_price
             << left << setw_u8(20, store_goods[i].time) << store_goods[i].time
             << left << setw_u8(20, store_goods[i].seller_id) << store_goods[i].seller_id
             << left << setw_u8(20, store_goods[i].stock) << store_goods[i].stock
             << left << setw_u8(20, store_goods[i].condition) << store_goods[i].condition << endl;
      }
      cout
          << "*************************************************************************************************************************************"
          << endl;
    }
    cout << endl;
    ofstream ofs("/Users/huwenjing/project01/commands.txt",ios::app);
    ofs << sql_date() << instruction << endl;
    ofs.close();
  }
  else if(instruction.find("order") != string::npos){
    int len = store_orders.size();
    if(len == 0){
      cout << "*************" << endl;
      cout << "当前没有订单！" << endl;
      cout << "*************" << endl;
    }
    else {
      cout
          << "*************************************************************************************************************************************"
          << endl;
      cout << left << setw_u8(20, "订单ID") << "订单ID"
           << left << setw_u8(20, "商品ID") << "商品ID"
           << left << setw_u8(20, "交易单价") << "交易单价"
           << left << setw_u8(20, "数量") << "数量"
           << left << setw_u8(20, "交易时间") << "交易时间"
           << left << setw_u8(20, "卖家ID") << "卖家ID"
           << left << setw_u8(20, "买家ID") << "买家ID" << endl;

      for (int i = 0; i < len; i++) {
        cout << left << setw_u8(20, store_orders[i].order_id) << store_orders[i].order_id
             << left << setw_u8(20, store_orders[i].good_id) << store_orders[i].good_id
             << left << setw_u8(20, store_orders[i].per_price) << store_orders[i].per_price
             << left << setw_u8(20, store_orders[i].amount) << store_orders[i].amount
             << left << setw_u8(20, store_orders[i].time) << store_orders[i].time
             << left << setw_u8(20, store_orders[i].seller_id) << store_orders[i].seller_id
             << left << setw_u8(20, store_orders[i].buyer_id) << store_orders[i].buyer_id << endl;
      }
      cout
          << "*************************************************************************************************************************************"
          << endl;
    }
    cout << endl;
    ofstream ofs("/Users/huwenjing/project01/commands.txt",ios::app);
    ofs << sql_date() << instruction << endl;
    ofs.close();
  }
  else{
    int len = store_users.size();
    if(len == 0){
      cout << "*************" << endl;
      cout << "当前没有用户！" << endl;
      cout << "*************" << endl;
    }
    else {
      cout
          << "*************************************************************************************************************************************"
          << endl;
      cout << left << setw_u8(20, "用户ID") << "用户ID"
           << left << setw_u8(20, "用户名") << "用户名"
           << left << setw_u8(20, "联系方式") << "联系方式"
           << left << setw_u8(20, "地址") << "地址"
           << left << setw_u8(20, "钱包余额") << "钱包余额"
           << left << setw_u8(20, "用户状态") << "用户状态" << endl;

      for (int i = 0; i < len; i++) {
        cout << left << setw_u8(20, store_users[i].user_id) << store_users[i].user_id
             << left << setw_u8(20, store_users[i].user_name) << store_users[i].user_name
             << left << setw_u8(20, store_users[i].tel) << store_users[i].tel
             << left << setw_u8(20, store_users[i].address) << store_users[i].address
             << left << setw_u8(20, store_users[i].money) << store_users[i].money
             << left << setw_u8(20, store_users[i].condition) << store_users[i].condition << endl;
      }
      cout
          << "*************************************************************************************************************************************"
          << endl;
    }
    cout << endl;
    ofstream ofs("/Users/huwenjing/project01/commands.txt",ios::app);
    ofs << sql_date() << instruction << endl;
    ofs.close();
  }
}

void search_admin(string instruction) {
  int point_I = instruction.find("I");
  string this_name = instruction.substr(point_I+4);

  int len  = store_goods.size();
  bool res = false;
  for(int i = 0; i < len; i++){
    if(store_goods[i].good_name.find(this_name) != string::npos){
      res = true;
      break;
    }
  }

  if(res) {
    cout
        << "*************************************************************************************************************************************"
        << endl;
    cout << left << setw_u8(20, "商品ID") << "商品ID"
         << left << setw_u8(20, "名称") << "名称"
         << left << setw_u8(20, "价格") << "价格"
         << left << setw_u8(20, "上架时间") << "上架时间"
         << left << setw_u8(20, "卖家ID") << "卖家ID"
         << left << setw_u8(20, "数量") << "数量"
         << left << setw_u8(20, "商品状态") << "商品状态" << endl;
    for (int i = 0; i < len; i++) {
      if (store_goods[i].good_name.find(this_name) != string::npos) {
        cout << left << setw_u8(20, store_goods[i].good_id) << store_goods[i].good_id
             << left << setw_u8(20, store_goods[i].good_name) << store_goods[i].good_name
             << left << setw_u8(20, store_goods[i].good_price) << store_goods[i].good_price
             << left << setw_u8(20, store_goods[i].time) << store_goods[i].time
             << left << setw_u8(20, store_goods[i].seller_id) << store_goods[i].seller_id
             << left << setw_u8(20, store_goods[i].stock) << store_goods[i].stock
             << left << setw_u8(20, store_goods[i].condition) << store_goods[i].condition << endl;
      }
    }
    cout
        << "*************************************************************************************************************************************"
        << endl;
    cout << endl;
  }
  else{
    cout << "******************************" << endl;
    cout << "没有找到您想要的商品！返回初始界面" << endl;
    cout << "******************************" << endl;
  }
  ofstream ofs("/Users/huwenjing/project01/commands.txt",ios::app);
  ofs << sql_date() << instruction << endl;
  ofs.close();
}

void update_good_admin(string instruction) {
  int p = instruction.find('M');
  string this_good_id = instruction.substr(p);
  int len = store_goods.size();
  for(int i = 0; i < len; i++){
    if(store_goods[i].good_id == this_good_id){
      store_goods[i].condition = "已下架";
      break;
    }
  }
  write_goods();

  //更新购物车中的商品信息
  int cart_len = store_cart.size();
  for(int i = 0; i < cart_len; i++){
    int this_len = store_cart[i].shoppingCart.size();
    for(int j = 0; j < this_len; j++){
      if(store_cart[i].shoppingCart[j].good_id == this_good_id){
        store_cart[i].shoppingCart[j].condition = "已下架";
      }
    }
  }
  write_cart();

  ofstream ofs("/Users/huwenjing/project01/commands.txt",ios::app);
  ofs << sql_date() << instruction << endl;
  ofs.close();
}

void update_user_admin(string instruction) {
  int p1 = instruction.find('U');
  string instruction1 = instruction.substr(p1+1);
  int p2 = instruction1.find('U');
  string this_user_id = instruction1.substr(p2);
  int len = store_users.size();
  for(int i = 0; i < len; i++){
    if(store_users[i].user_id == this_user_id){
      store_users[i].condition = "封禁";
      break;
    }
  }
  write_users();

  ofstream ofs("/Users/huwenjing/project01/commands.txt",ios::app);
  ofs << sql_date() << instruction << endl;
  ofs.close();
}

void update_commodity_admin(string instruction){
  int p1 = instruction.find('U');
  string instruction1 = instruction.substr(p1+1);
  int p2 = instruction1.find('U');
  string this_user_id = instruction1.substr(p2);
  int len = store_goods.size();
  for(int i = 0; i < len; i++){
    if(store_goods[i].seller_id == this_user_id){
      store_goods[i].condition = "已下架";
    }
  }
  write_goods();

  ofstream ofs("/Users/huwenjing/project01/commands.txt",ios::app);
  ofs << sql_date() << instruction << endl;
  ofs.close();
}

void select_buyer(string instruction, User& user){
  if(instruction.find("commodity") != string::npos){
    bool res = false;
    int len  = store_goods.size();
    for(int i = 0; i < len; i++){
      if(store_goods[i].condition == "销售中"){
        res = true;
        break;
      }
    }

    if(res) {
      cout
          << "*************************************************************************************************************************************"
          << endl;
      cout << left << setw_u8(20, "商品ID") << "商品ID"
           << left << setw_u8(20, "名称") << "名称"
           << left << setw_u8(20, "价格") << "价格"
           << left << setw_u8(20, "上架时间") << "上架时间"
           << left << setw_u8(20, "卖家ID") << "卖家ID"
           << left << setw_u8(20, "数量") << "数量" << endl;

      for (int i = 0; i < len; i++) {
        if (store_goods[i].condition == "销售中") {
          cout << left << setw_u8(20, store_goods[i].good_id) << store_goods[i].good_id
               << left << setw_u8(20, store_goods[i].good_name) << store_goods[i].good_name
               << left << setw_u8(20, store_goods[i].good_price) << store_goods[i].good_price
               << left << setw_u8(20, store_goods[i].time) << store_goods[i].time
               << left << setw_u8(20, store_goods[i].seller_id) << store_goods[i].seller_id
               << left << setw_u8(20, store_goods[i].stock) << store_goods[i].stock << endl;
        }
      }
      cout
          << "*************************************************************************************************************************************"
          << endl;
      cout << endl;
    }
    else{
      cout << "********************************************" << endl;
      cout << "当前没有销售中商品哦！您可以切换为卖家模式发布商品！" << endl;
      cout << "********************************************" << endl;
    }
    ofstream ofs("/Users/huwenjing/project01/commands.txt",ios::app);
    ofs << sql_date() << instruction << endl;
    ofs.close();
  }
  else{ //order
    int len = store_orders.size();
    bool res = false;
    for(int i = 0; i < len; i++){
      if(store_orders[i].buyer_id == user.id){
        res = true;
        break;
      }
    }

    if(res) {
      cout
          << "*************************************************************************************************************************************"
          << endl;
      cout << left << setw_u8(20, "订单ID") << "订单ID"
           << left << setw_u8(20, "商品ID") << "商品ID"
           << left << setw_u8(20, "交易单价") << "交易单价"
           << left << setw_u8(20, "数量") << "数量"
           << left << setw_u8(20, "交易时间") << "交易时间"
           << left << setw_u8(20, "卖家ID") << "卖家ID" << endl;

      for (int i = 0; i < len; i++) {
        if (store_orders[i].buyer_id == user.id) {
          cout << left << setw_u8(20, store_orders[i].order_id) << store_orders[i].order_id
               << left << setw_u8(20, store_orders[i].good_id) << store_orders[i].good_id
               << left << setw_u8(20, store_orders[i].per_price) << store_orders[i].per_price
               << left << setw_u8(20, store_orders[i].amount) << store_orders[i].amount
               << left << setw_u8(20, store_orders[i].time) << store_orders[i].time
               << left << setw_u8(20, store_orders[i].seller_id) << store_orders[i].seller_id << endl;
        }
      }
      cout
          << "*************************************************************************************************************************************"
          << endl;
      cout << endl;
    }
    else{
      cout << "********************************" << endl;
      cout << "您还没有订单哦！快去购买一些商品吧！" << endl;
      cout << "********************************" << endl;
    }
    ofstream ofs("/Users/huwenjing/project01/commands.txt",ios::app);
    ofs << sql_date() << instruction << endl;
    ofs.close();
  }
}

void search_buyer(string instruction) {
  if(instruction.find("名称") != string::npos){ //查找在售商品
    int point_I = instruction.find("I");
    string this_name = instruction.substr(point_I+4);

    int len  = store_goods.size();
    bool res = false;
    bool is_alive = false;
    for(int i = 0; i < len; i++){
      if(store_goods[i].good_name.find(this_name) != string::npos){
        res = true;
        if(store_goods[i].condition == "销售中"){
          is_alive = true;
          break;
        }
      }
    }

    if(res){
      if(is_alive) {
        cout
            << "*************************************************************************************************************************************"
            << endl;
        cout << left << setw_u8(20, "商品ID") << "商品ID"
             << left << setw_u8(20, "名称") << "名称"
             << left << setw_u8(20, "价格") << "价格"
             << left << setw_u8(20, "上架时间") << "上架时间"
             << left << setw_u8(20, "卖家ID") << "卖家ID"
             << left << setw_u8(20, "数量") << "数量" << endl;
        for (int i = 0; i < len; i++) {
          if (store_goods[i].condition == "销售中") {
            cout << left << setw_u8(20, store_goods[i].good_id) << store_goods[i].good_id
                 << left << setw_u8(20, store_goods[i].good_name) << store_goods[i].good_name
                 << left << setw_u8(20, store_goods[i].good_price) << store_goods[i].good_price
                 << left << setw_u8(20, store_goods[i].time) << store_goods[i].time
                 << left << setw_u8(20, store_goods[i].seller_id) << store_goods[i].seller_id
                 << left << setw_u8(20, store_goods[i].stock) << store_goods[i].stock << endl;
          }
        }
        cout
            << "*************************************************************************************************************************************"
            << endl;
        cout << endl;
      }
      else{
        cout << "******************************" << endl;
        cout << "您想要的商品已下架！返回初始界面" << endl;
        cout << "******************************" << endl;
      }
    }
    else{
      cout << "******************************" << endl;
      cout << "没有找到您想要的商品！返回初始界面" << endl;
      cout << "******************************" << endl;
    }
  }
  else{ //查看商品详情
    int point_A = instruction.find("A");
    string this_good_id = instruction.substr(point_A+5);

    int len  = store_goods.size();
    bool res = false;
    bool is_alive = false;
    int i;
    for(i = 0; i < len; i++){
      if(store_goods[i].good_id == this_good_id){
        res = true;
        if(store_goods[i].condition == "销售中"){
          is_alive = true;
        }
        break;
      }
    }

    if(res){
      if(is_alive) {
        cout << "*********************************" << endl;
        cout << "商品ID：" << store_goods[i].good_id << endl;
        cout << "商品名称：" << store_goods[i].good_name << endl;
        cout << "商品价格：" << store_goods[i].good_price << endl;
        cout << "上架时间：" << store_goods[i].time << endl;
        cout << "商品描述：" << store_goods[i].information << endl;
        cout << "商品卖家：" << store_goods[i].seller_id << endl;
        cout << "*********************************" << endl;
      }
      else{
        cout << "****************************" << endl;
        cout << "该商品不在销售中！返回初始界面" << endl;
        cout << "****************************" << endl;
      }
    }
    else{
      cout << "************************" << endl;
      cout << "不存在该商品！返回初始界面" << endl;
      cout << "************************" << endl;
    }
  }
  ofstream ofs("/Users/huwenjing/project01/commands.txt",ios::app);
  ofs << sql_date() << instruction << endl;
  ofs.close();
}

void insert_buyer(string instruction, User& user) {
  //修改订单vector及文件
  int p1 = instruction.find('(');
  string ins1 = instruction.substr(p1+1);
  int p2 = ins1.find(',');
  string ins2 = ins1.substr(p2+1);
  string this_order_id = ins1.erase(p2);
  int p3 = ins2.find(',');
  string ins3 = ins2.substr(p3+1);
  string this_good_id = ins2.erase(p3);
  int p4 = ins3.find(',');
  string ins4 = ins3.substr(p4+1);
  string this_good_price = ins3.erase(p4);
  int p5 = ins4.find(',');
  string ins5 = ins4.substr(p5+1);
  string this_order_amount = ins4.erase(p5);
  int p6 = ins5.find(',');
  string ins6 = ins5.substr(p6+1);
  string this_order_time = ins5.erase(p6);
  int p7 = ins6.find(',');
  string this_buyer_id = ins6.substr(p7+1, 4);
  string this_seller_id = ins6.erase(p7);
  order this_order;
  this_order.order_id = this_order_id;
  this_order.good_id = this_good_id;
  this_order.per_price = this_good_price;
  this_order.amount = this_order_amount;
  this_order.time = this_order_time;
  this_order.seller_id = this_seller_id;
  this_order.buyer_id = this_buyer_id;
  store_orders.push_back(this_order);
  write_orders();

  //修改user.money，包括买家、卖家
  string buyer_rest;
  string buyer_notation;
  buyer_notation = user.money+"-"+this_order_amount+"*"+this_good_price;
  buyer_rest = calculator(buyer_notation);
  user.money = buyer_rest;
  int len = store_users.size();
  for(int i = 0; i < len; i++){
    if(store_users[i].user_id == user.id){
      store_users[i].money = buyer_rest;
      break;
    }
  }

  string seller_rest;
  string seller_notation;
  for(int i = 0 ; i < len; i++){
    if(store_users[i].user_id == this_seller_id){
      string seller_rest;
      string seller_notation;
      seller_notation = store_users[i].money+"+"+this_order_amount+"*"+this_good_price;
      seller_rest = calculator(seller_notation);
      store_users[i].money = seller_rest;
      break;
    }
  }
  write_users();

  //输出交易提醒
  cout << "********************" << endl;
  cout << "交易提醒！" << endl;
  cout << "交易时间：" << this_order_time << endl;
  cout << "交易单价：" << this_good_price << endl;
  cout << "交易数量：" << this_order_amount << endl;
  cout << "交易状态：交易成功" << endl;
  cout << "您的余额：" << user.money << endl;
  cout << "********************" << endl;

  //写入命令
  ofstream ofs("/Users/huwenjing/project01/commands.txt",ios::app);
  ofs << sql_date() << instruction << endl;
  ofs.close();
}

void update_buyer(string instruction, User& user){ //两种指令，一种下架，一种更新商品数量
  if(instruction.find("商品状态") != string::npos){ //下架商品
    int p = instruction.find('M');
    string this_good_id = instruction.substr(p);
    int len = store_goods.size();
    for(int i = 0; i < len; i++){
      if(store_goods[i].good_id == this_good_id){
        store_goods[i].condition = "已下架";
        break;
      }
    }
    write_goods();

    //更新购物车中的商品信息
    int cart_len = store_cart.size();
    for(int i = 0; i < cart_len; i++){
      int this_len = store_cart[i].shoppingCart.size();
      for(int j = 0; j < this_len; j++){
        if(store_cart[i].shoppingCart[j].good_id == this_good_id){
          store_cart[i].shoppingCart[j].condition = "已下架";
        }
      }
    }
    write_cart();
  }
  else{ //更新商品数量
    int p1 = instruction.find('=');
    string ins1 = instruction.substr(p1+2);
    int p2 = ins1.find(' ');
    string ins2 = ins1.substr(p2+1);
    string this_rest_stock = ins1.erase(p2);
    int p3 = ins2.find('M');
    string this_good_id = ins2.substr(p3);
    int len = store_goods.size();
    for(int i = 0; i < len; i++){
      if(store_goods[i].good_id == this_good_id){
        store_goods[i].stock = this_rest_stock;
        break;
      }
    }
    write_goods();
  }

  //写入命令
  ofstream ofs("/Users/huwenjing/project01/commands.txt",ios::app);
  ofs << sql_date() << instruction << endl;
  ofs.close();
}

void select_seller(string instruction, User& user) {
  if(instruction.find("commodity") != string::npos){
    int len  = store_goods.size();
    bool res = false;
    for(int i = 0; i < len; i++) {
      if (store_goods[i].seller_id == user.id) {
        res = true;
        break;
      }
    }

    if(res) {
      cout
          << "*************************************************************************************************************************************"
          << endl;
      cout << left << setw_u8(20, "商品ID") << "商品ID"
           << left << setw_u8(20, "名称") << "名称"
           << left << setw_u8(20, "价格") << "价格"
           << left << setw_u8(20, "数量") << "数量"
           << left << setw_u8(20, "上架时间") << "上架时间"
           << left << setw_u8(20, "商品状态") << "商品状态" << endl;

      for (int i = 0; i < len; i++) {
        if (store_goods[i].seller_id == user.id) {
          cout << left << setw_u8(20, store_goods[i].good_id) << store_goods[i].good_id
               << left << setw_u8(20, store_goods[i].good_name) << store_goods[i].good_name
               << left << setw_u8(20, store_goods[i].good_price) << store_goods[i].good_price
               << left << setw_u8(20, store_goods[i].stock) << store_goods[i].stock
               << left << setw_u8(20, store_goods[i].time) << store_goods[i].time
               << left << setw_u8(20, store_goods[i].condition) << store_goods[i].condition << endl;
        }
      }
      cout
          << "*************************************************************************************************************************************"
          << endl;
      cout << endl;
    }
    else{
      cout << "**********************************" << endl;
      cout << "您还没有发布过商品哦！快去发布商品吧！" << endl;
      cout << "**********************************" << endl;
    }
    ofstream ofs("/Users/huwenjing/project01/commands.txt",ios::app);
    ofs << sql_date() << instruction << endl;
    ofs.close();
  }
  else{ //order
    int len = store_orders.size();
    bool res = false;
    for(int i = 0; i < len; i++){
      if(store_orders[i].seller_id == user.id) {
        res = true;
        break;
      }
    }

    if(res) {
      cout
          << "*************************************************************************************************************************************"
          << endl;
      cout << left << setw_u8(20, "订单ID") << "订单ID"
           << left << setw_u8(20, "商品ID") << "商品ID"
           << left << setw_u8(20, "交易单价") << "交易单价"
           << left << setw_u8(20, "数量") << "数量"
           << left << setw_u8(20, "交易时间") << "交易时间"
           << left << setw_u8(20, "买家ID") << "买家ID" << endl;

      for (int i = 0; i < len; i++) {
        if (store_orders[i].seller_id == user.id) {
          cout << left << setw_u8(20, store_orders[i].order_id) << store_orders[i].order_id
               << left << setw_u8(20, store_orders[i].good_id) << store_orders[i].good_id
               << left << setw_u8(20, store_orders[i].per_price) << store_orders[i].per_price
               << left << setw_u8(20, store_orders[i].amount) << store_orders[i].amount
               << left << setw_u8(20, store_orders[i].time) << store_orders[i].time
               << left << setw_u8(20, store_orders[i].buyer_id) << store_orders[i].buyer_id << endl;
        }
      }
      cout
          << "*************************************************************************************************************************************"
          << endl;
      cout << endl;
    }
    else{
      cout << "*********************" << endl;
      cout << "您还没有历史出售订单哦！" << endl;
      cout << "*********************" << endl;
    }
    ofstream ofs("/Users/huwenjing/project01/commands.txt",ios::app);
    ofs << sql_date() << instruction << endl;
    ofs.close();
  }
}

void insert_seller(string instruction, User& user){
  //上架商品
  string this_name;
  string this_price;
  string this_stock;
  string this_information;
  string copy = instruction;
  int p1 = instruction.find('(');
  instruction = instruction.substr(p1+1);
  int p2 = instruction.find(',');
  string without_name = instruction.substr(p2+1);
  this_name = instruction.erase(p2);
  int p3 = without_name.find(',');
  string without_price = without_name.substr(p3+1);
  this_price = without_name.erase(p3);
  int p4 = without_price.find(',');
  string without_stock = without_price.substr(p4+1);
  this_stock = without_price.erase(p4);
  int p5 = without_stock.find(')');
  this_information = without_stock.erase(p5);
  int len = store_goods.size();

  string new_good_id;
  if(len==0){
    new_good_id = "M001";
  }
  else {
    string last_good_id = store_goods[len - 1].good_id.substr(1);
    int pre = stoi(last_good_id);
    pre++;
    stringstream ss;
    ss << pre;
    ss >> new_good_id;
    while (new_good_id.size() < 3) {
      new_good_id = "0" + new_good_id;
    }
    new_good_id = "M" + new_good_id;
  }
  commodity this_good;
  this_good.good_id = new_good_id;
  this_good.good_name = this_name;
  this_good.good_price = this_price;
  this_good.stock = this_stock;
  this_good.information = this_information;
  this_good.seller_id = user.id;
  this_good.time = date();
  this_good.condition = "销售中";
  store_goods.push_back(this_good);
  write_goods();

  ofstream ofs("/Users/huwenjing/project01/commands.txt",ios::app);
  ofs << sql_date() << copy << endl;
  ofs.close();
}

void update_seller(string instruction, User& user){
  if(instruction.find("商品状态") != string::npos){
    int p = instruction.find('M');
    string this_good_id = instruction.substr(p);
    int len = store_goods.size();
    for(int i = 0; i < len; i++){
      if(store_goods[i].good_id == this_good_id){
        store_goods[i].condition = "已下架";
        break;
      }
    }
    write_goods();

    //更新购物车中的商品信息
    int cart_len = store_cart.size();
    for(int i = 0; i < cart_len; i++){
      int this_len = store_cart[i].shoppingCart.size();
      for(int j = 0; j < this_len; j++){
        if(store_cart[i].shoppingCart[j].good_id == this_good_id){
          store_cart[i].shoppingCart[j].condition = "已下架";
        }
      }
    }
    write_cart();
  }
  else{
    if(instruction.find("价格") != string::npos){
      int p1 = instruction.find('=');
      string this_good_price = instruction.substr(p1+2);
      int p2 = this_good_price.find(' ');
      this_good_price.erase(p2);
      int p = instruction.find('M');
      string this_good_id = instruction.substr(p);
      int len = store_goods.size();
      for(int i = 0; i < len; i++){
        if(store_goods[i].good_id == this_good_id){
          store_goods[i].good_price = this_good_price;
          break;
        }
      }
      write_goods();
    }
    else{
      int p1 = instruction.find('=');
      string this_information = instruction.substr(p1+2);
      int p2 = this_information.find(' ');
      this_information.erase(p2);
      int p = instruction.find('M');
      string this_good_id = instruction.substr(p);
      int len = store_goods.size();
      for(int i = 0; i < len; i++){
        if(store_goods[i].good_id == this_good_id){
          store_goods[i].information = this_information;
          break;
        }
      }
      write_goods();
    }
  }

  ofstream ofs("/Users/huwenjing/project01/commands.txt",ios::app);
  ofs << sql_date() << instruction << endl;
  ofs.close();
}
