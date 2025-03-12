#!/usr/bin/env python
# coding: utf-8

# **Task#2**

# In[ ]:


num=56
flt=45.90
str1='Hello World'
cond=True
k=[45,78,'abc']
car = {
  "brand": "Ford",
  "model": "Mustang",
  "year": 1964
}
print(type(num))
print(type(flt))
print(type(str1))
print(type(cond))
print(type(car))
print(type(k))


# **Task#3**

# In[ ]:


a1=56
a2=67.90
a3='78'
a4=float(a1)
a5=int(a2)
a6=int(a3)
print(a1,type(a1))
print(a2,type(a2))
print(a3,type(a3))
print(a4,type(a4))
print(a5,type(a5))
print(a6,type(a6))


# **Task#4**

# In[ ]:


a1=int(input("Enter first Number: " ))
a2=int(input("Enter second Number: " ))
sum=a1+a2
diff=a1-a2
mul=a1*a2
md=a1%a2
ex=a1**a2
div=a1/a2
fdiv=a1//a2
print(sum)
print(diff)
print(mul)
print(md)
print(ex)
print(div)
print(fdiv)


# 

# **Task#5**

# In[ ]:


print(True and False)
print(True or False)
print(not True)


# **Task#6**

# In[ ]:


k=int(input("Enter a Number: "))
if(k%2==0):
  print(f"Number {k} is Even")
elif(k%2!=0):
  print(f"Number {k} is Odd")
else:
  print(f"Number {k} is Invalid Entry")


# **Task#7**

# In[ ]:


k1=int(input("Enter first Number: "))
k2=int(input("Enter second Number: "))
k3=int(input("Enter third Number: "))
if(k1>k2 and k1>k3):
  print(f"{k1} is Greatest")
if(k2>k1 and k2>k3):
  print(f"{k2} is Greatest")
if(k3>k2 and k3>k1):
  print(f"{k3} is Greatest")


# **Task#8**

# In[ ]:


num=int(input("Enter Your Age: "))
if(num>=18 and num<150):
  print("You are eligible to Vote")
else:
  print("Not Eligibe")


# **Task#9**

# In[ ]:


num=int(input("Enter Year: "))
if (num%4==0 and num%100!=0):
  print(f"{num} is Leap")
else:
  print(f"{num} is not Leap")


# **Task#10**

# In[ ]:


str1=input("Enter the Day: ")
if(str1=='Sunday' or str1=='sunday' or str1=='Saturday' or str1=='saturday'):
  print("It is Weekend")
else:
  print("It is Not Weekend")

