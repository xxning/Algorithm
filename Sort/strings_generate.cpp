#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

int main(){
	
	FILE *output;
	output=fopen("../input/input_strings.txt","w");
	if(!output){
		printf("error:can't open objcct file.\n");
		exit(1);
	}
		
	int i,j;
	int scale=pow(2,13);
	int length;
	char str[17];
	int chose;  //ѡ��26����ĸ�е�һ�� 
	int capital; //ѡ���Сд 
	srand((unsigned)time(NULL));
	for(i=0;i<scale;i++){
		length=1+rand()%16;
		for(j=0;j<length;j++){
			capital=rand()%2;
			chose=rand()%26;//����0-25��������� 
			chose=(capital)?(65+chose):(97+chose); 
			str[j]=(char)chose;
		}
		str[j]='\0';
		fprintf(output,"%s\n",str);		
	}

	fclose(output);
	
	system("pause");	
	return 0;
}
