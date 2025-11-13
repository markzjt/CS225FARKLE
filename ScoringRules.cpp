#include "ScoringRules.h"
using namespace std;

// Define die class for use
class Die {
private:
    int face;   
public:
    int getFace() {
        return face;
    }
};

bool ScoringRules::hasStraight(int frequencyCount[]) {
    for (int i = 1; i <= 6; i++) {
        if (frequencyCount[i] != 1) {
            return false;
        }
    }
    return true;
}

bool ScoringRules::hasThreePair(int frequencyCount[]) {
    int pairs = 0;
    for (int i = 1; i <= 6; i++) {
        if (frequencyCount[i] == 2) {
            pairs++;
        }
    }
    if (pairs == 3) {
        return true;
    }
    return false;
}  

bool ScoringRules::hasSixOfKind(int frequencyCount[]) {
    for (int i = 1; i <= 6; i++) {
        if (frequencyCount[i] == 6) {
            return true;
        }
    }
    return false;
}

bool ScoringRules::hasTwoTriplets(int frequencyCount[]) {
    int triplets = 0;
    for (int i = 1; i <= 6; i++) {
        if (frequencyCount[i] == 3) {
            triplets++;
        }
    }
    if (triplets == 2) {
        return true;
    }   
    return false;     
}

bool ScoringRules::hasFourAndPair(int frequencyCount[]) {
    bool hasFourKind = false;
    bool hasPair = false;
    for (int i = 1; i <= 6; i++) {
        if (frequencyCount[i] == 4) {
            hasFourKind = true;
        } 
        if (frequencyCount[i] == 2) { 
            hasPair = true;
        }
        if (hasFourKind == true && hasPair == true) {
            return true;
        }
    }
    return false;
}

int ScoringRules::calculateScore(Die dice[], int numDice) {
    int frequencyCount[7] = {0}; 
    int score = 0;
    // Count each die number of occurences
    for (int i = 0; i < numDice; i++) {
        int face = dice[i].getFace();
        frequencyCount[face]++;
    }   
    // Scoring combos with 6 die
    if (numDice == 6) {
        if (hasStraight(frequencyCount) == true) {
            return 1500;  
        }
        if (hasThreePair(frequencyCount) == true) {
            return 1500;  
        }
        if (hasSixOfKind(frequencyCount) == true) {
            return 3000;  
        }
        if (hasTwoTriplets(frequencyCount) == true) {
            return 2500;  
        }
        if (hasFourAndPair(frequencyCount) == true) {
            return 1500;  
        }
    }
    // Scoring combos 4/5 die
    for (int face = 1; face <= 6; face++) {
        if (frequencyCount[face] == 4) {
            frequencyCount[face] -= 4;
            score += 1000; 
        }
        if (frequencyCount[face] == 5) {
            frequencyCount[face] -= 5;
            score += 2000; 
        }
    }
    // Score three of a kind
    for (int face = 1; face <= 6; face++) {
        if (frequencyCount[face] >= 3) {
            if (face == 1) {
                score += 300;  
            } else {
                score += face * 100;  
            }
            frequencyCount[face] -= 3;  
        }
    }
    // Score leftover 1s
    score += frequencyCount[1] * 100;
    // Score leftover 5s 
    score += frequencyCount[5] * 50;
    
    return score;
}

bool ScoringRules::isFarkle(Die dice[], int numDice) {
    if (calculateScore(dice, numDice) == 0) {
        return true;
    }
    return false;
}