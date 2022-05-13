# CH(x,y,z) = (x ^ y) xor (not x ^ z)
# If x is 0, the output takes whatever value z is
# If x is 1, the output takes whatever value y is
import time

from threading import Thread

def fFunc(x,y,z):
    return (x&y) | (~x&z)

def gFunc(x,y,z):
    return (x&z) | (y&(~z))

def hFunc(x,y,z):
    return (x ^ y ^ z)

def iFunc(x,y,z):
    return (y ^ (x | (~z)))

def tripleLoop(i,size):
    
    for j in range(size):
        for k in range(size):
            outputF[fFunc(i,j,k)] += 1
                

def writeToFile(output):
    with open("func.txt", 'a') as file:
        file.write("------\n")
        for item in output:
            file.write("%d\n" % item)
        


cores = 8
size = 2**9
outputF = [0]*size

threadInput = size//cores
st = time.perf_counter()
threads = []
for n in range(size):
    t = Thread(target=tripleLoop, args=(n, size))
    threads.append(t)
    t.start()
    
for thread in threads:
    thread.join()
et = time.perf_counter()
print(et-st)

#writeToFile(outputF)


