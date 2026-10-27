
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* funhilo(void *arg);

int main(){
    pthread_t hilo;
    pthread_create(&hilo,NULL,funhilo ,NULL);
    int val2 = 0;
    while(val2 != 10000){
    printf("%d \n",val2);
    val2++;
    }
    pthread_join(hilo,NULL);
    return 0;
}

void* funhilo(void *arg){
    int val = 10000;
    while(val != 0){
        printf("%d \n",val);
        val--;
    }
    pthread_exit(NULL);
}
