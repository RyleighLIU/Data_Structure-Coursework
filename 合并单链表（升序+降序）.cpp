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

// 第八题：升序
// 算法：创造新链表，利用尾插法，两个链表比较然后把按顺序排列的结点数据依次放进进新链表中
void MergeAscending(LinkList L1, LinkList L2)
{	LinkList L3;
	LinkList p1, p2, p3;
	p1 = L1->next;
	p2 = L2->next;
	L3 = p3 = new(node); //创建一个空结点
	while (p1 && p2)
	{
		if (p1->data <= p2->data)
		{ //把小的数据(p1)链接到L3表上
			p3->next = p1;
			p3 = p1;	   //保证指向最后的节点上
			p1 = p1->next; //指针后移
		}
		else if (p1->data > p2->data)
		{ 
			p3->next = p2;
			p3 = p2;
			p2 = p2->next;
		}

	}
	p3->next = p1?p1:p2;
	//这里把比较之后剩下的值给填进去，如果p1不为空就取p1的值填进去，否则取p2
	display(L3);
}



// 第九题：降序
void reverse1(LinkList &L)
{
    node *p,*q,*r;
	p=L->next;
	if(p==NULL||p->next==NULL)
	{printf("No reverse needed!\n");
		return;
	}
	q=p->next;
	p->next=NULL;
    while(q!=NULL)
	{
		r=q->next;
		q->next=p;
		p=q;
		q=r;
	}
	L->next=p;
}


// 算法一：先用合并为升序的算法（尾插法）算出升序的排列，然后直接用reverse函数逆置就是倒序的。

void MergeDescending1(LinkList L1, LinkList L2,LinkList L3){
		LinkList p1, p2, p3;
		p1 = L1->next;
		p2 = L2->next;
		L3 = p3 = new(node); //创建一个空结点
		while (p1 && p2)
		{
			if (p1->data <= p2->data)
			{ //把小的数据(p1)链接到L3表上
				p3->next = p1;
				p3 = p1;	   //保证指向最后的节点上
				p1 = p1->next; //指针后移
			}
			else if (p1->data > p2->data)
			{ //把小的数据(p2)链接到L3表上
				p3->next = p2;
				p3 = p2;
				p2 = p2->next;
			}
	
		}
		p3->next = p1?p1:p2;//这里把比较之后剩下的值给填进去，如果p1不为空就取p1的值填进去，否则取p2
		reverse1(L3);
		display(L3);
}



// 算法二：创建新链表，用头插法，把比较后更小的那一个先插入，然后不断前插，创建出倒序单链表
void MergeDescending(LinkList L1, LinkList L2){
		LinkList p1, p2, p3,q;
		p1 = L1->next;
		p2 = L2->next;
		p3 = new(node); //创建一个空结点
		p3->next = NULL;
		
		while (p1 && p2)
		{
			if (p1->data <= p2->data)
			{ //把小的数据(p1)链接到L3表上
				q = p1;
				p1 = p1->next; //指针后移
				q->next = p3->next;	   
				p3 ->next =q; //头插法
			}
			else if (p1->data > p2->data)
			{ 
				q = p2;
				p2 = p2->next;
				q->next = p3->next;
				p3->next = q;
			}
	
		}
		
		while(p1||p2){
			if(p1!=NULL){
				q = p1;
				p1 = p1->next;
				q->next = p3->next;	   
				p3 ->next =q; //头插法
			
			}else if(p2!=NULL){
			q = p2;
			p2 = p2->next;
			q->next = p3->next;
			p3->next = q;
			}
		}
		//这里把比较之后剩下的值给插进去，如果p1不为空就取p1的值插进去，否则取p2
		
		display(p3);
}


int main(){
	LinkList L1,L2;
	L1 = build(3);
	L2 = build(5);
	
	printf("L1:");display(L1);
	printf("L2:");display(L2);
	
//	printf("合并后的表为（升序）：");
//	MergeAscending(L1,L2);
	
	printf("\n合并后的表为（降序）：");
	MergeDescending(L1,L2);
	
}
