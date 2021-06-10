import lzma, sys, random, string
from statistics import mean
import matplotlib.pyplot as plt

def randstr(n):
   randlst = [random.choice(string.ascii_letters + string.digits) for i in range(n)]
   return ''.join(randlst)

def savein(savename, data):
    f = open(savename+'.bin', 'wb')
    f.write(b.encode())
    f.close()

sz_bf_test = []
cmp_r_mean = []

for n in range(10,21):
    sz_bf = []
    sz_af = []
    cmp_r = []
    for i in range(10):
        # s = randstr(int(sys.argv[1]))
        s = randstr(2**n)
        b = b''.join(format(ord(s), 'b') for  s in s)
        savein('in', b)
        t = lzma.compress(b.encode())
        savein('out', t)
        sz_bf = len(b.encode())
        sz_af.append(len(t))
        cmp_r.append(((len(b.encode()) - len(t))/len(b.encode())*100))
    sz_bf_test.append(sz_bf)
    cmp_r_mean.append(mean(cmp_r))
    print("lzma 圧縮前: " + str(round(sz_bf/8000)) + "KB, 圧縮後(平均): " + str(round(mean(sz_af)/8000)) + "KB, 圧縮率(平均): " + str(round(mean(cmp_r))) + "%")

plt.semilogx(sz_bf_test, cmp_r_mean)
plt.grid()
plt.show()