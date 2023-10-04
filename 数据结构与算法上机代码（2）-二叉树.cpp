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

// ջ�ṹ����
typedef struct stack {
	bitree data[100];
	int top; // ջ��ָ��
}seqstack; //����˳��ջ

// ��ջ������ջ����ջ��
void push(seqstack *s, bitree t){
	s->data[++s->top] = t;
}

// ��ջ������ջ����ջ��
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
    int  front;   //ͷָ��ָʾ�� 
    int  rear;  //βָ��ָʾ��
} Sequeue;

typedef struct Queue
{
  node *data[100];
  int front;
  int rear;
}Queue;

// 0.1 �õݹ鷽������������
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

// 0.2 �÷ǵݹ鷽��ǰ�����������������ջ����ţ�
// �㷨˼�룺�ڷ�����t->data�󣬽�t��ջ������������������������������ʱ��ջ��Ԫ��ӦΪt����ջ�����������t��������
void DLR_nonrecursive(bitree t){
	seqstack s;
	s.top = -1; // ��ʼ��
	// �жϵ�ǰ������Ϊ�ջ���ջ��Ϊ����ѭ��
	while((t!=NULL)||(s.top!=-1)){
		while(t!=NULL){
			printf("%c",t->data);
			s.top++;
			s.data[s.top]=t;
			t=t->lchild; 
		}// �������ѭ����������������
		if(s.top>-1){
			t = pop(&s); //��������Ϊ�����ջ������
			t = t->rchild; // ��ʼ����������
		}
	}
}


// 0.3.1 �ݹ鷽��ǰ�����������
void DLR( node *root )
{if (root ==NULL) return; //�ն�����
 printf("%c",root->data); //���ʸ��ڵ�
 DLR(root->lchild); //�ݹ����������
 DLR(root->rchild); //�ݹ����������
 }
// 0.3.2 �ݹ鷽���������������
void LDR( node *root )
{if (root ==NULL) return; //�ն�����
 LDR(root->lchild);
 printf("%c",root->data); //���ʸ��ڵ�
 LDR(root->rchild);
 }
// 0.3.3 �ݹ鷽���������������
void LRD( node *root )
{if (root ==NULL) return; //�ն�����
 LRD(root->lchild);
 LRD(root->rchild);
 printf("%c",root->data); //���ʸ��ڵ�
 }

// 1. ���������Գƽ������������������
// �㷨һ���ݹ��㷨���Ȱ��������еĽڵ�ŵ�rchild�У�Ȼ���ٰ��ұ߽��ŵ�lchild�У����������Ҫ�Ȱ���ڵ��ݴ浽һ���ط�
void mirrorTree1(node *root){
	node *temp;
	if(root){
		temp = root->lchild;
		root->lchild = root->rchild;
		root->rchild = temp; //�������ڵ����Һ���ָ��
		mirrorTree1(root->lchild);//��������Ҳ��һ���Ĳ���
		mirrorTree1(root->rchild);//����������һ���Ĳ���
	}
}

// �㷨�������ö����Ƚ��ȳ������ԣ���α���ÿһ�㣬Ȼ���ڶ����ڲ���������Ȼ���������
void mirrorTree2(bitree t){
	node *temp;
	queue<bitree> q;
	q.push(t);
		while(!q.empty()){
		node *t1 = q.front(); //�����½ڵ�Ѷ��׸��ڵ���ȥ
		printf("%c",t1->data);
		q.pop(); // ���������������
		
		temp = t1->lchild;
		t1->lchild = t1->rchild;
		t1->rchild = temp; //��������	
		
		if(t1->lchild){
			q.push(t1->lchild); //���������
		}
		if(t->rchild){
			q.push(t1->rchild); //���������
			}
		}
}



// 2.��������ĸ߶ȣ������
// �㷨���ݹ��㷨��Ϊ�����������ȣ���������������������ȣ�ȡ���߽ϴ��߼�1����������ȣ�

int bitreeDepth(bitree t){
	int left =0; 
	int right = 0; 
	if(t) {
	left = bitreeDepth(t->lchild)+1;
	right = bitreeDepth(t->rchild)+1;//������������+1�����ڵ㣩
	}
	 return left>=right?left:right;
}

// �ǵݹ��㷨�����ò������������ǰ�ڵ���С�ڶ��е�size��ʱ��˵����һ��û�н����������ƽ���
int bitreeDepth2(bitree t)
{ 
 	queue<bitree> q; // ֱ�ӵ���C++����ͷ�ļ���������
 	q.push(t);// ���ڵ����
 	int num = 0; //��¼�ڵ���
 	int depth = 0; //��¼����
 	while(!q.empty()){
 		++depth;
 		num = q.size(); //�ڵ�����Ϊ���еĳ���
		//��ǰ��ڵ�ĸ���
		int current_num = 0;
		while(current_num < num) //��ǰ������С��size��ʱ��->�ƽ�
		{
		    ++current_num;
			node *t1 = q.front(); //�����½ڵ�Ѷ��׸��ڵ���ȥ
		 	q.pop(); // ���������������
		 	if(t1->lchild){
		 		q.push(t1->lchild); //���������
		 	}
		 	if(t1->rchild){
		 		q.push(t1->rchild); //���������
		 	}
		      }
 	}
	return depth;	
}


// 3. ��֪ǰ�����к��������У����������
// �㷨������֪���������еĵ�һ���Ǹ��ڵ㣬�������������ҵ����ڵ㣬���ڵ���ߵĶ�����������
//�ұߵľ����������ĳ�Ա���ٽ��к����ݹ飬���¸�ֵ����������һ���Ĳ�����������һ�Ŷ�������

bitree buildTree_Pre_In(string pre,string in,int a,int b,int c,int d)
{
	node *root;
	if(a <= b)
	{
		root = new(node);	 //�������ڵ�	
		root->data = pre[a]; 	//������ڵ���ֵ
		root->lchild = NULL;	
		root->rchild = NULL;	
		int i;
		for(i = c; i <= d; i++)		//�����������в��Ҹ���λ��i 
		{
			if(in[i] == pre[a])
				break;  //�ҵ�֮���ѭ��
		}
		root->lchild = buildTree_Pre_In(pre,in,a+1,a+i-c,c,i-1);	//�ݹ齨������ 
		root->rchild = buildTree_Pre_In(pre,in,a+i-c+1,b,i+1,d);	//�ݹ齨������ 
	}
	return root;
}


// 4. �ֲ������������������δ������£���������˳����� 
// �㷨�����ö����Ƚ��ȳ������ʣ��ȰѸ��ڵ���ӣ�Ȼ���ø��ڵ����������������ͬʱ��ӣ�Ȼ�����γ���
void levelOrder(bitree t){
	queue<bitree> q; // ֱ�ӵ���C++����ͷ�ļ���������
	q.push(t);// ���ڵ����
	while(!q.empty()){
		node *t1 = q.front(); //�����½ڵ�Ѷ��׸��ڵ���ȥ
		printf("%c",t1->data);
		q.pop(); // ���������������
		if(t1->lchild){
			q.push(t1->lchild); //���������
		}
		if(t->rchild){
			q.push(t1->rchild); //���������
		}
	}
}

// 5.��������Ŀ�ȣ�������������Ĳ������еĽ����
// �㷨����α������������趨һ���ر�ı��#�����ÿһ������ұߣ�����һ������Ľ���
// ������mark�ᵼ����������ѭ����Ϊ���ʣ�µ��Ǹ�һ����#�����ÿ��������#ʱ��Ҫ���������Ƿ�������Ԫ��
int treeWidth(bitree t)
{
  if(t==NULL) return 0; //��Ϊ��ֱ�ӷ���
  int num = 0; //��¼ÿһ��ڵ���
  int max = 0; //��¼�ڵ��е����ֵ
  Queue q;
  q.rear = 0; q.front = 0;//��ʼ������
  q.data[q.rear++] = t; // ���������

  bitree tree = new(node);
  tree->data = '#'; //������
  tree->lchild = NULL;
  tree->rchild = NULL;
  q.data[q.rear++] = tree;//���#���
  while(q.rear!=q.front) // �ж϶����Ƿ�Ϊ��
  {
    tree = q.data[q.front++];  //�ڲ�α����м���һ��#�ж�
    if(tree->data=='#')  //����#���
    {
      if(max<num)
      {
        max = num;
        num = 0;
      } //�ж����ڵ���
      if(q.data[q.front]!=NULL) //����Ӳ�Ϊ��->����������Ԫ��
      {
        tree = new(node);//�ӱ��
        tree->data = '#'; 
        tree->lchild = NULL;
        tree->rchild = NULL;
        q.data[q.rear++] = tree;
      }
      
    }else {// û�������������+����
      ++num;
      if(tree->lchild) q.data[q.rear++] = tree->lchild;
      if(tree->rchild) q.data[q.rear++] = tree->rchild;
    }
  }
  	return max;
}

//  �����⣺��������Ľ�����
// ���ö��н��в�α��������ü�ʱ�����м��ܼ��ɡ�
int nodeCount(bitree t)
{
  if(t==NULL) return 0; //��Ϊ��ֱ�ӷ���
  int num = 0; //��¼�ڵ���
  Queue q;//���ö���
  q.rear = 0;
  q.front = 0;//��ʼ������
  q.data[q.rear++] = t; // ͷ������
  while(q.rear!=q.front) // �ж϶����Ƿ�Ϊ��
  {
    t = q.data[q.front++];  
      ++num;
      if(t->lchild) q.data[q.rear++] = t->lchild;
      if(t->rchild) q.data[q.rear++] = t->rchild;
    
  }
  	return num;
}

// �����⣺�ǵݹ鷽�����򡢺������������
// ����ջ��ʵ��
void InOrder(bitree t)
{
	seqstack s;
	s.top = -1; // ��ʼ��
	node *root = t;
	// �жϵ�ǰ������Ϊ�ջ���ջ��Ϊ����ѭ��
	while((root!=NULL)||(s.top!=-1)){
		while(root!=NULL){
			s.top++;
			s.data[s.top]=root;
			root=root->lchild; 
		}// һֱ���������������±ߣ��߱����߱�����ڵ㵽ջ��
		if(s.top>-1){ //��ջ��Ϊ��
			root = pop(&s); //��������Ϊ�����ջ������
			printf("%c",root->data);
			root = root->rchild; // ��ʼ����������
		}
	}
}

void postOrder(bitree t)
{
	seqstack s;
	s.top = -1; // ��ʼ��
	node *root = t;
	node *last = NULL; // ��һ�����ʵĽ��
		while(root!=NULL){
			s.top++;
			s.data[s.top]=root;
			root=root->lchild; 
		}// �ߵ������Ѿ������������±�
		while((s.top!=-1)){
		root = pop(&s);
		if (root->rchild == NULL || root->rchild == last)
		//�жϸ��ڵ���ҽڵ��Ƿ񱻷��ʹ�(=last)
		{	printf("%c",root->data);
				last = root;	// ������һ�������ʵĽڵ�
				}else{
					s.top++;
					s.data[s.top]=root; //���ڵ�����ջ
					root = root->rchild; //����������
					while (root!=NULL){	 
					s.top++;
					s.data[s.top]=root;
					root = root->lchild; 
				}
		}
	}
}

//�ڰ��⣺
// �㷨1�����ò�����������Ҽ�һ����������������������Kʱ�����㵱��ڵ����������ظýڵ�����
int nodecountK1(bitree t,int K)
{ 
 	queue<bitree> q; // ֱ�ӵ���C++����ͷ�ļ���������
 	q.push(t);// ���ڵ����
 	int num = 0; //��¼�ڵ���
 	int depth = 0; //��¼����
 	
 	while(!q.empty()){
 		++depth;
 		num = q.size(); //�ڵ�����Ϊ���еĳ���
 		if(depth==K) break;// ����ҵ���k���˾�����ѭ��
		//��ǰ��ڵ�ĸ���
		int current_num = 0;
		while(current_num < num) //��ǰ������С��size��ʱ��->�ƽ�
		{
		    ++current_num;
			node *t1 = q.front(); //�����½ڵ�Ѷ��׸��ڵ���ȥ
		 	q.pop(); // ���������������
		 	if(t1->lchild){
		 		q.push(t1->lchild); //���������
		 	}
		 	if(t1->rchild){
		 		q.push(t1->rchild); //���������
		 	}
		      }
		}
		if(depth == K) return num;	
}

// �㷨2�����õݹ��㷨��
int nodecountK2(bitree t,int k)
{
    if(!t||k<1)return 0; //��tΪ���򷵻�
    if(k==1)return 1;
    int num = nodecountK2(t->lchild,k-1)+nodecountK2(t->rchild,k-1);
    return num;
}

// �ھ���
int Leaves(bitree t)
{ 
 	queue<bitree> q; // ֱ�ӵ���C++����ͷ�ļ���������
 	q.push(t);// ���ڵ����
 	int num = 0; //��¼�ڵ���
 	int depth = 0; //��¼����
 	while(!q.empty()){
 		++depth;
 		num = q.size(); //�ڵ�����Ϊ���еĳ���
		//��ǰ��ڵ�ĸ���
		int current_num = 0;
		while(current_num < num) //��ǰ������С��size��ʱ��->�ƽ�
		{
		    ++current_num;
			node *t1 = q.front(); //�����½ڵ�Ѷ��׸��ڵ���ȥ
		 	q.pop(); // ���������������
		 	if(t1->lchild){
		 		q.push(t1->lchild); //���������
		 	}
		 	if(t1->rchild){
		 		q.push(t1->rchild); //���������
		 	}
		      }
		}
		return num;	
}

// �㷨2���ݹ�
int Leaves2(bitree t){
	if(!t) return 0;
	if(t->lchild==NULL && t->rchild==NULL) return 1;
	int a = Leaves2(t->lchild);
	int b = Leaves2(t->rchild);
	return(a+b);
}


// ��ʮ�⣺�ж����ö������Ƿ�ṹ��ͬ
// �㷨�����һ�ö���������ͨ�����ɴ����Һ��ӻ����ͱ����һ������������ô���ǳ�����������ͬ���ģ����õݹ顣
// ���������սṹһ����ͬ��ֻ��һ����Ϊ�գ��ṹһ����ͬ�ݹ飬��ȫ�����Ƚ�һ��
bool isSame(bitree t1,bitree t2){
	if(!t1 && !t2){ return true;} //��������Ϊ��
	if(!t1 && !t2){return false;} // ֻ��һ����Ϊ��
	bool judge_left = isSame(t1->lchild,t2->lchild);
	bool judge_right = isSame(t2->rchild,t2->rchild);
	bool judge_final = judge_left&&judge_right;
	return judge_final;
}


//��ʮһ�⣺�������������������͹������Ƚ��
// �㷨˼�룺���õݹ��㷨��������Ŀ��ڵ�n1,n2��ֱ�ӷ��أ����õݹ�鿴ÿһ���������Ƿ���Ŀ��ڵ�
bitree lowest_common_ancestor(node *root,char n1, char n2){
	    if (root == NULL) return NULL;
	    // ����Ŀ��ڵ���ͨ������ֵ��Ǹ�����������ĳ��Ŀ����
	    if (root->data == n1 || root->data == n2)
	        return root;
	 
	    // �ݹ�Ѱ�����������е�Ŀ��ڵ㣬���û�з���NULL
	    node* left_lca = lowest_common_ancestor(root->lchild,n1,n2);
	    node* right_lca = lowest_common_ancestor(root->rchild,n1,n2);
	 
	    // �����߶���Ϊ�գ�˵��������������Ŀ���㣬�򷵻ع������ȸ��ڵ�
	    if (left_lca && right_lca)
	        return root;
	 
	    // ����鿴�����ڵ��ǲ���������������ĳ���ӽڵ�������
	    if( left_lca == NULL) { //������û�з���Ŀ��ڵ�
			return right_lca; //����ȥ�ұ���
		}else{  //�����߷�����Ŀ��ڵ�
			return left_lca; // ���ر��
		}
}





int main()
{
    bitree t;
    t=buildtree();//  ����������abc00d00ef00g000

  /**
 	printf("�ǵݹ�ǰ�������\n");
	DLR_nonrecursive(t);
	printf("\n");

    printf("�ݹ�ǰ�������\n");
    DLR(t);
    printf("\n");
    
    printf("�ݹ����������\n");
    LDR(t);
    printf("\n");

    printf("�ݹ���������\n");
    LRD(t);
    printf("\n");
  	
  	
    // ��һ��
    printf("����������֮ǰ��ǰ���������\n");
    DLR(t);
    printf("\n");
    printf("����������֮��ǰ���������\n");
    mirrorTree1(t);
    //DLR(t);
	printf("\n");

	// �ڶ���
	int depth = bitreeDepth(t);
	printf("\n�����������Ϊ��%d\n",depth);

	// ������
	
	string pre = "abcdefg";
	string in = "cbdafeg";
	t = rebuildTree(t,pre,in,0,6,0,6);	
	printf("�����������������Ķ������ĺ��������");
	LRD(t);
	printf("\n");
	printf("�����������������Ķ������Ĳ�α�����");
	levelOrder(t);
	printf("\n");
	
	// ������
	printf("\n��α��������");
	levelOrder(t);

	
	// ������
	int width = treeWidth(t);
	printf("�������Ŀ��Ϊ��%d",width);

	
	// ������
	int num_of_node = nodeCount(t);
	printf("�������ڵ���Ϊ��%d",num_of_node);

	
	// ������
	printf("�ǵݹ����������\n");
	InOrder(t);
	printf("\n");
	printf("�ǵݹ���������\n");
	postOrder(t);
	printf("\n");
	

	// �ڰ���
	int count = nodecountK1(t,3);
	printf("��������3��Ľ����Ϊ��%d",count); 
	printf("\n");
			
	
	// �ھ���
	int leaves = Leaves(t);
	printf("\n������Ҷ�ӽ�����Ϊ��%d",leaves);

	
	// ��ʮ��

	bitree t1 = buildtree(); //���ԣ�abc00d00ef00g000
	bitree t2 = buildtree(); //���ԣ�abc00d00ef000
	bool judge = isSame(t1, t2);
	if(judge){
		printf("t1��t2���ö������ṹ��ͬ\n");
		}else{
		printf("t1��t2���Ŷ������ṹ��ͬ\n");
		}
	*/
	
	
	// ��ʮһ��
	char n1 = 'c';
	char n2 = 'd';
	node *res = lowest_common_ancestor(t,n1,n2);
	printf("c��d����͹����ڵ��ǣ�%c",res->data);
	
	return 0;
}
