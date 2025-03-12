#!/usr/bin/env python
# coding: utf-8

# Question_1

# In[9]:


def func1(lst):
    if(len(lst)<3):
        print("The List has Less than 3 Objects")
        lst=lst.clear()
        return lst
    else:
        new_lst=lst[:3]
        new_lst=new_lst+lst[-3:]
        return new_lst
        
      
orignal_lst=[1,2,3,4,5,6,7,8,9]  
print("Orignal List:",orignal_lst) 
print("New Modified list is:", func1(orignal_lst))


# Question_2

# In[10]:


def func2(target,lst):
    size=len(lst)
    i=0
    while(i<size):
        if(lst[i]==target):
            return i
        i=i+1
    return -1    

lst=["apple","mango","banana","grapes","oranges"]
print("Orignal List: ", lst)
target = input("Enter Target you want to find index of: ") 
index = func2(target,lst)
print("Target found at index:", index)


# In[ ]:




