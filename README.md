
# crypto-analysis

This project was my undertaking to create output tables from the first 2^16 numbers, run through the F G H and I functions from MD5.


## Tech Stack

Python 3.9.1

C using the -std=c99 and -pthread flags for compiling with gcc

\> gcc -std=c99 -pthread allFunctions.c -o allFunctions
\> gcc -std=c99 -pthread thf.c -o funcf
\> gcc -std=c99 -pthread thg.c -o funcg
\> gcc -std=c99 -pthread thh.c -o funch
\> gcc -std=c99 -pthread thi.c -o funci


Make the sbatch_script executable and run, with: ./sbatch_script




