
//list of prototypes

bool is_prime(int);
void calculate_CoGroup(int, int group[]);
bool check_coprimes(int, int);
void print_array(int a[],int dim);
int optimize(int group[],int p);
void allocate_val(int a[], int b[], int dim);
int calculate_generator(int group[], int p);
bool is_contained(int num, int a[], int dim);
void calculate_discreteLog(int g, int group[], int p, int ris[]);
int calculate_legendre(int,int);
bool is_even(int);
bool is_quadratic_residue(int q,int p);
void calculate_jacobi(int a, int b, int p, int q, int jac[]);


//begin of functions


void calculate_jacobi(int a, int b, int p, int q, int jac[]){

	int val1,val2,val3,val4;

	val1=calculate_legendre(a,p);
	val2=calculate_legendre(b,p);
	val3=calculate_legendre(a,q);
	val4=calculate_legendre(b,q);

	/*
	printf("(%d|%d)=%d\n",a,p,val1);
	printf("(%d|%d)=%d\n",b,p,val2);
	printf("(%d|%d)=%d\n",a,q,val3);
	printf("(%d|%d)=%d\n",b,q,val4);
	*/

	jac[0]=val1*val2;
	jac[1]=val3*val4;

}




int calculate_legendre(int a, int p){

	// number is square mod p iff his legendre number is 1

	if(a==0) return 0;

	if( is_quadratic_residue(a,p) ){
		return 1;
	}

	if( ! is_quadratic_residue(a,p) ){
		return -1;
	}

}


bool is_quadratic_residue(int q, int p){
 
	int x;
	for(x=1; x<p; x++){		
		if((x*x) %p == q%p ) return true;
	}
	return false; 

}


/*allocate values of the group*/
void allocate_val(int real[], int old[], int p){

	int i,index;

	for(i=0,index=0; i<p-1; i++){
		if(old[i]!=0){
			real[index]=old[i];
			index++;
		}	
	}
}
/*remove zero values from a group*/
int optimize(int group[], int p){
	
	int i,dim;

	for(i=0,dim=0; i<p-1; i++){
		if(group[i]!=0){
			dim++;
		}
	}
	return dim;


}


void print_array(int a[], int dim){

	int i;

	printf("[");
	for(i=0; i<dim; i++){
		printf(" %d ",a[i]);
	}
	printf("]\n");

}

/*
return true if n is prime number
*/
bool is_prime(int n){

	int i;
	for ( i = (n - 1);  i > 1; i--){
        if ( (n % i) == 0){
            return false;
        }
    }
    return true;

}

/*calculate a coprimes group*/
void calculate_CoGroup(int p, int group[]){

	int i=0, index=0;

	for(i=1; i<=p-1; i++){
		if(check_coprimes(i,p)){
			group[index]=i;
			index++;
		}
	}

}

/* check if two numbers are coprime*/
bool check_coprimes(int a, int b){
	
	int min = a;
    if(b<a) min = b;

    for(int i=2; i<min; i++){
        if(a%i==0 && b%i==0){
           	return false;
        }
    }
	return true;

}

/* given a cyclic group and prime number p, calculate its generator*/
int calculate_generator(int group[], int p){

	int i,j;
	int g,count=0;
	
	for(i=1; i<p-1; i++){//i=1 to remove number one!
		g=group[i];
		count=0;
		
		//printf("trying g=%d\n",g);	
	
		for(j=1; j<=p-1; j++){
			if( is_contained( (int)(pow(g,j)+0.5)%p , group, p ) ){
				//printf("%d\n", (int)(pow(g,j)+0.5)%p );
				count++;
			}
			if((int)(pow(g,j)+0.5)%p == 1) { break; }
		}

		if( count==(p-1) ){ return g;}
	}
	return 0;

}

bool is_contained(int num, int a[], int dim){

	int i;
	
	for(i=0; i<dim; i++){
		if(num==a[i]){
			return true;
		}
	}
	return false;
}

/* calculate discrete log given a seed of the cyclic group*/
void calculate_discreteLog(int g, int group[], int p, int ris[]){

	//random discrete log
	srand(time(NULL));
	
	int i = rand()%p;
	
	int a = (int) ( pow( g, group[i] ) + 0.5 );

	ris[0]=a;
	ris[1]=i;

	return;

}

bool is_even(int i){
	
	return i%2==0;	

}

