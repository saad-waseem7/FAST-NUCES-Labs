import random

def number_guessing_game():
    secret_number = random.randint(1, 100)
    guesses = 0
    print("Welcome to the Number Guessing Game!")
    print("I'm thinking of a number between 1 and 100.")

    while True:
        guess = int(input("Take a guess: "))
        guesses += 1

        if guess < secret_number:
            print("Higher number please")
        elif guess > secret_number:
            print("Lower number please")
        else:
            print(f"Congratulations! You guessed the number in {guesses} guesses!")
            break


number_guessing_game()
