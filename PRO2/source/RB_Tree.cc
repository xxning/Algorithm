#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//#include "node.hh"
//#include "dumpdot.hh"


char *dumpfile_name = NULL; // dump file's name
FILE *dumpfp = NULL;        // dump file's pointer

struct TreeNode{
	int Key;   //记录该节点表示的关键字 
	int Color; //0表示红色，1表示黑色； 
	int Size;  //记录以该节点为根的子树的节点个数 
	TreeNode *Left; //指向左子树 
	TreeNode *Right; //指向右子树 
	TreeNode *Parent; //指向父节点 
};

//definition of basic operations
void LEFT_ROTATE(TreeNode *T,TreeNode *x);
void RIGHT_ROTATE(TreeNode *T,TreeNode *x);
void RB_INSERT(TreeNode *T,TreeNode *z);
void RB_INSERT_FIXUP(TreeNode *T,TreeNode *z);
void RB_TRANSPLANT(TreeNode *T,TreeNode *u,TreeNode *v);
TreeNode* TREE_MINIMUM(TreeNode *z);
void RB_DELETE(TreeNode *T,TreeNode *z);
void RB_DELETE_FIXUP(TreeNode *T,TreeNode *x);
TreeNode* OS_SELECT(TreeNode* x,int i);
void RB_PREORDER(TreeNode *T);
void RB_INORDER(TreeNode *T);
void RB_POSTORDER(TreeNode *T);
void OUTPUT_INITIAL(void);
void TEST(void);
void RANDOMIZED_SELECT(int *A,int p,int r,int i);
int RANDOMIZED_PARTITION(int *A,int p,int r);
void GRAPH(TreeNode *T);

TreeNode *TreeRoot=(TreeNode*)malloc(sizeof(TreeNode));
TreeNode *T_nil=(TreeNode*)malloc(sizeof(TreeNode));
//output file 
FILE* output_preorder;
FILE* output_inorder;
FILE* output_postorder;
FILE* output_time1;
FILE* output_time2;
FILE* output_delete_data;
FILE* Graph;
int N_test;
int count=0;

double Time=0;

double Ti[10]={0,0,0,0,0,0,0,0,0,0};
struct timespec time_start={0,0},time_end={0,0};

int main(int argc,char *argv[]){
	
	FILE* input;

	int i,j;
	int Scale=100;
	input=fopen("./input/input_numbers.txt","r");
	if(!input){
		printf("error:can't open objcct file.\n");
		exit(1);
	}
	int* num=(int*)malloc(Scale*sizeof(int));
	for(i=0;i<Scale;i++)
		fscanf(input,"%d",&num[i]);	
	fclose(input);

	TreeRoot->Left=T_nil;
	T_nil->Left=NULL;
	T_nil->Right=NULL;
	T_nil->Color=1;
	T_nil->Size=0;
	
	N_test=atoi(argv[1]);
	
	OUTPUT_INITIAL();		
	int count=0,index=0;
	
	for(i=0;i<N_test;i++){
		
		count++;  	
		TreeNode *z=(TreeNode*)malloc(sizeof(TreeNode));
		z->Key=num[i];
		z->Size=1;
		z->Color=0; 
		//z->Color=0; 
		clock_gettime(CLOCK_REALTIME,&time_start);
		RB_INSERT(TreeRoot,z);	
		clock_gettime(CLOCK_REALTIME,&time_end);
		Ti[index]+=(double)(time_end.tv_nsec-time_start.tv_nsec); 
		if(count==10){			
			index++;
			count=0; 
		}
	}
	
	for(i=0;i<index;i++){
		fprintf(output_time1,"%d: %.0f\n",i,Ti[i]);
		Time+=Ti[i];
	} 

	fprintf(output_time1,"Total time: %.0f\n",Time);
	fprintf(Graph,"digraph \{\n");
	fprintf(Graph,"	node [shape = record];\n");
	TEST();
	fprintf(Graph,"\r}\n");
	
	RANDOMIZED_SELECT(num,0,N_test-1,N_test/3);
	RANDOMIZED_SELECT(num,0,N_test-1,(2*N_test-2)/3);
	
	fclose(output_preorder);
	fclose(output_inorder);
	fclose(output_postorder);
	fclose(output_time1);
	fclose(output_time2);
	fclose(output_delete_data);
	fclose(Graph);
	
	printf("Complete size of %d!\n",N_test);
	//system("pause");
	return 0;
} 

//T->Left指向根节点 
void LEFT_ROTATE(TreeNode *T,TreeNode *x){
	
	TreeNode *y=(TreeNode*)malloc(sizeof(TreeNode));
	y=x->Right;
	x->Right=y->Left;
	if(y->Left!=T_nil)
		y->Left->Parent=x; 	
	y->Parent=x->Parent;
	if(x->Parent==T_nil)
		T->Left=y;
	else if(x==x->Parent->Left)
		x->Parent->Left=y;
	else
		x->Parent->Right=y;
	y->Left=x;
	x->Parent=y; 
	y->Size=x->Size;				//size属性维护 
	x->Size=x->Left->Size+x->Right->Size+1;
}

//T->Left指向根节点 
void RIGHT_ROTATE(TreeNode *T,TreeNode *x){
	
	TreeNode *y=(TreeNode*)malloc(sizeof(TreeNode));
	y=x->Left;
	x->Left=y->Right;
	if(y->Right!=T_nil)
		y->Right->Parent=x; 	
	y->Parent=x->Parent;
	if(x->Parent==T_nil)
		T->Left=y;
	else if(x==x->Parent->Left)
		x->Parent->Left=y;
	else
		x->Parent->Right=y;
	y->Right=x;
	x->Parent=y; 
	y->Size=x->Size;						//size属性维护 
	x->Size=x->Left->Size+x->Right->Size+1;  
}

void RB_INSERT(TreeNode *T,TreeNode *z){
	
	TreeNode *x=(TreeNode*)malloc(sizeof(TreeNode));
	TreeNode *y=(TreeNode*)malloc(sizeof(TreeNode));
	y=T_nil;
	x=T->Left;
	while(x!=T_nil){
		y=x;
		x->Size++;
		if(z->Key<x->Key)
			x=x->Left;
		else
			x=x->Right; 
	} 
	z->Parent=y;
	if(y==T_nil)
		T->Left=z;	
	else if(z->Key<y->Key)
		y->Left=z;
	else 
		y->Right=z;
	z->Left=T_nil;
	z->Right=T_nil;
	z->Color=0;
	RB_INSERT_FIXUP(T,z);
}

void RB_INSERT_FIXUP(TreeNode *T,TreeNode *z){
	
	TreeNode *y=(TreeNode*)malloc(sizeof(TreeNode));
	while( z->Parent->Color==0 ){
		if(z->Parent==z->Parent->Parent->Left){
			y=z->Parent->Parent->Right;
			if(y->Color==0){
				z->Parent->Color=1;              //case1
				y->Color=1;					     //case1 
				z->Parent->Parent->Color=0;		 //case1
				z=z->Parent->Parent;	         //case1
			}
			else if(z==z->Parent->Right){
				z=z->Parent;				     //case2
				LEFT_ROTATE(T,z);				 //case2
			}
			else{			
			z->Parent->Color=1;					 //case3
			z->Parent->Parent->Color=0;			 //case3
			RIGHT_ROTATE(T,z->Parent->Parent);	 //case3
			}
		}
		else{
			y=z->Parent->Parent->Left;
			if(y->Color==0){
				z->Parent->Color=1;				//case1
				y->Color=1;						//case1
				z->Parent->Parent->Color=0;		//case1
				z=z->Parent->Parent;			//case1
			}
			else if(z==z->Parent->Left){
				z=z->Parent;					//case2
				RIGHT_ROTATE(T,z);				//case2				
			}
			else{
			z->Parent->Color=1;					//case3
			z->Parent->Parent->Color=0;			//case3
			LEFT_ROTATE(T,z->Parent->Parent);	//case3
			}	
		}
		
	}
	T->Left->Color=1;	
}

void RB_TRANSPLANT(TreeNode *T,TreeNode *u,TreeNode *v){

	if(u->Parent==T_nil)
		T->Left=v;
	else if(u==u->Parent->Left)
		u->Parent->Left=v;
	else 
		u->Parent->Right=v;
	v->Parent=u->Parent; 
}

TreeNode* TREE_MINIMUM(TreeNode *z){
	
	TreeNode *y=(TreeNode*)malloc(sizeof(TreeNode));
	TreeNode *x=(TreeNode*)malloc(sizeof(TreeNode));
	x=z;
	while(x!=T_nil){
		y=x;
		x=x->Left;
	}
	return y;
}

void RB_DELETE(TreeNode *T,TreeNode *z){
	
	TreeNode *x=(TreeNode*)malloc(sizeof(TreeNode));
	TreeNode *y=(TreeNode*)malloc(sizeof(TreeNode));
	y=z->Parent;
	if(y!=T_nil){      //修改size属性 
		y->Size=y->Size-1;
		y=y->Parent;
	}	
	y=z;
	int y_original_color=y->Color; 
	if(z->Left==T_nil){
		x=z->Right;
		RB_TRANSPLANT(T,z,z->Right);
	}
	else if(z->Right==T_nil){
		x=z->Left;
		RB_TRANSPLANT(T,z,z->Left);
	}
	else{ 
		y=TREE_MINIMUM(z->Right);
		y_original_color=y->Color;
		x=y->Right;
		if(y->Parent==z)
			x->Parent=y;
		else{
			RB_TRANSPLANT(T,y,y->Right);
			y->Right=z->Right;
			y->Right->Parent=y;
		} 
		RB_TRANSPLANT(T,z,y); 
		y->Left=z->Left;
		y->Left->Parent=y;
		y->Color=z->Color;
	}
	if(y_original_color==1)
		RB_DELETE_FIXUP(T,x);	 
}

void RB_DELETE_FIXUP(TreeNode *T,TreeNode *x){
	
	TreeNode *w=(TreeNode*)malloc(sizeof(TreeNode));
	while( x!=T->Left && x->Color==1 ){
		if(x==x->Parent->Left){
			w=x->Parent->Right;
			if(w->Color==0){
				w->Color=1;				//case1
				x->Parent->Color=0;		//case1
				LEFT_ROTATE(T,x->Parent);		//case1
				w=w->Parent->Right;		//case1
			}
			if( w->Left->Color==1 && w->Right->Color==1){
				w->Color=0;				//case2
				x=x->Parent;			//case2
			}
			else if(w->Right->Color==1){
				w->Left->Color=1;		//case3
				w->Color=0;				//case3
				RIGHT_ROTATE(T,w);		//case3
				w=x->Parent->Right; 	//case3
			}			
			else{
				w->Color=x->Parent->Color;	//case4
				x->Parent->Color=1;			//case4
				w->Right->Color=1;			//case4
				LEFT_ROTATE(T,x->Parent);	//case4
				x=T->Left;						//case4
			}
		}
		else{
			w=x->Parent->Left;
			if(w->Color==0){
				w->Color=1;				//case1
				x->Parent->Color=0;		//case1
				RIGHT_ROTATE(T,x->Parent);	//case1
				w=w->Parent->Left;	 	//case1
			}
			if( w->Left->Color==1 && w->Right->Color==1){
				w->Color=0;			    //case2
				x=x->Parent;			//case2
			}
			else if(w->Right->Color==1){
				w->Left->Color=1;		//case3
				w->Color=0;				//case3
				LEFT_ROTATE(T,w);		//case3
				w=x->Parent->Right; 	//case3
			}
			else{
				w->Color=x->Parent->Color;	//case4
				x->Parent->Color=1;			//case4
				w->Left->Color=1;			//case4
				RIGHT_ROTATE(T,x->Parent);	//case4
				x=T->Left;						//case4
			}			
		}
	}
	x->Color=1;
}

TreeNode* OS_SELECT(TreeNode* x,int i){
	
	int r=x->Left->Size+1;
	if(i==r)
		return x;
	else if(i<r)
		return OS_SELECT(x->Left,i);
	else 
		return OS_SELECT(x->Right,i-r);
}
 
void RB_PREORDER(TreeNode* T){
	
	if(T==T_nil)		
		return;	
	else{
		fprintf(output_preorder,"Key:%8d	Color:%s	Size:%d\n",T->Key,(T->Color==1)?"BLACK":"RED",T->Size);
		RB_PREORDER(T->Left);
		RB_PREORDER(T->Right);
	}	
}

void RB_INORDER(TreeNode* T){

	if(T==T_nil)		
		return;	
	else{
		RB_INORDER(T->Left);
		fprintf(output_inorder,"Key:%8d	Color:%s	Size:%d\n",T->Key,(T->Color==1)?"BLACK":"RED",T->Size);
		RB_INORDER(T->Right);
	}	
}

void RB_POSTORDER(TreeNode* T){
	if(T==T_nil)		
		return;	
	else{	
		RB_POSTORDER(T->Left);
		RB_POSTORDER(T->Right);
		fprintf(output_postorder,"Key:%8d	Color:%s	Size:%d\n",T->Key,(T->Color==1)?"BLACK":"RED",T->Size);
	}	
}

void OUTPUT_INITIAL(void){
	 
	switch(N_test){
		case(20):{ 
			output_preorder=fopen("./output/size20/preorder.txt","w");
			output_inorder=fopen("./output/size20/inorder.txt","w");
			output_postorder=fopen("./output/size20/postorder.txt","w");
			output_time1=fopen("./output/size20/time1.txt","w");
			output_time2=fopen("./output/size20/time2.txt","w");
			output_delete_data=fopen("./output/size20/delete_data.txt","w");
			Graph=fopen("./output/size20/graph.dot","w");
			if(!output_preorder||!output_inorder||!output_postorder||!output_time1||!output_time2||!output_delete_data||!Graph){
				printf("Error:can't open objcct file.\n");
				exit(1);
			}
			break;
		}
		case(40):{
			output_preorder=fopen("./output/size40/preorder.txt","w");
			output_inorder=fopen("./output/size40/inorder.txt","w");
			output_postorder=fopen("./output/size40/postorder.txt","w");
			output_time1=fopen("./output/size40/time1.txt","w");
			output_time2=fopen("./output/size40/time2.txt","w");
			output_delete_data=fopen("./output/size40/delete_data.txt","w");
			Graph=fopen("./output/size40/graph.dot","w");
			if(!output_preorder||!output_inorder||!output_postorder||!output_time1||!output_time2||!output_delete_data||!Graph){
				printf("Error:can't open objcct file.\n");
				exit(1);
			}
			break;
		}
			
		case(60):{
			output_preorder=fopen("./output/size60/preorder.txt","w");
			output_inorder=fopen("./output/size60/inorder.txt","w");
			output_postorder=fopen("./output/size60/postorder.txt","w");
			output_time1=fopen("./output/size60/time1.txt","w");
			output_time2=fopen("./output/size60/time2.txt","w");
			output_delete_data=fopen("./output/size60/delete_data.txt","w");
			Graph=fopen("./output/size60/graph.dot","w");
			if(!output_preorder||!output_inorder||!output_postorder||!output_time1||!output_time2||!output_delete_data||!Graph){
				printf("Error:can't open objcct file.\n");
				exit(1);
			}
			break;
		}		
		case(80):{
			output_preorder=fopen("./output/size80/preorder.txt","w");
			output_inorder=fopen("./output/size80/inorder.txt","w");
			output_postorder=fopen("./output/size80/postorder.txt","w");
			output_time1=fopen("./output/size80/time1.txt","w");
			output_time2=fopen("./output/size80/time2.txt","w");
			output_delete_data=fopen("./output/size80/delete_data.txt","w");
			Graph=fopen("./output/size80/graph.dot","w");
			if(!output_preorder||!output_inorder||!output_postorder||!output_time1||!output_time2||!output_delete_data||!Graph){
				printf("Error:can't open objcct file.\n");
				exit(1);
			}
			break;
		}			
		case(100):{
			output_preorder=fopen("./output/size100/preorder.txt","w");
			output_inorder=fopen("./output/size100/inorder.txt","w");
			output_postorder=fopen("./output/size100/postorder.txt","w");
			output_time1=fopen("./output/size100/time1.txt","w");
			output_time2=fopen("./output/size100/time2.txt","w");
			output_delete_data=fopen("./output/size100/delete_data.txt","w");
			Graph=fopen("./output/size100/graph.dot","w");
			if(!output_preorder||!output_inorder||!output_postorder||!output_time1||!output_time2||!output_delete_data||!Graph){
				printf("Error:can't open objcct file.\n");
				exit(1);
			}
			break;
		}			
		default:{
			printf("Error:invalid argument.\n");
			exit(1);
		}
	}
}

void TEST(void){
	
	//三种遍历 
	RB_PREORDER(TreeRoot->Left);
	RB_INORDER(TreeRoot->Left);
	RB_POSTORDER(TreeRoot->Left);
	GRAPH(TreeRoot->Left);
	//两次删除 
	TreeNode *z=(TreeNode*)malloc(sizeof(TreeNode));
	//Delete 1
	z=OS_SELECT(TreeRoot->Left,N_test/3);
	fprintf(output_delete_data,"Key:%d	Color:%s	Size:%d\n",z->Key,(z->Color==1)?"BLACK":"RED",z->Size);
	clock_gettime(CLOCK_REALTIME,&time_start);
	RB_DELETE(TreeRoot,z);//
	clock_gettime(CLOCK_REALTIME,&time_end);
	Time=(double)(time_end.tv_nsec-time_start.tv_nsec); 
	fprintf(output_time2,"Delete 1 :%.0f\n",Time);
	//Delete 2
	z=OS_SELECT(TreeRoot->Left,((N_test-1)*2)/3);
	fprintf(output_delete_data,"Key:%d	Color:%s	Size:%d\n",z->Key,(z->Color==1)?"BLACK":"RED",z->Size);
	clock_gettime(CLOCK_REALTIME,&time_start);
	RB_DELETE(TreeRoot,z);//
	clock_gettime(CLOCK_REALTIME,&time_end);
	Time=(double)(time_end.tv_nsec-time_start.tv_nsec); 
	fprintf(output_time2,"Delete 2 :%.0f\n",Time);
	
}

void RANDOMIZED_SELECT(int *A,int p,int r,int i){
	
	if(p==r){
		fprintf(output_delete_data,"delete: %8d\n",A[p]);
		return ;
	}
		
	int q,k;
	q=RANDOMIZED_PARTITION(A,p,r);
	k=q-p+1;
	if(i==k){
		fprintf(output_delete_data,"delete: %8d\n",A[q]);
		return ;
	}
		
	else if(i<k)
		RANDOMIZED_SELECT(A,p,q-1,i);
	else
		RANDOMIZED_SELECT(A,q+1,r,i-k);	
}

int RANDOMIZED_PARTITION(int *A,int p,int r){
	
	int i,j;
    int tem,sel;
	double Rand;  
	srand((unsigned)time(NULL));
	Rand=rand()/(RAND_MAX+1.0);
	Rand=Rand*(r-p);
	tem=p+Rand;	
	sel=A[tem];
	A[tem]=A[r];
	A[r]=sel;
	i=p-1;
	sel=A[r];
	for(j=p;j<r;j++){
		if(A[j]<sel){
			i=i+1;
			tem=A[i];
			A[i]=A[j];
			A[j]=tem;
		}
	}
	tem=A[i+1];
	A[i+1]=A[r];
	A[r]=tem;
	
	return (i+1);
}

void GRAPH(TreeNode* T){

	if(T==T_nil) {printf("err\n");return;}
	if(T->Color==1)
		fprintf(Graph,"	%d [label = \"<0>  |<1> %d|<2> %d|<3> %d|<4> \"];\n",count,T->Key,T->Color,T->Size);
	else 
		fprintf(Graph,"	%d [label = \"<0>  |<1> %d|<2> %d|<3> %d|<4> \",color=Red];\n",count,T->Key,T->Color,T->Size);
	count++;
		
	if(T->Left!=T_nil) {

		fprintf(Graph,"	%d: %d -> %d;\n",count-1,0,count);
		GRAPH(T->Left);
	}		
	if(T->Right!=T_nil) {
		fprintf(Graph,"	%d: %d -> %d;\n",count-(T->Left->Size)-1,4,count);
		GRAPH(T->Right);
	}
}

