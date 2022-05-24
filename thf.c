#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#define SIZE 4096
#define CORES 8
#define F(x,y,z) ((x & y) | (~x & z))
#define G(x,y,z) ((x & z) | (y & ~z))
#define H(x,y,z) (x ^ y ^ z)
#define I(x,y,z) ((y) ^ (x | ~z))
#define CHUNK (SIZE/CORES)

unsigned int iFunc(unsigned int x, unsigned int y, unsigned int z){ return (y^(x|(~z))); }


unsigned int output[0xfffff] = {0};



void* threadFunc(void *index)
{
    unsigned int *i = (unsigned int *)(index);    
    unsigned int min,max;
    min = ((*i)-1) * CHUNK;
    max = min + CHUNK;
    
    
    for(;min < max;min++)
    {
             
        for (unsigned int j=0;j<SIZE;j++)
        {
            
            for (unsigned int k=0;k<SIZE;k++)
            {
                unsigned int idx = F(min,j,k);
                output[idx] += 1;
            }
        }
    }
    pthread_exit(NULL);
    return NULL;    
}

int main() 
{    
    time_t start,end;
    start = clock();
    
    pthread_t tid[CORES];

    for (unsigned int i=0;i<CORES;i++)
    {
        pthread_create (&tid[i], NULL, threadFunc, (void *)(&i));
    }
        
    
    for (int i=0; i<CORES;i++)
        pthread_join(tid[i],NULL);
    
    end = clock();
    long t = (end - start)/10;
    int i = 0;
     
    // for I function:
    //for (; i<SIZE; i++) { printf("%d - %d\n", (~i+((int)pow(2.0,32.0))), output[i]); }
    // for F,G,H functions: 
    //for (; i<SIZE; i++) { printf("%d - %d\n", i, output[i]); } 
       
    printf("Time for SIZE(%d), CORES(%d), CHUNK(%d) -> %ld \xC2\xB5s\n", SIZE, CORES, CHUNK, t);

    
    return 0;
}
