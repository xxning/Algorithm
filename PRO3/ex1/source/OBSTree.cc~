#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

struct TreeNode{
	int Seq;   //记录该节点代表的p或q的序号 
	int Kind; //0表示d，1表示p； 
	int Size;  //记录以该节点为根的子树的节点个数 
	TreeNode *Left; //指向左子树 
	TreeNode *Right; //指向右子树 
};

#define INF 10000.0 //定义无穷大 
void OPTIMAL_BST(float *p,float *q,int n);
void TREE_CREATE(TreeNode *T,int s,int t,int flag);
void TREE_COMPLETE(TreeNode *T);
int  SIZE_CALCULATE(TreeNode *T);
void FormatOut(TreeNode *T);
void GRAPH(TreeNode* T);
void RB_INORDER(TreeNode* T);
//文件名定义 
char Filename[6][28]={"./ex1/input/size1/input.txt",
						  "./ex1/input/size2/input.txt",
						  "./ex1/input/size3/input.txt",
						  "./ex1/input/size4/input.txt",
						  "./ex1/input/size5/input.txt",
						  "./ex1/input/size6/input.txt"	
					 	};
char Out_Tree[6][31]={"./ex1/output/size1/output1.txt",
						"./ex1/output/size2/output1.txt",
						"./ex1/output/size3/output1.txt",
						"./ex1/output/size4/output1.txt",
						"./ex1/output/size5/output1.txt",
						"./ex1/output/size6/output1.txt",			
					};
char Out_Time[6][29]={"./ex1/output/size1/time1.txt",
						"./ex1/output/size2/time1.txt",
						"./ex1/output/size3/time1.txt",
						"./ex1/output/size4/time1.txt",
						"./ex1/output/size5/time1.txt",
						"./ex1/output/size6/time1.txt",
					};

char Out_Graph[6][29]={"./ex1/output/size1/graph.dot",
						"./ex1/output/size2/graph.dot",
						"./ex1/output/size3/graph.dot",
						"./ex1/output/size4/graph.dot",
						"./ex1/output/size5/graph.dot",
						"./ex1/output/size6/graph.dot",

			};
										
int Scale;
int n;
float **e,**w;
int **root;
TreeNode *TreeRoot=(TreeNode*)malloc(sizeof(TreeNode)); //根结点 
FILE *outTr,*outTi;//输出文件指针 
FILE *Graph;
struct timespec time_start={0,0},time_end={0,0};
double Time;
int count=0;

int main(int argc,char *argv[]){
	
	FILE *input;
	char filename[28];  //输入文件名 
	char outTree[31];	//树输出文件名 
	char outTime[29];	//时间输出文件名 
	char outGraph[29];	//用于图像形成的文件
	Scale=atoi(argv[1]);
	strcpy(filename,Filename[Scale-1]);
	strcpy(outTree,Out_Tree[Scale-1]);
	strcpy(outTime,Out_Time[Scale-1]);
	strcpy(outGraph,Out_Graph[Scale-1]);
	input=fopen(filename,"r");
	outTr=fopen(outTree,"w");
	outTi=fopen(outTime,"w");
	Graph=fopen(outGraph,"w");
	if(!input||!outTr||!outTi||!Graph){
		printf("error:can't open objcct file.\n");
		exit(1);
	}
	int n=Scale*5;
	float *p=(float*)malloc((n+1)*sizeof(float));
	float *q=(float*)malloc((n+1)*sizeof(float));
	int i,j;
	for(i=1;i<=n;i++)  		  //先读入n个P 
		fscanf(input,"%f",&p[i]);
	for(i=0;i<=n;i++)		//再读入n+1个q 
		fscanf(input,"%f",&q[i]);
	
	e=(float**)malloc((n+2)*sizeof(float*));
	w=(float**)malloc((n+2)*sizeof(float*));
	for(i=0;i<n+2;i++){
		e[i]=(float*)malloc((n+1)*sizeof(float));
		w[i]=(float*)malloc((n+1)*sizeof(float));
	}
	root=(int**)malloc((n+1)*sizeof(int*));
	for(i=0;i<n+1;i++){
		root[i]=(int*)malloc((n+1)*sizeof(int));
	}

	clock_gettime(CLOCK_REALTIME,&time_start);		
	OPTIMAL_BST(p,q,n);
	clock_gettime(CLOCK_REALTIME,&time_end);
	Time=(double)(time_end.tv_nsec-time_start.tv_nsec); 
	fprintf(outTi,"%lf\n",Time);	

	TreeRoot->Left=NULL;
	TREE_CREATE(TreeRoot,1,n,0);
	TREE_COMPLETE(TreeRoot->Left);
	SIZE_CALCULATE(TreeRoot->Left);
	fprintf(outTr,"expected cost:%f\n",e[1][n]);
	FormatOut(TreeRoot->Left);
	fprintf(Graph,"digraph \{\n");
	fprintf(Graph,"	node [shape = record];\n");
	GRAPH(TreeRoot->Left);
	fprintf(Graph,"\r}\n");	

	fclose(input);
	fclose(outTr);
	fclose(outTi);
	fclose(Graph);
	printf("Complete ex1:n=%d\n",n);
//**************************************
//just for test 
/*
	printf("matric e:\n");
	for(i=1;i<=6;i++){
		for(j=0;j<=5;j++)
			printf("%f ",e[i][j]);
		printf("\n");
	}
	printf("matric w:\n");
	for(i=1;i<=6;i++){
		for(j=0;j<=5;j++)
			printf("%f ",w[i][j]);
		printf("\n");
	}	
	printf("matric root:\n");
	for(i=1;i<=5;i++){
		for(j=1;j<=5;j++)
			printf("%d ",root[i][j]);
		printf("\n");
	}
//**************************************
*/	
	return 0;
} 

void OPTIMAL_BST(float *p,float *q,int n){
	
	int i,j,l,r;
	float t;
	for(i=1;i<=n+1;i++){
		e[i][i-1]=q[i-1];
		w[i][i-1]=q[i-1];
	}
	for(l=1;l<=n;l++){
		for(i=1;i<=n-l+1;i++){
			j=i+l-1;
			e[i][j]=INF; 
			w[i][j]=w[i][j-1]+p[j]+q[j];
			for(r=i;r<=j;r++){
				t=e[i][r-1]+e[r+1][j]+w[i][j];
				if(t<e[i][j]){
					e[i][j]=t;
					root[i][j]=r;
				}
			} 
		}		
	}	
}

void TREE_CREATE(TreeNode *T,int s,int t,int flag){
	if(s>t)
		return;
	TreeNode *z=(TreeNode*)malloc(sizeof(TreeNode));
	z->Kind=1;
	z->Left=NULL;
	z->Right=NULL;
	if(s==t){
		z->Seq=s;
		if(!flag)
	    	T->Left=z;
	    else
	    	T->Right=z;
		return;	
	}
	else{
		z->Seq=root[s][t];
		if(!flag){
			T->Left=z;
			TREE_CREATE(T->Left,s,root[s][t]-1,0);
			TREE_CREATE(T->Left,root[s][t]+1,t,1);
		}
	    	
	    else{
	    	T->Right=z;
			TREE_CREATE(T->Right,s,root[s][t]-1,0);
			TREE_CREATE(T->Right,root[s][t]+1,t,1);
	    }
	}	
}

void TREE_COMPLETE(TreeNode *T){
	
	if(T->Left!=NULL&&T->Right!=NULL){
		TREE_COMPLETE(T->Left);
		TREE_COMPLETE(T->Right);
	}
	else if(T->Left==NULL&&T->Right!=NULL){
		TreeNode *z=(TreeNode*)malloc(sizeof(TreeNode));
		z->Kind=0;
		z->Seq=T->Seq-1;
		T->Left=z;
		TREE_COMPLETE(T->Right);
	}
	else if(T->Left!=NULL&&T->Right==NULL){
		TreeNode *z=(TreeNode*)malloc(sizeof(TreeNode));
		z->Kind=0;
		z->Seq=T->Seq;
		T->Right=z;
		TREE_COMPLETE(T->Left);
	}
	else{
		TreeNode *z=(TreeNode*)malloc(sizeof(TreeNode));
		z->Kind=0;
		z->Seq=T->Seq-1;
		T->Left=z;
		z=(TreeNode*)malloc(sizeof(TreeNode));
		z->Kind=0;
		z->Seq=T->Seq;
		T->Right=z;
		return;
	}
}

int SIZE_CALCULATE(TreeNode *T){
	if(T->Left!=NULL&&T->Right!=NULL){
		T->Size=1+SIZE_CALCULATE(T->Left)+SIZE_CALCULATE(T->Right);
	}
	else if(T->Left==NULL&&T->Right!=NULL){
		T->Size=1+SIZE_CALCULATE(T->Right);
	}
	else if(T->Left!=NULL&&T->Right==NULL){
		T->Size=1+SIZE_CALCULATE(T->Left);
	}
	else{
		T->Size=1;
		return 1; 
	}
	return T->Size;
}

void FormatOut(TreeNode *T){
	if(T==NULL)
		return;
	else{
		fprintf(outTr,"%c%d(",(T->Kind==1)?'k':'d',T->Seq);
	}
	if(T->Left!=NULL){
		FormatOut(T->Left);
		if(T->Right!=NULL){
			fprintf(outTr,",");
			FormatOut(T->Right);
		}	
	}
	else if(T->Right!=NULL){
		fprintf(outTr,",");
		FormatOut(T->Right);
	}	
	
	fprintf(outTr,")");
}

void GRAPH(TreeNode* T){

	if(T==NULL) {printf("err\n");return;}
	if(T->Kind==1)
		fprintf(Graph,"	%d [label = \"<0>  |<1>k%d|<2>  \"];\n",count,T->Seq);
	else 
		fprintf(Graph,"	%d [label = \"<0>  |<1>d%d|<2>  \",color=Red];\n",count,T->Seq);
	count++;
		
	if(T->Left!=NULL) {

		fprintf(Graph,"	%d: %d -> %d;\n",count-1,0,count);
		GRAPH(T->Left);
	}		
	if(T->Right!=NULL) {
		fprintf(Graph,"	%d: %d -> %d;\n",count-(T->Left->Size)-1,2,count);
		GRAPH(T->Right);
	}
}

//used to test
void RB_INORDER(TreeNode* T){

	if(T==NULL)		
		return;	
	else{
		RB_INORDER(T->Left);
		printf("Seq:%d	Kind:%d  Size:%d\n",T->Seq,T->Kind,T->Size);
		RB_INORDER(T->Right);
	}	
}
