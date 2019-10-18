#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "mylib.h"

/*A simple implementation of dh scheme. This program uses random number for simulation. 
To prevent critto-analytic attacks you have to solve pseudorandom problem.

*/

int main(){

	//define p e g of Z(p)*. p is a prime number and g is a generator of the group
	srand(time(NULL));
	int p,g,i,val;
	int * group;

	principal principals[MAXUSER];//principals 	
	directory dir;//directory public keys

	for(i=0; i<100; i++){
		dir.P[i]=0;
		principals[i].public_key=0;
		principals[i].private_key=0;
		principals[i].symmetric_key=0;
	}

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

	
	for(i=0,val=1; i<=p-1; i++, val++){
		group[i]=val;
	}

	printf("\nThe group of %d is:\n", p);
	print_array(group, p-1);
	
	printf("generator g of the cyclic group is %d\n", g=calculate_generator(group,p));

	//BEGIN  OF DIFFIE HELLMAN


	//ALICE creation and update
	update_principals(principals,g,p,group,0);
	puts("principal created");
	dir=update_dir(principals,dir, 0);
	puts("directory updated");	

		
	sleep(rand()%10); //change of the seed

	//BOB creation and update
	update_principals(principals,g,p,group, 1);
	puts("\nprincipal created");
	dir=update_dir(principals,dir, 1);
	puts("directory updated");

	/*
	puts("\ndirectory:");
	for(i=0; i<2; i++){
		printf("%d\n",dir.P[i]);
	}
	puts("\nprincipals:");
	for(i=0; i<=1; i++){
		printf("PU=%d PR=%d SYM=%d\n",principals[i].public_key, principals[i].private_key, principals[i].symmetric_key);
	}
	*/

	//generate a symmetic key and show it's the same
	int Kab=generate_Kab(principals, dir, p, 0, 1); //Kab	principal alice with bob
	int Kba=generate_Kab(principals, dir, p, 1, 0); //Kba

	/*
	//show that Kab==Kba 
	if(Kab!=0  &&  Kba!=0) printf("Kab=%d Kba=%d\n",Kab,Kba);
	else puts("error in the key generation of keys");
	*/

	printf("ALICE AND BOB symmetric keys are equals? %s\n", Kab==Kba ? "true" : "false");
	free(group);

}//fine main
    



