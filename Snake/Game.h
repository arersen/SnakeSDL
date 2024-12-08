#pragma once
#include "Window.h"
#include <vector>

typedef struct {
	int x, y;
} Pos;


typedef struct {
	uint8_t red, green, blue, alpha;
} Color;
class Game
{
public:
	Game(Window* pWindow);
	void draw_snake();
	void draw_food();
	void draw();
	void step();
	//void check_food();
	void tick();

	void generate_food();

	void up();
	void down();
	void left();
	void right();
private:
	Window* window;
	Pos pos, direction, food;
	std::vector<Pos> tail;
	int score, size;
	Color color, food_color;
	uint32_t tick_period_ms;
	clock_t timer;
	
	

};

