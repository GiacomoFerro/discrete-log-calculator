#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "mylib.h" //contains functions used in this program

/*
this script calculates coprimes cyclic group and find its generator g. 

After this step, calcolate i t.c. a=g^i according to discrete log problem.


DH handshake uses a very large prime number p and seed g (its generator). Pa e Pb know the relation used to 
create the group and takes Xa e Xb from this group generated starting from p. 
The intruder cannot derive this information even if he may know [p,g].

*/

int main(){

	int p=0;	
	int scelta=2;

	int * group;
	int * trimmed_group;


	printf("1---> generate a cyclic group.\n2---> generate a non cyclic group.\nMake your choice: ");
	scanf("%d",&scelta);
	
	if(scelta<1 || scelta >2 ) {puts("not a valid choice."); exit(1);}

	if(scelta==1){

		printf("digit a prime integer:");
		scanf("%d",&p);
		
		while( ! is_prime(p) ){
			printf("The number was not prime. Digit a prime integer:");
			scanf("%d",&p);
		}

		group = (int *) malloc(sizeof(int)*(p-1));
		if(group == NULL) {
			printf("out of memory fault\n");
			exit(1);
		}

		//calculate_CoGroup(p,group);

		int i;
		int val;
		for(i=0,val=1; i<=p-1; i++){
			group[i]=val;
			val++;
		}

		printf("\nThe group of %d is:\n", p);
		print_array(group, p-1);
	}
	else{

		printf("digit a integer:");
		scanf("%d",&p);
		
		group = (int *) malloc(sizeof(int)*(p-1));
		if(group == NULL) {
			printf("out of memory fault\n");
			exit(1);
		}
		
		calculate_CoGroup(p,group);
		int dim=optimize(group,p);//calculare number of real residues

		trimmed_group = (int *) malloc(sizeof(int)*dim);

		if(trimmed_group == NULL) {
			printf("out of memory fault\n");
			exit(1);
		}
		else{
			allocate_val(trimmed_group, group, p);
		}
		
		free(group);

		printf("\nThe group of %d is:\n", p);
		print_array(trimmed_group, dim);


	}//end of else

	if(scelta!=1){
		free(trimmed_group);
		return 0;
	}
	
	//calculate generator of a cyclic group
	int g;
	printf("generator of the cyclic group is %d\n", g=calculate_generator(group,p));

	int ris[2]={0};
	calculate_discreteLog(g,group,p,ris);

	printf("a=g^i. a=%d i=%d, group[i]=%d\n", ris[0],ris[1], group[ris[1]]);

	free(group);


}


void calculate_discreteLog(int g, int group[], int p, int ris[]){

	
	srand(time(NULL));
	
	int i = rand()%p;
	
	int a = (int) ( pow( g, group[i] ) + 0.5 );

	ris[0]=a;
	ris[1]=i;

	return;

}





