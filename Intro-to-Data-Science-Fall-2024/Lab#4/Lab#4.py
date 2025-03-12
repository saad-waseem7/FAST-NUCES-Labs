#!/usr/bin/env python
# coding: utf-8

# In[2]:


import numpy as np
import pandas as pd


# # **Numpy Questions**

# **Task#1**

# In[3]:


matrix = np.random.randint(1, 100, (4, 4))
print(matrix)
matrix[matrix % 2 != 0] = -1
print(matrix)


# **Task#2**

# In[4]:


arr = np.random.randint(1, 100, (15))
print(arr)
print("Index of Maximun in Array:", np.where(arr == np.max(arr)))
print("Index of Minimun in Array:", np.where(arr == np.min(arr)))


# **Task#3**

# In[5]:


matrix = np.random.randint(1, 100, (3, 3))
print(matrix)
print("Row-wise Sum:", np.sum(matrix, axis=1))
print("Column-wise Sum:", np.sum(matrix, axis=0))


# **Task#4**

# In[6]:


matrix = np.random.rand(5, 5)
print(matrix)
min_value = 0
max_value = 1
normalized_matrix = (matrix - min_value) / (max_value - min_value)
print(normalized_matrix)


# **Task#5**

# In[7]:


arr1 = np.random.randint(1, 100, 5)
arr2 = np.random.randint(1, 100, 5)
print(arr1)
print(arr2)
print("Dot Product:", np.dot(arr1, arr2))


# **Task#6**

# In[8]:


arr = np.random.randint(1, 100, (5, 5))
print(arr)
arr.sort(axis=1)
print(arr)


# **Task#7**

# In[ ]:


matrix = np.random.randint(1, 100, (5, 5))
print(matrix)
print("Sum of Diagonal Elements:", np.trace(matrix))


# # **Pandas Questions**

# **Task#1**

# In[9]:


df = pd.DataFrame({'Date': ['2024-02-02', '2024-03-02', '2024-04-01', '2024-05-02'],
                   'Product': ['A', 'B', 'C', 'D'],
                   'Sales': [300, 240, 110, 190]})

product_sales = df.groupby('Product')['Sales'].sum()
print(product_sales)


# **Task#2**

# In[ ]:


df = pd.DataFrame(np.random.randint(0, 100, size=(10, 4)), columns=list('ABCD'))
print(df)
print(df[df['A'] > 50])


# **Task#3**

# In[ ]:


data = {'Name': ['Ahmed', 'Taha', 'Ali', 'Ahmed'],
        'Age': [26, 24, 29, 25],
        'Salary': [55000, 67000, 65000, 79000],
        'Bonus': [4000, 5000, 7000, 6000]}

df = pd.DataFrame(data)
df['Total Compensation'] = df['Salary'] + df['Bonus']
print(df)


# **Task#4**

# In[ ]:


data = {'Name': ['Alice', 'Bob', 'Charlie', 'David', 'Emily'],
        'Age': [25, 30, np.nan, 28, np.nan],
        'Salary': [60000, np.nan, 80000, 75000, np.nan],
        'Bonus': [np.nan, 5000, np.nan, 4000, np.nan]}

print(df)
df = pd.DataFrame(data)
df = df.dropna()
print(df)


# **Task#5**

# In[ ]:


data = {'Year': ['2001', '2002', '2003', '2004', '2004'],
        'Revenue': [250000, 300000, 400000, 350000, 220000],
        'Profit': [60000, 68000, 80000, 75000, 71000],
        }

df = pd.DataFrame(data)
print(df)
print(df[df['Profit'] < 0])


# **Task#6**

# In[10]:


data = {'Date': pd.date_range(start='2023-01-01', end='2023-01-10'),
        'Value': np.random.randint(10, 100, 10)}
df = pd.DataFrame(data)

df['Previous Day Value'] = df['Value'].shift(periods=1)

print(df)


# **Task#7**

# In[11]:


data = {'Product': ['Apple', 'Bag', 'Airplane', 'Boat'],
        'Price': [120, 80, 150, 70],
        'Discount': [0, 0, 0, 0]}
df = pd.DataFrame(data)

df.loc[df['Price'] > 100, 'Price'] = df['Price'] * 0.9
df.loc[df['Price'] > 100, 'Discount'] = 10

print(df)

