#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#define SIZE 2048
#define CORES 8
#define F(x,y,z) ((x & y) | (~x & z))
#define G(x,y,z) ((x & z) | (y & ~z))
#define H(x,y,z) (x ^ y ^ z)
#define I(x,y,z) ((y) ^ (x | ~z))
#define CHUNK (SIZE/CORES)



unsigned int output[SIZE] = {0};



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
    pthread_t tid[CORES];

    for (unsigned int i=0;i<CORES;i++)
    {
        pthread_create (&tid[i], NULL, threadFunc, (void *)(&i));
    }
        
    
    for (int i=0; i<CORES;i++)
        pthread_join(tid[i],NULL);
     
    FILE *out_file = fopen("output/Ffunction.txt", "w");

    if (out_file == NULL)
    {
        printf("Error\n");
    } 
    for (int i=0; i<SIZE; i++) 
    {  
        fprintf(out_file,"%d\n",output[i]);    
    }

    return 0;
}
