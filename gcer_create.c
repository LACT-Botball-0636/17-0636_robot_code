#include <kipr/botball.h>
#include "createDrive.h"

//Motor Ports
#define RIGHT 1
#define LEFT 0
//Servo Ports
#define WRIST 3
#define CLAW 1
//Sensor Ports
#define TOUCH_DOWN 1
#define TOUCH_DOWN2 2
#define TOUCH_UP 0
#define SEE_COW 0
//Motor Constants
#define MAX_SPEED 1500
#define ARM_SPEED 100
//Claw Positions
#define CLAW_OPEN 2047
#define CLAW_CLOSE 0
#define CLAW_COW 1600
//Wrist Positions
#define WRIST_UP 1379
#define WRIST_DOWN 674
//Other Variables
int botguy_offset;

void servo_slow(int servo, int end, int time) //time is in MS
{
   int start = get_servo_position(servo);
   float poschange = 10 * (end - start) / time;
   float i;
   if (start < end)
   {
      for(i = start; i < end; i += poschange)
      {
         set_servo_position(servo, (int)i);
         msleep(10);
      }
   } 
   else 
   {
      for(i = start; i > end; i += poschange)
      {
         set_servo_position(servo, (int)i);
         msleep(10);
      }
   }
}

void arm_up()
{
   mav(RIGHT, -MAX_SPEED);
   mav(LEFT, -MAX_SPEED);
   while(digital(TOUCH_UP) != 1)
      msleep(1);
   ao();
}

void arm_down()
{
   mav(RIGHT, MAX_SPEED);
   mav(LEFT, MAX_SPEED);
   while(digital(TOUCH_DOWN) != 1)
      msleep(1);
   ao();
}

void claw_open(int wait) // Wait is in ms
{
   set_servo_position(CLAW, CLAW_OPEN);
   msleep(wait);
}

void claw_close(int wait) // Wait is in ms
{
   set_servo_position(CLAW, CLAW_CLOSE);
   msleep(wait);
}

void claw_close_cow(int wait) // Wait is in ms
{
   set_servo_position(CLAW, CLAW_COW);
   msleep(wait);
}

void arm_up_for_time(int time)// Time is in ms
{
   mav(RIGHT, -MAX_SPEED);
   mav(LEFT, -MAX_SPEED);
   msleep(time);
   ao();
}

void arm_down_for_time(int time)// Time is in ms
{
   mav(RIGHT, MAX_SPEED);
   mav(LEFT, MAX_SPEED);
   msleep(time);
   ao();
}

void arm_down_for_dist(int dist) // Dist is in Back-EMF's
{
	cmpc(RIGHT);
    cmpc(LEFT);
    mav(RIGHT, MAX_SPEED);
   	mav(LEFT, MAX_SPEED);
    while(!(gmpc(RIGHT) > dist) && !(gmpc(LEFT) > dist))
    {
    	msleep(1);
    }
    ao();
}

void arm_up_for_dist(int dist) // Dist is in Back-EMF's
{
	cmpc(RIGHT);
    cmpc(LEFT);
    mav(RIGHT, -MAX_SPEED);
   	mav(LEFT, -MAX_SPEED);
    while(!(gmpc(RIGHT) > -dist) && !(gmpc(LEFT) > -dist))
    {
    	msleep(1);
    }
    ao();
}

//Initialization. Do not modify without good reason!
void initialize()
{
    create_connect();
    
    while(!a_button() && !b_button() && !c_button()) 
    {
    	if (a_button())
        {
        	botguy_offset = -3;
        }
        else if (b_button())
        {
        	botguy_offset = 0;
        }
        else if (c_button())
        {
        	botguy_offset = 3;
        }
    }
    
    //enable_servos();
    cmpc(LEFT);
    cmpc(RIGHT);
}

void cow_dump_wrist()
{
    servo_slow(WRIST, WRIST_UP, 1000);
}

void cow_dump_claw()
{
    servo_slow(CLAW, CLAW_OPEN-600, 2400);
    set_servo_position(CLAW, CLAW_OPEN);
    msleep(200);
}

void cow_dump()
{
    arm_down_for_time(1000);
    msleep(200);
    cow_dump_wrist();
    msleep(750);
    cow_dump_claw();
    set_servo_position(WRIST, WRIST_DOWN);
    msleep(750);
    arm_up();
}

int main()
{
    initialize();
    arm_up();
    enable_servos();
    
    //test
    create_forward(105, 400);
    msleep(200);
    create_left(90, 300);
    create_backward(40, 300);
    
    // Shake Water tank
    create_forward(35, 300);
    set_servo_position(WRIST, WRIST_UP);
    set_servo_position(CLAW, CLAW_OPEN);
    arm_down_for_dist(5500);
    create_backward(26, 300);
    msleep(200);
    set_servo_position(WRIST, WRIST_DOWN);
    arm_up();
    
    
    return 0;
    set_servo_position(WRIST, WRIST_UP);
    msleep(300);

    //getting out of starting box
    claw_open(500);
    create_backward(5, 300);
    create_right(150, 300);
    create_backward(25,300);
    create_forward(45,300);
    create_right(90,300);
    create_backward(20, 300);

    //moving down middle of field towards botguy
    create_forward(121+botguy_offset, 300);
    msleep(500);
    create_right(90,150);
    create_backward(50,300);
    //create_forward(15, 300);

    //positioning arm for botguy and grabbing him
    set_servo_position(WRIST, WRIST_UP);
    create_forward(35,300); //35 || 
    msleep(300);
    arm_down_for_dist(5200); //5200
    set_servo_position(WRIST, WRIST_DOWN);
    create_backward(16,300); //16
    arm_down_for_time(500);
    claw_close(500);
    arm_up_for_time(1750);
    create_forward(13,300);
    arm_up();
    set_servo_position(WRIST, WRIST_DOWN - 100);
    create_backward(10,300);
    msleep(200);

    //dumping botguy on the ramp
    create_right(90,200);
    msleep(200);
    create_backward(42,300);
    msleep(200);
    create_right(90,200);
    msleep(200);
    create_backward(38,300);
    msleep(500);
    set_servo_position(WRIST, WRIST_UP);
    //arm_down_for_time(800);
    msleep(1000);
    set_servo_position(CLAW, CLAW_OPEN);
    msleep(1000);
    set_servo_position(WRIST, 1000);

    //moving away from the ramp and starting route to pick up the first blue cow
    msleep(250);
    create_forward(26,300);
    msleep(250);
    create_right(125,300);
    set_servo_position(WRIST, WRIST_UP);
    arm_down_for_time(1000);
    msleep(250);
    create_backward(30,300);
    msleep(250);
    create_right(27,300);
    msleep(250);
    //square up
    create_backward(30,300);
    msleep(250);
    create_forward(35,300);
    msleep(500);
    create_right(86,50);
    msleep(500);


    //positioning arm for blue cow
    //arm_down();
    //arm_up_for_time(1500);
    create_backward(42-botguy_offset,200);
    while (analog(SEE_COW) < 2900){
    	create_backward(1,45);
    }
    create_forward(31,200);
    msleep(500);
    set_servo_position(WRIST, WRIST_DOWN);
    arm_down_for_dist(4800);
    msleep(500);

    //grab blue cow and bring to ramp
    set_servo_position(CLAW, CLAW_CLOSE);
    msleep(700);
    arm_up_for_time(1000);
    set_servo_position(WRIST, WRIST_DOWN);
    arm_up();
    msleep(250);
    create_backward(40,300); //move along platform to place the cow to the left of botguy
    create_right(90,100);
    create_backward(25,200);
    msleep(500);
    create_forward(10,100);
    msleep(500);

    //msleep(500);
    //create_backward(6,350);
    //msleep(500);

    cow_dump();

    create_forward(20,200);
    msleep(500);

    //turn and square up against far wall
    set_servo_position(WRIST, WRIST_UP);
    create_left(90, 300);
    msleep(200);
    create_backward(50, 400);
    msleep(200);

    //go towards 2nd cow
    create_forward(67, 400);
    msleep(200);
    create_left(90, 300);
    create_backward(40, 300);
    
    // Shake Water tank
    create_forward(17, 300);
    create_left(45, 50);
    arm_down_for_dist(3500);
    create_backward(24, 300);
    msleep(300);
    create_forward(24, 300);
    create_right(45, 50);
    create_backward(40, 300);
    msleep(200);

    // position arm for 2nd cow
    set_servo_position(WRIST, WRIST_UP);
    msleep(200);
    arm_down_for_dist(1000);
    set_servo_position(WRIST, WRIST_DOWN);
    arm_down_for_dist(3800);
    msleep(200);
    set_servo_position(CLAW, CLAW_CLOSE);
    msleep(300);
    arm_up_for_time(1000);
    set_servo_position(WRIST, WRIST_DOWN);
    arm_up();

    //head towards ramp
    create_forward(20, 300);
    msleep(200);
    create_left(180, 200);
    //create_left(95, 200);
    //create_forward(3, 300);
    //msleep(300);
    //create_left(84, 200);
    msleep(300);
    create_backward(33, 300);
    msleep(200);

    cow_dump();
    
    create_forward(20, 300);

	set_servo_position(WRIST, WRIST_UP);
    msleep(200);

    disable_servos();
    return 0;
}
