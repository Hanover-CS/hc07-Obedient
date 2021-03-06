#include "function_composite.h"
#include "obedient.h"

//group
extern const int GROUP_0 = 0;
extern const int GROUP_1 = 1;
extern const int GROUP_2 = 2;
extern const int GROUP_3 = 3;

//command group0 idx
extern const int G0_OBEDIENT = 0;

//command group1 idx
extern const int G1_FOWARD = 0;
extern const int G1_BACKWARD = 1;
extern const int G1_LEFTTURN = 2;
extern const int G1_RIGHTTURN = 3;
extern const int G1_TURNBACKLEFT = 4;
extern const int G1_TURNBACKRIGHT = 5;
extern const int G1_STOP = 6;

//command group2 idx
extern const int G2_FOWARD = 0;
extern const int G2_BACKWARD = 1;
extern const int G2_LEFTTURN = 2;
extern const int G2_RIGHTTURN = 3;

//command idx with forward (group3)
extern const int G3_1 = 0;
extern const int G3_2 = 1;
extern const int G3_3 = 2;
extern const int G3_4 = 3;
extern const int G3_5 = 4;
extern const int G3_6 = 5;
extern const int G3_7 = 6;
extern const int G3_8 = 7;
extern const int G3_9 = 8;
extern const int G3_10 = 9;
extern const int G3_11 = 10;
extern const int G3_12 = 11;
extern const int G3_13 = 12;
extern const int G3_14 = 13;
extern const int G3_15 = 14;
extern const int G3_16 = 15;
extern const int G3_17 = 16;
extern const int G3_18 = 17;
extern const int G3_19 = 18;
extern const int G3_20 = 19;

extern int group = -1;
extern int id = -1;
extern int funID;
//default value for movement with number that will ask Obedient to wait for the users' desired value
extern const int default = -2;

//initialize the num variable that will test whether the user already passes the number or not
int num = default;

Obedient obedient(10, 11);
obedient.attachServo();

/* This is the function that handle the trigger to start the Obedient
* This is only work if we passed the right idx, which is 0, and not working
* at all for other cases
*/
int trigger(int idx) {
	switch(idx) {
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
	switch(idx) {
	    case G1_FOWARD:
			return obedient.foward();
		case G1_BACKWARD:
			return obedient.backward();;
		case G1_LEFTTURN:
			return obedient.turnLeft();;
		case G1_RIGHTTURN:
			return obedient.turnRight();
		case G1_TURNBACKLEFT:
			return obedient.turnBackLeft();
		case G1_TURNBACKRIGHT:
			return obedient.turnBackRight();
	}
	return -1;
}

/* This is the function that direct to appropriate functions with numbers
*  This is only work if we passed the approriate idx's, which is 0-3, and not working
*  at all for other cases
*/
int direction(int idx) {
	switch(idx) {
	    case G2_FOWARD:
			return G2_FOWARD;
		case G2_BACKWARD:
			return G2_BACKWARD;
		case G2_RIGHTTURN:
			return G2_RIGHTTURN;
		case G2_LEFTTURN:
			return G2_LEFTTURN;
	}
	
	return -1;
}

/* This is the function that passed argument to forward function that will tell Obedient
*  to move forward for that seconds of time
*  This is only work if we passed the approriate idx's, which is 0-19, and not working
*  at all for other cases
*/
int foward_with_time() {
	int result;
	
	result = obedient.fowardSecond(id);

	return result;
}

/* This is the function that passed argument to backward function that will tell Obedient
*  to move forward for that seconds of time
*  This is only work if we passed the approriate idx's, which is 0-19, and not working
*  at all for other cases
*/
int backward_with_time() {
	int result;

	result = obedient.backwardSecond(id);

	return result;
}

/* This is the function that passed argument to turnLeft function that will tell Obedient
*  to move forward for that seconds of time
*  This is only work if we passed the approriate idx's, which is 0-19, and not working
*  at all for other cases
*/
int turnLeft_with_degree() {
	int result;

	result = obedient.turnLeftDegree(id * 10);

	return result;
}

/* This is the function that passed argument to turnRight function that will tell Obedient
*  to move forward for that seconds of time
*  This is only work if we passed the approriate idx's, which is 0-19, and not working
*  at all for other cases
*/
int turnRight_with_degree() {
	int result;

	result = obedient.turnRightDegree(id * 10);

	return result;
}

/* This is the function that recognizes a number said to the Obedient
*/
int numberRecognized(int idx) {
	return idx;
}

/* This is the function that passed argument to action that where the Obedient will take the input from users
*  With the help of switch statement based on group, it will direct the flow to the right place
*  at which, the appropriate function will get call and carry out the action.
*  This is will take two arguments group, and idx. The group will direct the flow to where the function lies,
*  then the function get call with the idx.
*/
int action(int group, int idx) {
	switch(group) {
	    case GROUP_0:
			trigger(idx);
			break;
		case GROUP_1:
			basic(idx);
			break;
		case GROUP_2:
			if (id != -1) {
				funID = direction(idx);
			}
			else {
				group = GROUP_3;
			}
			break;
		case GROUP_3:
			id = numberRecognized(idx);
			action (GROUP_2, funID);
			break;
	}
}