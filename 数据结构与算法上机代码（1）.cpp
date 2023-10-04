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

void reverse1(LinkList &L) // 头插法
{
    node *p,*q,*r;
	p=L->next;
	if(p==NULL||p->next==NULL)
	{printf("无需逆置\n");
		return;
	}
	q=p->next;
	p->next=NULL; //让p指向尾部
    while(q!=NULL)
	{
		r=q->next; //保存结点
		q->next=p; //插到前面
		p=q;
		q=r;//向后移动
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
    if(L->next->next!=NULL) //递归出口
    {
        p=L->next;
        q=p->next;
        L->next=q; // 把p指针所指的结点拿出来
        p->next=NULL;
        reverse2(L);//调用自身
        q->next=p;//串起来
    }
}


/** 0. 逆置单链表
int main()
{
    LinkList L1;
	L1=build();
	display(L1); //输出原本的单链表
	reverse1(L1); 
	display(L1); //输出逆置的单链表
}
*/

// 1.寻找单链表的中点

// 算法一：利用双指针，都从头结点出发，快指针一次走两步，慢指针一次走一步，当快指针走到尾结点时慢指针刚好走到一半（中点
// 快慢指针：哈希判断法

/*
LinkList FindMiddle(LinkList L){ 
	    LinkList fast = L;
	    LinkList slow = L;
	    int flag = 0;  //flag用作标志变量，使得fast能够走两次并且不遇到非法状况
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
 
 // 算法二：把单链表先遍历一遍得到表长size，然后在遍历第二遍，到size/2+1就停住，则是中点，如果是偶数列则返回中间偏后的那个
 
 LinkList FindMiddle(LinkList L){
 	node *p;
 	p = L;
 	int size = 0;
 	while(p->next!=NULL){
	 	p = p->next;
	 	++size;
	 } //遍历第一次得出链表长度
	int k = 0;
	p = L;
	
	while(k < (size/2+1)){
		++k;
		p = p->next;
	}
	printf("\n");
 	return(p);
 	
 }

// 2.寻找单链表的倒数第K个点
//算法：把单链表先遍历一遍得到表长size，然后在遍历第二遍，到size-k就停住，即找到倒数第K个点

 LinkList FindLastK(LinkList L, int k){
 	node *p;
 	p = L;
 	int size = 0;
 	while(p->next!=NULL){
	 	p = p->next;
	 	++size;
	 } //遍历第一次得出链表长度

	p = L;
	if(k>size){return 0;}
	else{
	for(int i = 0; i<=(size-k);i++){
		p = p->next;
	}
	}
 	return(p);	
 }


// 3.删除单链表的倒数第K个点

LinkList DeleteLastK(LinkList L, int k){
	//查找到k点
		 node *p,*q;
	 	p = L;
	 	int size = 0;
	 	while(p->next!=NULL){
		 	p = p->next;
		 	++size;
		 } //遍历第一次得出链表长度
		p = L;
		if(k>size){return 0;}
		else{
		for(int i = 0; i<(size-k);i++){
			p = p->next;}
		}
	//把k点删掉
		q = p->next; 
		p->next = q->next;
		free(q);
		return(L); //返回删除后的单链表
}


// 4.判断单链表是否有环，如果有，找出交点
// 算法：先找到尾部的点，然后将单链表尾部的点与中点连起来，创造一个环；
// 后设定两个指针，一个快指针（一次走两步），一个慢指针（一次走一步），如果有环，那么必然两个指针必然相遇；如果不存在环，fast会提前到达NULL
// 有一个数学定理，即相遇点到连接点的距离等于头结点到连接点的距离。因此，在快慢指针相遇后，我们让慢指针重新指向头结点，快指针依旧指向相遇点，
//二者同时开始，每次向后移动一个节点，当快慢指针再次相遇时，相遇的位置即连接点。


LinkList FindCircle(LinkList L){
	node *fast, *slow;
	fast = L; slow = L;
	while(fast != NULL && fast->next != NULL){
		fast = fast->next->next;
		slow = slow->next;
		
		if(fast == slow) break; //两点相遇，跳出循环
		
	}
	
	if (fast == NULL || fast->next == NULL)	return NULL;
	
	slow = L; // slow指针回到原点
	while(slow != fast){
		slow = slow->next;
		fast = fast->next;
	}
	return slow;
}


// 5.判断两个单链表是否相交，如果相交，找出交点
// 算法一（长短判断）；如果两个链表相交，那么他们的尾结点必然相交，分别遍历到两个链表的尾部，并判断二者是否相同
//两个链表必然有长短之差，设短单链表的长度为len1，长单链表的长度为len2，让长的往后移|len2-len1|，然后判断两个尾结点是不是相同就可以得到结点


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
	// 在这里已经可以判定出有没有相交
	gap = abs(len1-len2);
	if(len1>len2){
		p = L1;
		q = L2;	
	}else{
		p = L2;
		q = L1;}//判断两个链表的长短
	while(gap--){
		p=p->next; //长的链表往后移gap个结点
	}
	while(p!=q){
		p = p->next;
		q = q->next;}
	return(p);// 返回相遇的点，即为两链表的交点
}
 

 
// 算法二：暴力拦截，L1的一个点与L2的所有点进行比较，第一个节点与L2的所有节点都不相同，就向后推，直到找到相同的点，或者走完。

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
	printf("没有交点");
}



// 6.对于有序单链表，删除重复节点（保留一个/无保留）

// 创立一个有重复的有序单链表
LinkList buildDuplicate(int n)   //单链表尾插法
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
		if(i>=3 && i<=6){ //设定重复范围
		for(int j = 0;j<=1;j++){ //设定重复次数
			p->next = new(node);
			p->next->data = i+'a'-1;
			p = p->next;
		}
		}
	}
	
	p->next=NULL;
	return(head);
}

// 算法（保留一个）：用一个指针p指向起始结点，如果p所指的值等于后继结点的值，则删除后继节点；否则p就指向后继节点。
//重复以上过程，直到p的后继节点为空
// 删掉重复的部分
 LinkList DropDuplicate (LinkList L){
    node *p,*q;
    p = L;
    while (p->next){   //当p的后继结点不为空时执行
        if (p->data == p->next->data){  //找到重复结点并删除
            q = p->next;		
            p->next = q->next;	
            free(q);			//释放q的空间，删除q
        }else{
            p = p->next;		//不重复则p后移一个位置
        }
    }
    return(L); //返回删除后的链表
}

//算法（无保留）：遍历单链表的时候，检查当前节点与下一点是否为相同值，如果相同，继续查找祥同值的最大长度，然后指针改变指向
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
			}//如果不相等就往后走
			else{
				while(q!=NULL && p->data == q->data){
					q = q->next;
				} // 找到第一个重复的点
			 while(p!=q){
			 	node *del = p->next;
			 	free(p);
			 	p = del;
			 } //把所有重复的结点都删掉
			pre->next = q;
			q = q->next; //重新连接pre,p,q
			}
			}		
        return(L); //返回删除后的链表
    }
    

// 7.约瑟夫问题：见单独文件

// 8.合并两个升序单链表（保留重复点），合并后为升序
// 算法：链表直接一个一个比过去，然后插入，后面的元素直接从插入的点的后面开始比较（因为是升序），为了提高效率，我们遍历短的链表
void CombineA(LinkList L1,LinkList L2){
	node *p,*q,*r;
	p = L1; q = L2;
	r = q->next;
	while(p){
		
		if(p->data >= q->data && p->data<=r->data){
			q->next = p;
			p->next = r; //如果小于前面，大于后面，则将短链表中的值插入长链表
		}else{
			q = q->next;
		}
		
		p = p->next;
	}
	
	printf("合成链表为");
	display(L1);
	
}



// 9.合并两个升序单链表（保留重复点），合并后为降序

// 10.判断一个单链表是否对称



//验证用的主函数

int main(){
	
	node *p1,*p2, *p3,*p4,*p5,*p6,*q,*p7;
	LinkList L1, L2, L3;

	L1 = build(11);
	L2 = build(17);
	L3 = buildDuplicate(10);
	
	printf("L1: ");display(L1);
	printf("L2: ");display(L2);
	reverse2(L1);
	printf("进行逆置操作后的单链表为："); display(L1);
	

	 
	//第一题：找到中点
	p1 = FindMiddle(L1);
//	printf("FindMiddle（中点的值为）: %c",p1->data);
//	printf("\n");
//	printf("\n");
	
	//第二题：找到倒数第K个点
	p2 = FindLastK(L1,1);
//	printf("FindLastK（倒数第K个点的值为）: %c",p2->data);
//	printf("\n");
	
	//第三题：删除倒数第K个点
	p3 = DeleteLastK(L1,5);
//	printf("\n");
//	printf("进行删除操作后的单链表为："); display(p3);
	
	//第四题：找单链表的环的点
	p2->next = p1; //把L1的中点和尾部的点相连，创造环的节点
	p4 = FindCircle(L1);
//	printf("\n");
//	printf("单链表环的相交结点为: %c", p4->data);
	
	// 第五题：找两个链表相交的点
	q = FindMiddle(L2);
	p1->next = q; //让L1的中点与L2的中点相连，创造相交
//	printf("\n两个链表交点为："); 
//	FindCross1(L1, L2); //找出交点
	/***
	p5 = FindCross(L1,L2);
	printf("\n两个链表交点为：%c",p5->data);
	*/

	// 第六题：找重复的点
	printf("\n");
	printf("删除之前的链表：");display(L3);
	//p6=DropDuplicate(L3);
	//printf("\n");
//	printf("删除重复的点后的链表（有保留）：");display(p6);
	//printf("\n");
	p7 = DropAllDuplicate(L3);
	printf("删除重复的点后的链表（无保留）：");display(p7);
	printf("\n");
	
	// 第七题：约瑟夫算法（见单独文件）
	
	// 第八/九题：合并单链表（见单独文件）
	
	// 第十题：判断对称（见单独文件）
	
	

}
