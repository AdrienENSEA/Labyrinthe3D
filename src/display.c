/**
* @file     display.c
* @author   Sermet Adrien
* @version  1.0
* @date     11/09/2018
* @brief :  This file contains all the functions which use the SDL functions.
* There are 5 types of function, related to:
*   - the main
*   - the basic SDL functions
*   - the SDL functions for the map window
*   - the SDL functions for the game window
*   - the SDL functions to make basic figures
**/

#include "display.h"


    /*********************************************************************************/
                                /* SDL main */
    /*********************************************************************************/

int display_main(){
/**
 * @brief       The real main of the project
 * @param       None
 * @return      Nothing
 */

    /*********************************************************************************/
                                        /* Variables */
    /*********************************************************************************/

    position pos;
    direction dir = {0.00, 1.00};
    worldmap map;

    int a;

    int tPrecedent = 0, tActuel = 0;
    int n_frame;
    double frame_rate;




    /*********************************************************************************/
        /* Initialisation, creation windows/renderer. */
    /*********************************************************************************/

    SDL_initialisation();

    create_map(map);
    pos = create_position(map);

    show_world(map);
    show_pos(pos);
    show_dir(pos, dir);
    show_vision(pos, dir);
    display_game(pos, dir, map);
    SDL_update_windows();






    /*********************************************************************************/
                                        /* Main */
    /*********************************************************************************/


    SDL_Event event;
    SDL_bool quit = SDL_FALSE;
    SDL_EnableKeyRepeat(10,10);
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    while(!quit)
    {
        SDL_WaitEvent(&event);
		switch(event.type) {
			case SDL_KEYDOWN: // touche enfoncée
                SDL_PumpEvents();
				if(state[SDL_SCANCODE_ESCAPE]) {quit = SDL_TRUE;}
                if(state[SDL_SCANCODE_UP]) {arrow_up(&pos, &dir, map);}
                if(state[SDL_SCANCODE_DOWN]) {arrow_down(&pos, &dir, map);}
                if(state[SDL_SCANCODE_RIGHT]) {arrow_right(&dir);}
                if(state[SDL_SCANCODE_LEFT]) {arrow_left(&dir);}

                a = setWindowColor(renderer_map, black);
                a = setWindowColor(renderer_game, black);
				show_world(map);
				show_pos(pos);
                show_dir(pos, dir);
                show_vision(pos, dir);
                display_game(pos, dir, map);
                SDL_update_windows();
				break;
			case SDL_QUIT: // si on ferme manuellement en mode fenêtre
				quit = SDL_TRUE;
				break;
		}
		n_frame++;
		tActuel = SDL_GetTicks();
        if (tActuel > 1000 + tPrecedent){
            frame_rate = (double)(tActuel - tPrecedent) / n_frame;
            n_frame = 0;
            tPrecedent = tActuel;
            printf("%f \n", frame_rate);
        }
    }







    /*********************************************************************************/
                                        /* End */
    /*********************************************************************************/

    SDL_end();

    return statut;
}



    /*********************************************************************************/
                                /* Basic SDL functions */
    /*********************************************************************************/

int setWindowColor(SDL_Renderer *renderer, SDL_Color color){
/**
 * @brief       Fill the window with the color
 * @param       renderer        renderer (game or map)
 *              color           color to apply
 * @return      a int
 */
    if(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0)
        return -1;
    if(SDL_RenderClear(renderer) < 0)
        return -1;
    return 0;
}

void SDL_initialisation(){
/**
 * @brief       Initialize the renderers and the windows
 *  The dimensions of the windows are defined in functions.h
 * @param       None
 * @return      Nothing
 */
    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        SDL_end();
    }


    window_game = SDL_CreateWindow("Labyrinthe 3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_GAME_WIDTH, WINDOW_GAME_HEIGHT, SDL_WINDOW_SHOWN);
    window_map = SDL_CreateWindow("Map", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_MAP_WIDTH, WINDOW_MAP_HEIGHT, SDL_WINDOW_SHOWN);

    if(NULL == window_game || NULL == window_map)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        SDL_end();
    }

    renderer_game = SDL_CreateRenderer(window_game, -1, SDL_RENDERER_ACCELERATED);
    renderer_map = SDL_CreateRenderer(window_map, -1, SDL_RENDERER_ACCELERATED);

    if(NULL == renderer_game || NULL == renderer_map)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        SDL_end();
    }
}

void SDL_end(){
/**
 * @brief       Close the renderers and the windows
 * @param       None
 * @return      Nothing
 */
    if(0 != SDL_RenderClear(renderer_game) || 0 != SDL_RenderClear(renderer_map))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        SDL_end();
    }

    statut = EXIT_SUCCESS;
    if(NULL != renderer_game)
        SDL_DestroyRenderer(renderer_game);
    if(NULL != renderer_map)
        SDL_DestroyRenderer(renderer_map);
    if(NULL != window_game)
        SDL_DestroyWindow(window_game);
    if(NULL != window_map)
        SDL_DestroyWindow(window_map);
    SDL_Quit();
}

void SDL_update_windows(){
/**
 * @brief       Upadte the windows (map and game)
 * @param       None
 * @return      Nothing
 */
    SDL_RenderPresent(renderer_game);
    SDL_RenderPresent(renderer_map);
}

SDL_Color test_color(color c, brightness b){
/**
 * @brief       Initialize the renderers and the windows
 *  The dimensions of the windows are defined in functions.h
 * @param       c           the color (a int)
 *              b           the brightness (a int) in percentage
 * @return      SDL_color   the SDL_color are defined in display.h
 */
    SDL_Color color;
    switch (c){
        case 0:
            color.r = (int) black.r * b / 100; color.g = (int) black.g * b / 100; color.b = (int) black.b * b / 100; color.a = black.a;
            return color;
        case 1:
            color.r = (int) red.r * b / 100; color.g = (int) red.g * b / 100; color.b = (int) red.b * b / 100; red.a = red.a;
            return color;
        case 2:
            color.r = (int) white.r * b / 100; color.g = (int) white.g * b / 100; color.b = (int) white.b * b / 100; color.a = white.a;
            return color;
        case 3:
            color.r = (int) blue.r * b / 100; color.g = (int) blue.g * b / 100; color.b = (int) blue.b * b / 100; color.a = blue.a;
            return color;
        case 4:
            color.r = (int) orange.r * b / 100; color.g = (int) orange.g * b / 100; color.b = (int) orange.b * b / 100; color.a = orange.a;
            return color;
        case 5:
            color.r = (int) purple.r * b / 100; color.g = (int) purple.g * b / 100; color.b = (int) purple.b * b / 100; color.a = purple.a;
            return color;
    }

}





    /*********************************************************************************/
                                /* SDL functions map window */
    /*********************************************************************************/

void show_world(worldmap map){
/**
 * @brief       Create the map and the squares randomly
 * @details     La distance entre les \a point1 et \a point2 est calculée par l'intermédiaire
 *                  des coordonnées des points. (cf #Point)
 * @param       map         map pointer define in the display_main.c in display.c.
 * @return      Nothing.
 */
    int x = DECAL_MAP_WIDTH, y = DECAL_MAP_HEIGHT, Dx = WALLSIZE_MAP, Dy = WALLSIZE_MAP;
    for (int i = 0; i<MAP_WIDTH; i++){
        for (int j = 0; j<MAP_HEIGHT; j++){
            drawrectangle(renderer_map, x, y, Dx, Dy, map[i][j], 100);
            y += WALLSIZE_MAP;
        }
        x += WALLSIZE_MAP;
        y = DECAL_MAP_HEIGHT;
    }
}

void show_pos(position pos){
/**
 * @brief       Create the map and the squares randomly
 * @details     La distance entre les \a point1 et \a point2 est calculée par l'intermédiaire
 *                  des coordonnées des points. (cf #Point)
 * @param       map         map pointer define in the display_main.c in display.c.
 * @return      Nothing.
 */
    drawcircle(renderer_map, (DECAL_MAP_WIDTH + pos.x) * WALLSIZE_MAP / WALLSIZE, (DECAL_MAP_HEIGHT + pos.y) * WALLSIZE_MAP / WALLSIZE, 4, 2, 100);
}

void show_dir(position pos, direction dir){
/**
 * @brief       Create the map and the squares randomly
 * @details     La distance entre les \a point1 et \a point2 est calculée par l'intermédiaire
 *                  des coordonnées des points. (cf #Point)
 * @param       map         map pointer define in the display_main.c in display.c.
 * @return      Nothing.
 */
    int x1 = (int) ((DECAL_MAP_WIDTH + pos.x) * WALLSIZE_MAP / WALLSIZE), y1 = (int) ((DECAL_MAP_HEIGHT + pos.y) * WALLSIZE_MAP / WALLSIZE);
    int w = (int) (dir.x*100), h = (int) (dir.y*100);
    drawline(renderer_map, x1, y1, x1 + w, y1 + h, 2, 100);
}

void show_vision(position pos, direction dir){
    direction perp;
    double norm_v = sqrt(pow(dir.x, 2) + pow(dir.y, 2));
    int x1, y1, x2, y2;

    perp.x =  -1 * dir.y / norm_v; perp.y = dir.x / norm_v;

    x1 = (int) ((DECAL_MAP_WIDTH + pos.x) * WALLSIZE_MAP / WALLSIZE + dir.x * DISTANCE_CAMERA / norm_v - (CAMERA_WIDTH / 2) * perp.x);
    x2 = (int) ((DECAL_MAP_WIDTH + pos.x) * WALLSIZE_MAP / WALLSIZE + dir.x * DISTANCE_CAMERA / norm_v + (CAMERA_WIDTH / 2) * perp.x);
    y1 = (int) ((DECAL_MAP_HEIGHT + pos.y) * WALLSIZE_MAP / WALLSIZE + dir.y * DISTANCE_CAMERA / norm_v - (CAMERA_WIDTH / 2) * perp.y);
    y2 = (int) ((DECAL_MAP_HEIGHT + pos.y) * WALLSIZE_MAP / WALLSIZE + dir.y * DISTANCE_CAMERA / norm_v + (CAMERA_WIDTH / 2) * perp.y);

    drawline(renderer_map, x1, y1, x2, y2, 2, 100);
    drawline(renderer_map, (DECAL_MAP_WIDTH + pos.x) * WALLSIZE_MAP / WALLSIZE, (DECAL_MAP_HEIGHT + pos.y) * WALLSIZE_MAP / WALLSIZE, x1, y1, 2, 100);
    drawline(renderer_map, (DECAL_MAP_WIDTH + pos.x) * WALLSIZE_MAP / WALLSIZE, (DECAL_MAP_HEIGHT + pos.y) * WALLSIZE_MAP / WALLSIZE, x2, y2, 2, 100);
}

void show_hit(position pos, direction dir_hit, double dist, color c){
        position hit_pos;

        hit_pos.x = (pos.x + dir_hit.x * dist) * WALLSIZE_MAP / WALLSIZE;
        hit_pos.y = (pos.y + dir_hit.y * dist) * WALLSIZE_MAP / WALLSIZE;

        drawcross(renderer_map, hit_pos.x, hit_pos.y, c, 100);
}




    /*********************************************************************************/
                                /* SDL functions game window */
    /*********************************************************************************/

void display_game(position pos, direction dir, worldmap map) {
/**
 * @brief       Create the map and the squares randomly
 * @param       map         map pointer define in the display_main.c in display.c.
 * @return      Nothing.
 */
	/* Initialisation des variables locales */
    int debut_segment;
    int fin_segment;
    int line_height;

    double norm_u;
    position hit_pos;
    position hit_pos_h;
    position hit_pos_v;
    direction perp;
    direction dir_hit;
    dist_color_brightness p;
    dir_hit = f_dir_hit(dir, 1);

    //printf("%f %f\n", dir.x, dir.y);
    for (int j = 1; j<WINDOW_GAME_WIDTH; j++) {
        dir_hit = f_dir_hit(dir, j);
        p = dda(pos, dir_hit, map);
        show_hit(pos, dir_hit, p.distance, p.color);

        line_height = 50 * WINDOW_GAME_HEIGHT / p.distance; //* cos_vector(dir_hit, dir);
        debut_segment = (WINDOW_GAME_HEIGHT - line_height) / 2;
        if (debut_segment < 0){debut_segment = 0;}
        fin_segment = (WINDOW_GAME_HEIGHT + line_height) / 2;
        if (fin_segment >= WINDOW_GAME_HEIGHT){fin_segment = WINDOW_GAME_HEIGHT - 1;}

        drawline(renderer_game, j, debut_segment, j, (int) fin_segment, p.color, p.brightness);
    }
}




    /*********************************************************************************/
                                        /* Basic figures */
    /*********************************************************************************/

void drawcircle(SDL_Renderer *renderer, int x0, int y0, int radius, int a, int b){
/**
 * @brief       Create the map and the squares randomly
 * @details     La distance entre les \a point1 et \a point2 est calculée par l'intermédiaire
 *                  des coordonnées des points. (cf #Point)
 * @param       map         map pointer define in the display_main.c in display.c.
 * @return      Nothing.
 */
    SDL_Point point;
    SDL_Color color = test_color(a, b);
    if(0 != SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        SDL_end();
    }
    int x = radius-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    while (x >= y)
    {
        SDL_RenderDrawPoint(renderer, x0 + x, y0 + y);
        SDL_RenderDrawPoint(renderer, x0 + y, y0 + x);
        SDL_RenderDrawPoint(renderer, x0 + x, y0 + x);
        SDL_RenderDrawPoint(renderer, x0 - y, y0 + x);
        SDL_RenderDrawPoint(renderer, x0 - x, y0 - y);
        SDL_RenderDrawPoint(renderer, x0 - y, y0 - x);
        SDL_RenderDrawPoint(renderer, x0 + y, y0 - x);
        SDL_RenderDrawPoint(renderer, x0 + x, y0 - y);

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }

        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}

void drawfillcircle(SDL_Renderer *renderer, int x0, int y0, int radius, int a, int b){
/**
 * @brief       Create the map and the squares randomly
 * @details     La distance entre les \a point1 et \a point2 est calculée par l'intermédiaire
 *                  des coordonnées des points. (cf #Point)
 * @param       map         map pointer define in the display_main.c in display.c.
 * @return      Nothing.
 */
    for (int i = 0; i<=radius; i++){
        drawcircle(renderer, x0, y0, i, a, b);
    }
}

void drawline(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, int a, int b){
/**
 * @brief       Create the map and the squares randomly
 * @details     La distance entre les \a point1 et \a point2 est calculée par l'intermédiaire
 *                  des coordonnées des points. (cf #Point)
 * @param       map         map pointer define in the display_main.c in display.c.
 * @return      Nothing.
 */
    SDL_Color c = test_color(a, b);
    if(0 != SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        SDL_end();
    }
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void drawrectangle(SDL_Renderer* renderer, int x, int y, int h, int w, int a, int b){
/**
 * @brief       Create the map and the squares randomly
 * @details     La distance entre les \a point1 et \a point2 est calculée par l'intermédiaire
 *                  des coordonnées des points. (cf #Point)
 * @param       map         map pointer define in the display_main.c in display.c.
 * @return      Nothing.
 */
    SDL_Rect rect;
    rect.x = x; rect.y = y; rect.h = h; rect.w = w;
    SDL_Color c = test_color(a, b);
    if(0 != SDL_SetRenderDrawColor(renderer_map, c.r, c.g, c.b, c.a))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        SDL_end();
    }
    SDL_RenderDrawRect(renderer_map, &rect);
}

void drawfillrectangle(SDL_Renderer* renderer, int x, int y, int h, int w, int a, int b){
/**
 * @brief       Create the map and the squares randomly
 * @details     La distance entre les \a point1 et \a point2 est calculée par l'intermédiaire
 *                  des coordonnées des points. (cf #Point)
 * @param       map         map pointer define in the display_main.c in display.c.
 * @return      Nothing.
 */
    for (int i=0;  i<w; i++){
        drawline(renderer, x+i, y, x+i, y+h, a, b);
    }
}

void drawcross(SDL_Renderer *renderer, int x1, int y1, int a, int b){
/**
 * @brief       Create the map and the squares randomly
 * @param       map         map pointer define in the display_main.c in display.c.
 * @return      Nothing.
 */
    drawline(renderer, x1-10, y1-10, x1+10, y1+10, a, b);
    drawline(renderer, x1+10, y1-10, x1-10, y1+10, a, b);
}






//efsefsf
