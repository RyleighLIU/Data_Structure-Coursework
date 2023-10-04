#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	char data;
	node *next;
}node;
typedef node *LinkList;

LinkList buildSym(int n)   //�����Գ�����ż����
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
	for(i = n;i>0;i--){
		p->next = new(node);
		p->next->data = i+'a'-1;
		p = p->next;
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

// ��ʮ�⣺�жϵ������Ƿ�Գ�
// �㷨һ��ֱ�ӱȽϣ���������ָ��p��q��p����ͷ������p��qλ�öԳƣ�ѭ���Ƚ����ݣ�����û��ǰ���ڵ㣬
//ֻ��ÿѭ��һ�ν�q�Ż�ԭ�����ߣ��ߵ��е�ʱͣ������������������������κβ���ȼ�ֹͣ��


void isSym(LinkList L){
	node *p,*q;
	p = L;int len = 0;
	while(p->next){
	p = p->next;
	len++;
	}	
	p = L->next;//��p�ص�ԭ��
	int i,j;
	
	for(i=len;i>len/2;i--){
		q=L; //ÿ��ѭ�����ص�ԭ�㣬һ��Ҫ��len/2�Σ���ԭ��Ҫ��len/2��
		for(j=i;j>0;j--){
			q = q->next; 
		}
		if(p->data == q->data){
			p=p->next; //������������pָ�������ƣ�ͬʱ���ٽ���һ��ѭ��������q�Ƚ�һ��
		}else{
			printf("\n��������Գ�"); //���ֲ���ȵ�����������Գƣ�������
			return;
		}
	}
	printf("\n������Գ�"); //���ѭ�������˶�û�г��ֲ��ԳƵĻ�����ô˵���Գ�
	
}


//�㷨�����������飬��ǰһ�����ݴ������������棬Ȼ�󵹹������Ӻ���ǰ�ͺ��ε�����һһ�Ƚϣ����û�г��ֲ���ȵ������Գ�

void isSym1(LinkList L)
{
	node *p;
		p = L;int len = 0;
		while(p->next!=NULL){
		p = p->next;
		len++;
		}		
	char a[20]; //�趨����ǰ�벿�ֵ�����
	
	p=L->next;
	int i;
	for(i=0;i<len/2;i++)
	{	
		a[i]=p->data;
		p=p->next;//�����鴢�������ǰ�벿��
	}
	i--;
	while(p && i>=0){
		if(a[i]==p->data){
			i--;
			p = p->next;
		}
		else{
			printf("��������Գ�");
			return;
		}
	}
	printf("������Գ�");
	return;	
}


int main(){
	LinkList L;
	L = buildSym(4);
	display(L);
	isSym1(L);
}
