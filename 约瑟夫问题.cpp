#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	char data;
	node *next;
}node;
typedef node *LinkList;

LinkList build(int n)   //单链表尾插法
{
    node *p,*head;
	int i;
    head=new(node);
	p=head;
	for( i=1; i<=n; i++)
	{
		p->next=new(node);
		p->next->data=i+'a'-1;
		p=p->next;
	}
	p->next=NULL;
	return(head);
}

void display(LinkList L)
{
    node *p;
    p=L->next;
    while (p!=NULL)
    {
        printf("%c  ",p->data);
        p=p->next;
    }
    printf("\n");
}

// 算法思想：利用循环单列表，设置两个指针，一个p，一个指向p的前驱结点，从第一个结点出发，
// 报数数到m之后删掉该结点，然后往后走，直到最后p的后置结点为自身（即没有留下其他结点）

void Joseph(LinkList L,int m){
	node *prev=L;
	while(prev->next!=NULL){
		prev=prev->next;
	}
	prev->next= L->next;
	node *f;
	node *p = L->next,*q = L->next;
	while(p->next != p){
		int counter = 1;
		while(counter!=m){
			q = p;
			p = p->next;
			counter ++;
		}
		f=q->next;
		q->next = p->next;
		p = q->next; 
		free(f);
	}
	printf("最后留下来的是:%c",p->data);
	
}

int main(){
	LinkList L;
	//L= build(6);
    L = build(5);
    display(L);
	Joseph(L,3);
	return 0;
}
