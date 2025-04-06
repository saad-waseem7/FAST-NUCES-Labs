import random

# Base class for users
class User:
    def __init__(self, first_name, last_name, username, password, role):
        self.first_name = first_name
        self.last_name = last_name
        self.username = username
        self.password = password
        self.role = role

    def update_name(self, first_name, last_name):
        self.first_name = first_name
        self.last_name = last_name

    def __eq__(self, other):
        return self.username == other.username


# Admin subclass
class Admin(User):
    def __init__(self, first_name, last_name, username, password):
        super().__init__(first_name, last_name, username, password, "admin")


# Player subclass
class Player(User):
    def __init__(self, first_name, last_name, username, password):
        super().__init__(first_name, last_name, username, password, "player")
        self.scores = []  # List of quiz scores
        self.quiz_history = []  # List to store detailed quiz history

    def record_score(self, score, quiz_details):
        self.scores.append(score)
        self.quiz_history.append(quiz_details)

    def display_statistics(self):
        if not self.scores:
            print("No quizzes taken yet.")
            return
        print(f"Number of quizzes taken: {len(self.scores)}")
        print(f"Highest score: {max(self.scores)}")
        print(f"Lowest score: {min(self.scores)}")
        print(f"Average score: {sum(self.scores) / len(self.scores):.2f}")

    def display_all_scores(self):
        if not self.scores:
            print("No quizzes taken yet.")
            return
        print("\nQuiz History:")
        for i, score in enumerate(self.scores, start=1):
            print(f"Quiz {i}: {score}/{len(self.quiz_history[i - 1])}")

    def display_last_quiz_details(self):
        if not self.quiz_history:
            print("No quizzes taken yet.")
            return
        last_quiz = self.quiz_history[-1]
        print("\nLast Quiz Details:")
        for q, (user_answer, is_correct) in last_quiz:
            print(f"Question: {q.text}")
            print(
                f"Your answer: {user_answer} ({'Correct' if is_correct else 'Wrong'})"
            )
            print(f"Correct answer: {q.get_correct_answer()}")


# Base class for questions
class Question:
    question_id_counter = 1

    def __init__(self, text):
        self.text = text
        self.question_id = Question.question_id_counter
        Question.question_id_counter += 1

    def __eq__(self, other):
        return self.text == other.text

    def ask_question(self):
        pass

    def get_correct_answer(self):
        pass


# MCQ subclass
class MCQQuestion(Question):
    def __init__(self, text, options, correct_option):
        super().__init__(text)
        self.options = options
        self.correct_option = correct_option

    def ask_question(self):
        print(self.text)
        random.shuffle(self.options)
        for i, option in enumerate(self.options, start=1):
            print(f"{i}. {option}")
        choice = int(input("Your choice: ")) - 1
        return self.options[choice] == self.get_correct_answer(), self.options[choice]

    def get_correct_answer(self):
        return self.options[self.correct_option]


# True/False subclass
class TFQuestion(Question):
    def __init__(self, text, correct_answer):
        super().__init__(text)
        self.correct_answer = correct_answer

    def ask_question(self):
        print(f"{self.text} (True/False)")
        answer = input("Your answer: ").strip().lower()
        return answer == self.correct_answer.lower(), answer

    def get_correct_answer(self):
        return self.correct_answer


# Complete-the-blank subclass
class CompleteQuestion(Question):
    def __init__(self, text, correct_answer):
        super().__init__(text)
        self.correct_answer = correct_answer

    def ask_question(self):
        print(self.text)
        answer = input("Your answer: ").strip()
        return answer.lower() == self.correct_answer.lower(), answer

    def get_correct_answer(self):
        return self.correct_answer


# Main quiz game class
class QuizGame:
    def __init__(self):
        self.users = [
            Admin("user", "user", "ADMIN", "1234"),
            Player("user", "user", "PLAYER", "1234"),
        ]
        self.questions = []
        self.current_user = None

    def login(self):
        while True:
            print("*** Welcome to the Quiz Game ***")
            username = input("Enter username: ")
            password = input("Enter password: ")
            user = next(
                (
                    u
                    for u in self.users
                    if u.username == username and u.password == password
                ),
                None,
            )

            if user:
                self.current_user = user
                print(
                    f"Welcome, {user.first_name} {user.last_name} ({user.role.upper()})!"
                )
                if isinstance(user, Admin):
                    self.admin_menu()
                elif isinstance(user, Player):
                    self.player_menu()
            else:
                print("Invalid username or password. Try again.")

    def admin_menu(self):
        while True:
            print("\nAdmin Menu:")
            print("1. Switch accounts")
            print("2. View all users")
            print("3. Add new user")
            print("4. View all questions")
            print("5. Add new question")
            print("6. Exit")
            choice = input("Your choice: ")

            if choice == "1":
                break
            elif choice == "2":
                self.view_users()
            elif choice == "3":
                self.add_user()
            elif choice == "4":
                self.view_questions()
            elif choice == "5":
                self.add_question()
            elif choice == "6":
                exit()

    def player_menu(self):
        while True:
            if not isinstance(self.current_user, Player):
                print("You need to be logged in as a Player to access this menu.")
                break

            print("\nPlayer Menu:")
            print("1. Switch accounts")
            print("2. Start a new quiz")
            print("3. Display score statistics")
            print("4. Display all scores")
            print("5. Display last quiz details")
            print("6. Exit")
            choice = input("Your choice: ")

            if choice == "1":
                break
            elif choice == "2":
                self.start_quiz()
            elif choice == "3":
                if self.current_user:
                    self.current_user.display_statistics()
            elif choice == "4":
                if self.current_user:
                    self.current_user.display_all_scores()
            elif choice == "5":
                if self.current_user:
                    self.current_user.display_last_quiz_details()
            elif choice == "6":
                exit()

    def view_users(self):
        print("\nExisting Users:")
        for user in self.users:
            print(f"{user.first_name} {user.last_name} ({user.role.upper()})")

    def add_user(self):
        print("\nAdd New User:")
        first_name = input("First name: ")
        last_name = input("Last name: ")
        username = input("Username: ")
        password = input("Password: ")
        role = input("Role (admin/player): ").lower()

        if any(u.username == username for u in self.users):
            print("Username already exists!")
        else:
            if role == "admin":
                self.users.append(Admin(first_name, last_name, username, password))
            elif role == "player":
                self.users.append(Player(first_name, last_name, username, password))
            print("User added successfully.")

    def view_questions(self):
        print("\nExisting Questions:")
        for question in self.questions:
            print(f"[ID: {question.question_id}] {question.text}")

    def add_question(self):
        print("\nAdd New Question:")
        q_type = input("Question type (MCQ/TF/Complete): ").lower()
        text = input("Enter question text: ")

        if q_type == "mcq":
            options = [input(f"Option {i+1}: ") for i in range(4)]
            correct_option = int(input("Correct option (1-4): ")) - 1
            self.questions.append(MCQQuestion(text, options, correct_option))
        elif q_type == "tf":
            correct_answer = input("Answer (True/False): ")
            self.questions.append(TFQuestion(text, correct_answer))
        elif q_type == "complete":
            correct_answer = input("Correct answer: ")
            self.questions.append(CompleteQuestion(text, correct_answer))
        print("Question added successfully.")

    def start_quiz(self):
        if not isinstance(self.current_user, Player):
            print("Only players can take quizzes.")
            return

        if len(self.questions) < 5:
            print("Not enough questions to start a quiz. Please add more questions.")
            return

        print("\nStarting quiz...")
        random.shuffle(self.questions)
        selected_questions = self.questions[:5]
        score = 0
        quiz_details = []

        for question in selected_questions:
            is_correct, user_answer = question.ask_question()
            score += 1 if is_correct else 0
            quiz_details.append((question, (user_answer, is_correct)))

        print(f"\nQuiz finished! Your score: {score}/{len(selected_questions)}")
        if self.current_user:
            self.current_user.record_score(score, quiz_details)


# Run the quiz game
if __name__ == "__main__":
    game = QuizGame()
    game.login()
