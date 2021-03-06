#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define thread_count 8
long N = 800000;

//global array for prime # counter
int thread_sum[8];

//function prototypes
int is_prime(long);
void*thread_func(void*);

int main(){
        //local sum
    int sum;
	//initialize pthread ids
    pthread_t tid[thread_count];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    clock_t time = clock();
	//create threads
    for(int i=0; i<thread_count; i++){
        pthread_create(&tid[i], &attr, thread_func, (void*)i);
    }
    	//join threads
    for(int i=0; i<thread_count; i++){
        pthread_join(tid[i], NULL);
	sum += thread_sum[i];
    }
    time = clock()-time;
    printf("Time in ticks: %ld\n", time/1000);
    printf("sum: %d\n", sum);


        

    return 0;
}

void* thread_func(void* rank){
    int my_rank = (int)rank;
    //number indexes to check prime #s based on thread #
    long index1 = (N/thread_count) * my_rank + 1;
    long index2 = (N/thread_count) * (my_rank+1);
    
    
    //prints the index ranges for each thread
    //printf("index1: %ld index2: %ld\n", index1, index2);
    for(index1; index1<index2+1; index1++){
        int flag = is_prime(index1);
	//prime number func returns 0 if true.    (!flag) == prime
        if(!flag){
	    thread_sum[my_rank]+=1;
	}
    }

    pthread_exit(0);
    return NULL;
}


int is_prime(long n){
    if (n < 2)return 0;
    if (n == 2)return 1;
    if (n % 2 == 0)return 0;
    for (int i=3; i < n; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;

}

