#!/usr/bin/env python
# coding: utf-8

# # **Lab Manual 11**
# This lab manual covers three essential data transformation techniques:
# 
# 1. **Principal Component Analysis (PCA)**
# 2. **Feature/Label Encoding**
# 3. **Normalization/Standardization**
# 
# 

# ## Necessary Libraries

# In[51]:


import numpy as np
import pandas as pd
from sklearn.preprocessing import (
    StandardScaler,
    MinMaxScaler,
)
from sklearn.decomposition import PCA
import matplotlib.pyplot as plt


# ## **Part 1: Principal Component Analysis (PCA)**
# ### **Objective**
# Principal Component Analysis (PCA) is a simple **dimensionality reduction** (i.e. Reducing Number of features/Columns) technique that can capture linear correlations between the features. For a given (standardized) data, PCA can be calculated by eigenvalue decomposition of covariance (or correlation) matrix of the data, or Singular Value Decomposition (SVD) of the data matrix. The data standardization includes mean removal and variance normalization.

# In[52]:


# Load the Iris dataset
from sklearn.datasets import load_iris

iris = load_iris()
X = pd.DataFrame(iris.data, columns=iris.feature_names)
y = pd.Series(iris.target, name="species")
X.head()


# In[53]:


# Standardize the features
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)


# In[54]:


# Apply PCA
pca = PCA(n_components=2)
X_pca = pca.fit_transform(X_scaled)
pca_df = pd.DataFrame(X_pca, columns=["PC1", "PC2"])
pca_df["species"] = y
pca_df.head()


# ## PCA Transformation:
# 
# 
# ```
# pca = PCA(n_components=2)
# X_pca = pca.fit_transform(X_scaled)
# 
# ```
# 
# **n_components=2**: specifies that we want to reduce the dataset to 2 dimensions (2 principal components).
# 
# The **fit_transform** method finds the principal components and transforms the original data into a new 2-dimensional space.
# 
# The resulting **X_pca** is a transformed dataset where each data point is represented by its projections on the first two principal components (PC1 and PC2).
# 
# 
# 
# ## Interpretation of Principal Components
# - Principal Component 1 (PC1) captures the direction of maximum variance in the data. This means that PC1 is the linear combination of the original features that explains the most variation in the dataset.
# 
# - Principal Component 2 (PC2) captures the second highest variance, orthogonal (at a right angle) to PC1. It explains the next highest amount of variance that is not captured by PC1.
# 
# By reducing the data to these two components, we preserve as much of the original data's variance as possible while reducing dimensionality.

# In[55]:


# Visualize the PCA result
plt.figure(figsize=(10, 6))
for species in np.unique(y):
    subset = pca_df[pca_df["species"] == species]
    plt.scatter(subset["PC1"], subset["PC2"], label=iris.target_names[species])
plt.xlabel("Principal Component 1")
plt.ylabel("Principal Component 2")
plt.title("PCA of Iris Dataset")
plt.legend()
plt.grid(True)
plt.show()


# ## Analyzing the PCA Graph
# ### Separation of Species:
# The plot shows a good separation between the species, especially Setosa, which forms a distinct cluster on the left side of the graph.
# 
# Versicolor and Virginica overlap to some extent but still form identifiable clusters.
# 
# ### Variance Explained:
# The spread along the x-axis (PC1) indicates that it explains the majority of the variance. The y-axis (PC2) explains less variance but still captures significant patterns in the data.
# 

# In[56]:


pca.explained_variance_ratio_


# PC1 captures ~72% of the variance, and PC2 captures ~23%.

# **Task 1:**
# Try applying PCA with n_components=3. Plot the 3D scatter plot and observe the difference.
# 
# 

# ## **Part 2: Feature/Label Encoding**
# 
# To convert **categorical features into numerical representations** for machine learning models.
# - **Label Encoding:** Assigns a unique numerical value to each category. It is suitable for ordinal data but may introduce unintended ordinal relationships in nominal data.
# - **One-Hot Encoding:** Creates binary columns for each category. It avoids ordinal relationships and is preferred for nominal data.
# 
# 

# In[57]:


# Create a sample dataset
data = pd.DataFrame(
    {
        "color": ["red", "blue", "green", "blue", "red"],
        "size": ["S", "M", "L", "XL", "M"],
        "price": [10.5, 15.0, 14.0, 18.5, 12.0],
    }
)
data


# In[58]:


# Label Encoding for Ordinal Feature (Size)

size_mapping = {"S": 0, "M": 1, "L": 2, "XL": 3}
data["size_encoded"] = data["size"].map(size_mapping)
data


# In[59]:


# One-Hot Encoding for Nominal Feature color
one_hot_encoded = pd.get_dummies(data["color"], prefix="color").astype(int)
data = pd.concat([data, one_hot_encoded], axis=1)
data


# Task 2:
# Encode the **species** column of the iris dataset  using **OneHotEncoder from Scikit-Learn.**
# 
# 
# 

# ## **Part 3: Normalization and Standardization**
# ### **Objective**
# We use **Normalization and Standardization** To scale the features to a similar range, improving the performance and convergence of machine learning algorithms.
# 
# - **Normalization (Min-Max Scaling):** Scales the data to a fixed range, usually [0, 1]. It is sensitive to outliers.
# 
# - **Standardization (Z-score Normalization):** Centers the data to have a mean of 0 and a standard deviation of 1. It is robust against outliers and is preferred for algorithms like PCA and K-means clustering.

# In[60]:


# Create a sample dataset
df = pd.DataFrame(
    {"feature1": [10, 20, 30, 40, 50], "feature2": [100, 200, 300, 400, 500]}
)
df


# In[61]:


# Apply Min-Max Normalization
min_max_scaler = MinMaxScaler()
df_normalized = pd.DataFrame(min_max_scaler.fit_transform(df), columns=df.columns)
df_normalized


# In[62]:


# Apply Standardization
standard_scaler = StandardScaler()
df_standardized = pd.DataFrame(standard_scaler.fit_transform(df), columns=df.columns)
df_standardized


# ### Visualize the Effects of Scaling
# 

# In[63]:


plt.figure(figsize=(12, 6))
plt.subplot(1, 2, 1)
plt.boxplot(df_normalized.values)
plt.title("Min-Max Normalized Data")

plt.subplot(1, 2, 2)
plt.boxplot(df_standardized.values)
plt.title("Standardized Data")

plt.show()


# ## **Use the dataset "Train.csv" to complete the following task**

# In[64]:


# Load data
df = pd.read_csv("Train.csv")
df.head()


# ### **Task 1. Data Cleaning**
# - Check for any missing values in the dataset and handle them appropriately:
# - Fill missing values for numerical columns using the mean or median.
# - Fill missing values for categorical columns with the most frequent value or using forward fill.

# In[65]:


# TASK
missing_values = df.isnull().sum()

print("Number of missing values in each column:")
print(missing_values)


# In[66]:


df = df.drop(columns=["Cabin"])
df["Age"].fillna(df["Age"].median(), inplace=True)
df["Embarked"].fillna(df["Embarked"].mode()[0], inplace=True)
print("Number of missing values after imputation:")
print(df.isnull().sum())


# ### **Task 2: Feature/Label Encoding**
# Perform encoding on the categorical features:
# - Use **sklearn label encoding** for the Sex column.
# - Use  sklearn one-hot encoding for the Embarked column. Make sure to handle cases where missing values are present.
# 

# In[67]:


# TASK
size_mapping = {"female": 0, "male": 1}
df["gender_encoded"] = df["Sex"].map(size_mapping)
df.head()


# In[68]:


one_hot_encoded = pd.get_dummies(df["Embarked"], prefix="embarked").astype(int)
df = pd.concat([df, one_hot_encoded], axis=1)
df.head()


# ### **Task 3: Normalization/Standardization**
# Normalize or standardize the numerical features (**Age, Fare**):
# - Use standardization to transform these columns to have a mean of 0 and a standard deviation of 1.
# - Explain when it is more appropriate to use normalization versus standardization

# In[69]:


# TASK

num_cols = ["Age", "Fare"]
scaler = StandardScaler()
df[num_cols] = scaler.fit_transform(df[num_cols])
df.head()


# In[70]:


df.info()


# ### **Task 4: Principal Component Analysis (PCA)**
# Apply PCA to reduce the dimensionality of the dataset:
# - Use only numerical features (including transformed features) for PCA.
# - Reduce the data to 2 principal components and create a scatter plot colored by the Survived column.
# - Explain the variance captured by each component and interpret the results.

# In[71]:


# TASK
X = df.drop("Survived", axis=1)
y = df["Survived"]
X_numeric = X.select_dtypes(include=[np.number])

scaler = StandardScaler()
X_scaled = scaler.fit_transform(X_numeric)

# Apply PCA
pca = PCA(n_components=2)
X_pca = pca.fit_transform(X_scaled)

pca_df = pd.DataFrame(X_pca, columns=["PC1", "PC2"])
pca_df["Survived"] = y
pca_df.head()


# In[72]:


pca.explained_variance_ratio_


# PC1 captures ~22% of the variance, and PC2 captures ~18%.

# ### **Task 5: Exploratory Data Analysis (EDA)**
# - Visualize the relationship between the principal components and survival status by Creating a scatter plot of the principal components (PC1 vs. PC2).
# 
# - Add labels and a legend for better interpretation.

# In[73]:


# TASK
plt.figure(figsize=(10, 6))
for survival_status in np.unique(y):
    subset = pca_df[pca_df["Survived"] == survival_status]
    plt.scatter(
        subset["PC1"],
        subset["PC2"],
        label=f"Survived={survival_status}",
        color="red" if survival_status == 1 else "blue",
    )

plt.xlabel("Principal Component 1")
plt.ylabel("Principal Component 2")
plt.title("PCA: Scatter Plot by Survived")
plt.legend()
plt.grid(True)
plt.show()

