#include <kipr/botball.h>

#include "createDriveOld.h"
#include "main.h"
#include "vector.h"
#include "sort.h"


int main()
{
	camera_open_black();
    enable_servos();
    
    sort_colors();

    //sort poms
    //Drop-off all poms at the furrow
    
    //end funcs (close camera, motors, etc)
    camera_close();
    disable_servos();
    return 0;
}

void dump_poms(){
	//dump poms, reset counts
    blue_count = 0; green_count = 0; orange_count = 0; pink_count = 0;
}

//all unused right now
void sort_green()
{
    printf("Sorting green poms...\n");
}

void sort_pink()
{
    printf("Sorting pink poms...\n");
}

void sort_orange()
{
    printf("Sorting orange poms...\n");
}

void sort_blue()
{
    printf("Sorting blue poms...\n");
}

/*

i am inspecture
you can trust me
trust me
yes you can
trust me
illl shot you in the face

fandomheart : merasmus he evil
fandomheart : guy
fandomheart : were ids he now who know
fandomheart : he just threw his hat becuse he is the evilest guyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy
fandomheart : and hell stew out of you

*/