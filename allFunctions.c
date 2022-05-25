#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#define SIZE 8192
#define CORES 32
#define F(x,y,z) ((x & y) | (~x & z))
#define G(x,y,z) ((x & z) | (y & ~z))
#define H(x,y,z) (x ^ y ^ z)
#define I(x,y,z) ((y) ^ (x | ~z))
#define CHUNK (SIZE/CORES)




unsigned int output[SIZE] = {0};
unsigned int outputG[SIZE] = {0};
unsigned int outputH[SIZE] = {0};
unsigned int outputI[SIZE] = {0};



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

void* threadFunctionG(void *index)
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
                unsigned int idx = G(min,j,k);
                outputG[idx] += 1;
            }
        }
    }
    pthread_exit(NULL);
    return NULL;    
}
void* threadFunctionH(void *index)
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
                unsigned int idx = H(min,j,k);
                outputH[idx] += 1;
            }
        }
    }
    pthread_exit(NULL);
    return NULL;    
}

void* threadFunctionI(void *index)
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
                unsigned int idx = I(min,j,k);
                outputI[~idx] += 1;
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
    
    FILE *out_file = fopen("outputF.txt", "w");

    if (out_file == NULL)
    {
        printf("Error\n");
    } 
    for (int i=0; i<SIZE; i++) 
    {  
        fprintf(out_file,"%d\n",output[i]);    
    } 

    for (unsigned int i=0;i<CORES;i++)
    {
        pthread_create (&tid[i], NULL, threadFunctionG, (void *)(&i));
    }
        
    
    for (int i=0; i<CORES;i++)
        pthread_join(tid[i],NULL);

    FILE *out_fileG = fopen("outputG.txt", "w");

    if (out_fileG == NULL)
    {
        printf("Error\n");
    } 
    for (int i=0; i<SIZE; i++) 
    {  
        fprintf(out_fileG,"%d\n",outputG[i]);    
    } 

    for (unsigned int i=0;i<CORES;i++)
    {
        pthread_create (&tid[i], NULL, threadFunctionH, (void *)(&i));
    }
        
    
    for (int i=0; i<CORES;i++)
        pthread_join(tid[i],NULL);

    FILE *out_fileH = fopen("outputH.txt", "w");

    if (out_fileH == NULL)
    {
        printf("Error\n");
    } 
    for (int i=0; i<SIZE; i++) 
    {  
        fprintf(out_fileH,"%d\n",outputH[i]);    
    } 

    for (unsigned int i=0;i<CORES;i++)
    {
        pthread_create (&tid[i], NULL, threadFunctionI, (void *)(&i));
    }
        
    
    for (int i=0; i<CORES;i++)
        pthread_join(tid[i],NULL);
    
    FILE *out_fileI = fopen("outputI.txt", "w");

    if (out_fileI == NULL)
    {
        printf("Error\n");
    } 
    for (int i=0; i<SIZE; i++) 
    {  
        fprintf(out_fileI,"%d\n",outputI[i]);    
    } 
    
    end = clock();
    long t = (end - start)/10;
    int i = 0;
     
    // for I function:
    //for (; i<SIZE; i++) { printf("%d - %d\n", (~i+((int)pow(2.0,32.0))), output[i]); }
    // for F,G,H functions: 
    //for (; i<SIZE; i++) { printf("%d - %d\n", i, output[i]); }

    
    // FILE *out_file = fopen("Ffunction.txt", "w");

    // if (out_file == NULL)
    // {
    //     printf("Error\n");
    // } 
    // for (; i<SIZE; i++) 
    // {  
    //     fprintf(out_file,"%d\n",output[i]);    
    // }  
    printf("Time for SIZE(%d), CORES(%d), CHUNK(%d) -> %ld \xC2\xB5s\n", SIZE, CORES, CHUNK, t);

    
    return 0;
}
