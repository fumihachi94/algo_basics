import math
import time

def calc_distance(a,b):
    return math.sqrt(a**2 + b**2) 

class euclidean_distance(object):
    def __init__(self, a, b):
        self.a = a
        self.b = b

    @staticmethod
    def calc_distance(a,b):
        return math.sqrt(a**2 +b**2) 

    def calc_wo_staticmethod(self):
        return math.sqrt(self.a**2 +self.b**2) 
    
    def calc_w_staticmethod(self):
        return self.calc_distance(self.a, self.b)

class manhattan_distance(euclidean_distance):
    
    @staticmethod
    def calc_distance(a,b):
        return a + b 

a,b = 2, 2
ed = euclidean_distance(a,b)
print(ed.calc_w_staticmethod())
print(ed.calc_wo_staticmethod())
print(calc_distance(a,b))

md = manhattan_distance(a,b)
print(md.calc_w_staticmethod())

# start = time.time()
# for i in range(1000000):
#     ed.calc_w_staticmethod()
# elapsed_time = time.time() - start
# print ("elapsed_time:{0}".format(elapsed_time) + "[sec]")

# start = time.time()
# for i in range(1000000):
#     ed.calc_wo_staticmethod()
# elapsed_time = time.time() - start
# print ("elapsed_time:{0}".format(elapsed_time) + "[sec]")

# start = time.time()
# for i in range(1000000):
#     calc_distance(a,b)
# elapsed_time = time.time() - start
# print ("elapsed_time:{0}".format(elapsed_time) + "[sec]")