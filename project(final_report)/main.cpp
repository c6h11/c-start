
#include "create_data.h"
#include "data_read.h"
#include "mutex.h"
using namespace std;


void save()
{
    std::ofstream file("archive.xml");
    boost::archive::xml_oarchive oa(file);
    std::string s = "Hello World!\n";
    oa & BOOST_SERIALIZATION_NVP(s);
}

void load()
{
    std::ifstream file("archive.xml");
    boost::archive::xml_iarchive ia(file);
    std::string s;
    ia & BOOST_SERIALIZATION_NVP(s);
    std::cout << s << std::endl;
}



int main() {
    std::cout << "Hello, World!@@" << std::endl;
    save();
    load();
    int num_line = 0;

    int fd = open("chart.txt", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if(-1 == fd) {
        cout << "open error" << endl;
        cout << "errno is " << errno << endl;
        cout << strerror(errno) << endl;
    }
    close(fd);
    numline_exp = num_line;
    fd_exp = fd;
    pthread_create(&id1,NULL,create,NULL);  //线程1：创建并存储表
    pthread_join(id1,0);

    pthread_create(&id2,NULL,read,NULL);  //线程2：读取表中数据并查找
    pthread_join(id1,0);

    pthread_create(&id3,NULL,add_line,NULL);  //线程3：增加一行表中内容
    pthread_join(id1,0);

    return 0;
}
