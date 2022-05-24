#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#define SIZE 8
#define CORES 1
#define F(x,y,z) ((x & y) | (~x & z))
#define G(x,y,z) ((x & z) | (y & ~z))
#define H(x,y,z) (x ^ y ^ z)
#define I(x,y,z) ((y) ^ (x | ~z))
#define CHUNK (SIZE/CORES)

unsigned int iFunc(unsigned int x, unsigned int y, unsigned int z){ return (y^(x|(~z))); }


unsigned int output[0xfffff] = {0};



void* threadFunc(void *index)
{
    printf("threadFunc\n");
    unsigned int *i = (unsigned int *)(index);
    unsigned int min,max;
    min = (*i) * CHUNK;
    max = min + CHUNK;

    for(;min < max;min++)
    {     
        for (unsigned int j=0;j<SIZE;j++)
        {
            for (unsigned int k=0;k<SIZE;k++)
            {
                unsigned int idx = iFunc(min,j,k);
                printf("i: %d, j: %d, k: %d, idx: %d\n", *i,j,k, idx);
                //output[idx] += 1;
            }
        }
    }
    pthread_exit(NULL);
    return NULL;    
}

int main() 
{   
    printf("beginning\n"); 
    time_t start,end;
    start = clock();
    
    pthread_t tid[CORES];

    for (int i=0;i<CORES;i++)
    {
        printf("threadloop\n");
        pthread_create (&tid[i], NULL, threadFunc, (void *)(&i));
    }
        
    
    for (int i=0; i<CORES;i++)
        pthread_join(tid[i],NULL);

    end = clock();
    long t = end - start; 

    //for (int i=0; i<SIZE; i++) { printf("%d - %d\n", i, output[i]); } 
       
    printf("Time for SIZE(%d), CORES(%d), CHUNK(%d) -> %ld \xC2\xB5s\n", SIZE, CORES, CHUNK, t);

    
    return 0;
}
