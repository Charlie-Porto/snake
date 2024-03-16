#ifndef player1_hpp
#define player1_hpp

#include "tools/virtual_keyboard.hpp"
#include "snake_node.hpp"
#include "food.hpp"
#include "constants.cpp"
#include <utility>

namespace pce {

const std::pair<int, int> START_POSITION = std::make_pair(int(pce::grid_size),
                                                          int(pce::grid_size));
const std::pair<int, int> START_DIRECTION = std::make_pair(1, 0);
const double INITIAL_TIMED_MOVEMENTS_PER_SECOND = 4;
const double TIME_PRESS_BUTTON_UNTIL_MOVE_FAST_SECONDS = 0.1;
const double SECONDS_BETWEEN_INCREASE_MOVEMENT_FREQUENCY = 15;
const std::vector<int> SNAKE_NODE_COLOR = {50, 230, 100, 255};

typedef std::vector<std::pair<int, int>> CoordinateList;

class Player1
{ 
public:
  Player1()
    : vk_(VirtualKeyboard{})
    , movement_vector_(START_DIRECTION)
    , position_vector_(START_POSITION)
    , node_(SnakeNode{START_POSITION,
                      std::make_shared<CoordinateList>()})
    , food_(Food{})
    , alive_(true)
    , movement_interval_(double(1)/INITIAL_TIMED_MOVEMENTS_PER_SECOND)
    , time_last_moved_(0)
    , auto_moves_per_second_(INITIAL_TIMED_MOVEMENTS_PER_SECOND)
    , time_last_movement_frequency_updated_(0)
    , holding_key_to_move_fast_(false)
    , time_(0)
    , button_press_time_({})
    , color_(SNAKE_NODE_COLOR)
  {
    set_srand();
  }


  void updateMovementVector(const std::vector<SDL_Event>& events)
  {
    holding_key_to_move_fast_ = false;
    const ButtonInfo& button_info = vk_.checkButtons(events);
    const std::vector<KeyboardButton> ordered_button_presses = vk_.getOrderOfKeypressEvents();
    // std::vector<KeyboardButton> pressed_for_speed{};
    // holding_key_to_move_fast_ = false;
    // for (auto const& [button, pressed] : button_info)
    // {
    //   if (button_press_time_.find(button) != button_press_time_.end()
    //    && button_press_time_.at(button).first
    //    && time_ - button_press_time_.at(button).second > TIME_PRESS_BUTTON_UNTIL_MOVE_FAST_SECONDS
    //    && pressed)
    //   {
    //     holding_key_to_move_fast_ = true;
    //     // std::cout << "BUTTON PRESSED TO GO FAST: " << button << '\n';
    //     pressed_for_speed.push_back(button);
    //   }
    //   else if (button_press_time_.find(button) != button_press_time_.end()
    //         && button_press_time_.at(button).first
    //         && pressed)
    //   {
    //     continue;
    //   }
    //   else if (button_press_time_.find(button) != button_press_time_.end()
    //         && !button_press_time_.at(button).first
    //         && pressed)
    //   {
    //     button_press_time_[button] = std::make_pair(true, time_);
    //   }
    //   else
    //     button_press_time_[button] = std::make_pair(false, 0);
    // }
    if (ordered_button_presses.empty())
      return;
   
    KeyboardButton selected_button = KeyboardButton::R;
    switch (ordered_button_presses.back())
    {
      case KeyboardButton::R:
        movement_vector_ = std::make_pair(1, 0);
        break;
      case KeyboardButton::L:
        movement_vector_ = std::make_pair(-1, 0);
        selected_button = KeyboardButton::L;
        break;
      case KeyboardButton::UP:
        movement_vector_ = std::make_pair(0, -1);
        selected_button = KeyboardButton::UP;
        break;
      case KeyboardButton::DOWN:
        movement_vector_ = std::make_pair(0, 1);
        selected_button = KeyboardButton::DOWN;
        break;
    }
    holding_key_to_move_fast_ = true;
    updatePosition();
  }

  void updatePosition()
  {
    position_vector_.first += movement_vector_.first * SNAKE_NODE_WIDTH;
    if (position_vector_.first < 0)
      position_vector_.first = (pce::screen_x - (pce::screen_x % GRID_SIZE)) - GRID_SIZE;
    else if (position_vector_.first >= pce::screen_x)
      position_vector_.first = 0;
    position_vector_.second += movement_vector_.second * SNAKE_NODE_WIDTH;
    if (position_vector_.second < 0)
      position_vector_.second = pce::screen_y - (pce::screen_y % GRID_SIZE) - GRID_SIZE;
    else if (position_vector_.second >= pce::screen_y)
      position_vector_.second = 0;
    node_.resetNodePositions();

    // std::cout << "NODE X: " << position_vector_.first << '\n';
    // std::cout << "NODE Y: " << position_vector_.second << '\n';
    node_.updateCoordinates(position_vector_);
  }

  void update( const double time
             , SDL_Renderer* renderer
             , const std::vector<SDL_Event>& events)
  {
    time_ = time;
    updateMovementVector(events);
    const double time_of_next_move = time_last_moved_ + movement_interval_;
    if (time > time_of_next_move && !holding_key_to_move_fast_)
    {
      time_last_moved_ = time;
      updatePosition();
    }
    if (time > time_last_movement_frequency_updated_ + SECONDS_BETWEEN_INCREASE_MOVEMENT_FREQUENCY)
    {
      ++auto_moves_per_second_;
      movement_interval_ = double(1)/auto_moves_per_second_;
      time_last_movement_frequency_updated_ = time;
    }

    bool snake_just_ate = node_.checkForFoodCollision(food_.coordinates());
    if (snake_just_ate)
    {
      std::cout << "SNAKE ATE" << '\n';
      food_.updatePosition();
      color_ = get_rand_color();
      node_.createChild();
    }

    if (node_.collidedWithNode())
    {
      std::cout << "Collided with a node!!!! exiting" << '\n';
      alive_ = false;
    }

    // if (position_vector_.first < 0 || position_vector_.first >= pce::screen_x)
    //   alive_ = false;
    // if (position_vector_.second < 0 || position_vector_.second >= pce::screen_y)
    //   alive_ = false;

    node_.draw(renderer, color_);
    // std::cout << "NODE X: " << position_vector_.first << '\n';
    // std::cout << "NODE Y: " << position_vector_.second << '\n';
    food_.draw(renderer);
  }

  bool alive() const { return alive_; }

private:
  VirtualKeyboard vk_;
  std::pair<int, int> movement_vector_;
  std::pair<int, int> position_vector_;
  SnakeNode node_;
  Food food_;
  bool alive_;

  // For Movement
  double movement_interval_;
  double time_last_moved_;
  double auto_moves_per_second_;
  double time_last_movement_frequency_updated_;
  bool holding_key_to_move_fast_;
  double time_;
  std::unordered_map<KeyboardButton, std::pair<bool, double>> button_press_time_;

  std::vector<int> color_;
};

}

#endif /* player1_hpp */