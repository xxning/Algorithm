#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){

	FILE *input;
	char Filename[2][23]={"./ex2/input/inputA.txt",
						  "./ex2/input/inputB.txt",
						};

	int i,j,k;
	int chose;
	char c;
	srand((unsigned)time(NULL));	
	input=fopen(Filename[0],"w");
	if(!input){
		printf("error:can't open objcct file.\n");
		exit(1);
	}
	for(i=1;i<=6;i++){
		for(j=1;j<=15;j++){
			chose=65+rand()%26;//产生65+(0-25)的随机整数 
			c=(char)chose;
			fprintf(input,"%c",c);	
		}
		fprintf(input,"\n");
		for(j=1;j<=10*i;j++){
			chose=65+rand()%26;//产生65+(0-25)的随机整数 
			c=(char)chose;
			fprintf(input,"%c",c);	
		}	
		fprintf(input,"\n");	
	}
	fclose(input);	
//******************************************
//******************************************		
	input=fopen(Filename[1],"w");
	if(!input){
		printf("error:can't open objcct file.\n");
		exit(1);
	}
	for(i=1;i<=6;i++){
		for(j=1;j<=15*i;j++){
			chose=65+rand()%26;//产生65+(0-25)的随机整数 
			c=(char)chose;
			fprintf(input,"%c",c);	
		}
		fprintf(input,"\n");
		for(j=1;j<=25;j++){
			chose=65+rand()%26;//产生65+(0-25)的随机整数 
			c=(char)chose;
			fprintf(input,"%c",c);	
		}	
		fprintf(input,"\n");	
	}
	fclose(input);	
    printf("Complete the generate of strings.\n");
    
	return 0;
}
