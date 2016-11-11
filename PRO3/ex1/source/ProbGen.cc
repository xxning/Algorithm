#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
	
	FILE *input;
	float Prob[61];
	float PTotal,Sum;
	srand((unsigned)time(NULL));
	int i,j;
	int n;
	char Filename[6][28]={"./ex1/input/size1/input.txt",
						  "./ex1/input/size2/input.txt",
						  "./ex1/input/size3/input.txt",
						  "./ex1/input/size4/input.txt",
						  "./ex1/input/size5/input.txt",
						  "./ex1/input/size6/input.txt"	
						};
//******************************************
//******************************************
	for(j=0;j<6;j++){
	
		Sum=0;
		PTotal=0;
		n=10*j+11; 
		for(i=0;i<n;i++){
			Prob[i]=rand();
			Sum+=Prob[i];
		}
		for(i=0;i<n;i++){
			Prob[i]=Prob[i]/Sum;
			PTotal+=Prob[i];
		}
		if(PTotal!=1)
			Prob[n-1]+=(1-PTotal);
		input=fopen(Filename[j],"w");
		if(!input){
			printf("error:can't open objcct file.\n");
			exit(1);
		}
		for(i=0;i<n;i++){
			fprintf(input,"%f\n",Prob[i]);	
		}	
		fclose(input);	
	}
//******************************************
//******************************************	
	printf("Complete the generate of probability.\n");
	
	return 0;
}
