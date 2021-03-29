//
// Created by liyanze on 2020/10/30.
//

#ifndef DEMO_CREATE_DATA_H
#define DEMO_CREATE_DATA_H
#include "header.h"
class create_data
{
public:
    int data_create(int num_line);  //创建表中数据
    int data_catch(int fd);  //数据写入表中
    int get_numline();  //获取行数

public:
    create_data(int time,int fd);
    virtual ~create_data();
private:
    int num_line_get;
    int time;
    long data[100];
    long *data_buf;
};

#endif //DEMO_CREATE_DATA_H
