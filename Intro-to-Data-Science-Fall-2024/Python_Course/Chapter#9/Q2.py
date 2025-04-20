import random

path = "E:\\Python_Course\\Chapter#9\\hi_Score.txt"

def game():
    print("Playing the game...")
    score = random.randint(0, 100)
    print(f"Your score is: {score}")
    return score

with open(path, "r") as f:
    hiScore = int(f.readline().strip())
current_score = game()
if current_score > hiScore:
    print("Congratulations! You broke the high score!")
    with open(path, "w") as f:
        f.write(str(current_score))
else:
    print(f"The current high score is: {hiScore}")
