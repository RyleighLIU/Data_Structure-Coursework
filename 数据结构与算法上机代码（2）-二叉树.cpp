#include<stdio.h>
#include<queue>
#include<stdlib.h>
#include<string>
#include<utility>

using namespace std;

typedef struct node{
char data;
struct node *lchild,*rchild;
} node;

typedef node *bitree;

// 栈结构定义
typedef struct stack {
	bitree data[100];
	int top; // 栈顶指针
}seqstack; //定义顺序栈

// 进栈函数（栈顶进栈）
void push(seqstack *s, bitree t){
	s->data[++s->top] = t;
}

// 出栈函数（栈顶出栈）
bitree pop(seqstack *s){
	if(s->top != -1){
		s->top--;
		return(s->data[s->top+1]);
	}else{
		return NULL;
	}
}

typedef struct
{
    bitree *base;
    int  front;   //头指针指示器 
    int  rear;  //尾指针指示器
} Sequeue;

typedef struct Queue
{
  node *data[100];
  int front;
  int rear;
}Queue;

// 0.1 用递归方法建立二叉树
bitree buildtree()
{
    char c;
    node *p;
    c=getchar();
    if(c=='0')
    {
        p=NULL;
    }
    else
    {
           p=new(node);
           p->data=c;
           p->lchild=buildtree();
           p->rchild=buildtree();
    }
    return(p);
}

// 0.2 用非递归方法前序遍历二叉树（利用栈来存放）
// 算法思想：在访问完t->data后，将t入栈，遍历左子树；遍历完左子树返回时，栈顶元素应为t，出栈，再先序遍历t的右子树
void DLR_nonrecursive(bitree t){
	seqstack s;
	s.top = -1; // 初始化
	// 判断当前子树不为空或者栈不为空则循环
	while((t!=NULL)||(s.top!=-1)){
		while(t!=NULL){
			printf("%c",t->data);
			s.top++;
			s.data[s.top]=t;
			t=t->lchild; 
		}// 用这个子循环遍历树的左子树
		if(s.top>-1){
			t = pop(&s); //若左子树为空则把栈顶弹出
			t = t->rchild; // 开始遍历右子树
		}
	}
}


// 0.3.1 递归方法前序遍历二叉树
void DLR( node *root )
{if (root ==NULL) return; //空二叉树
 printf("%c",root->data); //访问根节点
 DLR(root->lchild); //递归遍历左子树
 DLR(root->rchild); //递归遍历右子树
 }
// 0.3.2 递归方法中序遍历二叉树
void LDR( node *root )
{if (root ==NULL) return; //空二叉树
 LDR(root->lchild);
 printf("%c",root->data); //访问根节点
 LDR(root->rchild);
 }
// 0.3.3 递归方法后序遍历二叉树
void LRD( node *root )
{if (root ==NULL) return; //空二叉树
 LRD(root->lchild);
 LRD(root->rchild);
 printf("%c",root->data); //访问根节点
 }

// 1. 将二叉树对称交换，即求二叉树镜像
// 算法一：递归算法，先把左子树中的节点放到rchild中，然后再把右边结点放到lchild中，这个过程中要先把左节点暂存到一个地方
void mirrorTree1(node *root){
	node *temp;
	if(root){
		temp = root->lchild;
		root->lchild = root->rchild;
		root->rchild = temp; //交换根节点左右孩子指针
		mirrorTree1(root->lchild);//对左子树也做一样的操作
		mirrorTree1(root->rchild);//对右子树做一样的操作
	}
}

// 算法二：利用队列先进先出的特性，层次遍历每一层，然后在队列内部做互换，然后再输出。
void mirrorTree2(bitree t){
	node *temp;
	queue<bitree> q;
	q.push(t);
		while(!q.empty()){
		node *t1 = q.front(); //创建新节点把队首根节点存进去
		printf("%c",t1->data);
		q.pop(); // 弹出来让子树入队
		
		temp = t1->lchild;
		t1->lchild = t1->rchild;
		t1->rchild = temp; //互换操作	
		
		if(t1->lchild){
			q.push(t1->lchild); //左子树入队
		}
		if(t->rchild){
			q.push(t1->rchild); //右子树入队
			}
		}
}



// 2.求二叉树的高度，即深度
// 算法：递归算法，为了求得树的深度，可以先求左右子树的深度，取二者较大者加1即是树的深度，

int bitreeDepth(bitree t){
	int left =0; 
	int right = 0; 
	if(t) {
	left = bitreeDepth(t->lchild)+1;
	right = bitreeDepth(t->rchild)+1;//子树的最大深度+1（根节点）
	}
	 return left>=right?left:right;
}

// 非递归算法：利用层序遍历，当当前节点数小于队列的size的时候，说明这一层没有结束，继续推进。
int bitreeDepth2(bitree t)
{ 
 	queue<bitree> q; // 直接调用C++队列头文件建立队列
 	q.push(t);// 根节点入队
 	int num = 0; //记录节点数
 	int depth = 0; //记录层数
 	while(!q.empty()){
 		++depth;
 		num = q.size(); //节点数即为队列的长度
		//当前层节点的个数
		int current_num = 0;
		while(current_num < num) //当前结点个数小于size的时候->推进
		{
		    ++current_num;
			node *t1 = q.front(); //创建新节点把队首根节点存进去
		 	q.pop(); // 弹出来让子树入队
		 	if(t1->lchild){
		 		q.push(t1->lchild); //左子树入队
		 	}
		 	if(t1->rchild){
		 		q.push(t1->rchild); //右子树入队
		 	}
		      }
 	}
	return depth;	
}


// 3. 已知前序序列和中序序列，构造二叉树
// 算法：可以知道先序序列的第一个是根节点，在中序序列中找到根节点，根节点左边的都是左子树，
//右边的就是右子树的成员，再进行函数递归，重新赋值对子树进行一样的操作，最后构造出一颗二叉树。

bitree buildTree_Pre_In(string pre,string in,int a,int b,int c,int d)
{
	node *root;
	if(a <= b)
	{
		root = new(node);	 //创建根节点	
		root->data = pre[a]; 	//存入根节点数值
		root->lchild = NULL;	
		root->rchild = NULL;	
		int i;
		for(i = c; i <= d; i++)		//在中序序列中查找根的位置i 
		{
			if(in[i] == pre[a])
				break;  //找到之后出循环
		}
		root->lchild = buildTree_Pre_In(pre,in,a+1,a+i-c,c,i-1);	//递归建左子树 
		root->rchild = buildTree_Pre_In(pre,in,a+i-c+1,b,i+1,d);	//递归建右子树 
	}
	return root;
}


// 4. 分层遍历二叉树，即按层次从上往下，从左往右顺序访问 
// 算法：利用队列先进先出的性质，先把根节点入队，然后让根节点的左子树和右子树同时入队，然后依次出队
void levelOrder(bitree t){
	queue<bitree> q; // 直接调用C++队列头文件建立队列
	q.push(t);// 根节点入队
	while(!q.empty()){
		node *t1 = q.front(); //创建新节点把队首根节点存进去
		printf("%c",t1->data);
		q.pop(); // 弹出来让子树入队
		if(t1->lchild){
			q.push(t1->lchild); //左子树入队
		}
		if(t->rchild){
			q.push(t1->rchild); //右子树入队
		}
	}
}

// 5.求二叉树的宽度，即求最大结点数的层所具有的结点数
// 算法：层次遍历二叉树，设定一个特别的标记#来标记每一层的最右边，代表一层遍历的结束
// 但是用mark会导致陷入无限循环因为最后剩下的那个一定是#，因此每当遍历到#时，要看队列中是否还有其他元素
int treeWidth(bitree t)
{
  if(t==NULL) return 0; //树为空直接返回
  int num = 0; //记录每一层节点数
  int max = 0; //记录节点中的最大值
  Queue q;
  q.rear = 0; q.front = 0;//初始化队列
  q.data[q.rear++] = t; // 二叉树入队

  bitree tree = new(node);
  tree->data = '#'; //特殊标记
  tree->lchild = NULL;
  tree->rchild = NULL;
  q.data[q.rear++] = tree;//标记#入队
  while(q.rear!=q.front) // 判断队列是否为空
  {
    tree = q.data[q.front++];  //在层次遍历中加入一个#判断
    if(tree->data=='#')  //碰到#结点
    {
      if(max<num)
      {
        max = num;
        num = 0;
      } //判断最大节点数
      if(q.data[q.front]!=NULL) //如果队不为空->即还有其他元素
      {
        tree = new(node);//加标记
        tree->data = '#'; 
        tree->lchild = NULL;
        tree->rchild = NULL;
        q.data[q.rear++] = tree;
      }
      
    }else {// 没碰到结点往后推+计数
      ++num;
      if(tree->lchild) q.data[q.rear++] = tree->lchild;
      if(tree->rchild) q.data[q.rear++] = tree->rchild;
    }
  }
  	return max;
}

//  第六题：求二叉树的结点个数
// 利用队列进行层次遍历，设置计时器进行加总即可。
int nodeCount(bitree t)
{
  if(t==NULL) return 0; //树为空直接返回
  int num = 0; //记录节点数
  Queue q;//利用队列
  q.rear = 0;
  q.front = 0;//初始化队列
  q.data[q.rear++] = t; // 头结点入队
  while(q.rear!=q.front) // 判断队列是否为空
  {
    t = q.data[q.front++];  
      ++num;
      if(t->lchild) q.data[q.rear++] = t->lchild;
      if(t->rchild) q.data[q.rear++] = t->rchild;
    
  }
  	return num;
}

// 第七题：非递归方法中序、后序遍历二叉树
// 利用栈来实现
void InOrder(bitree t)
{
	seqstack s;
	s.top = -1; // 初始化
	node *root = t;
	// 判断当前子树不为空或者栈不为空则循环
	while((root!=NULL)||(s.top!=-1)){
		while(root!=NULL){
			s.top++;
			s.data[s.top]=root;
			root=root->lchild; 
		}// 一直遍历到左子树最下边，边遍历边保存根节点到栈中
		if(s.top>-1){ //若栈不为空
			root = pop(&s); //若左子树为空则把栈顶弹出
			printf("%c",root->data);
			root = root->rchild; // 开始遍历右子树
		}
	}
}

void postOrder(bitree t)
{
	seqstack s;
	s.top = -1; // 初始化
	node *root = t;
	node *last = NULL; // 上一个访问的结点
		while(root!=NULL){
			s.top++;
			s.data[s.top]=root;
			root=root->lchild; 
		}// 走到这里已经到左子树最下边
		while((s.top!=-1)){
		root = pop(&s);
		if (root->rchild == NULL || root->rchild == last)
		//判断根节点的右节点是否被访问过(=last)
		{	printf("%c",root->data);
				last = root;	// 更新上一个被访问的节点
				}else{
					s.top++;
					s.data[s.top]=root; //根节点再入栈
					root = root->rchild; //进入右子树
					while (root!=NULL){	 
					s.top++;
					s.data[s.top]=root;
					root = root->lchild; 
				}
		}
	}
}

//第八题：
// 算法1：采用层序遍历，并且加一个计数器，当计数器等于K时，计算当层节点数，并返回该节点数。
int nodecountK1(bitree t,int K)
{ 
 	queue<bitree> q; // 直接调用C++队列头文件建立队列
 	q.push(t);// 根节点入队
 	int num = 0; //记录节点数
 	int depth = 0; //记录层数
 	
 	while(!q.empty()){
 		++depth;
 		num = q.size(); //节点数即为队列的长度
 		if(depth==K) break;// 如果找到第k层了就跳出循环
		//当前层节点的个数
		int current_num = 0;
		while(current_num < num) //当前结点个数小于size的时候->推进
		{
		    ++current_num;
			node *t1 = q.front(); //创建新节点把队首根节点存进去
		 	q.pop(); // 弹出来让子树入队
		 	if(t1->lchild){
		 		q.push(t1->lchild); //左子树入队
		 	}
		 	if(t1->rchild){
		 		q.push(t1->rchild); //右子树入队
		 	}
		      }
		}
		if(depth == K) return num;	
}

// 算法2：运用递归算法，
int nodecountK2(bitree t,int k)
{
    if(!t||k<1)return 0; //若t为空则返回
    if(k==1)return 1;
    int num = nodecountK2(t->lchild,k-1)+nodecountK2(t->rchild,k-1);
    return num;
}

// 第九题
int Leaves(bitree t)
{ 
 	queue<bitree> q; // 直接调用C++队列头文件建立队列
 	q.push(t);// 根节点入队
 	int num = 0; //记录节点数
 	int depth = 0; //记录层数
 	while(!q.empty()){
 		++depth;
 		num = q.size(); //节点数即为队列的长度
		//当前层节点的个数
		int current_num = 0;
		while(current_num < num) //当前结点个数小于size的时候->推进
		{
		    ++current_num;
			node *t1 = q.front(); //创建新节点把队首根节点存进去
		 	q.pop(); // 弹出来让子树入队
		 	if(t1->lchild){
		 		q.push(t1->lchild); //左子树入队
		 	}
		 	if(t1->rchild){
		 		q.push(t1->rchild); //右子树入队
		 	}
		      }
		}
		return num;	
}

// 算法2：递归
int Leaves2(bitree t){
	if(!t) return 0;
	if(t->lchild==NULL && t->rchild==NULL) return 1;
	int a = Leaves2(t->lchild);
	int b = Leaves2(t->rchild);
	return(a+b);
}


// 第十题：判断两棵二叉树是否结构相同
// 算法：如果一棵二叉树可以通过若干次左右孩子互换就变成另一个二叉树，那么我们称这两棵树是同构的，利用递归。
// 两棵树都空结构一定相同，只有一颗树为空，结构一定不同递归，把全部都比较一遍
bool isSame(bitree t1,bitree t2){
	if(!t1 && !t2){ return true;} //两棵树都为空
	if(!t1 && !t2){return false;} // 只有一棵树为空
	bool judge_left = isSame(t1->lchild,t2->lchild);
	bool judge_right = isSame(t2->rchild,t2->rchild);
	bool judge_final = judge_left&&judge_right;
	return judge_final;
}


//第十一题：求二叉树中两个结点的最低公共祖先结点
// 算法思想：利用递归算法，若发现目标节点n1,n2则直接返回，利用递归查看每一个子树中是否有目标节点
bitree lowest_common_ancestor(node *root,char n1, char n2){
	    if (root == NULL) return NULL;
	    // 发现目标节点则通过返回值标记该子树发现了某个目标结点
	    if (root->data == n1 || root->data == n2)
	        return root;
	 
	    // 递归寻找左右子树中的目标节点，如果没有返回NULL
	    node* left_lca = lowest_common_ancestor(root->lchild,n1,n2);
	    node* right_lca = lowest_common_ancestor(root->rchild,n1,n2);
	 
	    // 若二者都不为空，说明左右子树都有目标结点，则返回公共祖先根节点
	    if (left_lca && right_lca)
	        return root;
	 
	    // 否则查看公共节点是不是在左右子树的某个子节点来里面
	    if( left_lca == NULL) { //如果左边没有发现目标节点
			return right_lca; //返回去右边找
		}else{  //如果左边发现了目标节点
			return left_lca; // 返回标记
		}
}





int main()
{
    bitree t;
    t=buildtree();//  测试用例：abc00d00ef00g000

  /**
 	printf("非递归前序遍历：\n");
	DLR_nonrecursive(t);
	printf("\n");

    printf("递归前序遍历：\n");
    DLR(t);
    printf("\n");
    
    printf("递归中序遍历：\n");
    LDR(t);
    printf("\n");

    printf("递归后序遍历：\n");
    LRD(t);
    printf("\n");
  	
  	
    // 第一题
    printf("二叉树镜像之前（前序遍历）：\n");
    DLR(t);
    printf("\n");
    printf("二叉树镜像之后（前序遍历）：\n");
    mirrorTree1(t);
    //DLR(t);
	printf("\n");

	// 第二题
	int depth = bitreeDepth(t);
	printf("\n二叉树的深度为：%d\n",depth);

	// 第三题
	
	string pre = "abcdefg";
	string in = "cbdafeg";
	t = rebuildTree(t,pre,in,0,6,0,6);	
	printf("根据先序与中序建立的二叉树的后序遍历：");
	LRD(t);
	printf("\n");
	printf("根据先序与中序建立的二叉树的层次遍历：");
	levelOrder(t);
	printf("\n");
	
	// 第四题
	printf("\n层次遍历输出：");
	levelOrder(t);

	
	// 第五题
	int width = treeWidth(t);
	printf("二叉树的宽度为：%d",width);

	
	// 第六题
	int num_of_node = nodeCount(t);
	printf("二叉树节点数为：%d",num_of_node);

	
	// 第七题
	printf("非递归中序遍历：\n");
	InOrder(t);
	printf("\n");
	printf("非递归后序遍历：\n");
	postOrder(t);
	printf("\n");
	

	// 第八题
	int count = nodecountK1(t,3);
	printf("二叉树第3层的结点数为：%d",count); 
	printf("\n");
			
	
	// 第九题
	int leaves = Leaves(t);
	printf("\n二叉树叶子结点个数为：%d",leaves);

	
	// 第十题

	bitree t1 = buildtree(); //测试：abc00d00ef00g000
	bitree t2 = buildtree(); //测试：abc00d00ef000
	bool judge = isSame(t1, t2);
	if(judge){
		printf("t1和t2两棵二叉树结构相同\n");
		}else{
		printf("t1和t2两颗二叉树结构不同\n");
		}
	*/
	
	
	// 第十一题
	char n1 = 'c';
	char n2 = 'd';
	node *res = lowest_common_ancestor(t,n1,n2);
	printf("c和d的最低公共节点是：%c",res->data);
	
	return 0;
}
