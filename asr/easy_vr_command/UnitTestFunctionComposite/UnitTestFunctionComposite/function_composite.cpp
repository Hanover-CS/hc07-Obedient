#include "function_composite.h"

//group
extern const int GROUP_0 = 0;
extern const int GROUP_1 = 1;

//command idx
extern const int G0_OBEDIENT = 0;
extern const int G1_FOWARD = 0;
extern const int G1_BACKWARD = 1;
extern const int G1_LEFTTURN = 2;
extern const int G1_RIGHTTURN = 3;
extern const int G1_TURNBACKLEFT = 4;
extern const int G1_TURNBACKRIGHT = 5;
extern const int G1_STOP = 6;
extern int group = -1;

/* This is the function that handle the trigger to start the Obedient
* This is only work if we passed the right idx, which is 0, and not working
* at all for other cases
*/
int trigger(int idx) {
	switch (idx) {
	    case G0_OBEDIENT:
		    group = GROUP_1;
	}

	return group;
}

/* This is the function that handle the basic movements of the Obedient
*  This is only work if we passed the approriate idx's, which is 0-6, and not working
*  at all for other cases
*/
int basic(int idx) {
	switch (idx) {
	    case G1_FOWARD:
			return G1_FOWARD;
		case G1_BACKWARD:
			return G1_BACKWARD;
		case G1_LEFTTURN:
			return G1_LEFTTURN;
		case G1_RIGHTTURN:
			return G1_RIGHTTURN;
		case G1_TURNBACKLEFT:
			return G1_TURNBACKLEFT;
		case G1_TURNBACKRIGHT:
			return G1_TURNBACKRIGHT;
	}
	return -1;
}