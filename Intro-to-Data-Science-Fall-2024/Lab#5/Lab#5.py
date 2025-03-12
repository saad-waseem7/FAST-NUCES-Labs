#!/usr/bin/env python
# coding: utf-8

# # **Web Scrapping**

# # Necessary Libraries

# In[19]:


import requests
from bs4 import BeautifulSoup


# In[20]:


url = "https://www.wikipedia.org/"
res = requests.get(url)
soup = BeautifulSoup(res.content, "html.parser")


# **Q#1**

# In[21]:


main_title = soup.find('div', class_='central-textlogo').find('span').text
print("Main Title from the Logo:", main_title)


# **Q#2**

# In[22]:


url = "https://www.wikipedia.org/"
response = requests.get(url)
soup = BeautifulSoup(response.text, 'html.parser')
featured_languages = soup.find_all('a', class_='link-box')
for language in featured_languages[:10]:
    print(language.text)


# **Q#3**

# In[23]:


languages = soup.find_all('a', class_='link-box')
top_language_urls = []

for language in languages[:10]:
    lang_url = language['href']
    top_language_urls.append(lang_url)

for i, url in enumerate(top_language_urls, 1):
    print(f"{i}. {url}")


# **Q#4**

# In[24]:


para = soup.find_all('p')
print(f"Number of <p> elements on the page: {len(para)}")


# **Q#5**

# In[25]:


url = "https://en.wikipedia.org/wiki/Main_Page"
response = requests.get(url)
soup = BeautifulSoup(response.content, "html.parser")

featured_article = soup.find('div', id='mp-upper').find('div', id='mp-tfa').find('b').find('a').text
print("Featured Article Title:", featured_article)


# **Q#6**

# In[26]:


url = input("Enter a Wikipedia URL: ")

try:
    response = requests.get(url)
    if response.status_code == 200:
        print("Page fetched successfully!")
    else:
        print(f"Failed to fetch the page. Status code: {response.status_code}")
except requests.exceptions.RequestException as e:
    print(f"An error occurred: {e}")


# **Q#7**

# In[27]:


in_news = soup.find('div', id='mp-itn').find_all('li')

print("In the News headlines:")
for headline in in_news:
    print("-", headline.text)


# **Q#8**

# In[28]:


dyk = soup.find('div', id='mp-dyk').find_all('li')

print("Did You Know facts:")
for fact in dyk:
    print("-", fact.text)

