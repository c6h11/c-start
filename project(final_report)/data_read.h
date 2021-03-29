//
// Created by liyanze on 2020/11/2.
//

#ifndef DEMO_DATA_READ_H
#define DEMO_DATA_READ_H
#include "header.h"

class data_read {
public:
    long read_data(int fd);  //读取一列数据
    int data_select();  //数据按照B+树进行排序
    int data_find(long data_down, long data_up);  //按照B+树结果进行查找
    int data_find_sort(long data_down, long data_up);  //按照索引文件进行查找
    int struct_save_node();  //B+树结果存入索引文件
    int struct_load_node();  //读取索引文件
    int regist();  //记录该索引文件是哪个属性的
    int check();  //检查输入属性是否存在索引文件
public:
    data_read(int num_line,int coloun,int fd,int down,int up);
    virtual ~data_read();
private:
    int fd_get;  //存储表的文件序号
    int coloun_get;  //确定提取哪一列
    int num_line_get;  //确定总共多少行
    int down_get;  //查询下限
    int up_get;  //查询上限
    long *num_to_coloun;  //实际数据
    long *data_to_coloun;  //数据编号
    long coloun_after;  //索引列号
    long *num_after_coloun;  //索引编号
    long *data_after_coloun;  //索引数据
    long *node_after_coloun;  //索引结点

};


#endif //DEMO_DATA_READ_H
