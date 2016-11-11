#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>
#include<windows.h>

void radix_sort(int* num);
void counting_sort(int* num,int *res,int k);
int Scale;//记录排序规模

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
    radix_sort(num); 
    QueryPerformanceCounter(&nEndTime);  
    Time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart; 

	char filename[35]="../output/Radix_sort/result_";
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
       
	output_num=fopen(filename,"w+");	
	for(i=0;i<Scale;i++)
		fprintf(output_num,"%d\n",num[i]);		
	fclose(output_num);
			
	output_time=fopen("../output/Radix_sort/time.txt","a");
	fprintf(output_time,"Radix_%d:%.8f\n",scale,Time);
	fclose(output_time);
	
	system("pause");
	return 0;
}

void radix_sort(int* num){
	
//这里把排序数看做一个5位数，每一位的都是0-9
//如果直接看成一个1位数，那就和计数排序一样了
//这里用计数排序作为该排序的稳定算法 	
	int i,j;
	int* res=(int*)malloc(Scale*sizeof(int));
	for(i=0;i<5;i++){
		counting_sort(num,res,i);
		for(j=0;j<Scale;j++)
			num[j]=res[j];
	}	
}

void counting_sort(int* num,int *res,int k){
    
    int i,j;
    int w; 
    int* C=(int*)malloc(10*sizeof(int));
    int factor=pow(10,k);
    for(i=0;i<10;i++)
    	C[i]=0;
    for(j=0;j<Scale;j++){
	    w=(num[j]/factor)%10;
    	C[w]=C[w]+1;
    } 
	for(i=1;i<10;i++)
		C[i]=C[i]+C[i-1];
	for(j=Scale-1;j>=0;j--){
		w=(num[j]/factor)%10;
		res[C[w]-1]=num[j];
		C[w]--;
	} 

}

