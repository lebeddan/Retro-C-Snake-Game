#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <conio.h>
#include <random>

#include "GameObjects/Snake.h"
#include "GameObjects/Fruit.h"
#include "GameManager/DirectonEnum.h"
#include "Data/Data.h"
#include "GameManager/GameManager.h"

Snake *s;
Fruit *f;
GameManager *gm;
DirectonEnum dir;
int tailX[100];
int tailY[100];

std::mutex mutex;

/**
 * Function for generate random int number
 */
int int_rad(int min, int max)
{
    static std::mt19937 mt{ std::random_device{}() };
    static std::uniform_real_distribution<> dist(min, max);
    return dist(mt);
}

/**
 * Initialization function
 */
void Init()
{
    // Init game objects
    s = new Snake();
    f = new Fruit();

    // Init game manager
    gm = new GameManager();

    dir = DirectonEnum::STOP;

    // Set snake position on center of the map
    s->setPosX(WIDTH / 2);
    s->setPosY(HEIGHT / 2);

    // Set fruit random position on the map
    gm->setNewFruitPosition(f);
}
/**
 * Function for render game
 */
void Draw()
{
    std::unique_lock<std::mutex> lg(mutex);
    system("CLS");
    // Draw top raw of map
    for (int row = 0; row < WIDTH + 2; row++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;

    // Draw walls of map
    for (int col = 0; col < HEIGHT; col++) {

        for (int row = 0; row < WIDTH; row++)
        {
            if (row == 0)
            {
                std::cout << "|";
            }
            if (col == s->getPosY() && row == s->getPosX())
            {
                std::cout << s->head; // Draw head
            }
            else if (col == f->getPosY() && row == f->getPosX())
            {
                std::cout << f->fruit; // Draw fruit
            }
            else // Draw tail
            {
                bool print = false;
                for (int i = 0; i < s->getLenght(); i++)
                {
                    if (row == tailX[i] && col == tailY[i])
                    {
                        std::cout << s->tail;
                        print = true;
                    }
                }
                if (!print)
                {
                    std::cout << " ";
                }
            }

            if (row == WIDTH - 1)
            {
                std::cout << "|";
            }
        }
        std::cout << std::endl;
    }

    // Draw bottom raw of map
    for (int row = 0; row < WIDTH + 2; row++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;
    std::cout << "SCORE: " << gm->getScore() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
/**
 * Function to handle user input
 */
void Input()
{
    // Check if any key was pressed
    if (kbhit())
    {
        switch (_getch()) // Get pressed key
        {
            case 'a':
                dir = DirectonEnum::LEFT;
                break;
            case 'd':
                dir = DirectonEnum::RIGHT;
                break;
            case 'w':
                dir = DirectonEnum::UP;
                break;
            case 's':
                dir = DirectonEnum::DOWN;
                break;
            case 'q':
                gm->setGameOver(true);
                break;
            case 'p':
                system("PAUSE"); // Pause the game
                break;
            default:
                break;
        }
    }
}
/**
 * Function that's manage game logic
 */
void Logic()
{
    // Get coords of first tail
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prevX2, prevY2;
    // Set first segment of the tail to follow the head
    tailX[0] = s->getPosX();
    tailY[0] = s->getPosY();

    std::unique_lock<std::mutex> lg(mutex);
    for (int i = 1; i < s->getLenght(); i++)
    {
        prevX2 = tailX[i];
        prevY2 = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prevX2;
        prevY = prevY2;
    }

    // Set direction
    switch (dir)
    {
        case DirectonEnum::LEFT:
            s->setPosX(s->getPosX() - 1);
            break;
        case DirectonEnum::RIGHT:
            s->setPosX(s->getPosX() + 1);
            break;
        case DirectonEnum::UP:
            s->setPosY(s->getPosY() - 1);
            break;
        case DirectonEnum::DOWN:
            s->setPosY(s->getPosY() + 1);
            break;
        default:
            break;
    }

/*    // Collision with grid -> game over
    if (s->getPosX() > WIDTH || s->getPosX() < 0 || s->getPosY() > HEIGHT || s->getPosY() < 0)
    {
        gm->setGameOver(true);
    }*/

    // Teleport the snake through walls
    if (s->getPosX() >= WIDTH) s->setPosX(0);
    else if (s->getPosX() < 0) s->setPosX(WIDTH - 1);

    if (s->getPosY() >= HEIGHT) s->setPosY(0);
    else if (s->getPosY() < 0) s->setPosY(HEIGHT - 1);

    // Collision with tail -> game over
    for (int tail_seg = 0; tail_seg < s->getLenght(); tail_seg++)
    {
        if (tailX[tail_seg] == s->getPosX() && tailY[tail_seg] == s->getPosY())
        {
            gm->setGameOver(true);
        }
    }
    // Snake ate a Fruit -> increase length of snake
    if (s->getPosX() == f->getPosX() && s->getPosY() == f->getPosY())
    {
        // Increase score, increase length of the snake and set new pos of the fruit
        gm->increaseScore();
        f->setPosX(int_rad(0, WIDTH) % WIDTH);
        f->setPosY(int_rad(0, HEIGHT) % HEIGHT);
        s->increaseLength();
    }
}
/**
 * Function to reset game objects
 */
void Reset()
{
    dir = DirectonEnum::STOP;

    gm->setGameOver(false);

    gm->resetScore();
    s->resetLength();

    // Set snake position on center of the map
    s->setPosX(WIDTH / 2);
    s->setPosY(HEIGHT / 2);

    // Set fruit random position on the map
    gm->setNewFruitPosition(f);
}
void free_memory()
{
    delete s;
    delete f;
    delete gm;
}

int main()
{
    //Game with one thread
/*    Init();
    while(!gm->isOver()) // Game loop
    {
        Draw();
        Input();
        Logic();

    }*/

    Init();
    char again = 'n';
    do
    {
        if (again == 'y')
        {
            Reset();
        }
        else
        {
            std::cout << "Welcome to the retro C++ Snake Game" << std::endl << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        }

        // Sleep for 1 second, then start the game
        std::this_thread::sleep_for(std::chrono::seconds(1));

        while(!gm->isOver())
        {
            std::thread draw_thread(Draw);
            draw_thread.join();
            std::thread input_thread(Input);
            input_thread.join();
            std::thread logic_thread(Logic);
            logic_thread.join();
        }

        // Play again?
        std::cout << std::endl << "Current Score: " <<  gm->getScore()  << std::endl;;
        std::cout << "Want to play again? [y/n]: ";
        std::cin >> again;
    } while (again == 'y');

    std::cout << std::endl << "Thanks for playing the C++ Snake Game!" << std::endl;
    std::cout << "Goodbye!" << std::endl << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));

    free_memory();
    return EXIT_SUCCESS;
}