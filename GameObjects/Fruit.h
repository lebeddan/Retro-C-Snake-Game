/**
 * This is class that represent fruit.
 */

#ifndef TIC_TAC_TOE_1_FRUIT_H
#define TIC_TAC_TOE_1_FRUIT_H

#include <iostream>
#include "../Data/Data.h"

class Fruit {
public:
    const char fruit = 'F';

    Fruit() : posX(0), posY(0){}

    /**
     * Return X coord of fruit
     */
    int getPosX() const;
    /**
     * Return Y coord of fruit
     */
    int getPosY() const;
    /**
     * Set X coord of fruit
     */
    void setPosX(int x);
    /**
     * Set Y coord of fruit
     */
    void setPosY(int y);

private:
    int posX, posY;
};
#endif //TIC_TAC_TOE_1_FRUIT_H