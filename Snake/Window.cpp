#include "Window.h"


Window::Window() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Не вдалося ініціалізувати SDL: " << SDL_GetError() << std::endl;
    }


    window = SDL_CreateWindow("Snake by awlik", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Не вдалося створити вікно: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Не вдалося створити рендерер: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

}

void Window::SetBackgroundColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
    SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

Window::~Window() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::AddEvent(uint32_t event, void (*func)(void*), void* args) {
    events.push_back(std::make_tuple(event, func, args));
}

void Window::Poll() {
    while (SDL_PollEvent(&event) != 0) {
        for (auto& eventTuple : events) {
            uint32_t eventCode = std::get<0>(eventTuple);

            if (event.type == eventCode) {
                void(*handler)(void*) = std::get<1>(eventTuple);
                void* args = std::get<2>(eventTuple);  
                handler(args);  
            }
        }
    }
}