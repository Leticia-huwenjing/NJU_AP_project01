//
// Created by 胡文菁 on 2022/2/19.
//

#include "admin.h"
void Manager::admin_manu() {
  cout << "===========================================================================" << endl;
  cout << "1.查看所有商品 2.搜索商品 3.下架商品 4.查看所有订单 5.查看所有用户 6.封禁用户 7.注销" << endl;
  cout << "===========================================================================" << endl;
  cout << endl;
  cout << "请输入操作：";
}

bool Manager::log_in() {
  bool res = false;
  cout << "请输入管理员姓名：";
  string test_name;
  cin >> test_name;
  cout << "请输入密码：";
  string test_password;
  cin >> test_password;
  if(name == test_name){
    if(password == test_password){
      res = true;
      cout << endl;
      cout << "-----登录成功-----" << endl;
      cout << endl;
    }
    else{
      cout << endl;
      cout << "-----密码错误，登录失败，返回主菜单-----" << endl;
      cout << endl;
    }
  }
  else{
    cout << endl;
    cout << "-----姓名错误，登录失败，返回主菜单-----" << endl;
    cout << endl;
  }
  return res;
}

void Manager::view_goods() {
  string manipulator = "admin";
  string instruction = "SELECT * FROM commodity";
  string fake_name = "";
  string fake_password = "";
  User user(fake_name,fake_password);
  mysql(instruction, manipulator, user);
}

void Manager::view_orders() {
  string manipulator = "admin";
  string instruction = "SELECT * FROM order";
  string fake_name = "";
  string fake_password = "";
  User user(fake_name,fake_password);
  mysql(instruction, manipulator, user);
}

void Manager::search_goods() {
  string fake_name = "";
  string fake_password = "";
  User user(fake_name,fake_password);
  string manipulator = "admin";
  string instruction = "SELECT * FROM commodity WHERE 名称 CONTAINS ";
  cout << "请输入商品名称：";
  string this_name;
  cin >> this_name;
  instruction.append(this_name);
  mysql(instruction, manipulator, user);
}

void Manager::remove_good() {
  string fake_name = "";
  string fake_password = "";
  User user(fake_name,fake_password);

  cout << "请输入要下架的商品ID：";
  string this_good_id;
  cin >> this_good_id;

  //收拾离谱管理员
  bool res = true;
  int i;
  if(this_good_id.size() != 4 || this_good_id[0] != 'M' || !(this_good_id[1] >= '0' && this_good_id[1] <= '9'
     && this_good_id[2] >= '0' && this_good_id[2] <= '9' && this_good_id[3] >= '0' && this_good_id[3] <= '9')){
    res = false;
    cout << "***************" << endl;
    cout << "您的输入不合法！";
    cout << "***************" << endl;
  }

  //处理商品id不存在或已下架
  else{
    bool is_alive = false;
    int len = store_goods.size();
    for(i = 0; i < len; i++){
      if(store_goods[i].good_id == this_good_id){
        if(store_goods[i].condition == "销售中"){
          is_alive = true;
          break;
        }
      }
    }
    if(!is_alive){
      res = false;
      cout << "*******************" << endl;
      cout << "商品不存在或已下架！" << endl;
      cout << "*******************" << endl;
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
      while(getchar()!='\n');
      cin >> opt;
    }
    if(opt == 'n'){
      cout << "取消下架" << endl;
    }
    else{
      cout << "下架成功" << endl;
      string manipulator = "admin";
      string instruction = "UPDATE commodity SET 商品状态 = 已下架 WHERE 商品ID = ";
      instruction.append(this_good_id);
      mysql(instruction, manipulator, user);
    }
  }
  cout << endl;
}

void Manager::view_users() {
  string manipulator = "admin";
  string instruction = "SELECT * FROM user";
  string fake_name = "";
  string fake_password = "";
  User user(fake_name,fake_password);
  mysql(instruction, manipulator, user);
}

void Manager::ban_user() {
  string fake_name = "";
  string fake_password = "";
  User user(fake_name,fake_password);

  cout << "请输入要封禁的用户ID：";
  string this_user_id;
  cin >> this_user_id;

  //收拾离谱管理员
  bool res = true;
  int i;
  if(this_user_id.size() != 4 || this_user_id[0] != 'U' || !(this_user_id[1] >= '0' && this_user_id[1] <= '9'
      && this_user_id[2] >= '0' && this_user_id[2] <= '9' && this_user_id[3] >= '0' && this_user_id[3] <= '9')){
    res = false;
    cout << "***************" << endl;
    cout << "您的输入不合法！";
    cout << "***************" << endl;
  }

    //处理商品id不存在或已下架
  else{
    bool is_alive = false;
    int len = store_users.size();
    for(i = 0; i < len; i++){
      if(store_users[i].user_id == this_user_id){
        if(store_users[i].condition == "正常"){
          is_alive = true;
          break;
        }
      }
    }
    if(!is_alive){
      res = false;
      cout << "*******************" << endl;
      cout << "用户不存在或已被封禁！" << endl;
      cout << "*******************" << endl;
    }
  }

  if(res){
    cout << "确认要封禁该用户吗？" << endl;
    cout << "****************************************************************************" << endl;
    cout << left << setw_u8(20, "用户ID") << "用户ID"
         << left << setw_u8(20, "用户名")  << "用户名"
         << left << setw_u8(20,"联系方式") << "联系方式"
         << left << setw_u8(20, "地址") << "地址"
         << left << setw_u8(20, "钱包余额") << "钱包余额" << endl;

    cout << left << setw_u8(20, store_users[i].user_id) << store_users[i].user_id
         << left << setw_u8(20, store_users[i].user_name)  << store_users[i].user_name
         << left << setw_u8(20,store_users[i].tel) << store_users[i].tel
         << left << setw_u8(20, store_users[i].address) << store_users[i].address
         << left << setw_u8(20, store_users[i].money) << store_users[i].money << endl;
    cout << "****************************************************************************" << endl;
    cout << "请选择是否封禁(y/n)";

    char opt;
    cin >> opt;
    while(!cin || getchar()!='\n' || (opt !='y' && opt != 'n')){
      cout <<"输入不合法！请重新输入：";
      cin.clear();
      while(getchar()!='\n');
      cin >> opt;
    }
    if(opt == 'n'){
      cout << "取消封禁" << endl;
    }
    else{
      cout << "封禁成功" << endl;
      string manipulator = "admin";
      string instruction1 = "UPDATE user SET 用户状态 = 封禁 WHERE 用户ID = ";
      instruction1.append(this_user_id);
      mysql(instruction1, manipulator, user);

      //下架该商品所有东西
      string instruction2 = "UPDATE commodity SET 商品状态 = 已下架 WHERE 卖家ID = ";
      instruction2.append(this_user_id);
      mysql(instruction2, manipulator, user);
    }
  }
  cout << endl;
}