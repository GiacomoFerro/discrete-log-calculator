
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



void allocate_val(int real[], int old[], int p){

	int i,index;

	for(i=0,index=0; i<p-1; i++){
		if(old[i]!=0){
			real[index]=old[i];
			index++;
		}	
	}
}

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


bool is_prime(int n){

	int i;
	for ( i = (n - 1);  i > 1; i--){
        if ( (n % i) == 0){
            return false;
        }
    }
    return true;

}

void calculate_CoGroup(int p, int group[]){

	int i=0, index=0;

	for(i=1; i<=p-1; i++){
		if(check_coprimes(i,p)){
			group[index]=i;
			index++;
		}
	}

}


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
