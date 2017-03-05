#include <kipr/botball.h>

#include "vector.h"
#include "main.h"
#include "sort.h"



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
	//will be used to tell whether or not poms should be discarded after color detect
	//return 0 if discard the pom else return 1. basically used to balance # of poms 
	//to get maximum sorting points
	
	int nonzerocount;
	
	//vector for storing value info
	vector vect;
	vector valvect;
	vector_init(&vect);
	vector_init(&valvect);
	
	int count_array[4] = {green_count, pink_count, orange_count, blue_count};
	
	//rewrite so one list is a list of channel indices that arent 0 and the other is the list corresponding to it
	
	//sets up vectors
	int i;
	for (i = 0; i < CHANNEL_COUNT; i++)
	{
		vector_add(&vect, NULL);
		vector_add(&valvect, NULL);
		if (!count_array[i] && color != i)
		{ 
			nonzerocount += 1;
			vector_set(&vect,i,i);
			vector_set(&valvect,i,count_array[i]);
		}
	}
	
	//super inefficient. can be improved later
	if (nonzerocount == 0)
	{
		return 1; 
	} //if there arent any poms, no reason to discard
	else 
	{
		if (nonzerocount == 1)
		{
			if (count_array[color] == (int) vector_get(&valvect, 0))
			{
				return 0;
			}
		}
		else if (nonzerocount == 2)
		{
			if ((int) vector_get(&valvect, 0) == (int) vector_get(&valvect, 1))
			{
				if (count_array[color] == (int) vector_get(&valvect, 0))
				{
					return 0;
				} 
			}
		}
		else if (nonzerocount == 3)
		{
			if ((int) vector_get(&valvect, 0) == (int) vector_get(&valvect, 1) && (int) vector_get(&valvect, 0) == (int) vector_get(&valvect, 2))
			{
				if (count_array[color] == (int) vector_get(&valvect, 0))
				{
					return 0;
				}
			}
		}
		
	}
	//if nothing is wrong
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