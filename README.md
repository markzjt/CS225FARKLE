# CS225FARKLE
C++ Terminator Farkle 
An object oriented farkle game for 1 player vs the computer (Skynet). Roll all 6 dice and keep any scoring combinations you choose. Keep rolling remaining dice until you choose to keep your score, or you FARKLE (no scoring combinations).
## UML Class Diagram
```mermaid
classDiagram
    class Person {
        #string name
        +Person(string n)
        +~Person()
        +getName() string
    }
    
    class Player {
        -int totalScore
        +Player(string playerName)
        +getTotalScore() int
        +addPoints(int points)
        +setScore(int score)
        +setName(string n)
    }
    
    class Die {
        -int face
        +Die()
        +rollDie()
        +getFace() int
        +setFace(int newValue)
        +operator<<() friend
    }
    
    class Dice {
        -static const int MAX_DICE = 6
        -Die dice[6]
        -int numAvailable
        +bool keptDice[6]
        +Dice()
        +rollAvailable()
        +keepDie(int i)
        +resetDice()
        +getNumAvailable() int
        +getAllDice() Die*
        +displayDice()
    }
    
    class ScoringRules {
        -hasStraight(int[]) bool
        -hasThreePair(int[]) bool
        -hasSixOfKind(int[]) bool
        -hasTwoTriplets(int[]) bool
        -hasFourAndPair(int[]) bool
        +calculateScore(Die[], int) int
        +isFarkle(Die[], int) bool
    }
    
    class Game {
        -Player user
        -Player skynet
        -Dice gameDice
        -ScoringRules rules
        -bool isUsersTurn
        -const int targetScore = 10000
        -bool gameOver
        -string skynetTaunts[5]
        -skynetRollDecision(int, int) bool
        -displayRules()
        -userTurn()
        -playSkynetTurn()
        +Game()
        +setupGame()
        +checkForWinner() bool
        +displayScores()
        +getUser() Player&
        +getSkynet() Player&
        +getIsUsersTurn() bool
        +setIsUsersTurn(bool)
        +start(bool needsSetup)
    }
    
    Person <|-- Player : inherits
    Game *-- "2" Player : contains
    Game *-- "1" Dice : contains
    Game *-- "1" ScoringRules : contains
    Dice *-- "6" Die : contains
    ScoringRules ..> Die : uses
```
