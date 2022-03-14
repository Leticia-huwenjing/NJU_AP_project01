//
// Created by 胡文菁 on 2022/2/19.
//

#include "buyer.h"
void Buyer::menu() {
  cout << "=============================================================================" << endl;
  cout << "1.查看商品列表 2.购买商品 3.搜索商品 4.查看历史订单 5.查看商品详细信息 6.返回用户主界面" << endl;
  cout << "=============================================================================" << endl;
  cout << endl;
  cout << "请输入操作：";
}

void Buyer::view_goods(User &user) {
  string manipulator = "buyer";
  string instruction = "SELECT * FROM commodity";
  mysql(instruction, manipulator, user);
}

void Buyer::search_good(User &user) {
  string manipulator = "buyer";
  string instruction = "SELECT * FROM commodity WHERE 名称 CONTAINS ";
  cout << "请输入商品名称：";
  string this_name;
  getline(cin, this_name);
  if(this_name.find(' ') != string::npos){
    cout << "***************" << endl;
    cout << "您的输入不合法！";
    cout << "***************" << endl << endl;
    return ;
  }

  instruction.append(this_name);
  mysql(instruction, manipulator, user);
}

void Buyer::view_orders(User &user) {
  string manipulator = "buyer";
  string instruction = "SELECT * FROM order";
  mysql(instruction, manipulator, user);
}

void Buyer::buy_good(User &user) {
  cout << "请输入商品ID：";
  string this_good_id;
  getline(cin, this_good_id);
  if(this_good_id.find(' ') != string::npos){
    cout << "***************" << endl;
    cout << "您的输入不合法！";
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
    cout << "您的输入不合法！";
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
    cout << "**********************" << endl;
    cout << "您不可以购买自己发布的商品！" << endl;
    cout << "**********************" << endl;
    return ;
  }

  if(res){
    cout << "请输入数量：";
    string this_good_amount;
    getline(cin, this_good_amount);
    if(this_good_amount.find(' ') != string::npos){
      cout << "***************" << endl;
      cout << "您的输入不合法！";
      cout << "***************" << endl << endl;
      return ;
    }

    int size = this_good_amount.size();
    bool is_amount_valid = true;
    for(int j = 0; j < size; j++){
      if(!(this_good_amount[j] >= '0' && this_good_amount[j] <= '9')){
        is_amount_valid = false;
        cout << "***************" << endl;
        cout << "您的输入不合法！" << endl;
        cout << "***************" << endl;
        return ;
      }
    }
    if(is_amount_valid){
      bool all_zero = true;
      for(int j = 0; j < size; j++){
        if(this_good_amount[j] != '0'){
          all_zero = false;
          break;
        }
      }
      if(all_zero){
        is_amount_valid = false;
        cout << "***************" << endl;
        cout << "您的输入不合法！" << endl;
        cout << "***************" << endl;
        return ;
      }
    }
    //此时用户输入的商品ID以及购买数量是合法的
    if(is_amount_valid){
      int amount = stoi(this_good_amount);
      int this_stock = stoi(store_goods[i].stock);

      if(amount > this_stock){
        cout << "***********" << endl;
        cout << "库存量不足！" << endl;
        cout << "***********" << endl;
        return ;
      }

      else if(amount == this_stock){ //需要下架商品
        string notation = user.money+"-"+this_good_amount+"*"+store_goods[i].good_price;
        string rest_s = calculator(notation);
        double rest = stod(rest_s);
        if(rest < 0){
          cout << "**************" << endl;
          cout << "您的余额不足！" << endl;
          cout << "**************" << endl;
          return ;
        }
        else{ //生成三个指令
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
          instruction1 = instruction1+this_order_id+","+this_good_id+","+store_goods[i].good_price+","+this_good_amount+","+date()+","+store_goods[i].seller_id+","+user.id+")";
          mysql(instruction1, manipulator, user);

          string instruction2 = "UPDATE commodity SET 数量 = ";
          instruction2 = instruction2+"0"+" WHERE 商品ID = "+this_good_id;
          mysql(instruction2, manipulator, user);

          string instruction3 = "UPDATE commodity SET 商品状态 = 已下架 WHERE 商品ID = ";
          instruction3.append(this_good_id);
          mysql(instruction3, manipulator, user);
         }
      }

      else{ //不需要下架商品
        string notation = user.money+"-"+this_good_amount+"*"+store_goods[i].good_price;
        string rest_s = calculator(notation);
        double rest = stod(rest_s);
        if(rest < 0){
          cout << "**************" << endl;
          cout << "您的余额不足！" << endl;
          cout << "**************" << endl;
          return ;
        }
        else{ //生成两个指令
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
          instruction1 = instruction1+this_order_id+","+this_good_id+","+store_goods[i].good_price+","+this_good_amount+","+date()+","+store_goods[i].seller_id+","+user.id+")";
          mysql(instruction1, manipulator, user);

          string instruction2 = "UPDATE commodity SET 数量 = ";
          int rest_stock = this_stock-amount;
          string this_rest_stock = to_string(rest_stock);
          instruction2 = instruction2+this_rest_stock+" WHERE 商品ID = "+this_good_id;
          mysql(instruction2, manipulator, user);
        }
      }
    }
  }
  cout << endl;
}

void Buyer::good_detail(User &user) {
  string manipulator = "buyer";
  string instruction = "SELECT * FROM commodity WHERE 商品ID CONTAINS ";
  cout << "请输入您想要查看的商品ID：";
  string this_good_id;
  getline(cin, this_good_id);
  if(this_good_id.find(' ') != string::npos){
    cout << "***************" << endl;
    cout << "您的输入不合法！";
    cout << "***************" << endl << endl;
    return ;
  }

  instruction.append(this_good_id);
  mysql(instruction, manipulator, user);
}