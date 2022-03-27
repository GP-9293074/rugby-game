// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "defender.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_defender_strategy(
    position_t defender_position, Spy attacker_spy) {

  	// TODO: Implement Defender logic here
  	
	static direction_t best_direction = DIR_UP;
    static direction_t previous_direction = DIR_LEFT;
    static position_t previous_position = INVALID_POSITION;
    static int round = 0;

    if (round == 0) {
    	
    	best_direction = (direction_t) DIR_LEFT;

    } else if (round < 2) {

    	best_direction = (direction_t) DIR_STAY;

    } else if (round == 2) {

    	position_t attacker_position = get_spy_position(attacker_spy);
    	if (attacker_position.j < defender_position.j) {

    		best_direction = (direction_t) DIR_UP;
    		previous_direction = (direction_t) DIR_UP;
    		previous_position = defender_position;

    	} else if (attacker_position.j > defender_position.j) {

    		best_direction = (direction_t) DIR_DOWN;
    		previous_direction = (direction_t) DIR_DOWN;
    		previous_position = defender_position;

    	} else if (attacker_position.j == defender_position.j) {

    		srand(time(NULL));
    		int randomnumber = rand() % 2;
    		switch(randomnumber) {
    	
    			case 0:
    				best_direction = (direction_t) DIR_UP;
    				previous_direction = (direction_t) DIR_UP;
    				previous_position = defender_position;
    				break;

    			case 1:
    				best_direction = (direction_t) DIR_DOWN;
    				previous_direction = (direction_t) DIR_DOWN;
    				previous_position = defender_position;
    				break;

    		}

    	} else if (round > 2) {

    		if (previous_direction.i == (direction_t) DIR_UP.i && previous_direction.j == (direction_t) DIR_UP.j) {

    			if (equal_positions(defender_position, previous_position)) {

    				best_direction = (direction_t) DIR_DOWN;
    				previous_direction = (direction_t) DIR_DOWN;
    				previous_position = attacker_position;

    			} else {

					best_direction = (direction_t) DIR_UP;
    				previous_direction = (direction_t) DIR_UP;
    				previous_position = attacker_position;    				

    			}

    		} else if (previous_direction.i == (direction_t) DIR_DOWN.i && previous_direction.j == (direction_t) DIR_DOWN.j) {

    			if (equal_positions(defender_position, previous_position)) {

    				best_direction = (direction_t) DIR_UP;
    				previous_direction = (direction_t) DIR_UP;
    				previous_position = attacker_position;

    			} else {

					best_direction = (direction_t) DIR_DOWN;
    				previous_direction = (direction_t) DIR_DOWN;
    				previous_position = attacker_position;    				

    			}

    		}

    	}

    }

    round++;
    return best_direction;
}

/*----------------------------------------------------------------------------*/
