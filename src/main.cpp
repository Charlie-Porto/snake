#include "core/pceSDL.hpp"
#include "constants.cpp"
#include "player1.hpp"


int main(int argc, const char* argv[]) {

    pce::CoreManager core_manager{
        pce::window_title,
        pce::screen_x,
        pce::screen_y
    };
    
    pce::Player1 player1;

    while (core_manager.Running() && player1.alive()) {
        core_manager.DoCorePreUpdate();
        
        /* do all stuff */
        player1.update(pce::CoreManager::time_,
                       core_manager.getRenderer(),
                       core_manager.getFrameEvents());

        core_manager.DoCorePostUpdate();
    }

    return EXIT_SUCCESS;
}
