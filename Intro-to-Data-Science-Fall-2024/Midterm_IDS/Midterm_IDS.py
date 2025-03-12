#!/usr/bin/env python
# coding: utf-8

# **DL2001 - Introduction to Data Science Lab - Midterm Exam - Fall 2024** <br>
# Please note:
# - Total marks are 40
# - Total Question are 9
# - No internet or helping material is allowed
# - You are NOT allowed to take any smart gadget (Mobile, smart watch etc.). If found, your exam will be canceled
# - Please submit your code on Cactus.
# - Add #Roll_Number as filename and download the .ipynb file, submit the file.
# - Cases of plagiarism, use of AI, unfair means like placing lab solution in the system and copying code from it or use of mobile phone will result in straight zero without any chance to defend along with dc.
# - The allowed time is **2 hours**
# 

# **Question 1:**
# Imagine you’re organizing a music playlist for a party and have a library of songs with their durations (in minutes). Create a **Dictionary** where song titles are the keys, and their durations (as floats) are the values. Write a Python program that prompts the user to enter multiple song titles (comma-separated). For each song title, check if it exists in the dictionary. If it exists, print the duration; if it doesn't, print "Song not found." At the end, calculate and display the total duration of all the songs found. If no valid songs are entered, print "No valid songs found."
# 
# **(Marks:5)**
# 
# **Song Title	               Duration (min)**
# 
# "Blinding Lights" =	             3.5
# "Levitating"	     =            3.2
# "Peaches"	          =           3.1
# "Save Your Tears"	   =          3.6
# "Rain Drops"	      =         4.0
# 
# Sample Output:
# 
# 
# ```
# Enter song titles (comma-separated): Peaches, Blinding Lights, Stay
# The duration of "Peaches" is 3.1 minutes
# The duration of "Blinding Lights" is 3.5 minutes
# Song "Stay" not found.
# Total duration of the valid songs: 6.6 minutes
# ```
# 
# 
# 

# In[2]:


import numpy as np
import pandas as pd
from scipy import stats


# In[2]:


# Q1
songs = {
    "Blinding Lights": 3.5,
    "Save Your Tears": 3.6,
    "Rain Drops": 4.0,
    "Levitating": 3.2,
    "Peaches": 3.1,
}
s = input("Enter song titles (comma-separated): ")
title = [title.strip() for title in s.split(",")]
bool_found = False
final = 0.0
for title in title:
    if title in songs:
        print(f'The duration of "{title}" is {songs[title]} minutes')
        final = final + songs[title]
        bool_found = True
    else:
        print(f'Song "{title}" not found.')

if bool_found:
    print(f"Total duration of the valid songs: {final} minutes")
else:
    print("No valid songs.")


# **Question 2: Numpy array**
# You’re working with a student grading system where each student has a unique identifier. Create a 1D array of 15 random scores between 1 and 100 to represent the test scores of 15 students. Then, organize these scores into a 5x3 matrix, where each row represents a different class with 3 students. Display both the original 1D array of scores and the reshaped matrix.
# 
#  **`(Marks: 3)`**

# In[3]:


# Q2
s = np.random.randint(1, 101, size=15)
print("Original 1D array:")
print(s)
reshape_s = s.reshape(5, 3)
print("Reshaped 5x3 matrix:")
print(reshape_s)


# **Question 3:**
# You’re developing a DNA sequence comparison tool to find matching nucleotide pairs in two DNA sequences. Write a function **count_matching_pairs()** that accepts two DNA sequences as arguments and returns the count of positions where both sequences contain the same two-character nucleotide pairs. For example, if the inputs are **"ATGCCGTA"** and **"ATGTCGTT"**, the function should return 3, as the two-character pairs **"AT"**, **"GC"**, and **"GT"** appear in the same positions in both sequences.
# 
# **(Marks:5)**

# In[4]:


# Q3
def count_matching_pairs(str1, str2):
    num = 0
    if len(str1) != len(str2):
        print("The sequences must have same length")
    for i in range(len(str1) - 1):
        if str1[i : i + 2] == str2[i : i + 2]:
            num = num + 1
    return num


str1 = "ATGCCGTA"
str2 = "ATGTCGTT"
ans = count_matching_pairs(str1, str2)
print(ans)


# **Question 4:**
# Create a DataFrame with columns Book, Price, and Stock:
# 
# Using boolean indexing, select books with a Price greater than $8 and create a new column called TotalValue that calculates the total stock value for each book (i.e., Price * Stock). Display the resulting DataFrame with reset indexes.
# 
# **(Marks: 4)**

# In[5]:


# Q4
data = {
    "Book": ["Science", "Maths", "English", "Urdu"],
    "Price": [6.0, 15.5, 10.7, 7.5],
    "Stock": [12, 4, 15, 8],
}
df = pd.DataFrame(data)

new_df = df[df["Price"] > 8]
new_df["TotalValue"] = new_df["Price"] * new_df["Stock"]
result_df = new_df.reset_index(drop=True)
print(result_df)


# **Question 5:**
# Load the data file 'exam_data_1' and  'exam_data_2 'to a dataframe and display first 10 rows of the each dataset.
# 
# **(Marks:2)**

# In[6]:


# Q5
df_1 = pd.read_csv("exam_data_1.csv")
df_2 = pd.read_csv("exam_data_2.csv")
print("\nFirst dataset: ", df_1)
print("\nSecond dataset: ", df_2)


# **Question 6:**
# 
# You have two datasets:
# 
# 1.   **exam_data_1.csv** - Contains personal and physical attributes of employees, including columns:
# **Name, Age, Date of Birth, Height (cm), Weight (kg), Salary**
# 2.   **exam_data_2.csv** - Contains professional details of employees, including columns:
# **Name, Department, Join Date, Salary, Location**
# 
# 
# Write a Python program to:
# 
# **1)**Load both datasets into separate DataFrames.
# 
# **2)**Merge the two DataFrames on the Name column to create a combined DataFrame that includes all records from both datasets, even if an employee is missing from one of them (use an outer join).
# 
# **3)**Finally, display the merged DataFrame.
# 
# **(Marks: 5)**

# In[7]:


# Q6
df_1 = pd.read_csv("exam_data_1.csv")
df_2 = pd.read_csv("exam_data_2.csv")

merged_data = pd.merge(df_1, df_2, on="Name", how="outer")
merged_data.to_csv("merged_dataset.csv")
print(merged_data)


# **Question 7:** Use both the **Interquartile Range (IQR)** method and the **Z-score** method to identify outliers in the Weight (kg) column. Show the steps used to calculate the IQR and the bounds for identifying outliers using both methods. List the names and weights of any outliers you find.**(5 Marks)**
# 
# Explain why they are considered outliers.

# In[8]:


# Q7
df = pd.DataFrame(merged_data)

# IQR Method
q1 = df["Weight (kg)"].quantile(0.25)
q3 = df["Weight (kg)"].quantile(0.75)
IQR = q3 - q1

# IQR Method
iqr_outliers = df[
    (df["Weight (kg)"] < q1 - 1.5 * IQR) | (df["Weight (kg)"] > q3 + 1.5 * IQR)
]
print("Outliers using IQR method:")
print(iqr_outliers[["Name", "Weight (kg)"]])

# Z-score Method
df["Z-score"] = stats.zscore(df["Weight (kg)"])
z_score_outliers = df[(df["Z-score"] < -3) | (df["Z-score"] > 3)]
print("Outliers using Z-score method:")
print(z_score_outliers[["Name", "Weight (kg)"]])


# **Question 8:**
# Using the merged dataset created from **dataset1_expanded.csv** and **dataset2_expanded.csv**, write a Python program to handle missing values effectively.
# 
# **Perform the following steps:**
# 
# 
# 1.  **Drop Rows with Missing Values:** Create a DataFrame from the merged dataset that excludes any rows with missing values in any column, and display the result.
# 2.   **Fill Missing Values:**
# 
# 
# *   For numerical columns (Age, Height (cm), Weight (kg)), replace missing values with the mean of each respective column
# *   For categorical columns (Department, Location), replace missing values with the most frequent value in that column.
# *   Display the resulting DataFrame after applying these methods.
# 
# 
# 3.   **Forward Fill Remaining Missing Values:** Use forward filling to fill in any remaining missing values, and display the final DataFrame.
# **(Marks: 6)**
# 

# In[9]:


# Q8
merged_df = pd.read_csv("merged_dataset.csv")
df_1 = merged_df.dropna()
print("DataFrame after dropping rows with missing values:")
print(df_1)

num_cols = ["Age", "Height (cm)", "Weight (kg)"]
for col in num_cols:
    merged_df[col].fillna(merged_df[col].mean(), inplace=True)

cat_cols = ["Department", "Location"]
for col in cat_cols:
    merged_df[col].fillna(merged_df[col].mode()[0], inplace=True)

print("DataFrame after missing values fill:")
print(merged_df)
merged_df.ffill(inplace=True)

print("Final DataFrame after forward filling remaining missed values:")
print(merged_df)


# **Question 9:**
# Using the merged dataset created from dataset1_expanded.csv and dataset2_expanded.csv, perform the following data type conversions:
# 
# 1. Convert the data type of the Date of Birth column to DateTime format.
# 2. Convert the data type of the Weight (kg) column to integer.
# 3. Verifies and displays the data types of the Date of Birth and Weight (kg) columns after conversion.
# **(Marks: 5)**

# In[10]:


# Q9
new_df = pd.read_csv("merged_dataset.csv")
new_df["Date of Birth"] = pd.to_datetime(new_df["Date of Birth"])
new_df["Weight (kg)"] = pd.to_numeric(new_df["Weight (kg)"])
print(new_df[["Date of Birth", "Weight (kg)"]].dtypes)

