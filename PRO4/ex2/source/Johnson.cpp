#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>

#define INF 10000

struct Adj{
	int v;
	Adj *next;
};

struct Node{
	int h; 		//h函数值    
	int Seq;	//序号 
	int d;   //距离
	int Pi;		// 结点的祖先存的是祖先的编号，初始为-1 
	int flag;	// 0表示在Q中,1表示在S中
	Adj *adj;	//邻接链表，初始为NULL 
	
};

void INITIALIZE(Node *G,int s);
void RELAX(Node *G,int u,int v);
int  BELLMAN_FORD(Node *G,int s);
void DIJKSTRA(Node *G,int s);
void JOHNSON(Node *G);
void build_min_heap(Node *G);
void min_heapify(Node *G,int node);
int  EXTRACT_MIN(Node *G);
void PRINT_PATH(int i,int j);
void GRAPH(Node* G);

char Filename[6][28]={"./ex2/input/size1/input.txt",
						  "./ex2/input/size2/input.txt",
						  "./ex2/input/size3/input.txt",
						  "./ex2/input/size4/input.txt",
						  "./ex2/input/size5/input.txt",
						  "./ex2/input/size6/input.txt"	
					 	};
char Out_Path[6][30]={"./ex2/output/size1/output.txt",
						"./ex2/output/size2/output.txt",
						"./ex2/output/size3/output.txt",
						"./ex2/output/size4/output.txt",
						"./ex2/output/size5/output.txt",
						"./ex2/output/size6/output.txt",			
					};
char Out_Time[6][28]={"./ex2/output/size1/time.txt",
						"./ex2/output/size2/time.txt",
						"./ex2/output/size3/time.txt",
						"./ex2/output/size4/time.txt",
						"./ex2/output/size5/time.txt",
						"./ex2/output/size6/time.txt",
					};

char Out_Graph[6][29]={"./ex2/output/size1/graph.dot",
						"./ex2/output/size2/graph.dot",
						"./ex2/output/size3/graph.dot",
						"./ex2/output/size4/graph.dot",
						"./ex2/output/size5/graph.dot",
						"./ex2/output/size6/graph.dot",

			};
 
int Scale;
int N;
FILE *outPATH,*outTi;//输出文件指针 
FILE *Graph;
int **w;
struct timespec time_start={0,0},time_end={0,0};
int Size;
int **D,**P;
Node *Gt;
double Time;

int main(int argc,char *argv[]){
	
	FILE *input;
	char filename[28];  //输入文件名 
	char outScc[30];	//连通分量输出文件名 
	char outTime[28];	//时间输出文件名 
	char outGraph[29];	//用于图像形成的文件
	Scale=atoi(argv[1]);
	strcpy(filename,Filename[Scale-1]);	
	strcpy(outScc,Out_Path[Scale-1]);
	strcpy(outTime,Out_Time[Scale-1]);
	strcpy(outGraph,Out_Graph[Scale-1]);
	input=fopen(filename,"r");
	outPATH=fopen(outScc,"w");
	outTi=fopen(outTime,"w");
	Graph=fopen(outGraph,"w");
	if(!input||!outPATH||!outTi||!Graph){
		printf("error:can't open objcct file.\n");
		exit(1);
	}
	N=pow(2,Scale+2);
	int Edge=N*(Scale+2);
	Node *G=(Node*)malloc((N+1)*sizeof(Node)); 
	Gt=(Node*)malloc((N+1)*sizeof(Node)); 
	int i,j;
	int v1,v2,l;
	Adj *ptr,*ptr1;
	Adj *z;
	w=(int**)malloc((N+1)*sizeof(int*));
	D=(int**)malloc((N+1)*sizeof(int*));
	P=(int**)malloc((N+1)*sizeof(int*));
	for(i=0;i<N+1;i++){
		w[i]=(int*)malloc((N+1)*sizeof(int));
		D[i]=(int*)malloc((N+1)*sizeof(int));
		P[i]=(int*)malloc((N+1)*sizeof(int));
	}
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			w[i][j]=INF;
	for(i=0;i<Edge;i++){

		fscanf(input,"%d %d %d",&v1,&v2,&l);
		w[v1][v2]=l;
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
/*	
	for(i=0;i<N;i++){
		printf("%d:",i);
		ptr=G[i].adj;
		while(ptr!=NULL){
			printf("%d ",ptr->v);
			ptr=ptr->next;
		}
		printf("\n");
	}
*/	
	GRAPH(G);	
	
	clock_gettime(CLOCK_REALTIME,&time_start);
	JOHNSON(G);
	clock_gettime(CLOCK_REALTIME,&time_end);
	Time=(double)(time_end.tv_nsec-time_start.tv_nsec); 
	fprintf(outTi,"%lf\n",Time);
	
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(i==j)
				continue;
			if(P[i][j]<0)
				fprintf(outPATH,"%d->%d(Length=INF):",i,j);
			else
				fprintf(outPATH,"%d->%d(Length=%3d):",i,j,D[i][j]);
			PRINT_PATH(i,j);
			fprintf(outPATH,"\n");
		}
	}

	fclose(input);
	fclose(outPATH);
	fclose(outTi);
	fclose(Graph);
	
	printf("Complete ex2:size of %d.\n",N);

	return 0;
}

void INITIALIZE(Node *G,int s){

	int i;
	for(i=0;i<N;i++){
		G[i].d=INF;
		G[i].Pi=-1;
		G[i].flag=0;	
	}
	G[s].d=0;
}

void RELAX(Node *G,int u,int v){

	if(G[v].d>G[u].d+w[u][v]){
		G[v].d=G[u].d+w[u][v];
		G[v].Pi=u;
	}
}

int BELLMAN_FORD(Node *G,int s){
	
	INITIALIZE(G,s);
	int i,j,k;
	Adj *ptr;
	int ww;
	for(i=1;i<N;i++){
		for(j=0;j<N;j++){
			ptr=G[j].adj;
			while(ptr!=NULL){
				ww=ptr->v;
				RELAX(G,j,ww);
				ptr=ptr->next;		
			}
		}
	}
	for(j=0;j<N;j++){
		ptr=G[j].adj;
		while(ptr!=NULL){
			ww=ptr->v;
			if(G[ww].d>G[j].d+w[j][ww])
				return 0;
			ptr=ptr->next;		
		}
	}
	return 1;
}

void DIJKSTRA(Node *G,int s){
	
	INITIALIZE(G,s);
	int u,ww;
	int i,j;
	Adj *ptr;
	while(Size>0){
		u=EXTRACT_MIN(G);
		ptr=G[u].adj;
		while(ptr!=NULL){
			ww=ptr->v;
			RELAX(G,u,ww);	
			ptr=ptr->next;		
		}
	}
}
/*
void heap_sort(Node *G){
	
    build_min_heap(G);
    int i;
    char* tem=(Node)malloc(sizeof(Node));
    for(i=Scale-1;i>=1;i--){
    	strcpy(tem,*str);
		strcpy(*str,*(str+i));
		strcpy(*(str+i),tem); 
		heap_size=heap_size-1;
		max_heapify(str,0);
    }
}
*/
/*
void build_min_heap(Node *G){
	
	int i;
	for(i=(Scale-1)/2;i>=0;i--)
		min_heapify(G,i);		
}

void min_heapify(Node *G,int node){
	
	int l=2*node+1;
	int r=2*node+2;
	Node tem;
	int min;
	
	if(l<=heap_size&&G[l].d<G[node].d)
		min=l;
	else 
		min=node;
	if(r<=heap_size&&G[r].d<G[min].d)	
		min=r;
	if(min!=node){
		tem=G[node];
		G[node]=G[min];
		G[min]=tem;
		min_heapify(G,min);
	}
}
*/
int EXTRACT_MIN(Node *G){
	
	int i,seq;
	int min=1000000;
	for(i=0;i<N;i++){
		if(min>G[i].d&&G[i].flag==0){
			min=G[i].d;
			seq=i;
		}
	}
	G[seq].flag=1;
	Size--;
	return seq;
}

void JOHNSON(Node *G){

	int i,j;
	for(i=0;i<N;i++)
		w[N][i]=0;
	Adj *z;
	Adj *ptr=G[N].adj;
	int ww;
	for(i=0;i<N;i++){
		z=(Adj*)malloc(sizeof(Adj));
		z->v=i;
		z->next=NULL;
		ptr=z;
		ptr=ptr->next;
	}
	if(BELLMAN_FORD(G,N)==0){
		printf("the input graph contains a negative-weight cycle(ex2:size of %d).\n",N);
		exit(1);
	}
	else{
		for(i=0;i<N;i++)
			G[i].h=G[i].d;
		for(j=0;j<N;j++){
			ptr=G[j].adj;
			while(ptr!=NULL){
				ww=ptr->v;
				w[j][ww]=w[j][ww]+G[j].h-G[ww].h;
				ptr=ptr->next;		
			}
		}
		for(i=0;i<N;i++){
			Size=N;
			DIJKSTRA(G,i);
			for(j=0;j<N;j++){
				if(i==j){
					D[i][j]=0;
					P[i][j]=-1;
					continue;
				}
				else{
					D[i][j]=G[j].d+G[j].h-G[i].h;
					P[i][j]=G[j].Pi;
				}	
			}
		}
	}
}

void PRINT_PATH(int i,int j){
	
	if(i==P[i][j])
		fprintf(outPATH," %d->%d",i,j);
	else{
		if(P[i][j]<0)
			fprintf(outPATH,"can't access.");
		else{
			PRINT_PATH(i,P[i][j]);
			fprintf(outPATH,"->%d",j);
		}
	}
}

void GRAPH(Node* G){
	
	fprintf(Graph,"digraph \{\n");
	int i;
	Adj *ptr;
	int ww;
	for(i=0;i<N;i++){
		ptr=G[i].adj;
		while(ptr!=NULL){
			ww=ptr->v;
			fprintf(Graph,"	%d -> %d [label=\"%d\",fontcolor=red]\n",i,ww,w[i][ww]);
			//printf("	%d -> %d\n",i,w);
			ptr=ptr->next;	
		}
	}
	fprintf(Graph,"\r}\n");	
}
