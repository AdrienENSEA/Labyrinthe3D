/**
* @file     functions.c
* @author   Sermet Adrien
* @version  1.0
* @date     11/09/2018
* @brief :  This file contains all the functions which aren't using the SDL functions.
* There are 3 types of function, related to:
*   - the creation of the environment
*   - the management of the events
*   - the research of the wall hit by a vector
**/

#include "functions.h"


    /*********************************************************************************/
                                /* Global variables */
    /*********************************************************************************/

angle theta = 0.05;

bool allowed_hit = true;





    /*********************************************************************************/
                                /* Creation environment */
    /*********************************************************************************/

void create_map(worldmap map){
/**
 * @brief       Create the map and the squares randomly
 * @param       map         map pointer defined in the display_main.c in display.c.
 * @return      Nothing.
 */
    int a;
    for (int i = 0; i<MAP_WIDTH; i++){
        for (int j = 0; j<MAP_HEIGHT; j++){
            if (i==0 || i==MAP_WIDTH-1 || j==0 || j==MAP_HEIGHT-1){map[i][j] = 1;}
            else {
                a = rand() % 30;
                if (a > 3){map[i][j] = 0;}
                else {map[i][j] = a;}
            }
        }
    }
}

position create_position(worldmap map){
/**
 * @brief       Create the position in the middle of the first free square up left
 * @param       map         map pointer defined in the display_main.c in display.c.
 * @return      position    position of the character
 */
    position pos = {(double) WALLSIZE / 2, (double) WALLSIZE / 2};
    for (int i = 0; i<MAP_WIDTH; i++){
        for (int j = 0; j<MAP_HEIGHT; j++){
            if (map[j][i] == 0){
                return pos;
            }
            pos.y += (double) WALLSIZE;
        }
        pos.x += (double) WALLSIZE;
        pos.y = (double) WALLSIZE / 2;
    }
}




    /*********************************************************************************/
                                /* Showing environment */
    /*********************************************************************************/

void show_world_text(position pos, worldmap map){
/**
 * @brief       Show the map in the console
 * @details     the 'X' represents the position of the character, the 0 represent the empty squares and
 *              the other numbers are walls associated with a color defined in the function 'test_color'
 *              in display.c
 * @param       pos         position of the character
 *              map         map pointer defined in the display_main.c in display.c.
 * @return      Nothing.
 */

	/*		Calcul de la case sur laquelle on se trouve		(chaque case fait WALLSIZE de coté) */
	int i = 0, j= 0, a = 0, b = 0;
	while(pos.x >= i){ i += WALLSIZE; }
	a = i / WALLSIZE;
	while(pos.y >= j){ j += WALLSIZE; }
	b = j / WALLSIZE;
	//printf("%d %d", a, b);

	/*		Montre la map et notre position			*/
	printf("/---------------/");
	printf("\n");

	for (i = 0; i < MAP_WIDTH; i++){
		printf("|");
		for (j = 0; j < MAP_HEIGHT; j++){
			if (i == b-1 && j == a-1){ printf("X|"); }
			else { printf("%d|", map[i][j]); }
		}
		printf("\n");
	}
	printf("/---------------/");
	printf("\n \n");
}





    /*********************************************************************************/
                                        /* Events */
    /*********************************************************************************/

void arrow_up(position* pos, direction* dir, worldmap map){
/**
 * @brief       Increase the position of the direction when the arrow up is pushed
 * @param       pos*        pointer of the position of the character
 *              dir*        pointer of the direction of the character
 *              map         map pointer defined in the display_main.c in display.c.
 * @return      Nothing.
 */
    position pos1 = {pos->x, pos->y};
    direction dir1 = {dir->x, dir->y};
    if(!test_hit(pos1, dir1, map)){
        pos->x += dir->x * SPEED;
        pos->y += dir->y * SPEED;
    }
}

void arrow_down(position *pos, direction* dir, worldmap map){
/**
 * @brief       Decrease the position of the direction when the arrow up is pushed
 * @param       pos*        pointer of the position of the character
 *              dir*        pointer of the direction of the character
 *              map         map pointer defined in the display_main.c in display.c.
 * @return      Nothing.
 */
    position pos1 = {pos->x, pos->y};
    direction neg_dir = {-1*dir->x, -1*dir->y};
    if(!test_hit(pos1, neg_dir, map)){
        pos->x -= dir->x * SPEED;
        pos->y -= dir->y * SPEED;
    }
}

void arrow_right(direction* dir){
/**
 * @brief       Rotate the direction when the arrow right is pushed
 * @param       dir         direction of the character
 * @return      Nothing.
 */
	rotation(dir, theta);
}

void arrow_left(direction* dir){
/**
 * @brief       Rotate the direction when the arrow left is pushed
 * @param       dir         direction of the character
 * @return      Nothing.
 */
	rotation(dir, -theta);
}

void rotation(direction* dir, angle theta){
/**
 * @brief       Rotate the direction with the angle 'theta'
 * @param       dir         direction of the character
 *              theta       angle random
 * @return      Nothing.
 */
    double d_x = dir->x, d_y = dir->y;
	dir->x = d_x * cos(theta * SPEED_ROT) - d_y * sin(theta * SPEED_ROT);
	dir->y = d_y * cos(theta * SPEED_ROT) + d_x * sin(theta * SPEED_ROT);
}




direction rot(double x, double y, angle t){
/**
 * @brief       Rotate the direction with the angle t
 * @param       x           x-axe direction of the character
 *              y           y-axe direction of the character
 *              t           angle
 * @return      d           new direction
 */
    double x1 = x * cos(t) - y * sin(t);
	double y1 = y * cos(t) + x * sin(t);
    direction d = {x1, y1};
	return d;
}

double cos_vector(direction u, direction v){
/**
 * @brief       Rotate the direction with the angle t
 * @param       u           direction
 *              y           direction
 *              t           angle
 * @return      d           new direction
 */
    double t;
    double norme_u = sqrt(pow(u.x, 2) + pow(u.y, 2));
    double norme_v = sqrt(pow(v.x, 2) + pow(v.y, 2));

    t = (u.x * v.x + u.y * v.y) / (norme_u * norme_v);
    return t;
}




    /*********************************************************************************/
                                        /* Research wall */
    /*********************************************************************************/


color tangent_wall_h(double xprime, int yprime, direction dir, worldmap map){
/**
 * @brief       Return the color of the wall hit horizontally
 * @param       xprime      x position (double) of the hit of the square
 *              yprime      y position (int) of the hit of the square
 *              dir         direction
 *              map         map pointer defined in the display_main.c in display.c.
 * @return      map[i][j]   color of the square
 */
	int i = (int) (xprime / WALLSIZE), j = (int) (yprime / WALLSIZE);
	if (dir.y < 0){ j--; }
	if (i<0 || i>MAP_WIDTH-1 || j<0 || j>MAP_HEIGHT-1){ return (color) 5; }
	else { return map[i][j];}
}

color tangent_wall_v(int xprime, double yprime, direction dir, worldmap map){
/**
 * @brief       Return the color of the wall hit vertically
 * @param       xprime      x position (int) of the hit of the square
 *              yprime      y position (double) of the hit of the square
 *              dir         direction
 *              map         map pointer defined in the display_main.c in display.c.
 * @return      map[i][j]   color of the square
 */
	int i = (int) (xprime / WALLSIZE), j = (int) (yprime / WALLSIZE);
	if (dir.x < 0){ i--; }
	if (i<0 || i>MAP_WIDTH-1 || j<0 || j>MAP_HEIGHT-1){ return (color) 5; }
	else { return map[i][j]; }
}

dist_color_brightness dda_h(position pos, direction dir, worldmap map){
/**
 * @brief       Return the distance, the color and the brightness of the first wall hit horizontally
 * @param       pos         position of the character
 *              dir         direction of the character
 *              map         map pointer defined in the display_main.c in display.c.
 * @return      Nothing.
 */
    int i = (int) pos.y / WALLSIZE;
    int d_i = 1;
	if (dir.y >= 0){ i++; }
	else { d_i = -1; }
	double D_x = dir.x * WALLSIZE / fabs(dir.y);
	double d_u = sqrt(pow(WALLSIZE, 2) + pow(D_x, 2));
	double dist = fabs(WALLSIZE*i-pos.y)*fabs(d_u)/WALLSIZE;
	double hit_x = pos.x + fabs(pos.y-WALLSIZE*i)*D_x/WALLSIZE;
	while (tangent_wall_h(hit_x, WALLSIZE*i, dir, map)==0){
        i += d_i;
        dist += d_u;
        hit_x += D_x;
	}
	dist_color_brightness p = {dist, tangent_wall_h(hit_x, WALLSIZE*i, dir, map), 100};
	return p;
}

dist_color_brightness dda_v(position pos, direction dir, worldmap map){
/**
 * @brief       Return the distance, the color and the brightness of the first wall hit vertically
 * @param       pos         position of the character
 *              dir         direction of the character
 *              map         map pointer defined in the display_main.c in display.c.
 * @return      Nothing.
 */
    int i = (int) pos.x / WALLSIZE;
    int d_i = 1;
	if (dir.x >= 0){ i++; }
	else { d_i = -1; }
	double D_y = dir.y * WALLSIZE / fabs(dir.x);
	double d_u = sqrt(pow(WALLSIZE, 2) + pow(D_y, 2));
	double dist = fabs(WALLSIZE*i-pos.x)*fabs(d_u)/WALLSIZE;
	double hit_y = pos.y + fabs(pos.x-WALLSIZE*i)*D_y/WALLSIZE;
	while (tangent_wall_v(WALLSIZE*i, hit_y, dir, map)==0){
        i += d_i;
        dist += d_u;
        hit_y += D_y;
	}
	dist_color_brightness p = {dist, tangent_wall_v(WALLSIZE*i, hit_y, dir, map), 50};
	return p;
}

dist_color_brightness dda(position pos, direction dir, worldmap map){
/**
 * @brief       Return the distance, the color and the brightness of the first wall hit
 * @param       pos         position of the character
 *              dir         direction of the character
 *              map         map pointer defined in the display_main.c in display.c.
 * @return      Nothing.
 */
	dist_color_brightness v = dda_v(pos, dir, map), h = dda_h(pos, dir, map);
	if (v.distance < h.distance){ return v; }
	else { return h; }
}

bool test_hit(position pos, direction dir, worldmap map){
/**
 * @brief       Return a bool (true or false) if the next step of the character is inside a wall
 * @param       pos         position of the character
 *              dir         direction of the character
 *              map         map pointer defined in the display_main.c in display.c.
 * @return      Nothing.
 */
    int next_pos_x = (int) (pos.x + dir.x * SPEED) /WALLSIZE, next_pos_y = (int) (pos.y + dir.y * SPEED) / WALLSIZE;
    if(map[next_pos_x][next_pos_y] != 0 && allowed_hit) {return true;}
}

direction f_dir_hit(direction dir, int j){
/**
 * @brief       Return the direction (the unit vector) between the position of your character and the jth point of the camera
 * @param       dir         direction of the character
 *              j           the jth point of the camera
 * @return      Nothing.
 */
    double norm_v = sqrt(pow(dir.x, 2) + pow(dir.y, 2));
    double norm_perp;
    direction perp;

    perp.x =  -1 * dir.y / norm_v; perp.y = dir.x / norm_v;
    perp.x = dir.x * DISTANCE_CAMERA / norm_v + (j * CAMERA_WIDTH / WINDOW_GAME_WIDTH - CAMERA_WIDTH / 2) * perp.x;
    perp.y = dir.y * DISTANCE_CAMERA / norm_v + (j * CAMERA_WIDTH / WINDOW_GAME_WIDTH  - CAMERA_WIDTH / 2) * perp.y;

    norm_perp = sqrt(pow(perp.x, 2) + pow(perp.y, 2));
    perp.x = perp.x / norm_perp; perp.y = perp.y / norm_perp;
    return perp;
}
























//bhbqshbd
