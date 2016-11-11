#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>
#include<windows.h>

void bubble_sort(char** str); 
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
    bubble_sort(str); 
    QueryPerformanceCounter(&nEndTime);  
    Time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart; 
	
	char filename[36]="../output/Bubble_sort/result_";
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
			filename[29]=(char)(48+scale);
			filename[30]='.';
			filename[31]='t';
			filename[32]='x';
			filename[33]='t';
			filename[34]='\0';
			break;
		}
		case 10:
		case 11:
		case 12:
		case 13:{
			filename[29]=49;
			filename[30]=(char)(38+scale);
			filename[31]='.';
			filename[32]='t';
			filename[33]='x';
			filename[34]='t';
			filename[35]='\0';
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
	
	output_time=fopen("../output/Bubble_sort/time.txt","a");
	fprintf(output_time,"Bubble_sort_%d:%.8f\n",scale,Time);
	fclose(output_time);
	
	system("pause");
	return 0;
}

void bubble_sort(char** str){
    char* tem=(char*)malloc(17*sizeof(char));
    char* min=(char*)malloc(17*sizeof(char));
    int i,j;
    for(i=0;i<Scale-1;i++){
    	min=*(str+i);
    	for(j=i+1;j<Scale;j++){
    		if(strcmp(min,*(str+j))>0)
    			min=*(str+j);
    	}
    	strcpy(tem,*(str+i));
    	strcpy(*(str+i),min); 
    	strcpy(min,tem);
    }
}
