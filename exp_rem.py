# -*- coding: utf-8 -*-
def exp_rem(base, exponent, n):
  bin_array=bin(exponent)[2:][::-1]
  base_array=[]#存放基的^1,^2,^4 %n的数值
  base_array.append(base)
  temp=base
  for x in range(len(bin_array)):
    temp=(temp*temp)%n
    base_array.append(temp)
  s=multi(base_array,bin_array)
  return s%n

def multi(base_array,bin_array):#向量点乘
  result=1  
  for x in range(len(bin_array)):
    a=base_array[x]
    if not int(bin_array[x]):#必须把分量转成int才能正确运算
      continue		
    result *=base_array[x]
  return result
