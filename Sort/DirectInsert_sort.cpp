#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>
#include<windows.h>

void directinsert_sort(int* num);
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
    directinsert_sort(num); 
    QueryPerformanceCounter(&nEndTime);  
    Time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart; 

	char filename[42]="../output/DirectInsert_sort/result_";
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
			filename[35]=(char)(48+scale);
			filename[36]='.';
			filename[37]='t';
			filename[38]='x';
			filename[39]='t';
			filename[40]='\0';
			break;
		}
		case 10:
		case 11:
		case 12:
		case 13:{
			filename[35]=49;
			filename[36]=(char)(38+scale);
			filename[37]='.';
			filename[38]='t';
			filename[39]='x';
			filename[40]='t';
			filename[41]='\0';
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
			
	output_time=fopen("../output/DirectInsert_sort/time.txt","a");
	fprintf(output_time,"DirectInsert_%d:%.8f\n",scale,Time);
	fclose(output_time);
	
	system("pause");
	return 0;
}

void directinsert_sort(int* num){

	int i,j;
	int tem;
	for(i=1;i<Scale;i++){
		tem=num[i];
		j=i-1;
		while(j>=0 && tem<num[j]){
				num[j+1]=num[j];
    			j--;
    		}
    	num[j+1]=tem;
	}	
}



