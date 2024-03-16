#ifndef virtual_keyboard_hpp
#define virtual_keyboard_hpp

#include <unordered_map>
#include <string>
#include <utility>
#include <iostream>

namespace pce {

enum KeyboardButton
{
   UP
 , DOWN
 , R
 , L
};

typedef std::unordered_map<KeyboardButton, bool> ButtonInfo;

class VirtualKeyboard
{
public:
  VirtualKeyboard()
    : button_states_({
        std::make_pair(UP, false),
        std::make_pair(DOWN, false),
        std::make_pair(R, false),
        std::make_pair(L, false),
      })
    , order_of_events_({})
    , order_of_keypress_events_({})
  {}

  const ButtonInfo& checkButtons(const std::vector<SDL_Event>& events)
  {
    for (auto const& [button, pressed] : button_states_)
    {
      order_of_keypress_events_.push_back(button);
    }
    // std::cout << "[VK] checkButtons" << '\n';;
    order_of_events_.clear();
    order_of_keypress_events_.clear();
    if (events.empty())
    {
      // std::cout << "[VK] (checkButtons) NO EVENTS" << '\n';
    }
    for (auto const& event : events)
    {
      switch (event.type)
      {
      case SDL_KEYDOWN:
        // std::cout << "PRESSED: ";
        switch (event.key.keysym.sym)
        {
          case SDLK_UP:
            std::cout << UP << '\n';
            button_states_.at(UP) = true;
            order_of_events_.push_back(std::make_pair(UP, true));
            order_of_keypress_events_.push_back(UP);
            break;
          case SDLK_DOWN:
            // std::cout << "DOWN" << '\n';
            button_states_.at(DOWN) = true;
            order_of_events_.push_back(std::make_pair(DOWN, true));
            order_of_keypress_events_.push_back(DOWN);
            break;
          case SDLK_LEFT:
            // std::cout << "LEFT" << '\n';
            button_states_.at(L) = true;
            order_of_events_.push_back(std::make_pair(L, true));
            order_of_keypress_events_.push_back(L);
            break;
          case SDLK_RIGHT:
            button_states_.at(R) = true;
            // std::cout << "RIGHT" << '\n';
            order_of_events_.push_back(std::make_pair(R, true));
            order_of_keypress_events_.push_back(R);
            break;
          default:
            break;
        }
        break;
      case SDL_KEYUP:
        // std::cout << "RELEASED: ";
        switch (event.key.keysym.sym)
        {
          case SDLK_UP:
            button_states_.at(UP) = false;
            order_of_events_.push_back(std::make_pair(UP, false));
            // std::cout << UP << '\n';
            break;
          case SDLK_DOWN:
            button_states_.at(DOWN) = false;
            order_of_events_.push_back(std::make_pair(DOWN, false));
            // std::cout << DOWN << '\n';
            break;
          case SDLK_LEFT:
            button_states_.at(L) = false;
            // std::cout << "LEFT" << '\n';
            order_of_events_.push_back(std::make_pair(L, false));
            break;
          case SDLK_RIGHT:
            button_states_.at(R) = false;
            // std::cout << "RIGHT" << '\n';
            order_of_events_.push_back(std::make_pair(R, false));
            break;
          default:
            break;
        }
        break;
      default:
        break;
      }
    }

    // Print Button States
    // std::cout << "[VK] (checkButtons) R: " << button_states_.at(R) << '\n';
    // std::cout << "[VK] (checkButtons) L: " << button_states_.at(L) << '\n';
    // std::cout << "[VK] (checkButtons) D: " << button_states_.at(DOWN) << '\n';
    // std::cout << "[VK] (checkButtons) U: " << button_states_.at(UP) << '\n';

    return button_states_;
  }

  std::vector<KeyboardButton> getOrderOfKeypressEvents() const { return order_of_keypress_events_; }

private:
  ButtonInfo button_states_;
  std::vector<std::pair<KeyboardButton, bool>> order_of_events_;
  std::vector<KeyboardButton> order_of_keypress_events_;

};

} /* namespace pce */

#endif /* virtual_keyboard_hpp */
