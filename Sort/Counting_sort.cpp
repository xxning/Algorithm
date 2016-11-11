#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>
#include<windows.h>

void counting_sort(int* num,int *res,int k); 
int Scale;//¼ÇÂ¼ÅÅÐò¹æÄ£

int main(){
	
	FILE* input;
	FILE* output_num;
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
	
	int* num=(int*)malloc(Scale*sizeof(int));
	int* res=(int*)malloc(Scale*sizeof(int));
	
	input=fopen("../input/input_numbers.txt","r");
	if(!input){
		printf("error:can't open objcct file.\n");
		exit(1);
	}
	for(i=0;i<Scale;i++)
		fscanf(input,"%d",&num[i]);	
	fclose(input);
	
	QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);   
    counting_sort(num,res,65535); 
    QueryPerformanceCounter(&nEndTime);  
    Time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart; 	

	char filename[38]="../output/Counting_sort/result_";
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
			filename[31]=(char)(48+scale);
			filename[32]='.';
			filename[33]='t';
			filename[34]='x';
			filename[35]='t';
			filename[36]='\0';
			break;
		}
		case 10:
		case 11:
		case 12:
		case 13:{
			filename[31]=49;
			filename[32]=(char)(38+scale);
			filename[33]='.';
			filename[34]='t';
			filename[35]='x';
			filename[36]='t';
			filename[37]='\0';
			break;
		}
		default:{
			printf("error:the value of scale is illegal.\n"); 
			exit(1);
		}				
	}
       
	output_num=fopen(filename,"w+");	
	for(i=0;i<Scale;i++)
		fprintf(output_num,"%d\n",res[i]);		
	fclose(output_num);
			
	output_time=fopen("../output/Counting_sort/time.txt","a");
	fprintf(output_time,"Counting_sort_%d:%.8f\n",scale,Time);
	fclose(output_time);
	
	system("pause");
	return 0;
}

void counting_sort(int* num,int *res,int k){
    
    int i,j;
    int* C=(int*)malloc((k+1)*sizeof(int));
    for(i=0;i<=k;i++)
    	C[i]=0;
    for(j=0;j<Scale;j++)
    	C[num[j]]=C[num[j]]+1;
	for(i=1;i<=k;i++)
		C[i]=C[i]+C[i-1];
	for(j=Scale-1;j>=0;j--){
		res[C[num[j]]-1]=num[j];
		C[num[j]]--;
	} 

}
