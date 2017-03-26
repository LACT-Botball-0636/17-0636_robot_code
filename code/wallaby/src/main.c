#include <kipr/botball.h>
#include "drive.h"
#include "main.h"

int main()
{
    enable_servos();

    set_servo_position(0,BALE_UP);
    //if the robot takes too much time then reduce distance vars from square ups
    forward(23); //22.5
    pick_up_bale(); //picks up first bale 
	msleep(1000);
    mav(MOT_LEFT, SPD_L_B); //1 wheeled turn to square up
    msleep(2000);
    printf("Wassup fellas");
    backward(20);

    forward(100); //travel against all odds to the opposite half of the board

    left(90,ROBOT_DIAMETER/2); //turn to have the end face the wall at the half
    forward(40); //square up with wall
    right(90,ROBOT_DIAMETER/2); //one-wheel left turn/pivot
    int total_dist = 64; //distance covered by black tape
    int i;
    for(i = 0; i < 3; i++) //utilizing the stinger stacker
    {
        forward(total_dist / 4);
        pick_up_bale();
    }
    disable_servos();
    return 0;
}

void pick_up_bale(){
    servo_slow(BALE_UP, 0, BALE_DOWN, 5000);
    set_servo_position(0, BALE_UP);
}

void servo_slow(int start, int servo, int end, int time){ //time is in MS
    set_servo_position(servo, start);

    int difference = end - start;
    float timeper = difference/(time/1000.0);
    printf("timeper: %f", timeper);
    int i;
    for (i = 1; i <= (time/1000); i++){
        set_servo_position(servo, start+i*timeper);
        msleep(1000);
    }
}