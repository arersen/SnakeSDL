#pragma once
#include <SDL.h>
#include <SDL_types.h>

#include <iostream>
#include <vector>
#include <tuple>

class Window
{
	
public:
	Window();
	~Window();
	void SetBackgroundColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
	void AddEvent(uint32_t event, void (*func)(void*), void* args);
	void Poll();
	SDL_Event event;
	SDL_Renderer* renderer;

private:
	SDL_Window* window;
	
	
	std::vector<std::tuple<uint32_t, void(*)(void*), void*>> events;
};

