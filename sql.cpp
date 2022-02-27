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
    cout << "*************************************************************************************************************************************" << endl;
    cout << left << setw_u8(20, "商品ID") << "商品ID"
         << left << setw_u8(20, "名称")  << "名称"
         << left << setw_u8(20,"价格") << "价格"
         << left << setw_u8(20, "上架时间") << "上架时间"
         << left << setw_u8(20, "卖家ID") << "卖家ID"
         << left << setw_u8(20, "数量") << "数量"
         << left << setw_u8(20, "商品状态") << "商品状态" << endl;
    int len  = store_goods.size();
    for(int i = 0; i < len; i++){
      cout << left << setw_u8(20, store_goods[i].good_id) << store_goods[i].good_id
           << left << setw_u8(20, store_goods[i].good_name)  << store_goods[i].good_name
           << left << setw_u8(20,store_goods[i].good_price) << store_goods[i].good_price
           << left << setw_u8(20, store_goods[i].time) << store_goods[i].time
           << left << setw_u8(20, store_goods[i].seller_id) << store_goods[i].seller_id
           << left << setw_u8(20, store_goods[i].stock) << store_goods[i].stock
           << left << setw_u8(20, store_goods[i].condition) << store_goods[i].condition << endl;
    }
    cout << "*************************************************************************************************************************************" << endl;
    cout << endl;
    ofstream ofs("/Users/huwenjing/project01/commands.txt",ios::app);
    ofs << sql_date() << instruction << endl;
    ofs.close();
  }
  else if(instruction.find("order") != string::npos){
    cout << "*************************************************************************************************************************************" << endl;
    cout << left << setw_u8(20, "订单ID") << "订单ID"
         << left << setw_u8(20, "商品ID")  << "商品ID"
         << left << setw_u8(20,"交易单价") << "交易单价"
         << left << setw_u8(20, "数量") << "数量"
         << left << setw_u8(20, "交易时间") << "交易时间"
         << left << setw_u8(20, "卖家ID") << "卖家ID"
         << left << setw_u8(20, "买家ID") << "买家ID" << endl;
    int len = store_orders.size();
    for(int i = 0; i < len; i++){
      cout << left << setw_u8(20, store_orders[i].order_id) << store_orders[i].order_id
           << left << setw_u8(20, store_orders[i].good_id)  << store_orders[i].good_id
           << left << setw_u8(20,store_orders[i].per_price) << store_orders[i].per_price
           << left << setw_u8(20, store_orders[i].amount) << store_orders[i].amount
           << left << setw_u8(20, store_orders[i].time) << store_orders[i].time
           << left << setw_u8(20, store_orders[i].seller_id) << store_orders[i].seller_id
           << left << setw_u8(20, store_orders[i].buyer_id) << store_orders[i].buyer_id << endl;
    }
    cout << "*************************************************************************************************************************************" << endl;
    cout << endl;
    ofstream ofs("/Users/huwenjing/project01/commands.txt",ios::app);
    ofs << sql_date() << instruction << endl;
    ofs.close();
  }
  else{
    cout << "*************************************************************************************************************************************" << endl;
    cout << left << setw_u8(20, "用户ID") << "用户ID"
         << left << setw_u8(20, "用户名")  << "用户名"
         << left << setw_u8(20,"联系方式") << "联系方式"
         << left << setw_u8(20, "地址") << "地址"
         << left << setw_u8(20, "钱包余额") << "钱包余额"
         << left << setw_u8(20, "用户状态") << "用户状态" << endl;
    int len = store_users.size();
    for(int i = 0; i < len; i++){
      cout << left << setw_u8(20, store_users[i].user_id) << store_users[i].user_id
           << left << setw_u8(20, store_users[i].user_name)  << store_users[i].user_name
           << left << setw_u8(20,store_users[i].tel) << store_users[i].tel
           << left << setw_u8(20, store_users[i].address) << store_users[i].address
           << left << setw_u8(20, store_users[i].money) << store_users[i].money
           << left << setw_u8(20, store_users[i].condition) << store_users[i].condition << endl;
    }
    cout << "*************************************************************************************************************************************" << endl;
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
  ;
}

void update_user_admin(string instruction) {
  ;
}

void select_buyer(string instruction, User& user){
  if(instruction.find("commodity") != string::npos){
    cout << "*************************************************************************************************************************************" << endl;
    cout << left << setw_u8(20, "商品ID") << "商品ID"
         << left << setw_u8(20, "名称")  << "名称"
         << left << setw_u8(20,"价格") << "价格"
         << left << setw_u8(20, "上架时间") << "上架时间"
         << left << setw_u8(20, "卖家ID") << "卖家ID"
         << left << setw_u8(20, "数量") << "数量" << endl;
    int len  = store_goods.size();
    for(int i = 0; i < len; i++){
      if(store_goods[i].condition == "销售中") {
        cout << left << setw_u8(20, store_goods[i].good_id) << store_goods[i].good_id
             << left << setw_u8(20, store_goods[i].good_name) << store_goods[i].good_name
             << left << setw_u8(20, store_goods[i].good_price) << store_goods[i].good_price
             << left << setw_u8(20, store_goods[i].time) << store_goods[i].time
             << left << setw_u8(20, store_goods[i].seller_id) << store_goods[i].seller_id
             << left << setw_u8(20, store_goods[i].stock) << store_goods[i].stock << endl;
      }
    }
    cout << "*************************************************************************************************************************************" << endl;
    cout << endl;
    ofstream ofs("/Users/huwenjing/project01/commands.txt",ios::app);
    ofs << sql_date() << instruction << endl;
    ofs.close();
  }
  else{ //order
    cout << "*************************************************************************************************************************************" << endl;
    cout << left << setw_u8(20, "订单ID") << "订单ID"
         << left << setw_u8(20, "商品ID")  << "商品ID"
         << left << setw_u8(20,"交易单价") << "交易单价"
         << left << setw_u8(20, "数量") << "数量"
         << left << setw_u8(20, "交易时间") << "交易时间"
         << left << setw_u8(20, "卖家ID") << "卖家ID" << endl;
    int len = store_orders.size();
    for(int i = 0; i < len; i++){
      if(store_orders[i].buyer_id == user.id) {
        cout << left << setw_u8(20, store_orders[i].order_id) << store_orders[i].order_id
             << left << setw_u8(20, store_orders[i].good_id) << store_orders[i].good_id
             << left << setw_u8(20, store_orders[i].per_price) << store_orders[i].per_price
             << left << setw_u8(20, store_orders[i].amount) << store_orders[i].amount
             << left << setw_u8(20, store_orders[i].time) << store_orders[i].time
             << left << setw_u8(20, store_orders[i].seller_id) << store_orders[i].seller_id << endl;
      }
    }
    cout << "*************************************************************************************************************************************" << endl;
    cout << endl;
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
    for(int i = 0; i < len; i++){
      if(store_goods[i].good_name.find(this_name) != string::npos){
        res = true;
        break;
      }
    }
    if(res){
      cout << "*************************************************************************************************************************************" << endl;
      cout << left << setw_u8(20, "商品ID") << "商品ID"
           << left << setw_u8(20, "名称")  << "名称"
           << left << setw_u8(20,"价格") << "价格"
           << left << setw_u8(20, "上架时间") << "上架时间"
           << left << setw_u8(20, "卖家ID") << "卖家ID"
           << left << setw_u8(20, "数量") << "数量" << endl;
      int len  = store_goods.size();
      for(int i = 0; i < len; i++){
        if(store_goods[i].condition == "销售中") {
          cout << left << setw_u8(20, store_goods[i].good_id) << store_goods[i].good_id
               << left << setw_u8(20, store_goods[i].good_name) << store_goods[i].good_name
               << left << setw_u8(20, store_goods[i].good_price) << store_goods[i].good_price
               << left << setw_u8(20, store_goods[i].time) << store_goods[i].time
               << left << setw_u8(20, store_goods[i].seller_id) << store_goods[i].seller_id
               << left << setw_u8(20, store_goods[i].stock) << store_goods[i].stock << endl;
        }
      }
      cout << "*************************************************************************************************************************************" << endl;
      cout << endl;
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
    int i;
    for(i = 0; i < len; i++){
      if(store_goods[i].good_id == this_good_id){
        res = true;
        break;
      }
    }
    if(res){
      if(store_goods[i].condition == "销售中") {
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
        cout << "******************************" << endl;
        cout << "该商品不在销售中！返回初始界面" << endl;
        cout << "******************************" << endl;
      }
    }
    else{
      cout << "******************************" << endl;
      cout << "不存在该商品！返回初始界面" << endl;
      cout << "******************************" << endl;
    }
  }
  ofstream ofs("/Users/huwenjing/project01/commands.txt",ios::app);
  ofs << sql_date() << instruction << endl;
  ofs.close();
}

void insert_buyer(string instruction, User& user) {
  ;
}

void update_buyer(string instruction, User& user){
  ;
}

void select_seller(string instruction, User& user) {
  if(instruction.find("commodity") != string::npos){
    cout << "*************************************************************************************************************************************" << endl;
    cout << left << setw_u8(20, "商品ID") << "商品ID"
         << left << setw_u8(20, "名称")  << "名称"
         << left << setw_u8(20,"价格") << "价格"
         << left << setw_u8(20, "数量") << "数量"
         << left << setw_u8(20, "上架时间") << "上架时间"
         << left << setw_u8(20, "商品状态") << "商品状态" << endl;
    int len  = store_goods.size();
    for(int i = 0; i < len; i++){
      if(store_goods[i].seller_id == user.id) {
        cout << left << setw_u8(20, store_goods[i].good_id) << store_goods[i].good_id
             << left << setw_u8(20, store_goods[i].good_name) << store_goods[i].good_name
             << left << setw_u8(20, store_goods[i].good_price) << store_goods[i].good_price
             << left << setw_u8(20, store_goods[i].stock) << store_goods[i].stock
             << left << setw_u8(20, store_goods[i].time) << store_goods[i].time
             << left << setw_u8(20, store_goods[i].condition) << store_goods[i].condition << endl;
      }
    }
    cout << "*************************************************************************************************************************************" << endl;
    cout << endl;
    ofstream ofs("/Users/huwenjing/project01/commands.txt",ios::app);
    ofs << sql_date() << instruction << endl;
    ofs.close();
  }
  else{ //order
    cout << "*************************************************************************************************************************************" << endl;
    cout << left << setw_u8(20, "订单ID") << "订单ID"
         << left << setw_u8(20, "商品ID")  << "商品ID"
         << left << setw_u8(20,"交易单价") << "交易单价"
         << left << setw_u8(20, "数量") << "数量"
         << left << setw_u8(20, "交易时间") << "交易时间"
         << left << setw_u8(20, "买家ID") << "买家ID" << endl;
    int len = store_orders.size();
    for(int i = 0; i < len; i++){
      if(store_orders[i].seller_id == user.id) {
        cout << left << setw_u8(20, store_orders[i].order_id) << store_orders[i].order_id
             << left << setw_u8(20, store_orders[i].good_id) << store_orders[i].good_id
             << left << setw_u8(20, store_orders[i].per_price) << store_orders[i].per_price
             << left << setw_u8(20, store_orders[i].amount) << store_orders[i].amount
             << left << setw_u8(20, store_orders[i].time) << store_orders[i].time
             << left << setw_u8(20, store_orders[i].buyer_id) << store_orders[i].buyer_id << endl;
      }
    }
    cout << "*************************************************************************************************************************************" << endl;
    cout << endl;
    ofstream ofs("/Users/huwenjing/project01/commands.txt",ios::app);
    ofs << sql_date() << instruction << endl;
    ofs.close();
  }
}

void insert_seller(string instruction, User& user){
  ;
}

void update_seller(string instruction, User& user){
  ;
}







