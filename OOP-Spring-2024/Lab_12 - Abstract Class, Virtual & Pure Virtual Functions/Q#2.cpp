#include <iostream>
using namespace std;

class Character
{
public:
    Character(int health, int attack_power);

    virtual void attack(Character &target) const = 0;
    virtual void use_special_ability(Character &target) const = 0;

    int health;
    int attack_power;
};

Character::Character(int health, int attack_power) : health(health), attack_power(attack_power) {}

class Warrior : public Character
{
public:
    Warrior(int health, int attack_power);

    void attack(Character &target) const override;
    void use_special_ability(Character &target) const override;
};

Warrior::Warrior(int health, int attack_power) : Character(health, attack_power) {}

void Warrior::attack(Character &target) const
{
    cout << "Warrior attacks with basic attack, dealing " << attack_power << " damage." << endl;
    target.health -= attack_power;
}

void Warrior::use_special_ability(Character &target) const
{
    cout << "Warrior uses special ability: Power Strike, dealing " << attack_power * 2 << " damage." << endl;
    target.health -= attack_power * 2;
}

class Mage : public Character
{
public:
    Mage(int health, int attack_power);

    void attack(Character &target) const override;
    void use_special_ability(Character &target) const override;
};

Mage::Mage(int health, int attack_power) : Character(health, attack_power) {}

void Mage::attack(Character &target) const
{
    cout << "Mage attacks with basic attack, dealing " << attack_power << " damage." << endl;
    target.health -= attack_power;
}

void Mage::use_special_ability(Character &target) const
{
    cout << "Mage uses special ability: Fireball, dealing " << attack_power * 3 << " damage." << endl;
    target.health -= attack_power * 3;
}

class Archer : public Character
{
public:
    Archer(int health, int attack_power);

    void attack(Character &target) const override;
    void use_special_ability(Character &target) const override;
};

Archer::Archer(int health, int attack_power) : Character(health, attack_power) {}

void Archer::attack(Character &target) const
{
    cout << "Archer attacks with basic attack, dealing " << attack_power << " damage." << endl;
    target.health -= attack_power;
}

void Archer::use_special_ability(Character &target) const
{
    cout << "Archer uses special ability: Multi shot, dealing " << attack_power * 1.5 << " damage." << endl;
    target.health -= attack_power * 1.5;
}

int main()
{
    Warrior warrior(120, 20);
    Mage mage(100, 20);
    Archer archer(120, 10);

    cout << "Initial health points:" << endl;
    cout << "Warrior: " << warrior.health << endl;
    cout << "Mage: " << mage.health << endl;
    cout << "Archer: " << archer.health << endl;

    cout << "\nWarrior attacks Mage:" << endl;
    warrior.attack(mage);
    cout << "Mage health: " << mage.health << endl;

    cout << "\nMage uses special ability on Warrior:" << endl;
    mage.use_special_ability(warrior);
    cout << "Warrior health: " << warrior.health << endl;

    cout << "\nArcher attacks Warrior:" << endl;
    archer.attack(warrior);
    cout << "Warrior health: " << warrior.health << endl;

    cout << "\nWarrior uses special ability on Archer:" << endl;
    warrior.use_special_ability(archer);
    cout << "Archer health: " << archer.health << endl;

    return 0;
}
