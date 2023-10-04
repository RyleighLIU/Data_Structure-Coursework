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

void reverse1(LinkList &L) // ͷ�巨
{
    node *p,*q,*r;
	p=L->next;
	if(p==NULL||p->next==NULL)
	{printf("��������\n");
		return;
	}
	q=p->next;
	p->next=NULL; //��pָ��β��
    while(q!=NULL)
	{
		r=q->next; //������
		q->next=p; //�嵽ǰ��
		p=q;
		q=r;//����ƶ�
	}
	L->next=p;
}

void reverse(LinkList &L)
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
		q->next=L->next;
		L->next=q;
		q=r;
	}
}

void reverse2(LinkList &L)
{
    node *p,*q;
    if(L->next->next!=NULL) //�ݹ����
    {
        p=L->next;
        q=p->next;
        L->next=q; // ��pָ����ָ�Ľ���ó���
        p->next=NULL;
        reverse2(L);//��������
        q->next=p;//������
    }
}


/** 0. ���õ�����
int main()
{
    LinkList L1;
	L1=build();
	display(L1); //���ԭ���ĵ�����
	reverse1(L1); 
	display(L1); //������õĵ�����
}
*/

// 1.Ѱ�ҵ�������е�

// �㷨һ������˫ָ�룬����ͷ����������ָ��һ������������ָ��һ����һ��������ָ���ߵ�β���ʱ��ָ��պ��ߵ�һ�루�е�
// ����ָ�룺��ϣ�жϷ�

/*
LinkList FindMiddle(LinkList L){ 
	    LinkList fast = L;
	    LinkList slow = L;
	    int flag = 0;  //flag������־������ʹ��fast�ܹ������β��Ҳ������Ƿ�״��
	    while(fast->next){
	        if(!flag){ 
	            fast = fast->next;
	            flag = 1;
	        }
	        else{
	            fast = fast->next;
	            slow = slow->next;
	            flag = 0;
	        }
	    }
	    return slow->next;  
	 
 }
 
 */
 
 // �㷨�����ѵ������ȱ���һ��õ���size��Ȼ���ڱ����ڶ��飬��size/2+1��ͣס�������е㣬�����ż�����򷵻��м�ƫ����Ǹ�
 
 LinkList FindMiddle(LinkList L){
 	node *p;
 	p = L;
 	int size = 0;
 	while(p->next!=NULL){
	 	p = p->next;
	 	++size;
	 } //������һ�εó�������
	int k = 0;
	p = L;
	
	while(k < (size/2+1)){
		++k;
		p = p->next;
	}
	printf("\n");
 	return(p);
 	
 }

// 2.Ѱ�ҵ�����ĵ�����K����
//�㷨���ѵ������ȱ���һ��õ���size��Ȼ���ڱ����ڶ��飬��size-k��ͣס�����ҵ�������K����

 LinkList FindLastK(LinkList L, int k){
 	node *p;
 	p = L;
 	int size = 0;
 	while(p->next!=NULL){
	 	p = p->next;
	 	++size;
	 } //������һ�εó�������

	p = L;
	if(k>size){return 0;}
	else{
	for(int i = 0; i<=(size-k);i++){
		p = p->next;
	}
	}
 	return(p);	
 }


// 3.ɾ��������ĵ�����K����

LinkList DeleteLastK(LinkList L, int k){
	//���ҵ�k��
		 node *p,*q;
	 	p = L;
	 	int size = 0;
	 	while(p->next!=NULL){
		 	p = p->next;
		 	++size;
		 } //������һ�εó�������
		p = L;
		if(k>size){return 0;}
		else{
		for(int i = 0; i<(size-k);i++){
			p = p->next;}
		}
	//��k��ɾ��
		q = p->next; 
		p->next = q->next;
		free(q);
		return(L); //����ɾ����ĵ�����
}


// 4.�жϵ������Ƿ��л�������У��ҳ�����
// �㷨�����ҵ�β���ĵ㣬Ȼ�󽫵�����β���ĵ����е�������������һ������
// ���趨����ָ�룬һ����ָ�루һ������������һ����ָ�루һ����һ����������л�����ô��Ȼ����ָ���Ȼ��������������ڻ���fast����ǰ����NULL
// ��һ����ѧ�����������㵽���ӵ�ľ������ͷ��㵽���ӵ�ľ��롣��ˣ��ڿ���ָ����������������ָ������ָ��ͷ��㣬��ָ������ָ�������㣬
//����ͬʱ��ʼ��ÿ������ƶ�һ���ڵ㣬������ָ���ٴ�����ʱ��������λ�ü����ӵ㡣


LinkList FindCircle(LinkList L){
	node *fast, *slow;
	fast = L; slow = L;
	while(fast != NULL && fast->next != NULL){
		fast = fast->next->next;
		slow = slow->next;
		
		if(fast == slow) break; //��������������ѭ��
		
	}
	
	if (fast == NULL || fast->next == NULL)	return NULL;
	
	slow = L; // slowָ��ص�ԭ��
	while(slow != fast){
		slow = slow->next;
		fast = fast->next;
	}
	return slow;
}


// 5.�ж������������Ƿ��ཻ������ཻ���ҳ�����
// �㷨һ�������жϣ���������������ཻ����ô���ǵ�β����Ȼ�ཻ���ֱ���������������β�������ж϶����Ƿ���ͬ
//���������Ȼ�г���֮���̵�����ĳ���Ϊlen1����������ĳ���Ϊlen2���ó���������|len2-len1|��Ȼ���ж�����β����ǲ�����ͬ�Ϳ��Եõ����


LinkList FindCross(LinkList L1, LinkList L2){
	node *p, *q;
	p = L1;q = L2;
	int len1 = 0;	int len2 = 0;	int gap = 0;
	while(p->next!= NULL){
		p = p->next;
		++len1;}
	while(q->next!= NULL){
		q = q->next;
		++len2;}
	if(p != q) return 0;
	// �������Ѿ������ж�����û���ཻ
	gap = abs(len1-len2);
	if(len1>len2){
		p = L1;
		q = L2;	
	}else{
		p = L2;
		q = L1;}//�ж���������ĳ���
	while(gap--){
		p=p->next; //��������������gap�����
	}
	while(p!=q){
		p = p->next;
		q = q->next;}
	return(p);// ���������ĵ㣬��Ϊ������Ľ���
}
 

 
// �㷨�����������أ�L1��һ������L2�����е���бȽϣ���һ���ڵ���L2�����нڵ㶼����ͬ��������ƣ�ֱ���ҵ���ͬ�ĵ㣬�������ꡣ

void FindCross1(LinkList L1, LinkList L2){
	node *p,*q;
	p = L1; q = L2;
	while(p!=NULL){
		q = L2;
		while(q!=NULL){
			if(p==q){
				printf("%c",p->data);
				return;
			}else{
				q = q->next;
			}
	
		}
		p = p->next;
	}
	printf("û�н���");
}



// 6.������������ɾ���ظ��ڵ㣨����һ��/�ޱ�����

// ����һ�����ظ�����������
LinkList buildDuplicate(int n)   //������β�巨
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
		if(i>=3 && i<=6){ //�趨�ظ���Χ
		for(int j = 0;j<=1;j++){ //�趨�ظ�����
			p->next = new(node);
			p->next->data = i+'a'-1;
			p = p->next;
		}
		}
	}
	
	p->next=NULL;
	return(head);
}

// �㷨������һ��������һ��ָ��pָ����ʼ��㣬���p��ָ��ֵ���ں�̽���ֵ����ɾ����̽ڵ㣻����p��ָ���̽ڵ㡣
//�ظ����Ϲ��̣�ֱ��p�ĺ�̽ڵ�Ϊ��
// ɾ���ظ��Ĳ���
 LinkList DropDuplicate (LinkList L){
    node *p,*q;
    p = L;
    while (p->next){   //��p�ĺ�̽�㲻Ϊ��ʱִ��
        if (p->data == p->next->data){  //�ҵ��ظ���㲢ɾ��
            q = p->next;		
            p->next = q->next;	
            free(q);			//�ͷ�q�Ŀռ䣬ɾ��q
        }else{
            p = p->next;		//���ظ���p����һ��λ��
        }
    }
    return(L); //����ɾ���������
}

//�㷨���ޱ������������������ʱ�򣬼�鵱ǰ�ڵ�����һ���Ƿ�Ϊ��ֵͬ�������ͬ������������ֵͬ����󳤶ȣ�Ȼ��ָ��ı�ָ��
LinkList DropAllDuplicate (LinkList L){
    node *pre,*p,*q;
    pre=L;
    p = pre->next;
    q = p->next;
		while (q->next) {
			if(p->data!=q->data){
				pre = p;
				p = q;
				q = q->next;
			}//�������Ⱦ�������
			else{
				while(q!=NULL && p->data == q->data){
					q = q->next;
				} // �ҵ���һ���ظ��ĵ�
			 while(p!=q){
			 	node *del = p->next;
			 	free(p);
			 	p = del;
			 } //�������ظ��Ľ�㶼ɾ��
			pre->next = q;
			q = q->next; //��������pre,p,q
			}
			}		
        return(L); //����ɾ���������
    }
    

// 7.Լɪ�����⣺�������ļ�

// 8.�ϲ������������������ظ��㣩���ϲ���Ϊ����
// �㷨������ֱ��һ��һ���ȹ�ȥ��Ȼ����룬�����Ԫ��ֱ�ӴӲ���ĵ�ĺ��濪ʼ�Ƚϣ���Ϊ�����򣩣�Ϊ�����Ч�ʣ����Ǳ����̵�����
void CombineA(LinkList L1,LinkList L2){
	node *p,*q,*r;
	p = L1; q = L2;
	r = q->next;
	while(p){
		
		if(p->data >= q->data && p->data<=r->data){
			q->next = p;
			p->next = r; //���С��ǰ�棬���ں��棬�򽫶������е�ֵ���볤����
		}else{
			q = q->next;
		}
		
		p = p->next;
	}
	
	printf("�ϳ�����Ϊ");
	display(L1);
	
}



// 9.�ϲ������������������ظ��㣩���ϲ���Ϊ����

// 10.�ж�һ���������Ƿ�Գ�



//��֤�õ�������

int main(){
	
	node *p1,*p2, *p3,*p4,*p5,*p6,*q,*p7;
	LinkList L1, L2, L3;

	L1 = build(11);
	L2 = build(17);
	L3 = buildDuplicate(10);
	
	printf("L1: ");display(L1);
	printf("L2: ");display(L2);
	reverse2(L1);
	printf("�������ò�����ĵ�����Ϊ��"); display(L1);
	

	 
	//��һ�⣺�ҵ��е�
	p1 = FindMiddle(L1);
//	printf("FindMiddle���е��ֵΪ��: %c",p1->data);
//	printf("\n");
//	printf("\n");
	
	//�ڶ��⣺�ҵ�������K����
	p2 = FindLastK(L1,1);
//	printf("FindLastK��������K�����ֵΪ��: %c",p2->data);
//	printf("\n");
	
	//�����⣺ɾ��������K����
	p3 = DeleteLastK(L1,5);
//	printf("\n");
//	printf("����ɾ��������ĵ�����Ϊ��"); display(p3);
	
	//�����⣺�ҵ�����Ļ��ĵ�
	p2->next = p1; //��L1���е��β���ĵ����������컷�Ľڵ�
	p4 = FindCircle(L1);
//	printf("\n");
//	printf("���������ཻ���Ϊ: %c", p4->data);
	
	// �����⣺�����������ཻ�ĵ�
	q = FindMiddle(L2);
	p1->next = q; //��L1���е���L2���е������������ཻ
//	printf("\n����������Ϊ��"); 
//	FindCross1(L1, L2); //�ҳ�����
	/***
	p5 = FindCross(L1,L2);
	printf("\n����������Ϊ��%c",p5->data);
	*/

	// �����⣺���ظ��ĵ�
	printf("\n");
	printf("ɾ��֮ǰ������");display(L3);
	//p6=DropDuplicate(L3);
	//printf("\n");
//	printf("ɾ���ظ��ĵ��������б�������");display(p6);
	//printf("\n");
	p7 = DropAllDuplicate(L3);
	printf("ɾ���ظ��ĵ��������ޱ�������");display(p7);
	printf("\n");
	
	// �����⣺Լɪ���㷨���������ļ���
	
	// �ڰ�/���⣺�ϲ��������������ļ���
	
	// ��ʮ�⣺�ж϶Գƣ��������ļ���
	
	

}
