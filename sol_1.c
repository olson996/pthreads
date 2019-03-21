#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define thread_count 8
long N = 80000;
int sum;

pthread_mutex_t mutex;
int is_prime(long);
void*test(void*);

int main(){
    pthread_t tid[thread_count];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    for(int i=0; i<thread_count; i++){
        pthread_create(&tid[i], &attr, test, (void*)i);
    }
    for(int i=0; i<thread_count; i++){
        pthread_join(tid[i], NULL);
    }
    printf("sum: %d\n", sum);


        

    return 0;
}

void* test(void* rank){
    int my_rank = (int)rank;
    long index1 = (N/thread_count) * my_rank + 1;
    long index2 = (N/thread_count) * (my_rank+1);
    
    printf("index1: %ld index2: %ld\n", index1, index2);
    for(index1; index1<index2+1; index1++){
        int flag = is_prime(index1);
        if(!flag){
	    pthread_mutex_lock(&mutex);
	        sum+=1;
	    pthread_mutex_unlock(&mutex);
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

