#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>

struct Adj{
	int v;
	Adj *next;
};

struct Node{
	int Con;     
	int Seq;	//序号 
	int Color;   //结点的颜色，0白色，1灰色，2黑色，初始化为0
	int Pi;		// 结点的祖先存的是祖先的编号，初始为-1 
	Adj *adj;	//邻接链表，初始为NULL 
};

void DFS(Node* G);
void DFSt(Node *G);
void DFS_VISIT(Node *G,int u);
void SCC(Node *G,Node *Gt);
void GRAPH(Node* Gt);

char Filename[6][28]={"./ex1/input/size1/input.txt",
						  "./ex1/input/size2/input.txt",
						  "./ex1/input/size3/input.txt",
						  "./ex1/input/size4/input.txt",
						  "./ex1/input/size5/input.txt",
						  "./ex1/input/size6/input.txt"	
					 	};
char Out_SCC[6][30]={"./ex1/output/size1/output.txt",
						"./ex1/output/size2/output.txt",
						"./ex1/output/size3/output.txt",
						"./ex1/output/size4/output.txt",
						"./ex1/output/size5/output.txt",
						"./ex1/output/size6/output.txt",			
					};
char Out_Time[6][28]={"./ex1/output/size1/time.txt",
						"./ex1/output/size2/time.txt",
						"./ex1/output/size3/time.txt",
						"./ex1/output/size4/time.txt",
						"./ex1/output/size5/time.txt",
						"./ex1/output/size6/time.txt",
					};

char Out_Graph[6][29]={"./ex1/output/size1/graph.dot",
						"./ex1/output/size2/graph.dot",
						"./ex1/output/size3/graph.dot",
						"./ex1/output/size4/graph.dot",
						"./ex1/output/size5/graph.dot",
						"./ex1/output/size6/graph.dot",

			};
 
int Scale;
int N;
int *F;
int p=0;			//F数组的指针 
int Ti=0;
double Time;
FILE *outSCC,*outTi;//输出文件指针 
FILE *Graph;
int C=0;
struct timespec time_start={0,0},time_end={0,0};

int main(int argc,char *argv[]){
	
	FILE *input;
	char filename[28];  //输入文件名 
	char outScc[30];	//连通分量输出文件名 
	char outTime[28];	//时间输出文件名 
	char outGraph[29];	//用于图像形成的文件
	Scale=atoi(argv[1]);
	strcpy(filename,Filename[Scale-1]);	
	strcpy(outScc,Out_SCC[Scale-1]);
	strcpy(outTime,Out_Time[Scale-1]);
	strcpy(outGraph,Out_Graph[Scale-1]);
	input=fopen(filename,"r");
	outSCC=fopen(outScc,"w");
	outTi=fopen(outTime,"w");
	Graph=fopen(outGraph,"w");
	if(!input||!outSCC||!outTi||!Graph){
		printf("error:can't open objcct file.\n");
		exit(1);
	}
	N=pow(2,Scale+2);
	Node *G=(Node*)malloc(N*sizeof(Node)); 
	Node *Gt=(Node*)malloc(N*sizeof(Node)); 
	F=(int*)malloc(N*sizeof(int)); 
	int Edge=N*(Scale+2);
	//int Edge=N;
	int i,j,k;
	int v1,v2;
	Adj *ptr,*ptr1;
	for(i=0;i<N;i++){
		G[i].Seq=i;
		G[i].Color=0;
		G[i].Pi=-1;
		G[i].adj=NULL;
	}
	Adj *z;
	for(i=0;i<Edge;i++){
		fscanf(input,"%d %d",&v1,&v2);
		//fscanf(input,"%d",&v2);
		z=(Adj*)malloc(sizeof(Adj));
		z->v=v2;
		z->next=NULL;
		ptr1=G[v1].adj; 
		if(ptr1==NULL)				
			G[v1].adj=z;
		else{
			while(ptr1!=NULL){
				ptr=ptr1;
				ptr1=ptr1->next;
			}
			ptr->next=z;
		}		
	}
GRAPH(G);

	clock_gettime(CLOCK_REALTIME,&time_start);	
	SCC(G,Gt);
	clock_gettime(CLOCK_REALTIME,&time_end);
	Time=(double)(time_end.tv_nsec-time_start.tv_nsec); 
	fprintf(outTi,"%lf\n",Time);
/*
	for(i=0;i<N;i++){
		printf("%d:",i);
		ptr=G[i].adj;
		while(ptr!=NULL){
			printf("%d ",ptr->v);
			ptr=ptr->next;
		}
		printf("\n%d--fi:%d\n",G[i].Color,F[i]);
	}
*/
	fprintf(outSCC,"SCC=%d\n",C);
	for(i=1;i<=C;i++){
		fprintf(outSCC,"(");
		for(j=0;j<N;j++)
			if(Gt[j].Con==i)
				fprintf(outSCC,"%d ",j);
		fprintf(outSCC,")\n");
	}

	
	fclose(input);
	fclose(outSCC);
	fclose(outTi);
	fclose(Graph);

	printf("Complete ex1:size of %d.\n",N);

	return 0;
}

void SCC(Node *G,Node *Gt){
	
	DFS(G);	
	int i;
	Adj *ptr,*ptr0,*ptr1;
	Adj *z;
	int w;
	for(i=0;i<N;i++){
		Gt[i].Seq=i;
		Gt[i].Color=0;
		Gt[i].adj=NULL;
	}
		
	for(i=0;i<N;i++){
		ptr=G[i].adj;
		if(ptr==NULL){
			continue;
		}
		else{			
			while(ptr!=NULL){
				z=(Adj*)malloc(sizeof(Adj));
				z->v=i;
				z->next=NULL;
				w=ptr->v;
				ptr1=Gt[w].adj;
				if(ptr1==NULL)				
					Gt[w].adj=z;
				else{
					while(ptr1!=NULL){
						ptr0=ptr1;
						ptr1=ptr1->next;
					}
					ptr0->next=z;
				}	
				ptr=ptr->next;	
			}
		}		
	}	
		
	DFSt(Gt);	
}

void DFS(Node *G){

	int i;
	for(i=0;i<N;i++)
		if(G[i].Color==0)
			DFS_VISIT(G,i); 	
}

void DFSt(Node *G){
	
	int i;
	for(i=N-1;i>=0;i--){
		if(G[F[i]].Color==0){
			C++;
			DFS_VISIT(G,F[i]); 
		} 
	}
		
}

void DFS_VISIT(Node *G,int u){
	
	Ti++;
	G[u].Color=1;
	G[u].Con=C;
	Adj *ptr=G[u].adj;
	int w;
/*
	if(ptr!=NULL)
		for(;ptr!=NULL;ptr=ptr->next){
				w=ptr->v;
		if(G[w].Color==0){
			G[w].Pi=u.Seq;
			printf("w=%d\n",w);
			DFS_VISIT(G,G[w]);
			}
		} 
*/
	
	while(ptr!=NULL){
		
		w=ptr->v;
		if(G[w].Color==0){
			G[w].Pi=u;
			DFS_VISIT(G,w);
		}
		ptr=ptr->next;
	}

	G[u].Color=2;
	Ti++;
	F[p]=u;
	p++;
}

void GRAPH(Node* G){
	
	fprintf(Graph,"digraph \{\n");
	int i;
	Adj *ptr;
	int w;

	for(i=0;i<N;i++){
		ptr=G[i].adj;
		while(ptr!=NULL){
			w=ptr->v;
			fprintf(Graph,"	%d -> %d\n",i,w);
			//printf("	%d -> %d\n",i,w);
			ptr=ptr->next;	
		}
	}
	fprintf(Graph,"\r}\n");	
}
