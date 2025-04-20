import os
folder_name = "E:\\Python_Course\\Chapter#9\\Multiplication_Tables"

if os.path.exists(folder_name):
    print(f"The folder '{folder_name}' already exists.")
else:
    os.makedirs(folder_name)
    print(f"The folder '{folder_name}' has been created.")

for i in range(2, 21):
    filename = os.path.join(folder_name, f"Table_of_{i}.txt")
    with open(filename, "w") as f:
        for j in range(1, 11):
            f.write(f"{i} x {j} = {i * j}\n")
    
    print(f"Multiplication table for {i} generated and saved in {filename}")

print(f"Multiplication tables from 2 to 20 have been generated and saved in the folder '{folder_name}'.")