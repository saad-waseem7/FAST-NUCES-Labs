#!/usr/bin/env python
# coding: utf-8

# In[8]:


import pandas as pd
import numpy as np
from scipy import stats


# ## Task#1

# In[9]:


df = pd.read_csv('Score_data.csv')
df.head()


# In[10]:


def remove_missing_values(df):
    numeric_cols = df.select_dtypes(include=[np.number]).columns
    df[numeric_cols] = df[numeric_cols].fillna(df[numeric_cols].mean())
    return df

df=remove_missing_values(df)
df.head()


# ## Task#2

# In[17]:


df2=pd.read_csv('Score_data.csv')
df2=df2.dropna()
df2.head()


# ## Task#3

# In[18]:


df3=pd.read_csv('Salary_data.csv')
df3.head()


# In[19]:


z_scores = stats.zscore(df3["Salary"])
top_outliers = z_scores.sort_values(ascending=False).head(5)
df3 = df3.drop(top_outliers.index)

print(df3)


# ## Task#4

# In[21]:


df4 = pd.read_csv("Iris_data.csv")
df4.info()


# In[23]:


df4 = df4.drop_duplicates(keep="last")
df4.info()


# ## Task#5

# In[24]:


df5 = pd.read_csv("Score_data.csv")


# In[25]:


df5["Date"] = pd.to_datetime(df5["Date"])

df5["Year"] = df5["Date"].dt.year
df5.head()

