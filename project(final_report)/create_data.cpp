//
// Created by liyanze on 2020/10/30.
//
#include "create_data.h"


using namespace std;

create_data::create_data(int time,int fd){
    int num_line = 0;
    for (int i = 0; i < time; i++) {
        num_line = data_create(num_line);
        data_catch(fd);
    }
    printf("%d\n",num_line);
    num_line_get = num_line;
};
create_data::~create_data(){

};
int create_data::data_create(int num_line) {
    for (int i = 0; i < 100; i++) {
        data[i] = rand()%100000000;
    }
    num_line ++;
    return num_line;
}

int create_data::data_catch(int fd) {
//    fd = open("chart.txt", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
//    if(-1 == fd) {
//        cout << "open error" << endl;
//        cout << "errno is " << errno << endl;
//        cout << strerror(errno) << endl;
//    }
    char buf[MAX_BUF];
    int buf_len = 0;
    data_buf = data;
    for (int i = 0; i < 100; i++) {  //数据转化为8位按照字符存入文件
        if (data[i] >= 0 && data[i] < 10)
            snprintf(buf, MAX_BUF, "0000000%ld ", data[i]);
        else if (data[i] >= 10 && data[i] < 100)
            snprintf(buf, MAX_BUF, "000000%ld ", data[i]);
        else if (data[i] >= 100 && data[i] < 1000)
            snprintf(buf, MAX_BUF, "00000%ld ", data[i]);
        else if (data[i] >= 1000 && data[i] < 10000)
            snprintf(buf, MAX_BUF, "0000%ld ", data[i]);
        else if (data[i] >= 10000 && data[i] < 100000)
            snprintf(buf, MAX_BUF, "000%ld ", data[i]);
        else if (data[i] >= 100000 && data[i] < 1000000)
            snprintf(buf, MAX_BUF, "00%ld ", data[i]);
        else if (data[i] >= 1000000 && data[i] < 10000000)
            snprintf(buf, MAX_BUF, "0%ld ", data[i]);
        else
            snprintf(buf, MAX_BUF, "%ld ", data[i]);
        buf_len = strlen(buf);
        write(fd, buf, buf_len);
//          write(fd, data_buf + i, 8);
//          printf("%ld ",*(data_buf + i));
    }
    write(fd, "\n", strlen("\n"));
    return 0;
}

int create_data::get_numline() {
    return num_line_get;
}