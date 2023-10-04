#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	char data;
	node *next;
}node;
typedef node *LinkList;

LinkList build(int n)   //������β�巨
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

// �㷨˼�룺����ѭ�����б���������ָ�룬һ��p��һ��ָ��p��ǰ����㣬�ӵ�һ����������
// ��������m֮��ɾ���ý�㣬Ȼ�������ߣ�ֱ�����p�ĺ��ý��Ϊ������û������������㣩

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
	printf("�������������:%c",p->data);
	
}

int main(){
	LinkList L;
	//L= build(6);
    L = build(5);
    display(L);
	Joseph(L,3);
	return 0;
}
