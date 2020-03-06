/**
* @file     functions.h
* @author   Sermet Adrien
* @version  1.0
* @date     11/09/2018
* @brief :  There is just the display_main() function in the main.c file.
* I decided to divide the project in 2 files :
*    - fonctions.c : for the functions computing abstract things as the distance, the color of the wall
*    - display.c : for all the functions using the SDL2 library
**/

#include <stdio.h>
#include <stdlib.h>
#include <math.h> // For the use of functions cos() and sin()


    /*********************************************************************************/
                                /* Global variables */
    /*********************************************************************************/


#define MAP_WIDTH 30                    /// @def MAP_WIDTH Number of squares for the x-axe
#define MAP_HEIGHT 24                   /// @def MAP_HEIGHT Number of squares for the y-axe

#define WALLSIZE 32                     /// @def Size in pixels of a side of the squares in game
#define WALLSIZE_MAP 32                 /// @def Size in pixels of a side of the squares in the map

#define DECAL_MAP_WIDTH 0               /// @def Width's shift (number of pixels) of the map
#define DECAL_MAP_HEIGHT 0              /// @def Height's shift (number of pixels) of the map

#define CAMERA_WIDTH 256                /// @def Width of the camera
#define CAMERA_HEIGHT 960               /// @def Height of the camera
#define DISTANCE_CAMERA 320             /// @def Distance character / camera

#define WINDOW_MAP_WIDTH 1280           /// @def Width (number of pixels) of the map's window
#define WINDOW_MAP_HEIGHT 960           /// @def Height (number of pixels) of the map's window

#define WINDOW_GAME_WIDTH 1280          /// @def Width (number of pixels) of the map's window
#define WINDOW_GAME_HEIGHT 960          /// @def Height (number of pixels) of the map's window

#define SPEED 3                         /// @def Speed of your character
#define SPEED_ROT 1                     /// @def Speed of rotation of your character

#define true 1
#define false 0



    /*********************************************************************************/
                                /* Definition structures*/
    /*********************************************************************************/


typedef int color;

typedef int brightness; /// In percentage

typedef color worldmap[MAP_WIDTH][MAP_HEIGHT]; ///The map is composed with int-variables, the corresponding colors are in test_color, in display.c

typedef int bool;

typedef double angle;

typedef struct position {
/**
 * @struct position
 * @brief coordinates of a vector on x-axe and y-axe
 */
	double x;
	double y;
} position;

typedef struct direction {
/**
 * @struct direction
 * @brief coordinates of a vector on x-axe and y-axe
 */
	double x;
	double y;
} direction;

typedef struct dist_color_brightness {
/**
 * @struct dist_color_brightness
 * @brief Contains the distance, the color and the brightness of a wall hit
 */
	double distance;
	color color;
	brightness brightness;
} dist_color_brightness;





    /*********************************************************************************/
                                /* Creation environement */
    /*********************************************************************************/

position create_position(worldmap);

void create_map(worldmap);





    /*********************************************************************************/
                                /* Showing environment */
    /*********************************************************************************/

void show_world_text(position, worldmap);






    /*********************************************************************************/
                                        /* Events */
    /*********************************************************************************/

void arrow_up(position*, direction* dir, worldmap map);

void arrow_down(position*, direction* dir, worldmap map);

void arrow_right(direction* dir);

void arrow_left(direction* dir);

void rotation(direction*, angle);




direction rot(double, double, angle);

double cos_vector(direction, direction);





    /*********************************************************************************/
                                        /* Research wall */
    /*********************************************************************************/

color tangent_wall_h(double, int, direction, worldmap);

color tangent_wall_v(int, double, direction, worldmap);

dist_color_brightness dda_h(position, direction, worldmap);

dist_color_brightness dda_v(position, direction, worldmap);

dist_color_brightness dda(position, direction, worldmap);

bool test_hit(position, direction, worldmap);

direction f_dir_hit(direction, int);
