#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

int main(){
	
	FILE *input;
	srand((unsigned)time(NULL));
	int i,j,k;
	int n,e,v1,v2,w;
	char Filename[6][28]={"./ex2/input/size1/input.txt",
						  "./ex2/input/size2/input.txt",
						  "./ex2/input/size3/input.txt",
						  "./ex2/input/size4/input.txt",
						  "./ex2/input/size5/input.txt",
						  "./ex2/input/size6/input.txt"	
						};
	char Edge[256][256];
	for(i=0;i<256;i++)
		for(j=0;j<256;j++)
			Edge[i][j]=0;
//******************************************
//******************************************
	for(i=0;i<6;i++){
		n=pow(2,i+3);		
		e=n*(i+3);	
		input=fopen(Filename[i],"w");
		if(!input){
			printf("error:can't open objcct file.\n");
			exit(1);
		}
		for(j=0;j<e;j++){
			v1=rand()%n;
			v2=rand()%n;
			if(v1==v2||Edge[v1][v2]==1)
				j--;
			else{
				Edge[v1][v2]=1;
				w=rand()%10;
				//w=w-1;
				fprintf(input,"%d %d %d\n",v1,v2,w);
			}			
		}
		for(j=0;j<n;j++)
			for(k=0;k<n;k++)
				Edge[j][k]=0;
		fclose(input);	
	}
//******************************************
//******************************************	
	printf("Complete the generate of edge(ex1).\n");
		
	return 0;
} 
