#ifndef SCORINGRULES_H
#define SCORINGRULES_H

class Die;
class ScoringRules {
private:
    bool hasStraight(int frequencyCount[]);
    bool hasThreePair(int frequencyCount[]);
    bool hasSixOfKind(int frequencyCount[]);
    bool hasTwoTriplets(int frequencyCount[]);
    bool hasFourAndPair(int frequencyCount[]);
    
public:
    int calculateScore(Die dice[], int numDice);
    bool isFarkle(Die dice[], int numDice);
};

#endif