# CH(x,y,z) = (x ^ y) xor (not x ^ z)
# If x is 0, the output takes whatever value z is
# If x is 1, the output takes whatever value y is


from threading import Thread

def fFunc(x,y,z):
    return (x&y) | (~x&z)

def gFunc(x,y,z):
    return (x&z) | (y&(~z))

def hFunc(x,y,z):
    return (x ^ y ^ z)

def iFunc(x,y,z):
    return (y ^ (x | (~z)))

def tripleLoop(min, max, size):
    for i in range(min,max):
        for j in range(size):
            for k in range(size):
                output[gFunc(i,j,k)] += 1

def writeToFile(output):
    with open("gFunc.txt", 'w') as file:
        file.write("G Function in md5  -  frequency of numbers from 2^16\n")
        for item in output:
            file.write("%d\n" % item)
        


cores = 8
size = 2**8
output = [0]*size
threadInput = size//cores

threads = []
for n in range(cores):
    t = Thread(target=tripleLoop, args=(threadInput*n, threadInput*(n+1), size))
    threads.append(t)
    t.start()

for index, thread in enumerate(threads):
    thread.join()

writeToFile(output)

