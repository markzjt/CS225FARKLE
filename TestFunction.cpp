#include "TestFunction.h"
#include "ScoringRules.h"
#include <iostream>
using namespace std;

class Die {
private:
    int face;   
public:
    int getFace() {
        return face;
    }
    void setFace(int newValue) {
        face = newValue;
    }
};

class Dice {
private:
    static const int MAX_DICE = 6;
    Die dice[MAX_DICE];
public:
    Die* getAllDice() {
        return dice;
    }
};

// Test cases for development
void testAllScoringCombos() {
    Dice gameDice;
    ScoringRules rules;
    Die* allDice = gameDice.getAllDice();
    
    // Test 1: Straight (1-2-3-4-5-6)
    cout << "Test 1: Straight (1-2-3-4-5-6)" << endl;
    allDice[0].setFace(1);
    allDice[1].setFace(2);
    allDice[2].setFace(3);
    allDice[3].setFace(4);
    allDice[4].setFace(5);
    allDice[5].setFace(6);
    cout << "Expected: 1500, Got: " << rules.calculateScore(allDice, 6) << endl << endl;
    
    // Test 2: Three Pairs (1-1-3-3-5-5)
    cout << "Test 2: Three Pairs (1-1-3-3-5-5)" << endl;
    allDice[0].setFace(1);
    allDice[1].setFace(1);
    allDice[2].setFace(3);
    allDice[3].setFace(3);
    allDice[4].setFace(5);
    allDice[5].setFace(5);
    cout << "Expected: 1500, Got: " << rules.calculateScore(allDice, 6) << endl << endl;
    
    // Test 3: Six of a Kind (4-4-4-4-4-4)
    cout << "Test 3: Six of a Kind (4-4-4-4-4-4)" << endl;
    for (int i = 0; i < 6; i++) {
        allDice[i].setFace(4);
    }
    cout << "Expected: 3000, Got: " << rules.calculateScore(allDice, 6) << endl << endl;
    
    // Test 4: Two Triplets (2-2-2-5-5-5)
    cout << "Test 4: Two Triplets (2-2-2-5-5-5)" << endl;
    allDice[0].setFace(2);
    allDice[1].setFace(2);
    allDice[2].setFace(2);
    allDice[3].setFace(5);
    allDice[4].setFace(5);
    allDice[5].setFace(5);
    cout << "Expected: 2500, Got: " << rules.calculateScore(allDice, 6) << endl << endl;
    
    // Test 5: Four of a Kind + Pair (3-3-3-3-6-6)
    cout << "Test 5: Four of a Kind + Pair (3-3-3-3-6-6)" << endl;
    allDice[0].setFace(3);
    allDice[1].setFace(3);
    allDice[2].setFace(3);
    allDice[3].setFace(3);
    allDice[4].setFace(6);
    allDice[5].setFace(6);
    cout << "Expected: 1500, Got: " << rules.calculateScore(allDice, 6) << endl << endl;
    
    // Test 6: Five of a Kind (2-2-2-2-2-3)
    cout << "Test 6: Five of a Kind (2-2-2-2-2-3)" << endl;
    allDice[0].setFace(2);
    allDice[1].setFace(2);
    allDice[2].setFace(2);
    allDice[3].setFace(2);
    allDice[4].setFace(2);
    allDice[5].setFace(3);
    cout << "Expected: 2000, Got: " << rules.calculateScore(allDice, 6) << endl << endl;
    
    // Test 7: Four of a Kind only (3-3-3-3-2-4)
    cout << "Test 7: Four of a Kind (3-3-3-3-2-4)" << endl;
    allDice[0].setFace(3);
    allDice[1].setFace(3);
    allDice[2].setFace(3);
    allDice[3].setFace(3);
    allDice[4].setFace(2);
    allDice[5].setFace(4);
    cout << "Expected: 1000, Got: " << rules.calculateScore(allDice, 6) << endl << endl;
    
    // Test 8: Three 1s (1-1-1-2-3-4)
    cout << "Test 8: Three 1s (1-1-1-2-3-4)" << endl;
    allDice[0].setFace(1);
    allDice[1].setFace(1);
    allDice[2].setFace(1);
    allDice[3].setFace(2);
    allDice[4].setFace(3);
    allDice[5].setFace(4);
    cout << "Expected: 300, Got: " << rules.calculateScore(allDice, 6) << endl << endl;
    
    // Test 9: Three 5s (5-5-5-2-3-4)
    cout << "Test 9: Three 5s (5-5-5-2-3-4)" << endl;
    allDice[0].setFace(5);
    allDice[1].setFace(5);
    allDice[2].setFace(5);
    allDice[3].setFace(2);
    allDice[4].setFace(3);
    allDice[5].setFace(4);
    cout << "Expected: 500, Got: " << rules.calculateScore(allDice, 6) << endl << endl;
    
    // Test 10: Mixed 1's and 5's
    cout << "Test 10: Three 1s + Two 5s (1-1-1-5-5-2)" << endl;
    allDice[0].setFace(1);
    allDice[1].setFace(1);
    allDice[2].setFace(1);
    allDice[3].setFace(5);
    allDice[4].setFace(5);
    allDice[5].setFace(2);
    cout << "Expected: 400, Got: " << rules.calculateScore(allDice, 6) << endl << endl;
    
    // Test 11: Mixed 1s and 5s (1-5-2-3-4-6)
    cout << "Test 11: Single 1 and 5 (1-5-2-3-4-6)" << endl;
    allDice[0].setFace(1);
    allDice[1].setFace(5);
    allDice[2].setFace(2);
    allDice[3].setFace(3);
    allDice[4].setFace(4);
    allDice[5].setFace(6);
    cout << "Expected: 150, Got: " << rules.calculateScore(allDice, 6) << endl << endl;
    
    // Test 12: Four 1s (1-1-1-1-2-3)
    cout << "Test 12: Four 1s (1-1-1-1-2-3)" << endl;
    allDice[0].setFace(1);
    allDice[1].setFace(1);
    allDice[2].setFace(1);
    allDice[3].setFace(1);
    allDice[4].setFace(2);
    allDice[5].setFace(3);
    cout << "Expected: 1000, Got: " << rules.calculateScore(allDice, 6) << endl << endl;
    
    // Test 13: Farkle 
    cout << "Test 13: Farkle (2-3-4-6-2-3)" << endl;
    allDice[0].setFace(2);
    allDice[1].setFace(3);
    allDice[2].setFace(4);
    allDice[3].setFace(6);
    allDice[4].setFace(2);
    allDice[5].setFace(3);
    cout << "Expected: 0, Got: " << rules.calculateScore(allDice, 6) << endl;
   
    // Test 14: Testing with less than 6 dice
    cout << "Test 14: Three 2's (2-2-2)" << endl;
    allDice[0].setFace(2);
    allDice[1].setFace(2);
    allDice[2].setFace(2);
    cout << "Expected: 200, Got: " << rules.calculateScore(allDice, 3) << endl << endl;
}


