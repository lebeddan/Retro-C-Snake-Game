#include "Snake.h"

int Snake::getLenght() const
{
    return this->lenght;
}

int Snake::getPosX() const
{
    return this->posX;
}

int Snake::getPosY() const
{
    return this->posY;
}

void Snake::setPosX(int x)
{
    this->posX = x;
}

void Snake::setPosY(int y)
{
    this->posY = y;
}

void Snake::increaseLength()
{
    this->lenght += 1;
}

void Snake::resetLength()
{
    this->lenght = 0;
}