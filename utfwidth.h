//
// Created by 胡文菁 on 2022/2/26.
//

#ifndef MAIN_CPP__UTFWIDTH_H_
#define MAIN_CPP__UTFWIDTH_H_

#pragma once

#include <string_view>
#include <iomanip>

decltype(std::setw(0)) setw_u8(int w, std::string_view u8s);

#endif //MAIN_CPP__UTFWIDTH_H_
