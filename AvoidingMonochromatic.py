import numpy as math
import copy
import time 
# import matplotlib.pyplot as plt
# from matplotlib import colors
n=11

c=0
startTime = time.time()


#create a random coloring
coloring =[[]]
for z in range(1, n+1):
    coloring.append(math.random.choice([0, 1], size=n, p=[0, 1]).tolist())
coloring.remove([])
print(coloring)
permrow = math.random.permutation(n)
permcol = math.random.permutation(n)
print(permcol)
print(permrow)
def numofMAP(coloring):
    count = 0
    for x1 in range(0, n):
        for x2 in range(0, n):
            if ((x1+x2) % 2) == 0:
                for y1 in range (0, n):
                    for y2 in range(0,n):
                        if ((y1+y2) % 2) == 0:
                            if (coloring[x1][y1] == coloring[int((x1+x2)/2)][int((y1+y2)/2)] and coloring[x2][y2] == coloring[int((x1+x2)/2)][int((y1+y2)/2)]):
                                count = count + 1
    return count

def swapping(coloring, wasswaped):
    if(c < 2):
        print(numofMAP(coloring))
    for x in range (0,n):
        numofColoring = numofMAP(coloring)
        for y in range (0,n):
            isone = False
            if (coloring[permrow[x]][permcol[y]]==0):
                coloring[permrow[x]][permcol[y]] = 1
            else:
               coloring[permrow[x]][permcol[y]] = 0
               isone = True
            numOfNewColoring = numofMAP(coloring)
            if  numOfNewColoring < numofColoring:
                wasswaped = True
                numofColoring = numOfNewColoring
            elif(isone):
                coloring[permrow[x]][permcol[y]] = 1
            else:
                coloring[permrow[x]][permcol[y]] = 0
    if(c < 2):
        print(numofMAP(coloring))
    return coloring, wasswaped

wasswaped = True

while wasswaped:
    wasswaped=False
    coloring, wasswaped = swapping(coloring, wasswaped)
    c = c+1

print(coloring)
print(str(startTime - time.time()))
print(numofMAP(coloring))
