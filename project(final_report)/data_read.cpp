//
// Created by liyanze on 2020/11/2.
//
#include "data_read.h"
#include "b_tree.h"
data_read::data_read(int num_line,int coloun,int fd,int down,int up) {
    num_line_get = num_line;
    coloun_get = coloun;
    fd_get = fd;
    down_get = down;
    up_get = up;
    check();
}
data_read::~data_read() {

}


long data_read::read_data(int fd) {
//    fd = open("chart.txt", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    int start = 8*(coloun_get-1);
    char buf[MAX_BUF];
    long convert = 0;

    printf("num_line_get:%d\n",num_line_get);
    long *data_coloun = new long[num_line_get];
    long *num_coloun = new long[num_line_get];
    for (int i = 0; i < num_line_get; i++) {  //按照字节数读取数据
        lseek(fd, start + 901*i, SEEK_SET);
        read(fd, buf, 8);
        convert = atol(buf);  //读取数据转为long型变量
        data_coloun[i] = convert;
        num_coloun[i] = i + 1;
    }
    for (int i = 0; i < num_line_get; i++) {
        printf("%d:%ld ",num_coloun[i],data_coloun[i]);
    }
    printf("\n");
    data_to_coloun = data_coloun;
    num_to_coloun = num_coloun;
    return 0;
}

int data_read::data_select(){
    for (int i = 0; i < num_line_get; i++) {
        if(BTree::inserttree(data_to_coloun[i],num_to_coloun[i])==1)cout<<"插入成功"<<endl;
        else cout<<"插入失败"<<endl;
        x=new int[BTree::deep];
        Createlink(BTree::root);
    }
    cout<<"插入后的树如下"<<endl;
    printtree(BTree::root);

    return 0;
}

int data_read::data_find(long data_down, long data_up) {
    searchlink(data_down,data_up);
    return 0;
}

int data_read::struct_save_node() {
    char name[MAX_BUF];
    if (0<=coloun_get&&coloun_get<10)
        snprintf(name, MAX_BUF, "massage_00%d.txt", coloun_get);  //根据列数创建文件名
    else if(10<=coloun_get&&coloun_get<100)
        snprintf(name, MAX_BUF, "massage_0%d.txt", coloun_get);
    else
        snprintf(name, MAX_BUF, "massage_%d.txt", coloun_get);
    cout << name << endl;
    int fd4 = open(name, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if(-1 == fd4) {
        cout << "open error" << endl;
        cout << "errno is " << errno << endl;
        cout << strerror(errno) << endl;
    }
    sort_num(fd4,coloun_get);
    write(fd4, "\n", strlen("\n"));
    node_save(fd4);  //写入索引文件
    close(fd4);
    return 0;
}

int data_read::struct_load_node() {
    char name[MAX_BUF];
    if (0<=coloun_get&&coloun_get<10)  //查找索引文件名
        snprintf(name, MAX_BUF, "massage_00%d.txt", coloun_get);
    else if(10<=coloun_get&&coloun_get<100)
        snprintf(name, MAX_BUF, "massage_0%d.txt", coloun_get);
    else
        snprintf(name, MAX_BUF, "massage_%d.txt", coloun_get);
    cout << name << endl;
    int fd1 = open(name, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if(-1 == fd1) {
        cout << "open error" << endl;
        cout << "errno is " << errno << endl;
        cout << strerror(errno) << endl;
    }
    int m;
    int start = 0;
    char buf0[100];
    char buf1[9]="\0";
    char buf2[100];
    char buf3[100];
    long convert = 0;

    long *data_after = new long[num_line_get];
    long *num_after = new long[num_line_get];
    long *node_after = new long[num_line_get];

    lseek(fd1, start, SEEK_SET);  //读取索引文件所属属性
    m=read(fd1, buf0, 3);
    convert = atol(buf0);
    coloun_after = convert;
    cout<<coloun_after<<endl;


    for (int i = 0; i < num_line_get; i++) {

    lseek(fd1, 5+15*i , SEEK_SET);  //读取数据
    m=read(fd1, buf1, 8);
    convert = atol(buf1);
    data_after[i] = convert;

    lseek(fd1, 14+15*i , SEEK_SET);  //读取对应编号
    m=read(fd1, buf2, 3);
    convert = atol(buf2);
    num_after[i] = convert;

    lseek(fd1, 18+15*i, SEEK_SET);  //读取节点标号
    read(fd1, buf3, 1);
    convert = atol(buf3);
    node_after[i] = convert;
    }
    data_after_coloun = data_after;  //索引数据
    num_after_coloun = num_after;  //索引编号
    node_after_coloun = node_after;  //索引结点
    for (int i = 0; i < num_line_get; i++) {
        printf("%ld:%ld:%ld ",data_after[i],num_after[i],node_after[i]);
    }
    printf("\n");
    close(fd1);
    return 0;
}

int data_read::regist() {
    int fd0 = open("lookfor.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if(-1 == fd0) {
        cout << "open error" << endl;
        cout << "errno is " << errno << endl;
        cout << strerror(errno) << endl;
    }
    lseek(fd0,coloun_get-1,SEEK_SET);  //向标记文件中标记该属性已经建立索引
    write(fd0,"1",strlen("1"));
    return 0;
}

int data_read::check() {
    char buf00[100];
    long convert = 0;
    int fd0 = open("lookfor.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    lseek(fd0, coloun_get-1, SEEK_SET);
    read(fd0, buf00, 1);  //从标记文件中读取对应索引号的标记
    convert = atol(buf00);
    if (convert)  //如果标记为1，为存在索引，直接在索引中查找
    {
        cout<<"find success! start searching by struct file"<<endl;
        struct_load_node();
        data_find_sort(down_get,up_get);
    }else  //如果标记为0，不存在索引，需要先读取对应属性数据，根据读取结果建立B+树进行排序，再根据排序结果进行链式查找，最后将排序结果存入对应索引文件并在标记文件登记。
    {
        cout<<"find fail! start searching by B+ tree"<<endl;
        read_data(fd_get);
        data_select();
        data_find(down_get,up_get);
        struct_save_node();
        regist();
    }
    close(fd0);
}

int data_read::data_find_sort(long data_down, long data_up) {
    cout<<"索引查询结果："<<endl;
    for (int i = 0; i < num_line_get; i++) {
        if (data_down<=data_after_coloun[i]&&data_after_coloun[i]<=data_up)
            cout<<"success!~它在第"<<node_after_coloun[i]<<"个结点里,编号为"<<num_after_coloun[i]<<",数值为"<<data_after_coloun[i]<<endl;
    }
}