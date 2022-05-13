#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#define SIZE 1024
unsigned long* output=NULL;
#define F(x,y,z) ((x & y) | (~x & z))
#define G(x,y,z) ((x & z) | (y & ~z))
#define H(x,y,z) (x^y^z)
#define I(x,y,z) (y^(x|~z))




void* threadFunc(void *index)
{
    unsigned int i = (unsigned int)index; 
    for (unsigned int j=0;j<SIZE;j++){
        for (unsigned int k=0;k<SIZE;k++){
            unsigned int idx = I(i,j,k);
            output[idx] = output[idx] + 1;
        }
    }
    pthread_exit(NULL);
    return NULL;    
}

int main() 
{

    unsigned int outSize = SIZE;
    output = calloc(SIZE+1, sizeof *output);
    
    time_t start,end;
    start = clock();
    
    pthread_t t1;
    for (unsigned int i=0;i<SIZE;i++)
    {
        pthread_create (&t1, NULL, threadFunc, (void *)i);
    }

    pthread_join(t1,NULL);

    end = clock();
    long t = end - start;    
    printf("%ld\n", t);

    //printf("%d %d %d %d\n",I(1,2,3),I(2,3,1),I(3,1,2),I(2,1,3));

    //free(output);
    //output = NULL;
    return 0;
}