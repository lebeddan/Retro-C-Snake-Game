/**
 * This is class represent a snake
 */
#ifndef TIC_TAC_TOE_1_SNAKE_H
#define TIC_TAC_TOE_1_SNAKE_H

#include <iostream>
#include <vector>

class Snake{
public:
    const char head = 'O';
    const char tail = 'o';

    Snake() : posX(0), posY(0), lenght(0){}

    /**
     * Return X coord
     */
    int getPosX() const;
    /**
     * Return Y coord
     */
    int getPosY() const;
    /**
     * Return length of snake tail
     */
    int getLenght() const;

    /**
     * Set new X coord
     */
    void setPosX(int x);
    /**
     * Set new Y coord
     */
    void setPosY(int y);
    /**
     * Reset length of snake tail to zero
     */
    void resetLength();
    /**
     * Increase length
     */
    void increaseLength();

private:
    int posX, posY, lenght;
};
#endif //TIC_TAC_TOE_1_SNAKE_H