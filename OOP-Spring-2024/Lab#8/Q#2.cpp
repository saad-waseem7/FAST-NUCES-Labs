#include <iostream>
#include <string>
using namespace std;
class Ingredient
{
private:
    string name;
    double quantity;
    string unit;

public:
    Ingredient(string n, double q, string u = "")
    {
        name = n;
        quantity = q;
        unit = u;
    }

    string getName() const
    {
        return name;
    }
    double getQuantity() const
    {
        return quantity;
    }
    string getUnit() const
    {
        return unit;
    }

    void display() const
    {
        cout << "Ingredient: " << name << ", Quantity: " << quantity;
        if (!unit.empty())
            cout << ", Unit: " << unit;
        cout << endl;
    }
};

class Instruction
{
private:
    int stepNumber;
    string text;

public:
    Instruction(int sn, string t)
    {
        stepNumber = sn;
        text = t;
    }

    int getStepNumber() const
    {
        return stepNumber;
    }
    string getText() const
    {
        return text;
    }
};

class Recipe
{
private:
    string name;
    string description;
    Ingredient ingredients[10];
    Instruction instructions[10];
    int numIngredients;
    int numInstructions;

public:
    Recipe(string n, string d = "")
    {
        name = n;
        description = d;
        numIngredients = 0;
        numInstructions = 0;
    }

    string getName() const
    {
        return name;
    }
    string getDescription() const
    {
        return description;
    }
    int getNumIngredients() const
    {
        return numIngredients;
    }
    int getNumInstructions() const
    {
        return numInstructions;
    }

    void addIngredient(const Ingredient &ingredient)
    {
        if (numIngredients < 10)
        {
            ingredients[numIngredients++] = ingredient;
        }
        else
        {
            cout << "Cannot add more than 10 ingredients." << endl;
        }
    }

    void addInstruction(const Instruction &instruction)
    {
        if (numInstructions < 10)
        {
            instructions[numInstructions++] = instruction;
        }
        else
        {
            cout << "Cannot add more than 10 instructions." << endl;
        }
    }

    void displayRecipe() const
    {
        cout << "Recipe: " << name << endl;
        if (!description.empty())
        {
            cout << "Description: " << description << endl;
        }
        cout << "Ingredients:" << endl;
        for (int i = 0; i < numIngredients; ++i)
        {
            ingredients[i].display();
        }
        cout << "Instructions:" << endl;
        for (int i = 0; i < numInstructions; ++i)
        {
            cout << "Step " << instructions[i].getStepNumber()
                 << ": " << instructions[i].getText() << endl;
        }
    }
};