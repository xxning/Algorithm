#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>
#include<windows.h>

void merge_sort(char** str,char** str2,int start,int end);
void merge(char** str,char** str2,int start,int mid,int end);
int Scale;//¼ÇÂ¼ÅÅÐò¹æÄ£

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
	
	char* str[Scale];
	for(i=0;i<Scale;i++)
		str[i]=(char*)malloc(17*sizeof(char));	
		
	char* str2[Scale];
	for(i=0;i<Scale;i++)
		str2[i]=(char*)malloc(17*sizeof(char));	
		
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
    merge_sort(str,str2,0,Scale-1); 
    QueryPerformanceCounter(&nEndTime);  
    Time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;  
	
	char filename[35]="../output/Merge_sort/result_";
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
			filename[28]=(char)(48+scale);
			filename[29]='.';
			filename[30]='t';
			filename[31]='x';
			filename[32]='t';
			filename[33]='\0';
			break;
		}
		case 10:
		case 11:
		case 12:
		case 13:{
			filename[28]=49;
			filename[29]=(char)(38+scale);
			filename[30]='.';
			filename[31]='t';
			filename[32]='x';
			filename[33]='t';
			filename[34]='\0';
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
	
	output_time=fopen("../output/Merge_sort/time.txt","a");
	fprintf(output_time,"Merge_sort_%d:%.8f\n",scale,Time);
	fclose(output_time);
	
	system("pause");
	return 0;
}

void merge_sort(char** str,char** str2,int start,int end){
    int mid;
    if(start<end){
    	mid=(start+end)/2;
    	merge_sort(str,str2,start,mid);
    	merge_sort(str,str2,mid+1,end);
    	merge(str,str2,start,mid,end);
    }
}

void merge(char** str,char** str2,int start,int mid,int end){
	
	int i=start,j=mid+1;
	int index=start;
	while(i!=mid+1 && j!=end+1){
		if(strcmp(*(str+i),*(str+j))>0)
			strcpy(*(str2+(index++)),*(str+(j++)));
		else
			strcpy(*(str2+(index++)),*(str+(i++)));		
	}
	while(i!=mid+1)
		strcpy(*(str2+(index++)),*(str+(i++)));	
	while(j!=end+1)
		strcpy(*(str2+(index++)),*(str+(j++)));
	for(i=start;i<=end;i++)
		strcpy(*(str+i),*(str2+i));	
	
}
