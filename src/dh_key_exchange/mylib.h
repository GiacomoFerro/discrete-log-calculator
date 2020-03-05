#define MAXUSER 100

struct principal{
	
	int public_key;
	int private_key;
	int symmetric_key;
	
};

struct directory{

	//list of principal's public keys. max 100 principals
	int P[MAXUSER];
	
};

typedef struct principal principal;
typedef struct directory directory;

//list of prototypes
bool is_prime(int);
void print_array(int a[],int dim);
int calculate_generator(int group[], int p);
bool is_contained(int num, int a[], int dim);
void update_principals(principal pr[], int ,int, int group[],int);
directory update_dir(principal *, directory, int pos);
int generate_Kab(principal pr[] , directory dir, int prime, int initiator, int responder);

//begin of functions

/*
insert public key of the principal in the directory 'dir'
*/

directory update_dir(principal pr[], directory dir, int pos){
 	//insert public key of the principal
	dir.P[pos]=pr[pos].public_key;
	return dir;
   
}

/*generate KAB given:
 	prime = prime number
 	indexInit = index of principal private key in list of principal pr
	indexResp = index of prinicpal public key in dir
	pr = list of principal private key
	dir = directory of principal public key
*/

int generate_Kab( principal pr[],  directory dir, int prime, int indexInit, int indexResp){
	
	int public_b=dir.P[indexResp];
	int private_a=pr[indexInit].private_key;

	int Kab = (int) (pow(public_b, private_a)+0.5 ) % prime;
	pr[indexInit].symmetric_key=Kab;

	return Kab;

}

/*
	update of public anche private key for a principal of index 'pos' in the list
*/

void update_principals(principal pr[], int seed , int prime, int group[],int pos){
	
 	int secret=rand()%prime; // position 0 to p-1
	pr[pos].public_key=(int) pow(seed,group[secret]);
	pr[pos].private_key=group[secret];
	pr[pos].symmetric_key=0;
	return;
	
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


