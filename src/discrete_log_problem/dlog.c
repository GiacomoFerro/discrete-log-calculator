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
	printf("generator g of the cyclic group is %d\n", g=calculate_generator(group,p));

	int ris[2]={0};
	calculate_discreteLog(g,group,p,ris);

	printf("a=g^i. a=%d i=%d, group[i]=%d\n", ris[0],ris[1], group[ris[1]]);


	/*Legendre number is a "np-algo" to check in polytime if a number is a square
	if the gruop is cyclic then there is 1/2 square numbers in the group */

	printf("calculate Legendre number given seed g and the group just generated.\n");
	
	
	/*calculate legendre number in polytime. if ris=1 then a is a square, if ris=-1 a is NOT a square.
	(a,b)=a^(p-1)/2. */
	
	int i=0;
	scelta = 0;

	printf("do you want even/odd discrete log.\nDigit 1 or 2:");
	scanf("%d",&scelta);
	if(scelta==1){
		do{		
			printf("digit an even index i:");
			scanf("%d",&i);
		}while( ! is_even(i)  );
	}
	if(scelta==2){
		do{		
			printf("digit an odd index i:");
			scanf("%d",&i);
		}while(  is_even(i) );
	}
	if(scelta<1||scelta>2){ puts("error in the choice!");exit(1);}

	int y,a;

	if(scelta==1){// i is even thus 'a' is a quadratic residue mod p
		a=pow(g,i);
		y=calculate_legendre(a,p);
	}
	else{//odd
		a=pow(g,i);//i is odd thus 'a' is not a quadratic residue
		y=calculate_legendre(a,p);
	}

	if(y==1) printf("%d is a square because its legendre number is %d\n",a,y);
	else printf("%d is not a square because its legendre number is %d\n",a,y);

	//jacobi number trick 

	/*explanation: given a,b quadratic numbers, jacobi simbols are (ab|p) e (ab|q) are 1.
      given a,b non quadratic numbers, jacobi simbols are (ab|p) e (ab|q) are 1.

	  This is important to garantees secrecy of generation about the natura of the numbers.
	  
	  p.s we assume that p and q are primes number because the factorization problem is np-complete
	  and there is a P algo that solves this problem (to date).

	*/
	
	int q=0;
	p=0;//reset p

	do{
		printf("digit p and q primes numbers:");
		scanf("%d%d", &p,&q);
	}while( !  is_prime(p)&& ! is_prime(q) );


	a=0;//reset of 'a'
	int b=0;
	
	do{
		printf("digit a,b quadratic numbers for both mod p & mod q:");
		scanf("%d%d", &a,&b);
	}while( ! is_quadratic_residue(a,p) || ! is_quadratic_residue(b,p)
			||  !  is_quadratic_residue(a,q) ||  ! is_quadratic_residue(b,q) );

	
	int jacobi1[2]={0};
	calculate_jacobi(a,b,p,q, jacobi1);


	do{
		a=0;b=0;
		printf("digit a,b NON quadratic numbers for both mod p & mod q:");
		scanf("%d%d", &a,&b);
	}while(  is_quadratic_residue(a,p) || is_quadratic_residue(b,p)
			||  is_quadratic_residue(a,q) || is_quadratic_residue(b,q) );

	int jacobi2[2]={0};
	calculate_jacobi(a,b,p,q, jacobi2);

	puts("jacobi of quadratic numbers:");
	print_array(jacobi1,2);

	puts("jacobi of NON quadratic numbers:");
	print_array(jacobi2,2);

	puts("as you can see, with jacobi numbers =1 we can discriminate quadratic from non quadratic number.");
	

	free(group);


}//fine main




