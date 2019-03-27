# -*- coding: utf-8 -*-
def gcd(a,b):
  if b==0:
    return a
  else:
    return gcd(b,a%b)

def ex_gcd(a,b):
#返回ax+by=1的解，把a，b辗转一次的结果带回方程即知算法，需要a,b互质，没检查;
  if b == 0:
    return 1,0
  else:
    x1,y1=ex_gcd(b,a%b)
    x=y1
    y=x1-a/b*y1
    return x,y
    
