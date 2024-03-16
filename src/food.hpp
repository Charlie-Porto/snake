#ifndef food_hpp
#define food_hpp

#include <vector>
#include "constants.cpp"
#include "../include/randomness_functions.cpp"

namespace pce {
const int GRID_SIZE = pce::grid_size; // same size as snake node
const std::pair<int, int> FOOD_START_POSITION = std::make_pair(0, 0);
                                                          
const int FOOD_WIDTH = int(GRID_SIZE/2);
const std::vector<int> FOOD_COLOR = {200, 0, 100, 255};

class Food
{
public:
  Food()
    : sprite_(SDL_Rect{.h = FOOD_WIDTH,
                       .w = FOOD_WIDTH, 
                       .x = FOOD_START_POSITION.first, 
                       .y = FOOD_START_POSITION.second})
  {
    updatePosition();
  }

  void draw(SDL_Renderer* renderer)
  {
    // std::cout << "FOOD X: " << sprite_.x << '\n';
    // std::cout << "FOOD Y: " << sprite_.y << '\n';
    SDL_SetRenderDrawColor(renderer, FOOD_COLOR[0], FOOD_COLOR[1], FOOD_COLOR[2], FOOD_COLOR[3]);
    SDL_RenderFillRect(renderer, &sprite_);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 250);
  }

  // void updatePosition(std::vector<std::pair<int, int>> snake_node_positions)
  void updatePosition()
  {
    // x_ = mod_rand(pce::screen_x / GRID_SIZE) * GRID_SIZE;
    // y_ = mod_rand(pce::screen_y / GRID_SIZE) * GRID_SIZE;
    // sprite_.x = mod_rand(pce::screen_x / GRID_SIZE) * GRID_SIZE + (int((GRID_SIZE - FOOD_WIDTH)/2));
    // sprite_.y = mod_rand(pce::screen_y / GRID_SIZE) * GRID_SIZE + (int((GRID_SIZE - FOOD_WIDTH)/2));
    do 
    {
      sprite_.x = mod_rand(pce::screen_x / GRID_SIZE) * GRID_SIZE;
    } while (sprite_.x % GRID_SIZE != 0);
    do 
    {
      sprite_.y = mod_rand(pce::screen_y / GRID_SIZE) * GRID_SIZE;
    } while (sprite_.y % GRID_SIZE != 0);
  }

  // std::pair<int, int> coordinates() const { return std::make_pair(x_, y_); }
  std::pair<int, int> coordinates() const { return std::make_pair(sprite_.x, sprite_.y); }
private:
  SDL_Rect sprite_;
  // int x_ = 0;
  // int y_ = 0;

};

}

#endif  /* food_hpp */