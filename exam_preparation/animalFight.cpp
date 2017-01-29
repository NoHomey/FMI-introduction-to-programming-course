#include <ctime>
#include <iostream>
#include <new>

#define MAX(a, b) (a < b ? b : a)

const float EPSILON = 0.001;

class Animal {
protected:
size_t id;
float power;
float agility;
float haste;
float knowledge;
float health;

static unsigned short random() {
    return rand() % 100;
}

float hitChance(const Animal* oponent) const {
    return (1.0 + (knowledge / 100.0)) * (MAX(10, (agility - oponent->agility)) / 100.0) * 10.00;
}

float hitDamage(const Animal* oponent) const {
    return (1.0 + (MAX(10.0, (haste - oponent->haste)) / 100.0)) * MAX(10.0, (power - oponent->power));
}

public:
Animal(const size_t Id, const float Power, const float Agility, const float Haste, const float Knowledge, const float Health)
: id{Id}, power{Power}, agility{Agility}, haste{Haste}, knowledge{Knowledge}, health{Health} {}

float attack(const Animal* oponent) const {
    return (hitChance(oponent) - random()) > EPSILON ? hitDamage(oponent) : 0.0;
}

void takeDamage(const float Damage) {
    health -= Damage;
}

bool isAlive() const {
    return health > EPSILON;
}

size_t getId() const {
    return id;
}
};

class Arena {
protected:
static void alloc(Animal**& animals, size_t count) {
    try {
        animals = new Animal*[count];
    } catch(std::bad_alloc& error) {
        throw error;
    }
}

static Animal* figth(Animal* animal1, Animal* animal2) {
    Animal* attacking = animal1;
    Animal* attacked = animal2;
    Animal* tmp = nullptr;
    while(animal1->isAlive() and animal2->isAlive()) {
        attacked->takeDamage(attacking->attack(attacked));
        tmp = attacking;
        attacking = attacked;
        attacked = tmp;
    }
    delete attacking;

    return attacked;
}

size_t currentFigtherId;
size_t figthersCount;
Animal** figthers;
Animal** winners;

void allocWinners() {
    alloc(winners, figthersCount >> 1);
}

public:
static void initialize() {
    srand(time(NULL));
}

Arena(const size_t FigthersCount)
: currentFigtherId{0}, figthersCount{FigthersCount}, figthers{nullptr}, winners{nullptr} {
    alloc(figthers, FigthersCount);
    allocWinners();
}

~Arena() {
    delete[] figthers;
    delete[] winners;
}

void addFighter(const float Power, const float Agility, const float Haste, const float Knowledge, const float Health) {
    figthers[currentFigtherId++] = new Animal{currentFigtherId, Power, Agility, Haste, Knowledge, Health};
}

bool preparaForNextRound() {
    if(figthersCount == 2) {
        return false;
    }
    delete[] figthers;
    figthers = winners;
    figthersCount >>= 1;
    allocWinners();

    return true;
}

void round() {
    for(size_t i = 0; i < figthersCount; i += 2) {
        winners[i / 2] = figth(figthers[i], figthers[i + 1]);
    }
}

void start() {
    while(true) {
        round();
        if(!preparaForNextRound()) {
            return;
        }
    }
}

Animal* getWinner() const {
    return winners[0];
}
};

int main() {
    Arena::initialize();
    Arena forest = {4};
    forest.addFighter(20, 59, 23.1, 37.4, 200);
    forest.addFighter(20, 59, 23.1, 37.4, 200);
    forest.addFighter(20, 59, 23.1, 37.4, 200);
    forest.addFighter(20, 59, 23.1, 37.4, 200);
    forest.start();
    Animal* winner = forest.getWinner();
    std::cout << winner->getId() << std::endl;
    delete winner;

    return 0;
}
