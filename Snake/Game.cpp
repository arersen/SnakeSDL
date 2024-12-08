#include "Game.h"
Game::Game(Window* pWindow) {
	window = pWindow;
	pos = { 16, 12 };
	direction = { 1, 0 };
	food = { 1, 1 };
	color = {0, 255, 0, 255};
	food_color = { 255, 255, 255, 255 };
	score = 1;
	size = 25;
	tick_period_ms = 125;
	timer = clock();
}

void Game::generate_food() {
	srand(time(NULL));

	while (true) {
		food.x = rand() % 32;
		food.y = rand() % 24;

		if (food.x != pos.x && food.y != pos.y) break;
	}
}

void Game::draw_food() {
	SDL_Rect rect = { food.x * size, food.y * size, size, size };

	SDL_SetRenderDrawColor(window->renderer, food_color.red, food_color.green, food_color.blue, food_color.alpha);
	SDL_RenderFillRect(window->renderer, &rect);

}
void Game::draw_snake() {
	SDL_Rect rect = { pos.x * size, pos.y * size, size, size };
	
	SDL_SetRenderDrawColor(window->renderer, color.red, color.green, color.blue, color.alpha);
	SDL_RenderFillRect(window->renderer, &rect);

	
	for (int i = 0; i < score - 1; i++) {
		rect = { tail[i].x * size, tail[i].y * size, size, size };
		SDL_RenderFillRect(window->renderer, &rect);
	}

}


void Game::draw() {
	SDL_SetRenderDrawColor(window->renderer, 0, 0, 127, 255);
	SDL_RenderClear(window->renderer);

	draw_snake();
	draw_food();

	SDL_RenderPresent(window->renderer);
}

void Game::step() {
	tail.insert(tail.begin(), pos);
	pos.x += direction.x;
	pos.y += direction.y;

	if (pos.x == food.x && pos.y == food.y) {
		score++;
		generate_food();
	}

	if (tail.size() > 768) {
		tail.pop_back();
	}
}

void Game::tick() {
	if (clock() > timer + tick_period_ms) {
		step();
		draw();
		
		//std::cout << "Tail size: " << tail.size() << std::endl << "Score: " << score << std::endl;
		timer = clock();
	}
}

void Game::up() {
	if (direction.y != 1) direction = { 0, -1 };
}

void Game::down() {
	if (direction.y != -1) direction = { 0, 1 };
}

void Game::left() {
	if (direction.x != 1) direction = { -1, 0 };
}

void Game::right() {
	if (direction.x != -1) direction = { 1, 0 };
}