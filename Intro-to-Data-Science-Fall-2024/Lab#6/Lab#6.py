#!/usr/bin/env python
# coding: utf-8

# In[ ]:


import pandas as pd
from scipy import stats


# ### Task#1

# In[ ]:


df1 = pd.read_csv("Iris_data.csv")
df1.head()


# In[ ]:


df1.isnull().sum()


# In[ ]:


def fill_missing_with_mean(df):
    for col in df.select_dtypes(include=["number"]).columns:
        df[col] = df[col].fillna(df[col].mean())
    return df


df1 = fill_missing_with_mean(df1)


# In[ ]:


df1.isnull().sum()


# ### Task#2

# In[ ]:


df2 = pd.read_csv("Iris_data.csv")
df2.info()


# In[ ]:


df2 = df2.dropna()
df2.info()


# ### Task#3

# In[ ]:


df3 = pd.read_csv("Score_data.csv")
df3.head()


# In[ ]:


df3.shape


# In[ ]:


z_scores = stats.zscore(df3["Score"])
top_outliers = z_scores.sort_values(ascending=False).head(5)
df3 = df3.drop(top_outliers.index)

print(df3)


# In[ ]:


df3.shape


# ### Task#4

# In[ ]:


df4 = pd.read_csv("Iris_data.csv")
df4.head()


# In[ ]:


df4.info()


# In[ ]:


df4 = df4.drop_duplicates(keep="last")


# In[ ]:


df4.info()


# ### Task#5

# In[ ]:


df5 = pd.read_csv("Score_data.csv")


# In[ ]:


# Convert 'Date' column to datetime
df5["Date"] = pd.to_datetime(df5["Date"])

# Extract year from 'Date' and store in 'Year' column
df5["Year"] = df5["Date"].dt.year
df5.head()


# ### Task#6

# In[ ]:


df_1 = pd.read_csv("Salary_data.csv")
df_2 = pd.read_csv("Score_data.csv")


# In[ ]:


# Perform outer join
merged_df = pd.merge(df_1, df_2, on="ID", how="outer")

# Fill missing values with 0
merged_df.fillna(0, inplace=True)
merged_df.head()


# ### Task#7

# In[ ]:


# Concatenate DataFrames along columns with NaN for non-overlapping indices
merged_df_2 = pd.concat([df_1, df_2], axis=1)
merged_df_2.head()


# ### Task#8

# In[ ]:


df_8 = pd.read_csv("Score_data.csv")
df_8.info()


# In[ ]:


lower_limit = df_8["Score"].quantile(0.1)
upper_limit = df_8["Score"].quantile(0.9)

# Keep only rows within the 10th and 90th percentiles
df_8 = df_8[(df_8["Score"] >= lower_limit) & (df_8["Score"] <= upper_limit)]
df_8.head()


# In[ ]:


df_8.info()


# ### Task#9

# In[ ]:


df_9 = pd.read_csv("Iris_data.csv")
df_9.info()


# In[ ]:


# Get categorical columns
categorical_cols = df_9.select_dtypes(include=["object"]).columns

# Fill missing values with a specific value (e.g., 'Unknown')
df_9[categorical_cols] = df_9[categorical_cols].fillna("Unknown")

df_encoded = pd.get_dummies(df_9[categorical_cols])

# Concatenate original DataFrame with encoded DataFrame
df_final = pd.concat([df_9.drop(columns=categorical_cols), df_encoded], axis=1)
df_final.head()


# ### Task#10

# In[ ]:


df_x = pd.read_csv("Salary_data.csv")
df_y = pd.read_csv("Score_data.csv")


# In[ ]:


# Merge DataFrames based on multiple columns (ID and Name)
# Only one done here (ID)...
merged_df = pd.merge(df_x, df_y, on='ID')
print(merged_df)

