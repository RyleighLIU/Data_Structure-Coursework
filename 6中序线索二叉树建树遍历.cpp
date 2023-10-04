#include<stdio.h>
#define LINK 0
#define THREAD 1
typedef struct node{
char data;
struct node *lchild,*rchild;
int ltag,rtag;
} node,*bitree;
bitree pre;
bitree buildtree()
{
    char c;
    node *p;
    c=getchar();
    if(c=='0')return(0);
    p=new(node);
    p->data=c;
    p->ltag=p->rtag=THREAD;
    p->lchild=buildtree();
    if(p->lchild!=0)p->ltag=LINK;
    p->rchild=buildtree();
    if(p->rchild!=0)p->rtag=LINK;
    return(p);
}

void InThreading(bitree p)
{
    if(!p) return;
    InThreading(p->lchild);
    if(!p->lchild) p->lchild=pre;
    if(!pre->rchild) pre->rchild=p;
    pre=p;
    InThreading(p->rchild);
}

int buildTHtr(bitree &thrt, bitree t)
{
    thrt=new(node);
    thrt->ltag=thrt->rtag=LINK;
    thrt->rchild=thrt;
    if(!t)thrt->lchild=thrt;
    else{
        thrt->lchild=t;
        pre=thrt;
        InThreading(t);
        pre->rchild=thrt;
       // thrt->rchild=pre;
    }
    return 1;
}

int InOderTraverThr(bitree T)
{
    bitree p=T->lchild;
    while(p!=T)
    {
        while(p->ltag==LINK)p=p->lchild;
        printf("%c", p->data);
        while(p->rtag==THREAD&&p->rchild!=T)
        {
            p=p->rchild;
            printf("%c", p->data);
        }
        p=p->rchild;
    }
    return 1;
}

int main()
{
    bitree thrt,t;
    t=buildtree();   //测试用例：abc00d00ef00g000
    buildTHtr(thrt,t);
    printf("\n中序线索二叉树遍历：");
    InOderTraverThr(thrt);
    printf("\n\n");
}
