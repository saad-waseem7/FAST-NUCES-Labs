#!/usr/bin/env python
# coding: utf-8

# In[1]:


import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


# In[2]:


df=pd.read_csv('Train.csv')
df.head()


# In[3]:


df.info()


# In[4]:


missing_values = df.isnull().sum()
missing_percentage = (missing_values / len(df)) * 100
print("Missing Values:")
print(missing_values)
print("\nPercentage of Missing Values:")
print(missing_percentage)


# In[5]:


print(df.isnull().sum())


# In[6]:


df.shape


# In[7]:


df = df.drop(columns=["Cabin"])
df['Age'].fillna(df['Age'].median(), inplace=True)
df['Embarked'].fillna(df['Embarked'].mode()[0], inplace=True)
print("Number of missing values after imputation:")
print(df.isnull().sum())


# In[8]:


melted_df = pd.melt(df, id_vars=['PassengerId', 'Name'], value_vars=['Sex', 'Age', 'Fare'], var_name='Feature', value_name='Value')
melted_df.head()


# In[9]:


melted_df2 = pd.melt(df, id_vars=['PassengerId'], value_vars=['Pclass', 'Embarked', 'Survived'], var_name='Feature', value_name='Value')
melted_df2.head()


# In[10]:


melted_df3 = pd.melt(df, id_vars=['PassengerId'], value_vars=['SibSp', 'Parch'], var_name='Feature', value_name='Value')
melted_df3.head()


# In[11]:


survival_rate = df.groupby('Sex')['Survived'].mean()
print(survival_rate)


# In[12]:


average_fare = df.groupby('Pclass')['Fare'].mean()
print(average_fare)


# In[13]:


survivors_by_port = df.groupby('Embarked')['Survived'].sum()
print(survivors_by_port)


# In[14]:


pivot_table = pd.pivot_table(
    df,
    values='Survived',
    index='Sex',
    columns='Pclass',
    aggfunc='mean'
)
print(pivot_table)


# In[15]:


fare_pivot = pd.pivot_table(
    df,
    values='Fare',
    index='Sex',
    columns='Embarked',
    aggfunc='mean'
)

print(fare_pivot)


# In[16]:


passenger_count_pivot = pd.pivot_table(
    df,
    values='PassengerId',
    index='Pclass',
    columns='Survived',
    aggfunc='count'
)

print(passenger_count_pivot)


# ### Overview
# #### Part 1 (Data Overview)
# - Size of dataset (891, 12) where rows=891 & columns=12
# - Yes, there are missing values in "Age","Cabin" & "Embark" Columns:
# - Percentage of Missing Values:
#  - Age            19.865320
#  - Cabin          77.104377
#  - Embarked        0.224467
# 
# 

# #### Part 2 (Passenger Demographics)

# In[17]:


pclass_distribution = df['Pclass'].value_counts()
print(pclass_distribution)


# In[18]:


age_stats = df['Age'].describe()
print(age_stats)


# In[19]:


plt.hist(df['Age'], bins=20, color='skyblue', edgecolor='black')
plt.xlabel('Age')
plt.ylabel('Frequency')
plt.title('Age Distribution of Passengers')
plt.grid(True, linestyle='--', alpha=0.5)
plt.show()
print('\n\n')
plt.boxplot(df['Age'], patch_artist=True,
            boxprops=dict(facecolor='lightgreen', color='black'),
            whiskerprops=dict(color='black'),
            capprops=dict(color='black'),
            medianprops=dict(color='red'))
plt.ylabel('Age')
plt.title('Box Plot of Age')
plt.show()



# In[20]:


Q1 = df['Age'].quantile(0.25)
Q3 = df['Age'].quantile(0.75)
IQR = Q3 - Q1
lower_bound = Q1 - 1.5 * IQR
upper_bound = Q3 + 1.5 * IQR
outliers = df[(df['Age'] < lower_bound) | (df['Age'] > upper_bound)]
print("Potential Outliers:")
print(outliers)


# #### Part # (Survival Analysis)

# In[21]:


gender_distribution = df['Sex'].value_counts()
print(gender_distribution)


# In[22]:


overall_survival_rate = df['Survived'].mean()
print(f"Overall Survival Rate: {overall_survival_rate:.2f}")


# In[23]:


pivot_table = pd.pivot_table(
    df,
    values='Survived',
    index='Sex',
    columns='Pclass',
    aggfunc='mean'
)
print(pivot_table)


# In[24]:


correlation = df['Age'].corr(df['Survived'])
print(f"Correlation between Age and Survival: {correlation:.2f}")


# In[25]:


survival_rate = df.groupby('Sex')['Survived'].mean()
print(survival_rate)


# In[26]:


df['FamilySize'] = df['SibSp'] + df['Parch']
family_survival = df.groupby('FamilySize')['Survived'].mean()
print(family_survival)

