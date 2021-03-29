#include "header.h"
using namespace std;
class BTree
{
public:
    int n;       //该节点所含关键字的个数  大于等于2
    BTree *father;
    static int number;//阶数   大于等于3
    static BTree *root;
    BTree();
    long **data = new long*[2];
    BTree **down;

    static bool inserttree(long t, long m);//在树中插入t
    static	BTree* searchinsert(long t, long m);//搜索插入到某节点
    bool insertpoint(long t, long m,BTree *p);//在节点插入
    void split(long t, long m,BTree *p);  //分裂



    static int deep;  //深度

};
struct node
{
    BTree* q;
    node *next;
};
node *head=NULL;
int BTree::number=4;
int BTree::deep=0;
BTree *BTree::root=NULL;
BTree::BTree()             //创建一个节点
{
    for (int i = 0; i < 2; i++) {
        data[i]=new long[number];  //2行number列,第一行存数据，第二行存编号
    }
    down=new BTree*[number];
    for(int i=0;i<number;i++)
    {
        for (int j=0; j<2; j++) {
            data[j][i]=0;  //2行number列
        }
        down[i]=NULL;
    }
    father=NULL;
    n=0;
}

BTree* BTree::searchinsert(long t, long m)//搜索t的该插入的位置，返回指针
{
    if(root==NULL)
    {
        root=new BTree;
        deep=1;
        return root;
    }
    BTree *p;
    p=root;
    if(t>root->data[0][root->n-1])  //大于最大关键字要改父节点的关键字
    {
        while(p->down[0]!=NULL)
        {
            p->data[0][p->n-1]=t;
            p->data[1][p->n-1]=m;
            p=p->down[p->n-1];
        }
        return p;
    }
    while(p->down[0]!=NULL)
    {
        int i;
        for(i=0;i<p->n&&t>p->data[0][i];i++);
        p=p->down[i];
    }
    return p;
}
bool BTree:: inserttree(long t, long m)//将t插入树中
{
    BTree *p=BTree::searchinsert(t,m);
    if(1==p->insertpoint(t,m,NULL))
        return 1;
    else
        return 0;
}
bool BTree::insertpoint(long t, long m, BTree *p)//把元素t和它所指的子树插入this结点中
{

    int i,j;
    for(i=n-1;i>=0&&data[0][i]>t;i--);

    if(i>=0&&t==data[0][i])
        return 0;  //相同不做操作

    if(n+1>number)
    {
        split(t,m,p);
        return 1 ;
    }

    for(j=n-1;j>i;j--)      //插入元素和指针
    {
        data[0][j+1]=data[0][j];
        data[1][j+1]=data[1][j];
        down[j+1]=down[j];
    }
    data[0][i+1]=t;
    data[1][i+1]=m;
    down[i+1]=p;
    if(p!=NULL)
        p->father=this;
    n++;
    return 1;
}
void BTree::split(long t, long m,BTree *p)//t,p分别是多余的节点地址，关键字，分裂this节点
{

    int i,j;
    if(this==root)
    {
        deep++;
        root=new BTree;
        BTree *pt=new BTree;
        for(i=0,j=0;i<(number+1)/2;i++)//找到前(number+1)/2个给pt
        {
            if(t>data[0][j])
            {
                pt->data[0][i]=data[0][j];
                pt->data[1][i]=data[1][j];
                if(down[i]!=NULL)
                    down[i]->father=pt;
                pt->down[i]=down[j];
                j++;
            }
            else
            {
                pt->data[0][i]=t;
                pt->data[1][i]=m;
                t=99999999;
                if(p!=NULL)
                    p->father=pt;
                pt->down[i]=p;
            }

        }
        pt->father=root;
        pt->n=(number+1)/2;
        root->data[0][0]=pt->data[0][(number+1)/2-1];
        root->data[1][0]=pt->data[1][(number+1)/2-1];
        root->down[0]=pt;
        for(i=0;i<number-(number+1)/2+1;i++)
        {
            if(j==number)
            {
                data[0][i]=t;
                data[1][i]=m;
                down[i]=p;
                break;
            }
            if(t>data[0][j])
            {
                data[0][i]=data[0][j];
                data[1][i]=data[1][j];
                down[i]=down[j];
                j++;
            }
            else
            {
                data[0][i]=t;
                data[1][i]=m;
                down[i]=p;
                t=99999999;
            }
        }
        father=root;
        n=number-(number+1)/2+1;
        root->n=2;
        root->data[0][1]=data[0][number-(number+1)/2];
        root->data[1][1]=data[1][number-(number+1)/2];
        root->down[1]=this;
    }
    else
    {
        BTree *pt=new BTree;
        for(i=0,j=0;i<(number+1)/2;i++)
        {
            if(t>data[0][j])
            {
                pt->data[0][i]=data[0][j];
                pt->data[1][i]=data[1][j];
                if(down[j]!=NULL)down[j]->father=pt;
                pt->down[i]=down[j];
                j++;
            }
            else
            {
                pt->data[0][i]=t;
                pt->data[1][i]=m;
                t=99999999;
                if(p!=NULL)p->father=pt;
                pt->down[i]=p;
            }

        }
        pt->father=father;
        pt->n=(number+1)/2;
        for(i=0;i<number-(number+1)/2+1;i++)
        {
            if(j==number){data[0][i]=t;down[i]=p;break;}
            if(t>data[0][j])
            {
                data[0][i]=data[0][j];
                data[1][i]=data[1][j];
                down[i]=down[j];
                j++;
            }
            else
            {
                data[0][i]=t;
                data[1][i]=m;
                t=99999999;
                down[i]=p;
            }
        }
        n=number-(number+1)/2+1;
        father->insertpoint(pt->data[0][pt->n-1],pt->data[1][pt->n-1],pt);
    }

}

int *x;    //各层的结点数
class dui
{

public :
    BTree * data[200];  //元素
    int   num[200];    //该元素是第几层的
    int tp,tl;//tp为队头，tl为队尾
    dui(){tp=0;tl=0;}
    BTree* pop();
    void push(BTree*,int);
    bool empty();
};
BTree* dui::pop()//出队
{
    int t;
    t=tp;
    tp=(tp+1)%200;
    if(num[t]!=BTree::deep-1)//不为叶子节点
    {
        for(int i=0;i<data[t]->n;i++)
        {
            push(data[t]->down[i],num[t]+1);
        }
    }
    return data[t];
}
void dui::push(BTree *i,int j)
{
    data[tl]=i;
    num[tl]=j;
    tl=(tl+1)%200;
    x[j]++;
}
bool dui::empty()
{
    if(tp==tl)return 1;
    else return 0;
}
dui qu;
void print(BTree *p)
{

    for (int i=0; i <p->n; i++)
    {
        cout<<setw(10)<<p->data[0][i];
        cout<<",";
        cout<<setw(3)<<p->data[1][i];
        cout<<";";
    }

    cout<<" | ";
}
void printtree(BTree *q)  //输入树的root节点
{
    if(q==NULL)
    {
        cout<<"空树"<<endl;
        return;
    }
    int i,j;
    for(i=0;i<BTree::deep;i++)
    {
        x[i]=0;
    }
    qu.push(q,0);  //当前的根节点进入队列
    for(i=0;i<BTree::deep;i++)
    {
        cout<<"第"<<i+1<<"层:"<<endl;
        for(j=0;j<x[i];j++)
        {
            print(qu.pop());
        }
        cout<<endl;
    }
}

void Createlink(BTree* p)
{
    qu.push(p,0);
    BTree *tree;
    do
    {
        tree=qu.pop();
    }while(tree->down[0]!=NULL);
    node *p1,*p2;
    head=p1=new node;
    p1->q=tree;
    while(!qu.empty())
    {
        p2=new node;
        p2->q=qu.pop();
        p1->next=p2;
        p1=p2;
    }
    p1->next=NULL;
}


void searchroot(long t)
{
    if(BTree::root==NULL)
    {
        cout<<"空树"<<endl;
        return;
    }
    if(t>BTree::root->data[0][BTree::root->n-1])
    {
        cout<<"无改结点值"<<endl;
        return;
    }
    BTree *p=BTree::root;
    int i;
    while(p->down[0] != NULL)
    {
        for(i=0 ;i<p->n&&t>p->data[0][i];i++);
        p=p->down[i];
    }
    for(i=0;i<p->n&&t>p->data[0][i];i++);
    if(t==p->data[0][i])
    {
        cout<<"success!~~存在该结点值"<<endl;
        cout<<"success!~它在第"<<BTree::deep<<"层的第"<<p->n<<"个结点里"<<endl;
    }
    else
        cout<<"fail!~~~不存在该结点值！~~"<<endl;
}
void searchlink(long t_down, long t_up)
{
    if(head==NULL)
    {
        cout<<"空树"<<endl;
        return;
    }
    node *p=head;
    int r=0;
    cout<<"B+树查询结果："<<endl;
    while(p!=NULL)
    {
        r++;
        int i;
//        for(i=0;i<p->q->n&&t_down>=p->q->data[0][i];i++);
        for(i=0;i<p->q->n;i++)
        {
            if(t_down<=p->q->data[0][i]&&p->q->data[0][i]<=t_up)
            {
                cout<<"success!~它在第"<<BTree::deep<<"层的第"<<r<<"个结点里,编号为"<<p->q->data[1][i]<<",数值为"<<p->q->data[0][i]<<endl;
            }
        }


//        if(t_up<p->q->data[0][i])
//        {
//            cout<<"error!~无该结点值"<<endl;
//            break;
//        }
        p=p->next;
    }
    if(p==NULL)cout<<"fail!~无该结点值"<<endl;


}

void sort_num(int fd_1,int t)
{
    if (t >= 0 && t < 10)
    {
        char buf[MAX_BUF];
        int buf_len = 0;
        snprintf(buf, MAX_BUF, "00%ld ", t);
        buf_len = strlen(buf);
        write(fd_1, buf, buf_len);
    }
    else if
    (t >= 10 && t < 100)
    {
        char buf[MAX_BUF];
        int buf_len = 0;
        snprintf(buf, MAX_BUF, "0%ld ", t);
        buf_len = strlen(buf);
        write(fd_1, buf, buf_len);
    }
    else
    {
        char buf[MAX_BUF];
        int buf_len = 0;
        snprintf(buf, MAX_BUF, "%ld ", t);
        buf_len = strlen(buf);
        write(fd_1, buf, buf_len);
    }

}

void node_save(int fd_1)
{
    if(head==NULL)
    {
        cout<<"空树"<<endl;
        return;
    }
    node *p=head;
    int r=0;
    while(p!=NULL)
    {
        r++;
        int i;
//        for(i=0;i<p->q->n&&t_down>=p->q->data[0][i];i++);
        for(i=0;i<p->q->n;i++)
        {
            char buf[MAX_BUF];
            int buf_len = 0;
            if (p->q->data[0][i] >= 0 && p->q->data[0][i] < 10)
                snprintf(buf, MAX_BUF, "0000000%ld ", p->q->data[0][i]);
            else if (p->q->data[0][i] >= 10 && p->q->data[0][i] < 100)
                snprintf(buf, MAX_BUF, "000000%ld ", p->q->data[0][i]);
            else if (p->q->data[0][i] >= 100 && p->q->data[0][i] < 1000)
                snprintf(buf, MAX_BUF, "00000%ld ", p->q->data[0][i]);
            else if (p->q->data[0][i] >= 1000 && p->q->data[0][i] < 10000)
                snprintf(buf, MAX_BUF, "0000%ld ", p->q->data[0][i]);
            else if (p->q->data[0][i] >= 10000 && p->q->data[0][i] < 100000)
                snprintf(buf, MAX_BUF, "000%ld ", p->q->data[0][i]);
            else if (p->q->data[0][i] >= 100000 && p->q->data[0][i] < 1000000)
                snprintf(buf, MAX_BUF, "00%ld ", p->q->data[0][i]);
            else if (p->q->data[0][i] >= 1000000 && p->q->data[0][i] < 10000000)
                snprintf(buf, MAX_BUF, "0%ld ", p->q->data[0][i]);
            else
                snprintf(buf, MAX_BUF, "%ld ", p->q->data[0][i]);
            buf_len = strlen(buf);
            write(fd_1, buf, buf_len);
            sort_num(fd_1,p->q->data[1][i]);
            snprintf(buf, MAX_BUF, "%d\n", r);
            buf_len = strlen(buf);
            write(fd_1, buf, buf_len);
        }
        p=p->next;
    }


}