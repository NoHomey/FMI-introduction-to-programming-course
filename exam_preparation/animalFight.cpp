#include <ctime>
#include <iostream>

#define MAX(a, b) (a < b ? b : a)

const float EPSILON = 0.001;

class Animal {
protected:
float id;
float power;
float agility;
float haste;
float knowledge;
float health;

static unsigned short random() {
    return rand() % 100;
}

float hitChance(const Animal* oponent) const {
    return (1.0 + (knowledge / 100.0)) * (MAX(10, (agility - oponent->agility)) / 100.0) * 100.00;
}

float hitDamage(const Animal* oponent) const {
    return (1.0 + (MAX(10.0, (haste - oponent->haste)) / 100.0)) * MAX(10.0, (power - oponent->power));
}

public:
Animal(const float Id, const float Power, const float Agility, const float Haste, const float Knowledge, const float Health)
: id{Id}, power{Power}, agility{Agility}, haste{Haste}, knowledge{Knowledge}, health{Health} {}

float attack(const Animal* oponent) const {
    const float chance = hitChance(oponent);
    const int hit = random();
    const float damage = hitDamage(oponent);
    std::cout << chance << ' ' << hit << ' ' << damage << std::endl;
    return (chance - hit) > EPSILON ? damage : 0.0;
}

void takeDamage(const float Damage) {
    health -= Damage;
}

bool isAlive() const {
    return health > EPSILON;
}
};

int main() {
    srand(time(NULL));
    Animal animal1 = {1, 70, 80, 35, 70, 100};
    Animal animal2 = {2, 45, 50, 80, 10, 100};
    Animal* attacking = &animal1;
    Animal* attacked = &animal2;
    Animal* tmp = nullptr;
    while(animal1.isAlive() and animal2.isAlive()) {
        attacked->takeDamage(attacking->attack(attacked));
        tmp = attacking;
        attacking = attacked;
        attacked = tmp;
    }
    std::cout << animal1.isAlive() << ' ' << animal2.isAlive() << std::endl;

    return 0;
}
