//
// Created by liyanze on 2020/11/13.
//

#ifndef DEMO_1_MUTEX_H
#define DEMO_1_MUTEX_H
#include <pthread.h>
using namespace std;
#define TIME 10
pthread_t id1;
pthread_t id2;
pthread_t id3;
int fd_exp;
int numline_exp;
int numline_final;
pthread_mutex_t work_mutex;

void* create(void *arg)
{
    pthread_mutex_init(&(work_mutex),0);  //互斥量初始化
    pthread_mutex_lock(&(work_mutex));  //互斥量加锁
    fd_exp = open("chart.txt", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if(-1 == fd_exp) {
        cout << "open error" << endl;
        cout << "errno is " << errno << endl;
        cout << strerror(errno) << endl;
    }
    create_data data_1 = create_data(TIME,fd_exp);  //创建表中内容
    numline_exp = data_1.get_numline();  //获取表中行数
    close(fd_exp);
    pthread_mutex_unlock(&(work_mutex));  //互斥量解锁
    pthread_mutex_destroy(&(work_mutex));  //销毁互斥量
    numline_final = numline_exp;
}

void* read(void *arg)
{
    pthread_mutex_init(&(work_mutex),0);
    pthread_mutex_lock(&(work_mutex));
    data_read data_1_read(numline_exp,1,fd_exp,40000000,80000000);  //根据所提供的属性（列数）和查询上下限，在表中查找
    pthread_mutex_unlock(&(work_mutex));
    pthread_mutex_destroy(&(work_mutex));
}

void* add_line(void *arg)
{
    pthread_mutex_init(&(work_mutex),0);
    pthread_mutex_lock(&(work_mutex));
    fd_exp = open("chart.txt", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if(-1 == fd_exp) {
        cout << "open error" << endl;
        cout << "errno is " << errno << endl;
        cout << strerror(errno) << endl;
    }
    create_data data_2 = create_data(1,fd_exp);  //增加一行数据
    numline_final++;
    cout << numline_final << endl;
    close(fd_exp);
    pthread_mutex_unlock(&(work_mutex));
    pthread_mutex_destroy(&(work_mutex));
}
#endif //DEMO_1_MUTEX_H
