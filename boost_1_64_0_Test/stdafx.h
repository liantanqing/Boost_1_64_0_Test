// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//
#define  _SCL_SECURE_NO_WARNINGS
#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>

//模板通常定义在头文件当中
template <typename T>
int compare_lian(const T &value1, const T &value2)
{
    //return (value1 > value2 ? 1 : (value1 == value2 ? 0 : -1));
    if (less<T>()(value1, value2)) return -1;
    if (less<T>()(value2, value1)) return 1;
    return 0;
}
// TODO: 在此处引用程序需要的其他头文件
