#include <kipr/botball.h>

#include "vector.h"
#include "main.h"
#include "sort.h"
#include <thread.h>

#define SWITCH_PORT ?
#define SPINNER_PORT ?

#define SWITCH_RIGHT ?
#define SWITCH_LEFT ?
#define SWITCH_DUMP ?

#define SORT_TIME ?

int isbreak;

void timer()
{
    printf("Timer started.\n");
    msleep(SORT_TIME);
    isbreak = 1;
}

void sort_main(int time)
{
    isbreak = 0;
    //time milliseconds
    thread timer_thread = thread_create(timer);
    thread_start(timer_thread);
    
    int count;
    
    motor(SPINNER_PORT, 300);
    while (1)
    {
        if (isbreak)
        {
            off(SPINNER_PORT);
            thread_destroy(timer_thread);
            break;
        }
        int color = find_color();
        if (color != -1)
        {
            if (think(color)) 
            {
                //continue using motor
            }
            else
            {
                off(SPINNER_PORT);
                break;
            }
            msleep(500);
        }
    }
}

// ========================== //
//     Find current color     //
// ========================== //
int find_color()
{   
    int current_highest_area = 0;   //current highest number of detected objects
    int current_index = -1;          //current channel with highest number of detected objects
    int x, area_max;               //declares loop variable as well as a variable used for
                                    //storing current object count,
    int i;
    for (i = 0; i < CHANNEL_COUNT; i++) 
    {
        area_max = 0;
        //finds channel with largest area
        int k;
        for (k=0; k < 5; k++)
        {
            camera_update();
        }
        x = get_object_count(i);
        printf("x=%d i=%d\n", x, i);
        if ( x != 0)
        {   
            //for loop for getting the total area of the objects
            int j; 
            for(j = 0; j < x; j++)
            {
                if (get_object_area(i,j) > area_max)
                {
                    area_max = get_object_area(i,j);
                }
            } 
            printf("index: %d, area_max: %d\n", i, area_max);
            //for every object there is, run once and add to total area
            if (area_max > current_highest_area)
            {
                current_highest_area = area_max;
                current_index = i;
            }
        }
    }
    
    return current_index;
}

// ================================= //
// Decides whether or not to discard //
// ================================= //
int think(int color){
    //int greencount = 0;
    //int orangecount = 0;
    //int pinkcount = 0;
    //int bluecount = 0;
    int colorlist[4] = {greencount, orangecount, pinkcount, bluecount};
    
    //assuming first pom is green
    if ((colorlist[color] >= colorlist[GREEN] && color != GREEN) || ()
    {
        //has reached equillibrium among poms
        //stop sorting
        return 0;
    }
    else
    {
    
        switch(color)
        {
            case GREEN:
                greencount++;
                break;
            case PINK:
                pinkcount++;
                break;
            case ORANGE:
                orangecount++;
                break;
            case BLUE:
                bluecount++;
                break;
        }
    
        if (colorlist[color] % 2 == 0) 
        {
        //even amount of poms
            set_servo_position(SWITCH_PORT, SWITCH_RIGHT);
        } 
        else
        {
        //odd amount of poms
            set_servo_position(SWITCH_PORT, SWITCH_LEFT);
        }
    }
    return 1;
    
}

// ========================== //
//      Sorts the colors      //
// ========================== //
void sort_colors(){
    //reset counts of poms
    blue_count = 0; green_count = 0; orange_count = 0; pink_count = 0;
    
    stopSort = 0;
    while (!stopSort)
    {
        //detect color, return color. (-1=none,0=green,1=pink,2=orange,3=blue)
        int result = find_color();
        if (result != -1)
        {
            switch (result)
            {
                case GREEN:
                    //set_servo_position(FURROW_SERVO_PORT,FURROW_NEAR_POS);
                    printf("green detected. not discard? %d", think(GREEN));
                    green_count += 1;
                    break;
                case PINK:
                    //set_servo_position(FURROW_SERVO_PORT,FURROW_MIDDLE_POS);
                    printf("pink detected. not discard? %d", think(PINK));
                    pink_count += 1;
                    break;
                case ORANGE:
                    //set_servo_position(FURROW_SERVO_PORT,FURROW_FAR_POS);
                    printf("orange detected. not discard? %d", think(ORANGE));
                    orange_count += 1;
                    break;
                case BLUE:
                    //set_servo_position(FURROW_SERVO_PORT,FURROW_NEAR_POS);
                    printf("blue detected. not discard? %d", think(BLUE));
                    blue_count += 1;
                    break;
            }
            
            msleep(1300);
        }
        else
        {
            printf("no pom found");
            //maybe will "go to sleep" and update less often if it detects that it has neither 
            //seen the collection arm move nor has it seen a pom a certain number of times
            //in a row whilst in regular update mode. if the arm moves or it DOES see a pom on  
            //one of the infrequent checks, it will return to a regular update mode
            msleep(1300);
        }
    } 
}