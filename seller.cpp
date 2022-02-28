//
// Created by 胡文菁 on 2022/2/19.
//

#include "seller.h"
void Seller::menu() {
  cout << "========================================================================" << endl;
  cout << "1.发布商品 2.查看发布商品 3.修改商品信息 4.下架商品 5.查看历史订单 6.返回用户主界面" << endl;
  cout << "========================================================================" << endl;
  cout << endl;
  cout << "请输入操作：";
}

void Seller::view_goods(User &user) {
  string manipulator = "seller";
  string instruction = "SELECT * FROM commodity";
  mysql(instruction, manipulator, user);
}

void Seller::remove_good(User &user) {
  ;
}

void Seller::view_orders(User &user) {
  string manipulator = "seller";
  string instruction = "SELECT * FROM order";
  mysql(instruction, manipulator, user);
}

void Seller::sell_good(User &user) {
  string this_good_name;
  cout << "请输入商品名称：";
  cin >> this_good_name;
  string this_good_price;
  cout << "请输入商品价格：";
  cin >> this_good_price;
  string this_good_stock;
  cout << "请输入商品数量：";
  cin >> this_good_stock;
  string this_good_information;
  cout << "请输入商品描述：";
  cin >> this_good_information;
  cout << endl;

  //判断用户输入是否合法
  bool res = true;
  //判断价格是否为大于0的一位小数
  int len_price = this_good_price.size();
  int point_dot = this_good_price.find('.');
  if(len_price-point_dot > 2){
    res = false;
  }
  else{
    for(int i = 0; i < point_dot; i++){
      if(!(this_good_price[i] >= '0' && this_good_price[i] <= '9')){
        res = false;
        break;
      }
    }
    if(!(this_good_price[point_dot+1] >= '0' && this_good_price[point_dot+1] <= '9')){
      res = false;
    }

    bool all_zero = true;
    if(res) {
      for (int i = 0; i < point_dot; i++) {
        if(this_good_price[i] != '0'){
          all_zero = false;
          break;
        }
      }
      if(this_good_price[point_dot+1] != '0'){
        all_zero = false;
      }
    }

    if(all_zero){
      res = false;
    }
  }
  //判断数量是否为大于0的整数
  int len_stock = this_good_stock.size();
  for(int i = 0; i < len_stock; i++){
    if(!(this_good_stock[i] >= '0' && this_good_stock[i] <= '9')){
      res = false;
      break;
    }
  }
  bool is_zero = true;
  for(int i = 0; i < len_stock; i++){
    if(this_good_stock[i] != '0'){
      is_zero = false;
    }
  }
  if(is_zero){
    res = true;
  }

  //如果res合法，则生成指令
  if(!res){
    cout << "*******************" << endl;
    cout << "价格/数量输入不合法！" << endl;
    cout << "*******************" << endl;
  }
  else{
    cout << "请确认发布的商品信息无误！" << endl;
    cout << "***************************************" << endl;
    cout << "商品名称：" << this_good_name << endl;
    cout << "商品价格：" << this_good_price << endl;
    cout << "商品数量：" << this_good_stock << endl;
    cout << "商品描述：" << this_good_information << endl;
    cout << "***************************************" << endl;
    cout << endl;
    cout << "你确认要发布商品吗？(y/n)";

    //处理用户离谱输入
    char opt;
    cin >> opt;
    while(!cin || getchar()!='\n' || (opt !='y' && opt != 'n')){
      cout <<"输入不合法！请重新输入：";
      cin.clear();
      while(getchar()!='\n');
      cin >> opt;
    }

    //选择是否生成指令
    if(opt == 'n'){
      cout << "取消商品发布！" << endl;
    }
    else{
      cout << "发布商品成功！" << endl;
      string manipulator = "seller";
      string instruction = "INSERT INTO commodity VALUES (";
      instruction = instruction+this_good_name+","+this_good_price+","+this_good_stock+","+this_good_information+")";
      mysql(instruction, manipulator, user);
    }
  }
  cout << endl;
}

void Seller::change_good(User &user) {
  ;
}