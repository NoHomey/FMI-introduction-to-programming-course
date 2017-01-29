#include <ctime>
#include <iostream>

#define MAX(a, b) (a < b ? b : a)

const float EPSILON = 0.001;
const size_t BEGINING = 8;
size_t count = BEGINING;
size_t id[BEGINING];
float power[BEGINING];
float agility[BEGINING];
float haste[BEGINING];
float knowledge[BEGINING];
float health[BEGINING];

void shiftFloats(float* array, const size_t index) {
    array[index] = array[index + 1];
}

void kill(size_t index) {
    const size_t last = count - 1;
    for(size_t i = index; i < last; ++i) {
        id[i] = id[i + 1];
        shiftFloats(power, i);
        shiftFloats(agility, i);
        shiftFloats(haste, i);
        shiftFloats(knowledge, i);
        shiftFloats(health, i);
    }
    --count;
}

int randomChance() {
    return rand() % 100;
}

float hitChance(const size_t attacking, const size_t attacked) {
    return (1.0 + (knowledge[attacking] / 100.0)) * (MAX(10, (agility[attacking] - agility[attacked])) / 100.0) * 10.00;
}

float hitDamage(const size_t attacking, const size_t attacked) {
    return (1.0 + (MAX(10.0, (haste[attacking] - haste[attacked])) / 100.0)) * MAX(10.0, (power[attacking] - power[attacked]));
}

float attack(const size_t attacking, const size_t attacked) {
    return (hitChance(attacking, attacked) - randomChance()) > EPSILON ? hitDamage(attacking, attacked) : 0.0;
}

void takeDamage(const size_t attacked, const float damage) {
    health[attacked] -= damage;
}

bool isAlive(const size_t index) {
    return health[index] > EPSILON;
}

void figth(const size_t animal1, const size_t animal2) {
    size_t attacking = animal1;
    size_t attacked = animal2;
    size_t tmp = 0;
    while(isAlive(animal1) && isAlive(animal2)) {
        takeDamage(attacked, attack(attacking, attacked));
        tmp = attacking;
        attacking = attacked;
        attacked = tmp;
    }
    kill(attacking);
}

int main() {
    srand(time(NULL));
    size_t index = 0;
    size_t nextCount = 0;
    for(; index < BEGINING; ++index) {
        id[index] = index;
        power[index] = 20.2;
        agility[index] = 59.9;
        haste[index] = 23.1;
        knowledge[index] = 37.4;
        health[index] = 101;
    }
    while(count != 1) {
        nextCount = count >> 1;
        for(index = 0; index < nextCount; ++index) {
            figth(index, index + 1);
        }
    }
    std::cout << id[0] << std::endl;

    return 0;
}
