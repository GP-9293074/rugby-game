// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "attacker.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_attacker_strategy(
    position_t attacker_position, Spy defender_spy) {
  // TODO: Implement Attacker logic here

    static direction_t best_direction = DIR_UP;
    static direction_t previous_direction = DIR_LEFT;
    static position_t previous_position = INVALID_POSITION;
    static int round = 0;

    if (round < 2) {

    	if (equal_positions(attacker_position, previous_position)) {
    	
    		srand(time(NULL));
    		int randomnumber = rand() % 4;
    		switch(randomnumber) {
    	
    			case 0:
    				best_direction = (direction_t) DIR_UP;
    				break;

    			case 1:
    				best_direction = (direction_t) DIR_UP_RIGHT;
    				break;

    			case 2:
    				best_direction = (direction_t) DIR_DOWN_RIGHT;
    				break;

    			case 3:
    				best_direction = (direction_t) DIR_DOWN;
    				break;
    		}
    	} else {
    	
    		best_direction = (direction_t) DIR_RIGHT;
    	
    	}
    } else if (round == 2) {

    	position_t defender_position = get_spy_position(defender_spy);
    	if (defender_position.j < attacker_position.j) {
    		best_direction = (direction_t) DIR_DOWN_RIGHT;
    		previous_direction = (direction_t) DIR_DOWN_RIGHT;
    		previous_position = attacker_position;
    	}

		if (defender_position.j > attacker_position.j) {
    		best_direction = (direction_t) DIR_UP_RIGHT;
    		previous_direction = (direction_t) DIR_UP_RIGHT;
    		previous_position = attacker_position;
    	}    	

    	if (defender_position.j == attacker_position.j) {
    		srand(time(NULL));
    		int randomnumber = rand() % 2;
    		switch(randomnumber) {	

    			case 0:
    				best_direction = (direction_t) DIR_DOWN_RIGHT;
    				previous_direction = (direction_t) DIR_DOWN_RIGHT;
    				previous_position = attacker_position;
    				break;

    			case 1:
    				best_direction = (direction_t) DIR_UP_RIGHT;
    				previous_direction = (direction_t) DIR_UP_RIGHT;
    				previous_position = attacker_position;
    				break;

    		}
    	}
    } else if (round > 2) {

    	if (equal_positions(attacker_position, previous_position)) {

    		best_direction = (direction_t) DIR_RIGHT;
    		previous_position = attacker_position;

    	} else {

    		best_direction = previous_direction;
    		previous_position = attacker_position;

    	}

    }

    round++;
	return best_direction;

}

/*----------------------------------------------------------------------------*/
