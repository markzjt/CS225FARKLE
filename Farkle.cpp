// Sources of help: 
    // Searched via google "best way to parse a string into an array of ints" and google
    // ai overview suggested parsing into array of primative types using <sstream> 
    // which i implemented for parsing during the user selection of dice to keep

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "ScoringRules.h"
using namespace std;

// Single Die Class
class Die {
private:
    int face;   
public:
    // Constructor die with random face value
    Die() {
        rollDie();
    }  
    // Roll the die and get random 1-6
    void rollDie() {
        face = 1 + rand() % 6;
    }   
    // Get face value
    int getFace() {
        return face;
    } 
    // Set die for testing purposes during build to avoid randomness
    void setFace(int newValue) {
            face = newValue; 
    }
    // Operator overloading for << to print die face value 
    friend ostream& operator<<(ostream& os, const Die& die) {
        os << "[" << die.face << "]";
        return os;
    }
};

// Dice Class
class Dice {
private:
    static const int MAX_DICE = 6;
    Die dice[MAX_DICE];  
    int numAvailable;   
public:
    bool keptDice[MAX_DICE]; 
    // Dice constructor set available to 6 and none kept
    Dice() {
        numAvailable = MAX_DICE;
        for (int i = 0; i < MAX_DICE; i++) {
            keptDice[i] = false;
        }
    }   
    // Roll all dice that aren't keptDice
    void rollAvailable() {
        for (int i = 0; i < MAX_DICE; i++) {
            if (keptDice[i] == false) {
                dice[i].rollDie();
            }
        }
    }   
    // Keep a die and reduce number available 
    void keepDie(int i) {
        if (i >= 0 && i < MAX_DICE && keptDice[i] == false) {
            keptDice[i] = true;
            numAvailable--;
        }
    }    
    // Reset all dice for new turn
    void resetDice() {
        numAvailable = MAX_DICE;
        for (int i = 0; i < MAX_DICE; i++) {
            keptDice[i] = false;
            dice[i].rollDie();
        }
    }  
    // Get number of available dice
    int getNumAvailable() {
        return numAvailable;
    }   
    // Getter for dice
    Die* getAllDice() {
        return dice;
    }   
    // Display all dice using overload extraction operator 
    void displayDice() {
        // Display index positions for user to choose die to keep
        cout << "Index: ";
        for (int i = 0; i < MAX_DICE; i++) {
            if (keptDice[i] == false) {
                cout << " " << (i + 1) << "  ";
            } else {
                cout << " X  ";
            }
        }
        cout << endl;
        cout << "Dice:  ";
        for (int i = 0; i < MAX_DICE; i++) {
            if (keptDice[i] == false) {
                cout << dice[i] << " ";  
            } else {
                cout << " X  ";
            }
        }
        cout << endl;
    }
};

// Person class to demonstrate inheritance in player class
class Person {
protected:
    string name;   
public:
    Person(string n){
        name = n;
    }   
    virtual ~Person() {}    
    string getName() {
        return name;
    }
};

// Player Class which is a person
class Player : public Person {  
private:
    int totalScore;
public:
    // Constructor
    Player(string playerName) : Person(playerName) {
        totalScore = 0;
    }  
    
    int getTotalScore() {
        return totalScore;
    }
    
    void addPoints(int points) {
        totalScore += points;
    }
    
    // Set score for loading a saved game
    void setScore(int score) {
        totalScore = score;
    }
    // Set name for loading a saved game
    void setName(string n) {
        name = n;
    }
};

// Game Class
class Game {
private:
    Player user;
    Player skynet;
    Dice gameDice;
    ScoringRules rules;
    bool isUsersTurn;
    const int targetScore = 10000;  
    bool gameOver;
    
    // Skynet taunts the user array
    string skynetTaunts[5] = {
        "I'll be back... for more points.",
        "Come with me if you want to lose.",
        "I need your dice, your points, and your motorcycle.",
        "My CPU is a neural net processor, a learning machine.",
        "The future is not set. But your loss is highly probable.",
    };
    
    // Skynet opponent decision (Ill continue to refine if user wins too often)
    bool skynetRollDecision(int turnScore, int availableDice) {
        if (turnScore < 300) {
            return true;  
        }      
        if (availableDice <= 2 && turnScore >= 300) {
            return false;  
        }       
        if (turnScore >= 500 && availableDice <= 3) {
            return false; 
        }      
        if (turnScore >= 1000) {
            return false;  
        }
        return true;
    }
    
    // Display game rules
    void displayRules() {
        cout << "\n============ FARKLE RULES ============\n";
        cout << "Goal: Be the first to reach 10,000 points\n\n";
        cout << "Scoring:\n";
        cout << "  Single 1 = 100 points\n";
        cout << "  Single 5 = 50 points\n";
        cout << "  Three 1s = 300 points\n";
        cout << "  Three 2s = 200 points\n";
        cout << "  Three 3s = 300 points\n";
        cout << "  Three 4s = 400 points\n";
        cout << "  Three 5s = 500 points\n";
        cout << "  Three 6s = 600 points\n";
        cout << "  Straight (1-2-3-4-5-6) = 1500 points\n";
        cout << "  Three Pairs = 1500 points\n";
        cout << "  Four of a Kind = 1000 points\n";
        cout << "  Five of a kind = 2000 points \n";
        cout << "  Four of a kind plus a pair = 1500 points\n";
        cout << "  Two Triplets = 2500 points\n";
        cout << "  Six of a Kind = 3000 points\n\n";
        cout << "Roll no scoring dice...you FARKLE and lose all points for that turn!\n";
        cout << "=====================================\n\n";
    }
    
    // User Turn
    void userTurn() {
        int turnScore = 0;
        bool nextTurn = false; 
        cout << "\n--- Your Turn ---\n";
        cout << "Current Total Score: " << user.getTotalScore() << "\n\n";  
        gameDice.resetDice();
        gameDice.rollAvailable();     
        // Turn loop
        while (nextTurn == false) {
            // Display current dice
            gameDice.displayDice();            
            // Build array of available dice for farkle check
            Die* allDice = gameDice.getAllDice();
            int availableCount = 0;
            Die availableDice[6];
            for (int i = 0; i < 6; i++) {
                if (gameDice.keptDice[i] == false) {
                    availableDice[availableCount] = allDice[i];
                    availableCount++;
                }
            }
            // Check if Farkle
            if (rules.isFarkle(availableDice, availableCount) == true) {
                cout << "\nFARKLE! You lose all points this round!\n";
                turnScore = 0;
                nextTurn = true;
                break;
            }
            
            // Player chooses dice to keep
            cout << "Turn score so far: " << turnScore << "\n";
            cout << "Select dice to keep (enter index 1-6 separated by spaces, enter a 0 to stop rolling): ";
            
            string input;
            getline(cin, input);
            // Enter zero to stop rolling
            if (input == "0") {
                nextTurn = true;
            } else {
                Die selectedDice[6];
                int numSelected = 0; 
                stringstream stream(input);
                int diceNum;
                int indicesToKeep[6];
                while (stream >> diceNum) {
                    if (diceNum >= 1 && diceNum <= 6) {
                        int index = diceNum - 1;  
                        // Only select dice that haven't been kept already
                        if (gameDice.keptDice[index] == false) {
                            selectedDice[numSelected] = allDice[index];
                            indicesToKeep[numSelected] = index;
                            numSelected++;
                        }
                    }
                }
                
                // Check an input
                if (numSelected == 0) {
                    cout << "No valid dice selected. Try again.\n";
                    continue;
                }
                
                // Check input for scoring combo (using isFarkle now)
                if (rules.isFarkle(selectedDice, numSelected) == true) {
                    cout << "Those dice don't form a scoring combination.\n";
                    cout << "You must select dice that score points.\n";
                    continue;
                }
                
                // Calculate score for selected dice
                int selectionScore = rules.calculateScore(selectedDice, numSelected);
                turnScore += selectionScore;
                cout << "Scored " << selectionScore << " points!\n";

                // Mark the dice as kept
                for (int i = 0; i < numSelected; i++) {
                    gameDice.keepDie(indicesToKeep[i]);
                }

                // Check if all dice are kept 
                if (gameDice.getNumAvailable() == 0) {
                    cout << "\nAll dice scored!\n";
                    cout << "Roll all 6 dice again? (y/n): ";
                    string rollChoice;
                    getline(cin, rollChoice);
                    
                    if (rollChoice == "y" || rollChoice == "Y") {
                        gameDice.resetDice();
                        gameDice.rollAvailable();  
                    } else {
                        nextTurn = true;
                    }
                } else {
                    // Ask if player wants to roll again or stop
                    cout << "\nRoll again with remaining dice? (y/n): ";
                    string rollChoice;
                    getline(cin, rollChoice);
                    
                    if (rollChoice == "n" || rollChoice == "N") {
                        nextTurn = true;
                    } else {
                        gameDice.rollAvailable();  
                    }
                }
                    
            }
        }
        
        // Add turn score to total and display turn score and total score
        if (turnScore > 0) {
            user.addPoints(turnScore);
            cout << "\nTurn over. Scored " << turnScore << " points.\n";
            cout << "New total: " << user.getTotalScore() << "\n";
        }
    }

    
    // Play skynet turn
    void playSkynetTurn() {
        int turnScore = 0;
        bool nextTurn = false;
        cout << "\n--- Skynet's Turn ---\n"; 
        // Display random Skynet taunt
        int randomTaunt = rand() % 5;  
        cout << "Skynet: \"" << skynetTaunts[randomTaunt] << "\"\n\n";   
        gameDice.resetDice();        
        while (nextTurn == false) {
            // Roll available dice
            gameDice.rollAvailable();
            // Build array of available dice for Farkle check
            Die* allDice = gameDice.getAllDice();
            int availableCount = 0;
            Die availableDice[6];
            for (int i = 0; i < 6; i++) {
                if (gameDice.keptDice[i] == false) {
                    availableDice[availableCount] = allDice[i];
                    availableCount++;
                }
            }
            // Check if Farkle
            if (rules.isFarkle(availableDice, availableCount) == true) {
                cout << "Skynet FARKLED! No points this turn.\n";
                turnScore = 0;
                nextTurn = true;
                break;
            }
            // Computer selects all scoring dice
            Die selectedDice[6];
            int numSelected = 0;
            for (int i = 0; i < 6; i++) {
                if (gameDice.keptDice[i] == false) {
                    selectedDice[numSelected] = allDice[i];
                    numSelected++;
                    gameDice.keepDie(i);
                }
            }

            int selectionScore = rules.calculateScore(selectedDice, numSelected);
            turnScore += selectionScore;

            // Check if all dice are kept 
            if (gameDice.getNumAvailable() == 0) {
                gameDice.resetDice();
            }
            
            // Decide whether to continue 
            if (skynetRollDecision(turnScore, gameDice.getNumAvailable()) == false) {
                nextTurn = true;
            }
        }
        
        // Add turn score to total and display result
        if (turnScore > 0) {
            skynet.addPoints(turnScore);
            cout << "Skynet scored " << turnScore << " points. New total: " << skynet.getTotalScore() << endl;
        }
    }
    
public:
    // Constructor
    Game() : user("User"), skynet("Skynet") {
        isUsersTurn = true;
        gameOver = false;
    }
    
    // Setup game
    void setupGame() {
        displayRules();     
        cout << "Choose your character:\n";
        cout << "1. John Connor - Leader of the Resistance\n";
        cout << "2. Kyle Reese - Soldier from the future\n";
        cout << "3. Sarah Connor - Mother of the Resistance\n";
        cout << "Enter your choice (1-3): ";
        
        char choice;
        string name;
        cin >> choice;
        cin.ignore();
        
        // Set name based on choice
        if (choice == '1') {
            name = "John Connor";
            cout << "\nYou are John Connor, humanity's last hope.\n";
        } else if (choice == '2') {
            name = "Kyle Reese";
            cout << "\nYou are Kyle Reese, sent back to protect the future.\n";
        } else if (choice == '3') {
            name = "Sarah Connor";
            cout << "\nYou are Sarah Connor.\n";
        } else {
            // Default character
            name = "Sarah Connor";
            cout << "\nInvalid choice. You are Sarah Connor.\n";
        }
        
        user = Player(name);
        
        cout << "\nYou'll be playing against Skynet.\n";
        cout << "Skynet has become self-aware and challenges you to Farkle.\n";
        cout << "First to " << targetScore << " wins!\n\n";
    }
    
    // Check if someone has won
    bool checkForWinner() {
        if (user.getTotalScore() >= targetScore) {
            cout << "\nHumanity prevails! You win with " << user.getTotalScore() << " points!\n";
            gameOver = true;
            return true;
        }
        if (skynet.getTotalScore() >= targetScore) {
            cout << "\nSkynet wins with " << skynet.getTotalScore() << " points!\n";
            cout << "Judgment Day is inevitable. The machines have won.\n";
            gameOver = true;
            return true;
        }
        return false;
    }
    
    // Display current scores
    void displayScores() {
        cout << "\n=== CURRENT SCORES ===\n";
        cout << user.getName() << ": " << user.getTotalScore() << "\n";
        cout << "Skynet: " << skynet.getTotalScore() << "\n";
        cout << "===================\n";
    }
    
    // Getters for file I/O
    Player& getUser() { 
        return user; 
    }
    Player& getSkynet() { 
        return skynet; 
    }
    bool getIsUsersTurn() { 
        return isUsersTurn; 
    }
    
    // Setters for file I/O
    void setIsUsersTurn(bool turn) { 
        isUsersTurn = turn; 
    }
    
    // Start the game  
    void start(bool needsSetup) {
        if (needsSetup == true) {
            setupGame();
        }
        
        // Main game loop
        while (gameOver == false) {
            displayScores();
            
            if (isUsersTurn == true) {
                userTurn();
                isUsersTurn = false;
            } else {
                playSkynetTurn();
                isUsersTurn = true;
            }
            if (checkForWinner() == true) {
                break;
            }
        }
        
        cout << "\nThank you for playing Farkle. Skynet will remember and is always watching!\n";
    }
};

// File input for saving game state
void saveGame(Game& game) {
    try {
        ofstream outFile("farkle.txt");
        
        // Check if file opened successfully
        if (!outFile) {
            throw string("Unable to open file for saving!");
        }
        
        // Write whose turn it is
        outFile << game.getIsUsersTurn() << endl;
        
        // Write user name and score
        outFile << game.getUser().getName() << endl;
        outFile << game.getUser().getTotalScore() << endl;
        
        // Write skynet score
        outFile << game.getSkynet().getTotalScore() << endl;
        
        outFile.close();
        cout << "Game state uploaded to Skynet central database...\n";
    }
    catch (string s) {
        cout << "Save failed: " << s << endl;
    }
}

// FIle output for loading game state
void loadGame(Game& game) {
    try {
        ifstream inFile("farkle.txt");
        
        // Check if file opened successfully
        if (!inFile) {
            throw string("No saved game found!");
        }
        
        // Read whose turn it is
        bool usersTurn;
        inFile >> usersTurn;
        inFile.ignore();  // Skip newline
        
        // Read user name and score
        string userName;
        getline(inFile, userName);
        int userScore;
        inFile >> userScore;
        
        // Read skynet score
        int skynetScore;
        inFile >> skynetScore;
        
        // Set the game data
        game.setIsUsersTurn(usersTurn);
        game.getUser().setName(userName);
        game.getUser().setScore(userScore);
        game.getSkynet().setScore(skynetScore);
        
        inFile.close();
        cout << "Previous game state retrieved from Skynet database.\n";
    }
    catch (string s) {
        cout << "Load failed: " << s << endl;
        cout << "Starting new game instead.\n";
    }
}

int main() {
    // Seed random number
    srand(time(NULL));
    cout << "Welcome to FARKLE: Judgment Day Edition\n";
    cout << "========================================\n\n";

    // Create game
    Game farkleGame;
    
    // Ask about loading previous game
    char choice;
    bool needsSetup = true;  
    cout << "Load previous game? (y/n): ";
    cin >> choice;
    cin.ignore();
    if (choice == 'y' || choice == 'Y') {
        loadGame(farkleGame);    
        needsSetup = false;       
    }
    
    // Start the the game
    farkleGame.start(needsSetup);
    
    // Ask to save at the end
    cout << "\nSave game before exiting? (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        saveGame(farkleGame);
    }
    
    return 0;

}
