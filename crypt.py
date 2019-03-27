# -*- coding: utf-8 -*-
from exp_rem import exp_rem
from gcd import ex_gcd
def generate(p,q):
  n=p*q
  phi=(p-1)*(q-1)
  e=5	#e需要实现设置好,要求和phi互质
  d,t=ex_gcd(e,phi)#de=1 rem phi，需要d>0
  return (n,e),(n,d)#公钥对和私钥对

def encode(m,pubkey):
  return exp_rem(m,pubkey[1],pubkey[0])

def decode(c,selfkey):
  return exp_rem(c,selfkey[1],selfkey[0])

if __name__ == "__main__":
  p=5
  q=7
  pubkey,selfkey=generate(p,q)
  m=2
  c=encode(m,pubkey)
  d=decode(c,selfkey)
  print '密文：'
  print c
  print '明文：'
  print d
  
