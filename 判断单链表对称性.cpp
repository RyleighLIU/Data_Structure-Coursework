#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	char data;
	node *next;
}node;
typedef node *LinkList;

LinkList buildSym(int n)   //创建对称链表（偶数）
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

// 第十题：判断单链表是否对称
// 算法一：直接比较，设立两个指针p和q，p都从头出发，p与q位置对称，循环比较数据，由于没有前驱节点，
//只能每循环一次将q放回原点再走，走到中点时停下来，过程中数据如果出现任何不相等即停止。


void isSym(LinkList L){
	node *p,*q;
	p = L;int len = 0;
	while(p->next){
	p = p->next;
	len++;
	}	
	p = L->next;//让p回到原点
	int i,j;
	
	for(i=len;i>len/2;i--){
		q=L; //每次循环都回到原点，一共要比len/2次，回原点要回len/2次
		for(j=i;j>0;j--){
			q = q->next; 
		}
		if(p->data == q->data){
			p=p->next; //如果二者相等则p指针往后推，同时在再进入一次循环，再与q比较一次
		}else{
			printf("\n结果：不对称"); //出现不相等的立马输出不对称，并结束
			return;
		}
	}
	printf("\n结果：对称"); //如果循环跑完了都没有出现不对称的话，那么说明对称
	
}


//算法二：利用数组，把前一半数据储存在数组里面，然后倒过来，从后往前和后半段的数据一一比较，如果没有出现不相等的情况则对称

void isSym1(LinkList L)
{
	node *p;
		p = L;int len = 0;
		while(p->next!=NULL){
		p = p->next;
		len++;
		}		
	char a[20]; //设定储存前半部分的数组
	
	p=L->next;
	int i;
	for(i=0;i<len/2;i++)
	{	
		a[i]=p->data;
		p=p->next;//用数组储存链表的前半部分
	}
	i--;
	while(p && i>=0){
		if(a[i]==p->data){
			i--;
			p = p->next;
		}
		else{
			printf("结果：不对称");
			return;
		}
	}
	printf("结果：对称");
	return;	
}


int main(){
	LinkList L;
	L = buildSym(4);
	display(L);
	isSym1(L);
}
