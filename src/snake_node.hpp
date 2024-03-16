#ifndef snake_node_hpp
#define snake_node_hpp

#include <utility>
#include <memory>
#include <algorithm>

namespace pce {
typedef std::vector<std::pair<int, int>> CoordinateList;
const int SNAKE_NODE_WIDTH = pce::grid_size;
const int SNAKE_NODE_BORDER = 2;
const int SNAKE_NODE_SPRITE_WIDTH = SNAKE_NODE_WIDTH - SNAKE_NODE_BORDER;

class SnakeNode
{
public:
  SnakeNode(std::pair<int, int> coordinates
          , std::shared_ptr<CoordinateList> snake_node_positions)
    : coordinates_(coordinates)
    , nodes_coordinates_(snake_node_positions)
    , node_sprite_(SDL_Rect{.h = SNAKE_NODE_SPRITE_WIDTH, 
                            .w = SNAKE_NODE_SPRITE_WIDTH, 
                            .x = coordinates_.first,
                            .y = coordinates_.second})
    , child_node_(nullptr)
  {}

  void createChild()
  {
    if (child_node_ != nullptr)
    {
      child_node_->createChild();
      return;
    }
    child_node_.reset(new SnakeNode{ coordinates_, nodes_coordinates_ });
  }

  void clearNodePositions()
  {
    nodes_coordinates_.reset(new CoordinateList{});
    // delete nodes_coordinates_;
  }
  void resetNodePositions(std::shared_ptr<CoordinateList> list)
  {
    nodes_coordinates_ = list;
    if (child_node_ != nullptr)
      child_node_->resetNodePositions(list);
  }
  void resetNodePositions()
  {
    // std::cout << "reseting node positions" << '\n';
    nodes_coordinates_.reset(new CoordinateList{});
    resetNodePositions(nodes_coordinates_);
    // delete nodes_coordinates_;
    // nodes_coordinates_ = new CoordinateList;
  }

  bool checkForFoodCollision(std::pair<int, int> food_coordinates)
  {
    if (coordinates_ == food_coordinates)
      return true;
    return false;
  }

  bool collidedWithNode()
  {
    if (nodes_coordinates_ == nullptr)
      return false;
    auto& nodes_coordinates = *nodes_coordinates_;
    std::sort(nodes_coordinates.begin(), nodes_coordinates.end());
    return std::adjacent_find(nodes_coordinates.begin(), nodes_coordinates.end()) != nodes_coordinates.end();
  }

  // std::shared_ptr<CoordinateList> getNodeCoordinates() const
  // CoordinateList* getNodeCoordinates() const
  // {
  //   return nodes_coordinates_;
  // }

  void updateCoordinates(std::pair<int, int> coordinates)
  {
    std::cout << "NEW NODE COORDINATES: " << coordinates.first << ", " << coordinates.second << '\n';
    const auto old_coordinates = coordinates_;
    coordinates_ = coordinates;
    node_sprite_.x = coordinates_.first;
    node_sprite_.y = coordinates_.second;
    nodes_coordinates_->push_back(coordinates_);
    // printCoordinates();
    if (child_node_ != nullptr)
    {
      // std::cout << "UPDATING CHILD COORDINATES" << '\n';
      child_node_->updateCoordinates(old_coordinates);
    }
  }

  void draw(SDL_Renderer* renderer, const std::vector<int>& color)
  {
    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);
    SDL_RenderFillRect(renderer, &node_sprite_);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 250);
    if (child_node_ != nullptr)
      child_node_->draw(renderer, color);
  }


  int use_count() const { return nodes_coordinates_.use_count(); }

private:
  std::pair<int, int> coordinates_;
  std::shared_ptr<std::vector<std::pair<int, int>>> nodes_coordinates_;
  SDL_Rect node_sprite_;
  std::unique_ptr<SnakeNode> child_node_;
};


}

#endif /* snake_node_hpp */