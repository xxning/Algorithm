#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

int main(){
	
	FILE *output;
	output=fopen("../input/input_numbers.txt","w");
	if(!output){
		printf("error:can't open objcct file.\n");
		exit(1);
	}
		
	int i;
	int scale=200;
	double Rand;  
	srand((unsigned)time(NULL));
	for(i=0;i<scale;i++){
		
		Rand=rand()/(RAND_MAX+1.0);
		Rand=Rand*65535;
		fprintf(output,"%d\n",(int)Rand);		
	}
  
	fclose(output);
	
	system("pause");	
	return 0;
}
