// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//
#define  _SCL_SECURE_NO_WARNINGS
#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>

//ģ��ͨ��������ͷ�ļ�����
template <typename T>
int compare_lian(const T &value1, const T &value2)
{
    //return (value1 > value2 ? 1 : (value1 == value2 ? 0 : -1));
    if (less<T>()(value1, value2)) return -1;
    if (less<T>()(value2, value1)) return 1;
    return 0;
}
// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
