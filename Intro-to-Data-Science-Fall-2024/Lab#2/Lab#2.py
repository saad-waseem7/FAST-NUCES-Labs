#!/usr/bin/env python
# coding: utf-8

# **Task#1**

# In[ ]:


l1=["apple","banana","cherry","kiwi","mango"]
l2=input("Enter a String To Search: ")
if l2 in l1:
  print("Found")
else:
  print("Not Found")


# **Task#2**

# In[42]:


d1={
    "a":1,
    "b":2,
    "c":3,
    "d":4,
    "e":5
    }
d2={}
for k,v in d1.items():
  d2[v]=k
print(d2)


# **Task#3**

# In[ ]:


a=int(input("Enter a Number to print its table: "))
for i in range(1,11):
  print(f"{a} x {i} = {a*i}")


# **Task#4**

# In[ ]:


person1={
    "name":"Tom",
    "age":25,
    "city":"New York",
    "color":['red','blue','green'],
}
s1=input("Enter your favourite color: ")
person1["color"].append(s1)
person1["age"]=person1["age"]+1
print(person1)


# **Task#5**

# In[ ]:


a1=int(input("Enter a Starting Number: "))
while True:
  a2=int(input("Enter a Dividing Number (-1 to exit): "))
  if(a2>a1):
    print("Dividing Number should be less than Starting Number")
    continue
  a1=a1/a2
  if(a1<1 or a2==-1):
    break
  print("New Value: ",a1)


# **Task#6**

# In[ ]:


person = [
    {"first_name": "Wade", "last_name": "Wilson"},
    {"first_name": "Shawn", "last_name": "Levy"},
    {"first_name": "Wade", "last_name": "Wilson"},
    {"first_name": "Rocky", "last_name": "Johnson"},
    {"first_name": "Michael", "last_name": "Jordan"},
    {"first_name": "Rocky", "last_name": "Johnson"},
    {"first_name": "Wade", "last_name": "Wilson"},
]

f_names = {}

for person in person:
    f_name = person["first_name"] + " " + person["last_name"]
    f_names[f_name] = f_names.get(f_name, 0) + 1

print(f_names)


# **Task#7**

# In[ ]:


numbers = [23, 11, 46, 18, 25, 34, 67, 90, 13, 52]

even_num = []
odd_num = []

for num in numbers:
    if num % 2 == 0:
        even_num.append(num)
    else:
        odd_num.append(num)

print("Even numbers:", even_num)
print("Odd numbers:", odd_num)


# **Task#8**

# In[ ]:


prices = {
    "apple": 250,
    "banana": 200,
    "orange": 180,
    "milk": 220,
    "eggs": 300
}
while True:
    item_name = input("Enter an item name (or 'stop' to quit): ")
    if item_name == "stop":
        print("Exiting the program.")
        break
    if item_name in prices:
        print(f"The price of {item_name} is Rs.{prices[item_name]}")
    else:
        print(f"Not found: {item_name}")


# **Task#9**

# In[ ]:


a1=input("Enter the Number or 'exit' to Finish: ")
while True:
  a2=input("Enter the Number or 'exit' to Finish: ")
  if a2=="exit":
    print("The Total is:",a1)
    break
  else:
    a1=int(a1)+int(a2)
    print("New Value:",a1)


# **Task#10**

# In[ ]:


activities = {
    "Monday": ["Work", "Gym"],
    "Tuesday": ["Study", "Relax"],
    "Wednesday": ["Work", "Meet friends"],
    "Thursday": ["Study", "Watch movie"],
    "Friday": ["Work", "Party"],
    "Saturday": ["Relax", "Outdoor activities"],
    "Sunday": ["Relax", "Watch movie"]
}
day = input("Enter a day of the week: ")
if day.capitalize() in activities:
    print("Activities for", day, ":", activities[day.capitalize()])
else:
    print("Invalid day")

