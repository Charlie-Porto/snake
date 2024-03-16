#ifndef static_variables_cpp
#define static_variables_cpp


/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
to store static consts used in the project
-----------------------------------------------------------------*/

namespace pce {

const char* window_title = "ProjectTemplate";

const int screen_x = 1000;
const int screen_y = 672;

const double meter_to_pixel_ratio = 0.5/8.4;
const double screen_height_meters = double(screen_y) * meter_to_pixel_ratio;
const double screen_width_meters = double(screen_x) * meter_to_pixel_ratio;

const int grid_size = 20;

} /* namespace pce_settings */


#endif /* static_variables_cpp */
