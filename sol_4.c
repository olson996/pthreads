#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define thread_count 8
long N = 800000;


//scalar global sum
int sum;

//initialize mutex 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//function prototypes
int is_prime(long);
void*thread_func(void*);

int main(){
	//initialize pthread ids
    pthread_t tid[thread_count];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
	//create threads
    clock_t time = clock();
    for(int i=0; i<thread_count; i++){
        pthread_create(&tid[i], &attr, thread_func, (void*)i);
    }
    	//join threads
    for(int i=0; i<thread_count; i++){
        pthread_join(tid[i], NULL);
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

    int local_sum=0;
    
    
    //prints index ranges for each thread
    //printf("index1: %ld index2: %ld\n", index1, index2);
    for(index1; index1<index2+1; index1++){
        int flag = is_prime(index1);
	//prime number func returns 0 if true.    (!flag) == prime
        if(!flag){
	    local_sum+=1;
	}
    }
    //lock while updating global scalar sum
    pthread_mutex_lock(&mutex);
	sum += local_sum;
    pthread_mutex_unlock(&mutex);

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

