class Programmer:
    company = "Microsoft"

    def __init__(self, name, employee_id, programming_language, years_of_experience):
        self.name = name
        self.employee_id = employee_id
        self.programming_language = programming_language
        self.years_of_experience = years_of_experience

    def get_details(self):
        return (
            f"Name: {self.name}\n"
            f"Employee ID: {self.employee_id}\n"
            f"Programming Language: {self.programming_language}\n"
            f"Years of Experience: {self.years_of_experience}\n"
            f"Works at: {Programmer.company}"
        )

    def code(self, project_name):
        print(
            f"{self.name} is currently coding on the {project_name} project using {self.programming_language}."
        )


programmer1 = Programmer("Saadi", 101, "Python", 5)
programmer2 = Programmer("Billy", 102, "Java", 8)
programmer3 = Programmer("Zoha", 103, "C#", 3)

print("Details of Programmer 1:")
print(programmer1.get_details())
print("\nDetails of Programmer 2:")
print(programmer2.get_details())
print("\nDetails of Programmer 3:")
print(programmer3.get_details())

print("\nCoding activities:")
programmer1.code("Data Analysis Tool")
programmer2.code("Enterprise Backend System")
programmer3.code("Windows Application UI")
