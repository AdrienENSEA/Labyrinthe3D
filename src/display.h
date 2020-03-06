/**
* @file     display.h
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
#include <math.h>
#include <SDL2/SDL.h>
#include "functions.h"

    /*********************************************************************************/
                                /* Definition basic SDL elements */
    /*********************************************************************************/

SDL_Window *window_game = NULL, *window_map = NULL;                 //Define the 2 windows
SDL_Renderer *renderer_game = NULL, *renderer_map = NULL;           //Define the 2 renderer associated with the corresponding windows
int statut = EXIT_FAILURE;                                          //Status for failure SDL functions



    /*********************************************************************************/
                                    /* Definition color */
    /*********************************************************************************/

SDL_Color white = {255, 255, 255, 255};
SDL_Color black = {0, 0, 0, 255};
SDL_Color blue = {0, 0, 255, 255};
SDL_Color orange = {255, 127, 40, 255};
SDL_Color purple = {255, 0, 255, 255};
SDL_Color red = {255, 0, 0, 255};




    /*********************************************************************************/
                                /* SDL main */
    /*********************************************************************************/

int display_main();




    /*********************************************************************************/
                                /* Basic SDL functions */
    /*********************************************************************************/

void SDL_initialisation();

void SDL_end();

void SDL_update_windows();

SDL_Color test_color(color, brightness);

int setWindowColor(SDL_Renderer*, SDL_Color);




    /*********************************************************************************/
                                /* SDL functions map window */
    /*********************************************************************************/

void show_world(worldmap);

void show_pos(position);

void show_dir(position, direction);

void show_vision(position, direction);

void show_hit(position, direction, double, color);



    /*********************************************************************************/
                                /* SDL functions game window */
    /*********************************************************************************/

void display_game(position, direction, worldmap);




    /*********************************************************************************/
                                        /* Basic figures */
    /*********************************************************************************/

void drawcircle(SDL_Renderer*, int, int, int, int, int);

void drawfillcircle(SDL_Renderer*, int, int, int, int, int);

void drawline(SDL_Renderer*, int, int, int, int, int, int);

void drawrectangle(SDL_Renderer*, int, int, int, int, int, int);

void drawfillrectangle(SDL_Renderer*, int, int, int, int, int, int);

void drawcross(SDL_Renderer*, int, int, int, int);
