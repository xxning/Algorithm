#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>
#include<windows.h>

void heap_sort(char** str); 
void build_max_heap(char** str);
void max_heapify(char** str,int node);
int Scale;//¼ÇÂ¼ÅÅÐò¹æÄ£
int heap_size;

int main(){
	
	FILE* input;
	FILE* output_str;
	FILE* output_time; 
    int i;
    LARGE_INTEGER nFreq;  
    LARGE_INTEGER nBeginTime;  
    LARGE_INTEGER nEndTime;
    double Time;
    
    int scale;
	printf("Enter the scale of sort:\n");
	printf("e.g.   enter 10 to represent the scale of 2^10\n");
	scanf("%d",&scale);
	if(scale<1||scale>13){
		printf("error:not a proper scale.\n");
		exit(1);
	} 
	Scale=pow(2,scale);
	heap_size=Scale-1;
	
	char* str[Scale];
	for(i=0;i<Scale;i++)
		str[i]=(char*)malloc(17*sizeof(char));	
	input=fopen("../input/input_strings.txt","r");
	if(!input){
		printf("error:can't open objcct file.\n");
		exit(1);
	}
	for(i=0;i<Scale;i++){
		fscanf(input,"%s",*(str+i));
	}
	fclose(input);
	
	QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);   
    heap_sort(str); 
    QueryPerformanceCounter(&nEndTime);  
    Time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;  
	
	char filename[34]="../output/Heap_sort/result_";
	switch(scale){
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:{
			filename[27]=(char)(48+scale);
			filename[28]='.';
			filename[29]='t';
			filename[30]='x';
			filename[31]='t';
			filename[32]='\0';
			break;
		}
		case 10:
		case 11:
		case 12:
		case 13:{
			filename[27]=49;
			filename[28]=(char)(38+scale);
			filename[29]='.';
			filename[30]='t';
			filename[31]='x';
			filename[32]='t';
			filename[33]='\0';
			break;
		}
		default:{
			printf("error:the value of scale is illegal.\n"); 
			exit(1);
		}				
	}

	output_str=fopen(filename,"w+");
	for(i=0;i<Scale;i++){
		fprintf(output_str,"%s\n",*(str+i));
	}
	fclose(output_str);
	
	output_time=fopen("../output/Heap_sort/time.txt","a");
	fprintf(output_time,"Heap_sort_%d:%.8f\n",scale,Time);
	fclose(output_time);
	
	system("pause");
	return 0;
}

void heap_sort(char** str){
	
    build_max_heap(str);
    int i;
    char* tem=(char*)malloc(17*sizeof(char));
    for(i=Scale-1;i>=1;i--){
    	strcpy(tem,*str);
		strcpy(*str,*(str+i));
		strcpy(*(str+i),tem); 
		heap_size=heap_size-1;
		max_heapify(str,0);
    }
}

void build_max_heap(char** str){
	
	int i;
	for(i=(Scale-1)/2;i>=0;i--)
		max_heapify(str,i);		
}

void max_heapify(char** str,int node){
	
	int l=2*node+1;
	int r=2*node+2;
	char* tem=(char*)malloc(17*sizeof(char));
	int largest;
	
	if(l<=heap_size&&(strcmp(*(str+l),*(str+node)))>0)
		largest=l;
	else 
		largest=node;
	if(r<=heap_size&&(strcmp(*(str+r),*(str+largest)))>0)	
		largest=r;
	if(largest!=node){
		strcpy(tem,*(str+node));
		strcpy(*(str+node),*(str+largest));
		strcpy(*(str+largest),tem);
		max_heapify(str,largest);
	}
}

