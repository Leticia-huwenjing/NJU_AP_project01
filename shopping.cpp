//
// Created by 胡文菁 on 2022/3/20.
//

#include "shopping.h"

void Cart::cart_menu() {
  cout << "===========================================================" << endl;
  cout << "1.查看商品 2.加入商品 3.移出商品 4.购买全部商品 5.退出我的购物车" << endl;
  cout << "===========================================================" << endl;
  cout << endl;
  cout << "请输入操作：";
}

void Cart::add_cart(User &user) {
  cout << "请输入想加入购物车的商品ID：";
  string this_good_id;
  getline(cin, this_good_id);
  if(this_good_id.find(' ') != string::npos){
    cout << "***************" << endl;
    cout << "您的输入不合法！" << endl;
    cout << "***************" << endl << endl;
    return ;
  }

  //收拾离谱买家
  bool res = true;
  int i;
  if(this_good_id.size() != 4 || this_good_id[0] != 'M' || !(this_good_id[1] >= '0' && this_good_id[1] <= '9'
      && this_good_id[2] >= '0' && this_good_id[2] <= '9' && this_good_id[3] >= '0' && this_good_id[3] <= '9')){
    res = false;
    cout << "***************" << endl;
    cout << "您的输入不合法！" << endl;
    cout << "***************" << endl;
    return ;
  }

    //处理商品id不存在或已下架
  else{
    bool is_alive = false;
    int len = store_goods.size();
    for(i = 0; i < len; i++){
      if(store_goods[i].good_id == this_good_id){
        if(store_goods[i].condition == "销售中"){
          is_alive = true;
        }
        break;
      }
    }
    if(!is_alive){
      res = false;
      cout << "*******************" << endl;
      cout << "商品不存在或已下架！" << endl;
      cout << "*******************" << endl;
      return ;
    }
  }

  if(store_goods[i].seller_id == user.id){
    res = false;
    cout << "*******************************" << endl;
    cout << "您不可以将自己发布的商品加入购物车！" << endl;
    cout << "*******************************" << endl;
    return ;
  }
  if(res) {
    cout << "请输入数量：";
    string this_good_amount;
    getline(cin, this_good_amount);
    if (this_good_amount.find(' ') != string::npos) {
      cout << "***************" << endl;
      cout << "您的输入不合法！" << endl;
      cout << "***************" << endl << endl;
      return;
    }

    int size = this_good_amount.size();
    bool is_amount_valid = true;
    for (int j = 0; j < size; j++) {
      if (!(this_good_amount[j] >= '0' && this_good_amount[j] <= '9')) {
        is_amount_valid = false;
        cout << "***************" << endl;
        cout << "您的输入不合法！" << endl;
        cout << "***************" << endl;
        return;
      }
    }
    if (is_amount_valid) {
      bool all_zero = true;
      for (int j = 0; j < size; j++) {
        if (this_good_amount[j] != '0') {
          all_zero = false;
          break;
        }
      }
      if (all_zero) {
        is_amount_valid = false;
        cout << "***************" << endl;
        cout << "您的输入不合法！" << endl;
        cout << "***************" << endl;
        return;
      }
    }

    if(is_amount_valid) {
      int amount = stoi(this_good_amount);
      int this_stock = stoi(store_goods[i].stock);

      if (amount > this_stock) {
        cout << "***********" << endl;
        cout << "库存量不足！" << endl;
        cout << "***********" << endl;
        return;
      }
      else{
        commodity this_good;
        this_good.good_id = this_good_id;
        this_good.stock = this_good_amount;
        this_good.condition = "销售中";
        int len = store_cart.size();
        bool is_have_cart = false;
        for(int m = 0; m < len; m++){
          if(store_cart[m].user_id == user.id){
            is_have_cart = true;
            store_cart[m].shoppingCart.push_back(this_good);
            cout << "加入成功！" << endl;
            cout << "******************************" << endl;
            cout << "商品ID：" << this_good_id << endl;
            cout << "商品名称：" << store_goods[i].good_name << endl;
            cout << "商品价格：" << store_goods[i].good_price << endl;
            cout << "商品数量：" << this_good_amount << endl;
            cout << "商品描述：" << store_goods[i].information << endl;
            cout << "******************************" << endl;
            break;
          }
        }
        if(!is_have_cart){
          cart this_cart;
          this_cart.user_id = user.id;
          this_cart.shoppingCart.push_back(this_good);
          store_cart.push_back(this_cart);
          cout << "加入成功！" << endl;
          cout << "******************************" << endl;
          cout << "商品ID：" << this_good_id << endl;
          cout << "商品名称：" << store_goods[i].good_name << endl;
          cout << "商品价格：" << store_goods[i].good_price << endl;
          cout << "商品数量：" << this_good_amount << endl;
          cout << "商品描述：" << store_goods[i].information << endl;
          cout << "******************************" << endl;
        }
      }
    }
  }
  write_cart();
}

void Cart::rm_cart(User &user) {
  cout << "请输入想移出购物车的商品ID：";
  string this_good_id;
  getline(cin, this_good_id);

  if(this_good_id.find(' ') != string::npos){
    cout << "***************" << endl;
    cout << "您的输入不合法！" << endl;
    cout << "***************" << endl << endl;
    return ;
  }

  string this_good_amount;
  //收拾离谱用户
  bool res = true;
  int i, j, k;
  if(this_good_id.size() != 4 || this_good_id[0] != 'M' || !(this_good_id[1] >= '0' && this_good_id[1] <= '9'
      && this_good_id[2] >= '0' && this_good_id[2] <= '9' && this_good_id[3] >= '0' && this_good_id[3] <= '9')){
    res = false;
    cout << "***************" << endl;
    cout << "您的输入不合法！" << endl;
    cout << "***************" << endl;
  }

  //处理商品id不存在或不在购物车中
  else{
    bool is_alive = false;
    int len = store_goods.size();
    for(i = 0; i < len; i++){
      if(store_goods[i].good_id == this_good_id){
        int cart_len = store_cart.size();
        for(j = 0; cart_len; j++){
          if(store_cart[j].user_id == user.id){
            for(k = 0; k < store_cart[j].shoppingCart.size(); k++){
              if(store_cart[j].shoppingCart[k].good_id == this_good_id){
                is_alive = true;
                this_good_amount = store_cart[j].shoppingCart[k].stock;
                break;
              }
            }
            break;
          }
        }
        break;
      }
    }

    if(!is_alive){
      res = false;
      cout << "******************************" << endl;
      cout << "商品不存在/不在您的购物车中" << endl;
      cout << "******************************" << endl;
    }
  }
  if(res){
    cout << "确认要将该商品移出购物车吗？" << endl;
    cout << "******************************" << endl;
    cout << "商品ID：" << this_good_id << endl;
    cout << "商品名称：" << store_goods[i].good_name << endl;
    cout << "商品价格：" << store_goods[i].good_price << endl;
    cout << "商品数量：" << this_good_amount << endl;
    cout << "商品描述：" << store_goods[i].information << endl;
    cout << "******************************" << endl;
    cout << "请选择是否移出购物车(y/n)";
    char opt;
    cin >> opt;
    while(!cin || getchar()!='\n' || (opt !='y' && opt != 'n')){
      cout <<"输入不合法！请重新输入：";
      cin.clear();
      cin >> opt;
    }
    if(opt == 'n'){
      cout << "取消移出" << endl;
    }
    else{
      cout << "成功移出！" << endl;
      store_cart[j].shoppingCart.erase(store_cart[j].shoppingCart.begin()+k);
      write_cart();
    }
  }
}

void Cart::buy_all(User &user, Buyer &buyer) {
  double all_money=0;
  int alive_amount=0;
  int die_amount=0;
  cout << "您购物车中的商品如下：" << endl;
  cout << "***********************************************************************************************" << endl;
  cout << left << setw_u8(20, "商品ID") << "商品ID"
       << left << setw_u8(20, "名称")  << "名称"
       << left << setw_u8(20, "价格") << "价格"
       << left << setw_u8(20, "数量") << "数量"
       << left << setw_u8(20, "商品状态") << "商品状态"
       << endl;

  int len = store_cart.size();
  for(int i = 0; i < len; i++){
    if(store_cart[i].user_id == user.id){
      int cart_len = store_cart[i].shoppingCart.size();
      for(int j = 0; j < cart_len; j++){
        int good_len = store_goods.size();
        for(int k = 0; k < good_len; k++){
          if(store_goods[k].good_id == store_cart[i].shoppingCart[j].good_id){
            cout << left << setw_u8(20, store_goods[k].good_id) << store_goods[k].good_id
                 << left << setw_u8(20, store_goods[k].good_name) << store_goods[k].good_name
                 << left << setw_u8(20, store_goods[k].good_price) << store_goods[k].good_price
                 << left << setw_u8(20, store_cart[i].shoppingCart[j].stock) << store_cart[i].shoppingCart[j].stock
                 << left << setw_u8(20, store_goods[k].condition) << store_goods[k].condition
                 << endl;
            if(store_goods[k].condition != "已下架") {
              if(stoi(store_goods[k].stock) >= stoi(store_cart[i].shoppingCart[j].stock)) {
                all_money += stod(store_goods[k].good_price) * stod(store_cart[i].shoppingCart[j].stock);
                alive_amount++;
              }
              else{
                die_amount++;
              }
            }
            else{
              die_amount++;
            }
            break;
          }
        }
      }
      break;
    }
  }
  cout << "***********************************************************************************************" << endl;
  cout << endl;
  string money_amount = to_string(all_money);
  if(money_amount.find('.') != string::npos){
    int p = money_amount.find('.');
    if(p+2 <= money_amount.size()-1) {
      money_amount = money_amount.erase(p + 2);
    }
  }
  if(alive_amount == 0){
    cout << "您的购物车中尚无正在销售的商品！" << endl;
    cout << endl;
    return ;
  }
  cout << "您的购物车中共有" << alive_amount+die_amount << "件商品，" << endl;
  cout << "其中有" << alive_amount << "件商品正在销售，" << endl;
  cout << "有" << die_amount << "件商品已失效" << endl;
  cout << "总金额为：" << money_amount << endl;
  cout << "友情提示：购买后会自动删除购物车中商品！" << endl;
  cout << "请选择是否全部购买(y/n)";
  char opt;
  cin >> opt;
  while(!cin || getchar()!='\n' || (opt !='y' && opt != 'n')){
    cout <<"输入不合法！请重新输入：";
    cin.clear();
    cin >> opt;
  }
  if(opt == 'n'){
    cout << "取消购买" << endl;
  }
  else {
    if(all_money > stod(user.money)){
      cout << "您的余额不足！" << endl;
    }
    else{
      cout << "购买成功！" << endl;
      for(int i = 0; i < len; i++){
        if(store_cart[i].user_id == user.id){
          int cart_len = store_cart[i].shoppingCart.size();
          for(int j = 0; j < cart_len; j++){
            int good_len = store_goods.size();
            for(int k = 0; k < good_len; k++){
              if(store_goods[k].good_id == store_cart[i].shoppingCart[j].good_id){
                if(store_goods[k].condition != "已下架") {
                  if(stoi(store_goods[k].stock) == stoi(store_cart[i].shoppingCart[j].stock)) {
                    string this_order_id;
                    int length = store_orders.size();
                    string last_order_id;
                    if(length == 0){
                      this_order_id = "T001";
                    }
                    else {
                      last_order_id = store_orders[length - 1].order_id;
                      last_order_id = last_order_id.substr(1);
                      int last_order = stoi(last_order_id);
                      last_order++;
                      this_order_id = to_string(last_order);
                      while (this_order_id.size() < 3) {
                        this_order_id = "0" + this_order_id;
                      }
                      this_order_id = "T" + this_order_id; //当前订单id
                    }
                    string manipulator = "buyer";
                    string instruction1 = "INSERT INTO order VALUES (";
                    instruction1 = instruction1+this_order_id+","+store_goods[k].good_id+","+store_goods[k].good_price+","+store_cart[i].shoppingCart[j].stock+","+date()+","+store_goods[k].seller_id+","+user.id+")";
                    mysql(instruction1, manipulator, user);

                    string instruction2 = "UPDATE commodity SET 数量 = ";
                    instruction2 = instruction2+"0"+" WHERE 商品ID = "+store_goods[k].good_id;
                    mysql(instruction2, manipulator, user);

                    string instruction3 = "UPDATE commodity SET 商品状态 = 已下架 WHERE 商品ID = ";
                    instruction3.append(store_goods[k].good_id);
                    mysql(instruction3, manipulator, user);
                  }
                  else if(stoi(store_goods[k].stock) > stoi(store_cart[i].shoppingCart[j].stock)){
                    string this_order_id;
                    int length = store_orders.size();
                    string last_order_id;
                    if(length == 0){
                      this_order_id = "T001";
                    }
                    else {
                      last_order_id = store_orders[length - 1].order_id;
                      last_order_id = last_order_id.substr(1);
                      int last_order = stoi(last_order_id);
                      last_order++;
                      this_order_id = to_string(last_order);
                      while (this_order_id.size() < 3) {
                        this_order_id = "0" + this_order_id;
                      }
                      this_order_id = "T" + this_order_id; //当前订单id
                      string manipulator = "buyer";
                      string instruction1 = "INSERT INTO order VALUES (";
                      instruction1 = instruction1+this_order_id+","+store_goods[k].good_id+","+store_goods[k].good_price+","+store_cart[i].shoppingCart[j].stock+","+date()+","+store_goods[k].seller_id+","+user.id+")";
                      mysql(instruction1, manipulator, user);

                      string instruction2 = "UPDATE commodity SET 数量 = ";
                      instruction2 = instruction2+"0"+" WHERE 商品ID = "+store_goods[k].good_id;
                      mysql(instruction2, manipulator, user);
                    }
                  }
                }
                break;
              }
            }
          }
          break;
        }
      }
      for(int i = 0; i < len; i++){
        if(store_cart[i].user_id == user.id){
          store_cart[i].shoppingCart.clear();
          break;
        }
      }
      write_cart();
    }
  }
  cout << endl;
}

void Cart::see_cart(User &user) {
  cout << "您购物车中的商品如下：" << endl;
  cout << "***********************************************************************************************" << endl;
  cout << left << setw_u8(20, "商品ID") << "商品ID"
        << left << setw_u8(20, "名称")  << "名称"
        << left << setw_u8(20, "价格") << "价格"
        << left << setw_u8(20, "数量") << "数量"
        << left << setw_u8(20, "商品状态") << "商品状态"
        << endl;

  int len = store_cart.size();
  for(int i = 0; i < len; i++){
    if(store_cart[i].user_id == user.id){
      int cart_len = store_cart[i].shoppingCart.size();
      for(int j = 0; j < cart_len; j++){
        int good_len = store_goods.size();
        for(int k = 0; k < good_len; k++){
          if(store_goods[k].good_id == store_cart[i].shoppingCart[j].good_id){
            cout << left << setw_u8(20, store_goods[k].good_id) << store_goods[k].good_id
                << left << setw_u8(20, store_goods[k].good_name) << store_goods[k].good_name
                << left << setw_u8(20, store_goods[k].good_price) << store_goods[k].good_price
                << left << setw_u8(20, store_cart[i].shoppingCart[j].stock) << store_cart[i].shoppingCart[j].stock
                << left << setw_u8(20, store_goods[k].condition) << store_goods[k].condition
                << endl;
            break;
          }
        }
      }
      break;
    }
  }
  cout << "***********************************************************************************************" << endl;
  cout << endl;
}