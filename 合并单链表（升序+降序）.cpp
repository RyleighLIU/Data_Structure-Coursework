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

// �ڰ��⣺����
// �㷨����������������β�巨����������Ƚ�Ȼ��Ѱ�˳�����еĽ���������ηŽ�����������
void MergeAscending(LinkList L1, LinkList L2)
{	LinkList L3;
	LinkList p1, p2, p3;
	p1 = L1->next;
	p2 = L2->next;
	L3 = p3 = new(node); //����һ���ս��
	while (p1 && p2)
	{
		if (p1->data <= p2->data)
		{ //��С������(p1)���ӵ�L3����
			p3->next = p1;
			p3 = p1;	   //��ָ֤�����Ľڵ���
			p1 = p1->next; //ָ�����
		}
		else if (p1->data > p2->data)
		{ 
			p3->next = p2;
			p3 = p2;
			p2 = p2->next;
		}

	}
	p3->next = p1?p1:p2;
	//����ѱȽ�֮��ʣ�µ�ֵ�����ȥ�����p1��Ϊ�վ�ȡp1��ֵ���ȥ������ȡp2
	display(L3);
}



// �ھ��⣺����
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


// �㷨һ�����úϲ�Ϊ������㷨��β�巨�������������У�Ȼ��ֱ����reverse�������þ��ǵ���ġ�

void MergeDescending1(LinkList L1, LinkList L2,LinkList L3){
		LinkList p1, p2, p3;
		p1 = L1->next;
		p2 = L2->next;
		L3 = p3 = new(node); //����һ���ս��
		while (p1 && p2)
		{
			if (p1->data <= p2->data)
			{ //��С������(p1)���ӵ�L3����
				p3->next = p1;
				p3 = p1;	   //��ָ֤�����Ľڵ���
				p1 = p1->next; //ָ�����
			}
			else if (p1->data > p2->data)
			{ //��С������(p2)���ӵ�L3����
				p3->next = p2;
				p3 = p2;
				p2 = p2->next;
			}
	
		}
		p3->next = p1?p1:p2;//����ѱȽ�֮��ʣ�µ�ֵ�����ȥ�����p1��Ϊ�վ�ȡp1��ֵ���ȥ������ȡp2
		reverse1(L3);
		display(L3);
}



// �㷨����������������ͷ�巨���ѱȽϺ��С����һ���Ȳ��룬Ȼ�󲻶�ǰ�壬��������������
void MergeDescending(LinkList L1, LinkList L2){
		LinkList p1, p2, p3,q;
		p1 = L1->next;
		p2 = L2->next;
		p3 = new(node); //����һ���ս��
		p3->next = NULL;
		
		while (p1 && p2)
		{
			if (p1->data <= p2->data)
			{ //��С������(p1)���ӵ�L3����
				q = p1;
				p1 = p1->next; //ָ�����
				q->next = p3->next;	   
				p3 ->next =q; //ͷ�巨
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
				p3 ->next =q; //ͷ�巨
			
			}else if(p2!=NULL){
			q = p2;
			p2 = p2->next;
			q->next = p3->next;
			p3->next = q;
			}
		}
		//����ѱȽ�֮��ʣ�µ�ֵ�����ȥ�����p1��Ϊ�վ�ȡp1��ֵ���ȥ������ȡp2
		
		display(p3);
}


int main(){
	LinkList L1,L2;
	L1 = build(3);
	L2 = build(5);
	
	printf("L1:");display(L1);
	printf("L2:");display(L2);
	
//	printf("�ϲ���ı�Ϊ�����򣩣�");
//	MergeAscending(L1,L2);
	
	printf("\n�ϲ���ı�Ϊ�����򣩣�");
	MergeDescending(L1,L2);
	
}
