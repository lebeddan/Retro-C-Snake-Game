/**
 * This is class that manage game.
 */

#ifndef TIC_TAC_TOE_1_GAMEMANAGER_H
#define TIC_TAC_TOE_1_GAMEMANAGER_H
#include <iostream>
#include "../GameObjects/Fruit.h"
#include "../GameObjects/Snake.h"

class GameManager {
public:
    GameManager() : score(0), gameOver(false){}

    /**
    *  Return current score
    */
    int getScore() const;
    /**
    *  Return boolean if game is over
    */
    int isOver() const;

    /**
    *  Reset current score to zero
    */
    void resetScore();
    /**
    *  Set gameover to value
    */
    void setGameOver(bool _gameOver);
    /**
    *  Increase score
    */
    void increaseScore();
    /**
    *  Set random position for the fruit
    */
    void setNewFruitPosition(Fruit* f);

private:
    int score;
    bool gameOver;
    const int points = 10;
};
#endif //TIC_TAC_TOE_1_GAMEMANAGER_H