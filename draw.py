import numpy as np
import PIL.Image as Image

with open('newt.txt','r') as f:
    size = int(f.readline())
    M = np.zeros((size,size,3),np.uint8)
    for x in range(size):
        for y in range(size):
            l = f.readline()
            r,i = 0,0
            for c in l:
                if c == ',' or c == '\n':
                    M[x][y][i]=r
                    r=0
                    i+=1
                else:
                    r*=10
                    r+=int(c)
    img = Image.frombytes("RGB", (size,size), M)
    img.save("masterclass.png")

