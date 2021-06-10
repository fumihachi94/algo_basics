import lzma, sys, random, string
from statistics import mean
import matplotlib.pyplot as plt

def randstr(n):
   randlst = [random.choice(string.ascii_letters + string.digits) for i in range(n)]
   return ''.join(randlst)

def savein(savename, data):
    f = open(savename+'.txt', 'wb')
    f.write(data.encode())
    f.close()

sz_bf_test = []
cmp_r_mean = []

for n in range(10,21):
    sz_bf = []
    sz_af = []
    cmp_r = []
    for i in range(10):
        # s = randstr(int(sys.argv[1]))
        # savein('in', s)
        s = randstr(2**n)
        t = lzma.compress(s.encode())
        sz_bf = len(s)
        sz_af.append(len(t))
        cmp_r.append(((len(s) - len(t))/len(s)*100))
    sz_bf_test.append(sz_bf)
    cmp_r_mean.append(mean(cmp_r))
    print("lzma 圧縮前: " + str(round(sz_bf/1000)) + "KB, 圧縮後(平均): " + str(round(mean(sz_af)/1000)) + "KB, 圧縮率(平均): " + str(round(mean(cmp_r))) + "%")

plt.semilogx(sz_bf_test, cmp_r_mean)
plt.grid()
plt.show()