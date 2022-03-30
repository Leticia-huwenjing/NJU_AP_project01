//
// Created by 胡文菁 on 2022/2/19.
//

#include "seller.h"
void Seller::menu() {
  cout << "====================================================================================" << endl;
  cout << "1.发布商品 2.查看发布商品 3.修改商品信息 4.下架商品 5.查看历史订单 6.返回用户主界面" << endl;
  cout << "====================================================================================" << endl;
  cout << endl;
  cout << "请输入操作：";
}

void Seller::view_goods(User &user) {
  string manipulator = "seller";
  string instruction = "SELECT * FROM commodity";
  mysql(instruction, manipulator, user);
}

void Seller::remove_good(User &user) {
  cout << "请输入要下架的商品ID：";
  string this_good_id;
  getline(cin, this_good_id);

  if(this_good_id.find(' ') != string::npos){
    cout << "***************" << endl;
    cout << "您的输入不合法！" << endl;
    cout << "***************" << endl << endl;
    return ;
  }

  //收拾离谱用户
  bool res = true;
  int i;
  if(this_good_id.size() != 4 || this_good_id[0] != 'M' || !(this_good_id[1] >= '0' && this_good_id[1] <= '9'
      && this_good_id[2] >= '0' && this_good_id[2] <= '9' && this_good_id[3] >= '0' && this_good_id[3] <= '9')){
    res = false;
    cout << "***************" << endl;
    cout << "您的输入不合法！" << endl;
    cout << "***************" << endl;
  }

    //处理商品id不存在或已下架
  else{
    bool is_alive = false;
    int len = store_goods.size();
    for(i = 0; i < len; i++){
      if(store_goods[i].good_id == this_good_id){
        if(store_goods[i].condition == "销售中"){
          if(store_goods[i].seller_id == user.id) {
            is_alive = true;
          }
        }
        break;
      }
    }

    if(!is_alive){
      res = false;
      cout << "***********************************" << endl;
      cout << "商品不存在/已下架/不是您发布的商品" << endl;
      cout << "***********************************" << endl;
    }
  }

  //输出商品信息&选择是否下架
  if(res){
    cout << "确认要下架该商品吗？" << endl;
    cout << "*************************************************************************************************************************************" << endl;
    cout << left << setw_u8(20, "商品ID") << "商品ID"
         << left << setw_u8(20, "名称")  << "名称"
         << left << setw_u8(20,"价格") << "价格"
         << left << setw_u8(20, "上架时间") << "上架时间"
         << left << setw_u8(20, "卖家ID") << "卖家ID"
         << left << setw_u8(20, "数量") << "数量"
         << left << setw_u8(20, "商品状态") << "商品状态" << endl;

    cout << left << setw_u8(20, store_goods[i].good_id) << store_goods[i].good_id
         << left << setw_u8(20, store_goods[i].good_name)  << store_goods[i].good_name
         << left << setw_u8(20,store_goods[i].good_price) << store_goods[i].good_price
         << left << setw_u8(20, store_goods[i].time) << store_goods[i].time
         << left << setw_u8(20, store_goods[i].seller_id) << store_goods[i].seller_id
         << left << setw_u8(20, store_goods[i].stock) << store_goods[i].stock
         << left << setw_u8(20, store_goods[i].condition) << store_goods[i].condition << endl;
    cout << "*************************************************************************************************************************************" << endl;

    cout << "请选择是否下架(y/n)";
    char opt;
    cin >> opt;
    while(!cin || getchar()!='\n' || (opt !='y' && opt != 'n')){
      cout <<"输入不合法！请重新输入：";
      cin.clear();
      cin >> opt;
    }
    if(opt == 'n'){
      cout << "取消下架" << endl;
    }
    else{
      cout << "下架成功" << endl;
      string manipulator = "seller";
      string instruction = "UPDATE commodity SET 商品状态 = 已下架 WHERE 商品ID = ";
      instruction.append(this_good_id);
      mysql(instruction, manipulator, user);
    }
  }
  cout << endl;
}

void Seller::view_orders(User &user) {
  string manipulator = "seller";
  string instruction = "SELECT * FROM order";
  mysql(instruction, manipulator, user);
}

void Seller::sell_good(User &user) {
  string this_good_name;
  cout << "请输入商品名称：";
  getline(cin, this_good_name);
  if(this_good_name.find(' ') != string::npos){
    cout << "****************" << endl;
    cout << "您的输入不合法！" << endl;
    cout << "****************" << endl << endl;
    return ;
  }

  string this_good_price;
  cout << "请输入商品价格：";
  getline(cin, this_good_price);
  if(this_good_price.find(' ') != string::npos){
    cout << "****************" << endl;
    cout << "您的输入不合法！" << endl;
    cout << "****************" << endl << endl;
    return ;
  }

  string this_good_stock;
  cout << "请输入商品数量：";
  getline(cin, this_good_stock);
  if(this_good_stock.find(' ') != string::npos){
    cout << "****************" << endl;
    cout << "您的输入不合法！" << endl;
    cout << "****************" << endl << endl;
    return ;
  }

  string this_good_information;
  cout << "请输入商品描述：";
  getline(cin, this_good_information);
  if(this_good_information.find(' ') != string::npos){
    cout << "********************************" << endl;
    cout << "您输入的商品描述中不能含有空格！" << endl;
    cout << "********************************" << endl << endl;
    return ;
  }
  cout << endl;

  //判断用户输入是否合法
  bool res = true;
  //判断价格是否为大于0的一位小数
  if(this_good_price.find('.') == string::npos){
    this_good_price = this_good_price.append(".0");
  }
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
    cout << "********************" << endl;
    cout << "价格/数量输入不合法！" << endl;
    cout << "********************" << endl;
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
  cout << "请输入被修改的商品ID：";
  string this_good_id;
  getline(cin, this_good_id);
  if(this_good_id.find(' ') != string::npos){
    cout << "****************" << endl;
    cout << "您的输入不合法！" << endl;
    cout << "****************" << endl << endl;
    return ;
  }

  //收拾离谱用户
  bool id_res = true;
  int i;
  if(this_good_id.size() != 4 || this_good_id[0] != 'M' || !(this_good_id[1] >= '0' && this_good_id[1] <= '9'
      && this_good_id[2] >= '0' && this_good_id[2] <= '9' && this_good_id[3] >= '0' && this_good_id[3] <= '9')){
    id_res = false;
    cout << "****************" << endl;
    cout << "您的输入不合法！" << endl;
    cout << "****************" << endl;
  }

  //处理商品id不存在或已下架
  else{
    bool is_alive = false;
    int len = store_goods.size();
    for(i = 0; i < len; i++){
      if(store_goods[i].good_id == this_good_id){
        if(store_goods[i].condition == "销售中"){
          if(store_goods[i].seller_id == user.id) {
            is_alive = true;
          }
        }
        break;
      }
    }

    if(!is_alive){
      id_res = false;
      cout << "***********************************" << endl;
      cout << "商品不存在/已下架/不是您发布的商品" << endl;
      cout << "***********************************" << endl;
    }
  }

  if(id_res){
    bool opt_res = true;
    cout << "请输入被修改的商品属性（1.价格 2.描述）";
    string attribute;
    getline(cin, attribute);
    if(attribute != "1" && attribute != "2"){
      opt_res = false;
      cout << "***************" << endl;
      cout << "您的输入不合法！" << endl;
      cout << "***************" << endl;
    }
    if(opt_res){
      switch (attribute[0]) {
        case '1':{
          cout << "请输入被修改商品的价格：";
          string this_good_price;
          getline(cin, this_good_price);
          if(this_good_price.find(' ') != string::npos){
            cout << "****************" << endl;
            cout << "您的输入不合法！" << endl;
            cout << "****************" << endl << endl;
            return ;
          }

          bool res = true;
          //判断价格是否为大于0的一位小数
          int len_price = this_good_price.size();
          int point_dot = this_good_price.find('.');
          if(len_price-point_dot > 2){
            res = false;
          }
          else {
            for (int j = 0; j < point_dot; j++) {
              if (!(this_good_price[j] >= '0' && this_good_price[j] <= '9')) {
                res = false;
                break;
              }
            }
            if (!(this_good_price[point_dot + 1] >= '0' && this_good_price[point_dot + 1] <= '9')) {
              res = false;
            }

            bool all_zero = true;
            if (res) {
              for (int j = 0; j < point_dot; j++) {
                if (this_good_price[j] != '0') {
                  all_zero = false;
                  break;
                }
              }
              if (this_good_price[point_dot + 1] != '0') {
                all_zero = false;
              }
            }

            if (all_zero) {
              res = false;
            }
          }

          if(!res){
            cout << "****************" << endl;
            cout << "您的输入不合法！" << endl;
            cout << "****************" << endl;
          }
          else{
            cout << "请确认修改的信息无误！" << endl;
            cout << "*************************" << endl;
            cout << "商品ID：" << this_good_id << endl;
            cout << "商品名称：" << store_goods[i].good_name << endl;
            cout << "商品价格：" << this_good_price << endl;
            cout << "商品描述：" << store_goods[i].information << endl;
            cout << "*************************" << endl;
            cout << "确认修改？(y/n)";

            char opt;
            cin >> opt;
            while(getchar()!='\n' || (opt !='y' && opt != 'n')){
              cout <<"输入不合法！请重新输入：";
              cin.clear();
              cin >> opt;
            }

            if(opt == 'n'){
              cout << "取消修改" << endl;
            }
            else {
              cout << "修改成功" << endl;
              string manipulator = "seller";
              string instruction = "UPDATE commodity SET 价格 = ";
              instruction = instruction + this_good_price + " WHERE 商品ID = ";
              instruction.append(this_good_id);
              mysql(instruction, manipulator, user);
            }
          }
          break;
        }

        case '2':{
          cout << "请输入被修改商品的描述：";
          string this_information;
          getline(cin, this_information);
          if(this_information.find(' ') != string::npos){
            cout << "******************************" << endl;
            cout << "您输入的商品描述不能含有空格！" << endl;
            cout << "******************************" << endl << endl;
            return ;
          }

          cout << "请确认修改的信息无误！" << endl;
          cout << "*************************" << endl;
          cout << "商品ID：" << this_good_id << endl;
          cout << "商品名称：" << store_goods[i].good_name << endl;
          cout << "商品价格：" << store_goods[i].good_price << endl;
          cout << "商品描述：" <<  this_information << endl;
          cout << "*************************" << endl;
          cout << "确认修改？(y/n)";

          char opt;
          cin >> opt;
          while(getchar()!='\n' || (opt !='y' && opt != 'n')){
            cout <<"输入不合法！请重新输入：";
            cin.clear();
            cin >> opt;
          }

          if(opt == 'n'){
            cout << "取消修改" << endl;
          }
          else {
            cout << "修改成功" << endl;
            string manipulator = "seller";
            string instruction = "UPDATE commodity SET 描述 = ";
            instruction = instruction + this_information + " WHERE 商品ID = ";
            instruction.append(this_good_id);
            mysql(instruction, manipulator, user);
          }
          break;
        }
        default:{
          cout << "输入不合法！" << endl;
          break;
        }
      }
    }
  }
  cout << endl;
}