#include <FPT.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int screenWidth = 600;
int screenHeight = 600;

double bodies[3][2]; //X and Y coordinates of each body
int colors[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
double velocities[3][2]; //X and Y velocities of each body
int speed = 1; //Speed multiplier for testing

/* Bodies 1, 2, and 3 are Red, Green, and Blue*/
void draw_bodies(){
  for (int r = 0; r < 3; r++){
    G_rgb(colors[r][0], colors[r][1], colors[r][2]);
    G_fill_circle(bodies[r][0], bodies[r][1], 10);
  }
}

/* Generates X and Y components of gravity vector towards two other bodies */
void pull(int self, int o1, int o2){

  //Pull to body 1
  double dX1, dY1, dist1, mag1;
  dX1 = bodies[o1][0] - bodies[self][0];
  dY1 = bodies[o2][1] - bodies[self][1];
  dist1 = sqrt(dX1*dX1 + dY1*dY1)/10;
  mag1 = (dist1*dist1);
  dX1 = (speed*dX1)/mag1; dY1 = (speed*dY1)/mag1;

  //Pull to body 2
  double dX2, dY2, dist2, mag2;
  dX2 = bodies[o2][0] - bodies[self][0];
  dY2 = bodies[o2][1] - bodies[self][1];
  dist2 = sqrt(dX2*dX2 + dY2*dY2);
  mag2 = dist2*dist2;
  dX2 = (speed*dX2)/mag2; dY2 = (speed*dY2)/mag2;

  bodies[self][0] += dX1 + dX2;
  bodies[self][1] += dY1 + dY2;

  /* Next to fix: simple implementation of inverse square law leads to bodies approaching infinite speed as they come closer together. Need to tune distance mechanics for smoother behavior  */

}

/* apply 1 frame of gravitational pull on each body*/
void step(){
  pull(0, 1, 2);
  pull(1, 2, 0);
  pull(2, 0, 1);
}

int main(){

  G_init_graphics(screenWidth, screenHeight);
  G_rgb(0, 0, 0);
  G_clear();

  //Click to place the 3 bodies at first
  G_wait_click(bodies[0]);
  G_rgb(1,0,0); G_fill_circle(bodies[0][0], bodies[0][1], 10);
  G_wait_click(bodies[1]);
  G_rgb(0,1,0); G_fill_circle(bodies[1][0], bodies[1][1], 10);
  G_wait_click(bodies[2]);
  G_rgb(0,0,1); G_fill_circle(bodies[2][0], bodies[2][1], 10);

  while(1){
    G_rgb(0, 0, 0);
    G_clear();
    step();
    draw_bodies();
    G_display_image();
    usleep(1000);
  }
  G_wait_key();
}
