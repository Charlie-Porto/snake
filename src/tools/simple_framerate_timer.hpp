#ifndef simple_framerate_timer_hpp
#define simple_framerate_timer_hpp

#include <iostream>


/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
purpose: a simple timer for testing frame rate.
-----------------------------------------------------------------*/

class simple_framerate_timer
{
public:
    simple_framerate_timer()
      : seconds_since_start_(0)
      , loops_this_second_(0)
      , total_loops_(0)
      , avg_loops_per_second_(0)
    {}

    void update_timer(const int updated_seconds_since_start) {
        // std::cout << "[TIMER] updated_seconds_since_start: "  << updated_seconds_since_start << '\n';
        // std::cout << "[TIMER] seconds_since_start_: "  << seconds_since_start_ << '\n';
        if (seconds_since_start_ + 1 > updated_seconds_since_start)
        {
            ++loops_this_second_;
            return;
        }
        seconds_since_start_ = updated_seconds_since_start;
        total_loops_ += loops_this_second_;
        std::cout << "Time: " << seconds_since_start_ << "s" << "      Frame Rate: " << loops_this_second_ << "\n";
        loops_this_second_ = 0;
    }

private:
    int seconds_since_start_;
    int loops_this_second_;
    int total_loops_;
    int avg_loops_per_second_;
};

#endif /* simple_framerate_timer_hpp */
