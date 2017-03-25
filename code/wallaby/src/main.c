#include <kipr/botball.h>
#include "drive.h"
#include "main.h"
    
int main() 
{
    enable_servos();
    set_servo_position(0,BALE_UP);
    //if the robot takes too much time then reduce distance vars from square ups
    //backward(23); //22.5
    pick_up_bale(); //picks up first bale  
    forward(20);
    printf("hi");
    right(90, ROBOT_DIAMETER/2); //1 wheeled turn to square up
    printf("hello i am done wth it lolol");
    mav(MOT_LEFT, -SPD_L_B);
    mav(MOT_RIGHT, -SPD_R_B);
    msleep(2000);
    
    forward(180); //go to the half of the board
    
    right(-90,ROBOT_DIAMETER/2); //turn to have the end face the wall at the half
    forward(10); //square up with wall
    right(90,ROBOT_DIAMETER/2); //one-wheel left turn
    
    int total_dist = 64; //distance covered by black tape
    int i;
    for(i = 0; i < 3; i++) //utilizing the stinger stacker
    {
        forward(total_dist / 4);
        pick_up_bale();
        //msleep(1500);
    }
    disable_servos();
    return 0;
}

void pick_up_bale(){
    //servo_slow(BALE_UP, BALE_PORT, BALE_DOWN, 5000);
    set_servo_position(BALE_PORT, BALE_UP);
    msleep(1000);
    set_servo_position(BALE_PORT, BALE_DOWN);
    msleep(1000);
    set_servo_position(BALE_PORT, BALE_UP);
    msleep(1000);
}

void servo_slow(int start, int servo, int end, int time){ //time is in MS
    //work in progress!!
    set_servo_position(servo, start);
    
    int difference = end - start;
    float timeper = difference/(time/1000);
    
    int i;
    for (i = 1; i <= (time/1000); i++){
        set_servo_position(servo, start+i*timeper);
        msleep(time/timeper);
    }
}