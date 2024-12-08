// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Window.h"
#include "Game.h"

typedef struct {
    Window* snake_window;
    Game* snake;
} Keyhandler_t;

void KEYDOWN(void* args) {
    Keyhandler_t* keyhandler = (Keyhandler_t*)args;

    Window* pWindow = keyhandler->snake_window;
    Game* snake = keyhandler->snake;

    SDL_Keycode key_pressed = pWindow->event.key.keysym.sym;

    switch (key_pressed) {
        case SDLK_UP:
            snake->up();
            break;

        case SDLK_DOWN:
            snake->down();
            break;

        case SDLK_LEFT:
            snake->left();
            break;

        case SDLK_RIGHT:
            snake->right();
            break;

    }
    //std::cout << "Key pressed: " << SDL_GetKeyName(key_pressed) << std::endl;
}
void quit_handler(void* args) {
    bool* pquit = (bool*)args;
    *pquit = true;
}


int main(int argc, char** argv)
{   
    Window snake_window = Window();

    //snake_window.SetBackgroundColor(0, 0, 127, 255);

    bool quit = false;


    
    snake_window.AddEvent(SDL_QUIT, quit_handler, &quit);
    

    Game snake = Game(&snake_window);
    Keyhandler_t keyhandler = { &snake_window, &snake };
    snake_window.AddEvent(SDL_KEYDOWN, KEYDOWN, &keyhandler);
    snake.draw();

    while (!quit) {
        snake.tick();
        snake_window.Poll();
    }

    std::cout << "Hello World!\n";

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
