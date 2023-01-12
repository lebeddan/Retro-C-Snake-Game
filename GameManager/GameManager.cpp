#include "GameManager.h"

int GameManager::getScore() const
{
    return this->score;
}

int GameManager::isOver() const
{
    return this->gameOver;
}

void GameManager::resetScore()
{
    this->score = 0;
}

void GameManager::setGameOver(bool _gameOver)
{
    this->gameOver = _gameOver;
}

void GameManager::increaseScore()
{
    this->score += this->points;
}

void GameManager::setNewFruitPosition(Fruit* f)
{
    f->setPosX(rand() % WIDTH);
    f->setPosY(rand() % HEIGHT);
}