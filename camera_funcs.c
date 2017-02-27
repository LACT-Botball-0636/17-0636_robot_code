#include <kipr/botball.h>

#define CHANNEL_COUNT 4

#define GREEN_CHANNEL 0
#define PINK_CHANNEL 1
#define ORANGE_CHANNEL 2
#define BLUE_CHANNEL 3


// ========================== //
//      Sorts the colors      //
// ========================== //
void sort_colors()
{
    camera_open_black();
    int g;
    for (g = 0; g < 5; g++){
        camera_update();    //retrieve current frame
    }
    
    int current_highest_area = 0;   //current highest number of detected objects
    int current_index = -1;          //current channel with highest number of detected objects
    int x, area_max;               //declares loop variable as well as a variable used for
                                    //storing current object count,
    int i;
    for (i = 0; i < CHANNEL_COUNT; i++) 
    {
        area_max = 0;
        //finds channel with largest area
        
        x = get_object_count(i);
        printf("%d %d", i, x);
        if ( x != 0) //if there are objects!!!!!!!!!!!
        {   
            //for loop for getting the total area of the objects
            int j; 
            for(j = 0; j < x; j++)
            {
                if (get_object_area(i,j) > area_max)
                {
                    area_max = get_object_area(i,j);
                    current_index = i;
                }
            }                
            print  
            //for every object there is, run once and add to total area
        }
    }
    
    switch (current_index) 
    {
        case -1:
            printf("no poms found");
            break;
        case 0:
            sort_green();
            break;
        case 1:
            sort_pink();
            break;
        case 2:
            sort_orange();
            break;
        case 3:
            sort_blue();
            break;
           
    }
    
    camera_close();
}



void sort_green()
{
    printf("Sorting green poms ajays giant car");
}

void sort_pink()
{
    printf("Sorting pink poms...");
}

void sort_orange()
{
    printf("Sorting orange poms...");
}

void sort_blue()
{
    printf("Sorting blue poms...");
}
