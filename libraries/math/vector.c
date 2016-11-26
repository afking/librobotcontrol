/*******************************************************************************
* vector.c
*
* James Strawson & Matt Atlas 2016
*******************************************************************************/

#include "../roboticscape.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h> // for memset

#define PI (float)M_PI

/*******************************************************************************
* vector_t create_vector(int n)
*
* 
*******************************************************************************/
vector_t create_vector(int n){
	vector_t v;
	if(n<1){
		printf("error creating vector, n must be >=1");
		return v;
	}
	v.len = n;
	v.data = (float*)calloc(n, sizeof(float));
	v.initialized = 1;
	return v;
}

/*******************************************************************************
* void destroy_vector(vector_t* v)
*
* 
*******************************************************************************/
void destroy_vector(vector_t* v){
	if(v==NULL){
		printf("ERROR: Can't destroy vector, NULL pointer detected\n");
		return;
	}
	if(v->initialized==1){
		free(v->data);
	}
	memset(v, 0, sizeof(vector_t));
	return;
}

/*******************************************************************************
* vector_t empty_vector()
*
* 
*******************************************************************************/
vector_t empty_vector(){
	vector_t out;
	memset(&out, 0, sizeof(vector_t));
	return out;
}


/*******************************************************************************
* vector_t duplicate_vector(vector_t v)
*
* 
*******************************************************************************/
vector_t duplicate_vector(vector_t v){
	int i;
	vector_t out = empty_vector();
	if(!v.initialized){
		printf("ERROR: vector not initialized yet\n");
		return out;
	}
	out = create_vector(v.len);
	for(i=0;i<v.len;i++){
		out.data[i] = v.data[i];
	}
	return out;
}

/*******************************************************************************
* vector_t create_random_vector(int len)
*
* 
*******************************************************************************/
vector_t create_random_vector(int len){
	int i;
	vector_t v = empty_vector();
	if(len<1){
		printf("error creating vector, len must be >=1");
		return v;
	}
	v = create_vector(len);
	for(i=0;i<len;i++){
		v.data[i]=get_random_float();
	}
	return v;
}

/*******************************************************************************
* vector_t create_vector_of_ones(int len)
*
* 
*******************************************************************************/
vector_t create_vector_of_ones(int len){
	int i;
	vector_t v = empty_vector();
	if(len<1){
		printf("error creating vector, len must be >=1");
		return v;
	}
	v = create_vector(len);
	for(i=0;i<len;i++){
		v.data[i]=1;
	}
	return v;
}

/*******************************************************************************
* vector_t create_vector_from_array(int len, float* array)
*
* 
*******************************************************************************/
vector_t create_vector_from_array(int len, float* array){
	vector_t v = empty_vector();
	if(len<1){
		printf("ERROR: len must be greater than 0\n");
		return v;
	}
	v = create_vector(len);
	int i;
	for(i=0;i<len;i++){
		v.data[i] = array[i];
	}
	return v;
}

/*******************************************************************************
* int set_vector_entry(vector_t* v, int pos, float val)
*
* 
*******************************************************************************/
int set_vector_entry(vector_t* v, int pos, float val){
	if(v==NULL){
		printf("ERROR: v is null pointer\n");
		return -1;
	}
	if(!v->initialized){
		printf("ERROR: v not initialized yet\n");
		return -1;
	}
	if(pos<0 || pos>=v->len){
		printf("ERROR: pos out of bounds\n");
		return -1;
	}
	v->data[pos] = val;
	return 0;
}

/*******************************************************************************
* float get_vector_entry(vector_t v, int pos)
*
* 
*******************************************************************************/
float get_vector_entry(vector_t v, int pos){
	if(!v.initialized){
		printf("ERROR: v not initialized yet\n");
		return -1;
	}
	if(pos<0 || pos>=v.len){
		printf("ERROR: pos out of bounds\n");
		return -1;
	}
	return v.data[pos];
}

/*******************************************************************************
* void print_vector(vector_t v)
*
* 
*******************************************************************************/
void print_vector(vector_t v){
	int i;
	if(!v.initialized){
		printf("ERROR: vector not initialized yet\n");
		return;
	}
	for(i=0;i<v.len;i++){
		printf("%7.3f  ",v.data[i]);
	}
	printf("\n");
	return;
}

/*******************************************************************************
* void print_vector_sci_notation(vector_t v)
*
* 
*******************************************************************************/
void print_vector_sci_notation(vector_t v){
	int i;
	if(!v.initialized){
		printf("ERROR: vector not initialized yet\n");
		return;
	}
	for(i=0;i<v.len;i++){
		printf("%.4e  ",v.data[i]);
	}
	printf("\n");
	return;
}


/*******************************************************************************
* int vector_times_scalar(vector_t* v, float s)
*
* 
*******************************************************************************/
int vector_times_scalar(vector_t* v, float s){
	int i;
	if(!v->initialized){
		printf("ERROR: vector not initialized yet\n");
		return -1;
	}
	for(i=0;i<(v->len);i++){	
		v->data[i] = s*v->data[i];
	}
	return 0;
}




/*******************************************************************************
* float vector_norm(vector_t v)
*
* Returns the L2-Norm of a vector. This is also commonly known as the vector
* magnitude or length.
*******************************************************************************/
float vector_norm(vector_t v){
	float out = 0;
	int i;
	if(!v.initialized){
		printf("ERROR: vector not initialized yet\n");
		return -1;
	}
	for(i=0;i<v.len;i++){
		out = out + v.data[i]*v.data[i];
	}
	return sqrt(out);
}

/*******************************************************************************
* float standard_deviation(vector_t v)
*
* 
*******************************************************************************/
float standard_deviation(vector_t v){
	int i;
	float mean, mean_sqr;
	if(v.initialized != 1){
		printf("ERROR: vector not initialied\n");
		return -1;
	}
	if(v.len == 1) return 0;

	// calculate mean
	mean = 0;
	for(i=0;i<v.len;i++){
		mean += v.data[i];
	}
	mean = mean / v.len;
	// calculate mean square
	mean_sqr = 0;
	for(i=0;i<v.len;i++){
		mean_sqr += (v.data[i]-mean)*(v.data[i]-mean);
	}
	return sqrt(mean_sqr/v.len);
}

/*******************************************************************************
* float vector_mean(vector_t v)
*
* 
*******************************************************************************/
float vector_mean(vector_t v){
	int i;
	float sum = 0;

	if(v.initialized != 1){
		printf("ERROR: vector not initialied\n");
		return -1;
	}
	// calculate mean
	for(i=0;i<v.len;i++){
		sum += v.data[i];
	}
	return sum/ v.len;
}


/*******************************************************************************
* vector_t poly_conv(vector_t v1, vector_t v2)
*
* 
*******************************************************************************/
vector_t poly_conv(vector_t v1, vector_t v2){
	vector_t out = empty_vector();
	int m,n,i,j,k;
	if(!v1.initialized || !v2.initialized){
		printf("ERROR: vector not initialized yet\n");
		return out;
	}
	m = v1.len;
	n = v2.len;
	k = m+n-1;
	out = create_vector(k);
	
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			out.data[i+j] += v1.data[i] * v2.data[j];
		}
	}
	return out;	
}

/*******************************************************************************
* vector_t poly_power(vector_t v, int N)
*
* 
*******************************************************************************/
vector_t poly_power(vector_t v, int N){
	vector_t out = empty_vector();
	int i;
	if(!v.initialized){
		printf("ERROR: vector not initialized yet\n");
		return out;
	}
	if(N < 0){
		printf("ERROR: no negative exponents\n");
		return out;
	}
	if(N == 0){
		out = create_vector(1);
		out.data[0] = 1;
		return out;
	}	
	out = duplicate_vector(v);
	if(N == 1){
		return out;
	}
	vector_t temp;
	for(i=2;i<=N;i++){
		temp = poly_conv(out, v);
		out  = duplicate_vector(temp);
		destroy_vector(&temp);
	}
	return out;
}

/*******************************************************************************
* vector_t poly_add(vector_t a, vector_t b)
*
* add two polynomials with right justification
*******************************************************************************/
vector_t poly_add(vector_t a, vector_t b){
	vector_t out = empty_vector();
	int i, diff;

	if(!a.initialized){
		printf("ERROR: vector a not initialized yet\n");
		return out;
	}
	if(!b.initialized){
		printf("ERROR: vector b not initialized yet\n");
		return out;
	}

	// fill in out vector with longest input vector
	// if b is longer, replace reference a with contents of b
	if(a.len>b.len){
		out = duplicate_vector(a);
	}
	else{
		out = duplicate_vector(b);
		b=a;
	}

	// now the 'b' variable contains the shorter vector
	// itterate from the left
	diff = out.len - b.len;
	for(i=diff; i<out.len; i++)	out.data[i] += b.data[i-diff];

	return out;
}

/*******************************************************************************
* vector_t poly_diff(vector_t a, int d)
*
* calculate the dth derivative of the polynomial a
*******************************************************************************/
vector_t poly_diff(vector_t a, int d){
	vector_t out = empty_vector();
	int i, order;

	if(!a.initialized){
		printf("ERROR: vector a not initialized yet\n");
		return out;
	}
	if(d<=0){
		printf("ERROR: d must be greater than or qual to 0");
	}
	// 0th derivative is easy, return the input
	if(d==0){
		out = duplicate_vector(a);
		return out;
	}
	// do one derivative
	out = create_vector(a.len-1);
	order = a.len-1;
	for(i=0; i<(a.len-1); i++){
		out.data[i] = a.data[i] * (order-i);
	}
	// if 1st derivative was requested, return now
	if(d==1) return out;

	// for higher derivatives, call recursively
	vector_t out_r = poly_diff(out, d-1);
	destroy_vector(&out);
	return out_r;
}

/*******************************************************************************
* float poly_div(vector_t num, vector_t den, vector_t* remainder)
*
* divide denominator into numerator. Remainder is put in the user's remainder
* vector passed by pointer.
*******************************************************************************/
float poly_div(vector_t num, vector_t den, vector_t* remainder){

	printf("poly_div not implemented yet, sorry!!\n");
	return -1;
}


/*******************************************************************************
* vector_t poly_butter(int N, float wc)
*
* Return vector of coefficients for continuous-time Butterworth polynomial
* of order N and cutoff wc (rad/s)
*******************************************************************************/
vector_t poly_butter(int N, float wc){
	int i;
	vector_t filter = empty_vector();
	vector_t P2, P3, temp;
	if(N < 1){
		printf("ERROR: order must be > 1\n");
		return filter;
	}
	if(N > 10){
		printf("ERROR: order must be <= 10 to prevent overflow\n");
		return filter;
	}
	filter = create_vector(1);
	filter.data[0] = 1;
	P2 = create_vector(2);
	P3 = create_vector(3);
	if(N%2 == 0){
		for(i=1;i<=N/2;i++){
			P3.data[0] = 1/(wc*wc);
			P3.data[1] = -2*cos((2*i + N - 1)*PI/(2*N))/wc;
			P3.data[2] = 1;
			temp = duplicate_vector(filter);
			filter = poly_conv(temp,P3);
			destroy_vector(&temp);
		}
	}
	if(N%2 == 1){	
		P2.data[0] = 1/wc;
		P2.data[1] = 1;
		temp = duplicate_vector(filter);
		filter = poly_conv(temp,P2);
		destroy_vector(&temp);
		for(i=1;i<=(N-1)/2;i++){
			P3.data[0] = 1/(wc*wc);
			P3.data[1] = -2*cos((2*i + N - 1)*PI/(2*N))/wc;
			P3.data[2] = 1;
			temp = duplicate_vector(filter);
			filter = poly_conv(temp,P3);
			destroy_vector(&temp);
		}
	}
	destroy_vector(&P2);
	destroy_vector(&P3);
	return filter;
}

