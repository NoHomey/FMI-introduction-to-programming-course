/**
*
* Solution to homework task
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Ivo Stratev
* @idnumber 45342
* @task 9
* @compiler GCC
*
*/

#include <iostream>
#include <new>

#define CHECK_FIELD_MATCH(checked, requirements, field) \
  (checked->field >= requirements->field)

typedef unsigned short Price;
typedef unsigned int Number;

struct MobilePlan {
  Price price;
  Number minutes;
  Number megaBytes;
  Number smses;

  MobilePlan(const Price price_ = 0, const Number minutes_ = 0,
             const Number megaBytes_ = 0, const Number smses_ = 0);
} typedef MobilePlan;

template <typename T>
T input();

bool plansMatch(const MobilePlan* const checked,
                const MobilePlan* const requirements);

void printMobilePlan(const MobilePlan* const mobilePlan);

void sortMobilePlans(MobilePlan* plans, const Number length);

int main() {
  const Number count = input<Number>();
  MobilePlan* plans = nullptr;
  MobilePlan* mobilePlan = nullptr;
  MobilePlan mobilePlanRequirements = {};
  bool atleastOneMobilePlanMatchRequirements = false;
  try {
    plans = new MobilePlan[count];
  } catch (const std::bad_alloc& error) {
    throw error;
  }
  for (Number plan = 0; plan < count; ++plan) {
    mobilePlan = plans + plan;
    mobilePlan->price = input<Price>();
    mobilePlan->minutes = input<Number>();
    mobilePlan->megaBytes = input<Number>();
    mobilePlan->smses = input<Number>();
  }
  mobilePlanRequirements.minutes = input<Number>();
  mobilePlanRequirements.megaBytes = input<Number>();
  mobilePlanRequirements.smses = input<Number>();
  sortMobilePlans(plans, count);
  for (Number plan = 0; plan < count; ++plan) {
    mobilePlan = plans + plan;
    if (plansMatch(mobilePlan, &mobilePlanRequirements)) {
      atleastOneMobilePlanMatchRequirements = true;
      printMobilePlan(mobilePlan);
    }
  }
  delete[] plans;
  if (!atleastOneMobilePlanMatchRequirements) {
    std::cout << "No solution\n";
  }

  return 0;
}

MobilePlan::MobilePlan(const Price price_, const Number minutes_,
                       const Number megaBytes_, const Number smses_)
    : price{price_}, minutes{minutes_}, megaBytes{megaBytes_}, smses{smses_} {}

template <typename T>
T input() {
  T value;
  std::cin >> value;
  return value;
}

bool plansMatch(const MobilePlan* const checked,
                const MobilePlan* const requirements) {
  return CHECK_FIELD_MATCH(checked, requirements, minutes) &&
         CHECK_FIELD_MATCH(checked, requirements, megaBytes) &&
         CHECK_FIELD_MATCH(checked, requirements, smses);
}

void printMobilePlan(const MobilePlan* const mobilePlan) {
  std::cout << mobilePlan->price << ' ' << mobilePlan->minutes << ' '
            << mobilePlan->megaBytes << ' ' << mobilePlan->smses << '\n';
}

void sortMobilePlans(MobilePlan* plans, const Number length) {
  const Number lengthMinusOne = length - 1;
  Number indexOfMinElement = 0;
  Number previusIndex = 0;
  MobilePlan plan;
  for (Number i = 0; i < lengthMinusOne; ++i) {
    indexOfMinElement = i;
    for (Number j = i + 1; j < length; ++j) {
      if (plans[j].price < plans[indexOfMinElement].price) {
        indexOfMinElement = j;
      }
    }
    while (indexOfMinElement != i) {
      previusIndex = indexOfMinElement - 1;
      plan = plans[previusIndex];
      plans[previusIndex] = plans[indexOfMinElement];
      plans[indexOfMinElement] = plan;
      indexOfMinElement = previusIndex;
    }
  }
}