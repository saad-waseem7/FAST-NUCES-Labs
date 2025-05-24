#include <iostream>
#include <stdio.h>
using namespace std;

class Animal
{
public:
    virtual ~Animal()
    {
        cout << "~Animal() called." << endl;
    }

    virtual char *speak()
    {
        return speakMethod();
    }

protected:
    virtual char *speakMethod()
    {
        return (char *)"speak() called.";
    }
};

class Dog : public Animal
{
protected:
    char *speakMethod() override
    {
        return (char *)"woof!";
    }

public:
    ~Dog()
    {
        cout << "~Dog() called." << endl;
    }
};

class Cat : public Animal
{
protected:
    char *speakMethod() override
    {
        return (char *)"mew!";
    }

public:
    ~Cat()
    {
        cout << "~Cat() called." << endl;
    }
};

int main()
{
    Animal objAnimal;
    Dog objDog;

    Animal *ptrAnimal = &objAnimal;
    Dog *ptrDog = &objDog;

    cout << objAnimal.speak() << endl;
    cout << objDog.speak() << endl;
    cout << ptrAnimal->speak() << endl;
    cout << ptrDog->speak() << endl;
    cout << endl;

    // Animal objAnimal;
    // Dog objDog;

    // Animal* ptrAnimal = &objDog;
    // Dog* ptrDog = &objDog;

    cout << objAnimal.speak() << endl;
    cout << objDog.speak() << endl;
    cout << ptrAnimal->speak() << endl;
    cout << ptrDog->speak() << endl;
    cout << endl;

    Dog lassie;

    Animal *myPet = &lassie;

    cout << myPet->speak() << endl;

    Dog mutley;
    Cat whiskers;

    const int size1 = 2;
    Animal *myPets1[size1];

    myPets1[0] = &whiskers;
    myPets1[1] = &mutley;

    for (int i = 0; i < size1; i++)
    {
        cout << myPets1[i]->speak() << endl;
    }
    //
    cout << endl;

    const int size2 = 5;
    Animal *myPets2[size2];

    int i = 0;
    cout << "Press 1 for a Dog and 2 for a Cat." << endl;
    while (i < size2)
    {
        char input;
        cin.get(input);
        switch (input)
        {
        case '1':
            myPets2[i] = new Dog;
            cout << "Dog added at position " << i << endl
                 << endl;
            i++;
            break;
        case '2':
            myPets2[i] = new Cat;
            cout << "Cat added at position " << i << endl
                 << endl;
            i++;
            break;
        default:
            // cout << "Invalid input. Enter again." << endl << endl;
            break;
        }
    }

    for (int j = 0; j < size2; j++)
    {
        cout << myPets2[j]->speak() << endl;
    }

    for (int j = 0; j < size2; j++)
    {
        delete myPets2[j];
    }
    return 0;
}