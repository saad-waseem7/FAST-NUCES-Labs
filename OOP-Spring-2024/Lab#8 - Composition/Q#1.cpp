#include <iostream>
#include <string>
using namespace std;

class Engine
{
private:
    int hp;
    string type;

public:
    Engine(int hp, string type)
    {
        this->hp = hp;
        this->type = type;
    }

    int get_hp()
    {
        return this->hp;
    }
    string getType()
    {
        return this->type;
    }

    void set_hp(int hp)
    {
        this->hp = hp;
    }
    void setType(string type)
    {
        this->type = type;
    }
};

class Car
{
private:
    string model;
    int year;
    Engine engine;

public:
    Car(string model, int year, int engine_hp, string engineType) : engine(engine_hp, engineType)
    {
        this->model = model;
        this->year = year;
    }

    string getModel()
    {
        return this->model;
    }
    int getYear()
    {
        return this->year;
    }
    Engine getEngine()
    {
        return this->engine;
    }

    void setModel(string model)
    {
        this->model = model;
    }
    void setYear(int year)
    {
        this->year = year;
    }
    void setEngine(int engine_hp, string engineType)
    {
        engine.set_hp(engine_hp);
        engine.setType(engineType);
    }
    void setEngine(Engine engine)
    {
        this->engine = engine;
    }
    ~Car()
    {
        cout << "Destructor Called" << endl;
    }
};

int main()
{
    Car myCar("Audi", 2024, 500, "Electric");

    cout << "Model: " << myCar.getModel() << endl;
    cout << "Year: " << myCar.getYear() << endl;
    cout << "Engine Type: " << myCar.getEngine().getType() << endl;
    cout << "hp: " << myCar.getEngine().get_hp() << endl;

    Engine newEngine(600, "Electric");
    myCar.setEngine(newEngine);
    cout << "New Engine hp: " << myCar.getEngine().get_hp() << endl;

    return 0;
}