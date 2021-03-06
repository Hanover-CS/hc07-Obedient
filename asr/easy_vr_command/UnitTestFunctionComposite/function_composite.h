#ifndef _FUNCTION_COMPOSITE_H_
#define _FUNCTIONC_COMPOSITE_H_

#include "obedient.h"

/* This is the function that handle the trigger to start the Obedient
 * This is only work if we passed the right idx, which is 0, and not working 
 * at all for other cases
 */
int trigger(int idx);

/* This is the function that handle the user's choices between basic or advanced commands
 * then it will direct the flow to the corresponding place to tell what Obedient should obey
 * This is only work if we passed the right idx, which is 0 for "basic" and 1 for "advanced"
 * it will set the group to the value corresponding to basic and advanced group of commands.
 */
void basicOrAdvanced(int idx);

/* This is the function that handle the basic movements of the Obedient
*  This is only work if we passed the approriate idx's, which is 0-6, and not working
*  at all for other cases
*/
int basic(int idx);

/* This is the function that direct to appropriate functions with numbers
*  This is only work if we passed the approriate idx's, which is 0-3, and not working
*  at all for other cases
*/
int pickMovement(int idx);

/* This is the function that passed argument to forward function that will tell Obedient 
*  to move forward for that seconds of time
*  This is only work if we passed the approriate idx's, which is 0-19, and not working
*  at all for other cases
*/
int foward_with_time();

/* This is the function that passed argument to backward function that will tell Obedient
*  to move forward for that seconds of time
*  This is only work if we passed the approriate idx's, which is 0-19, and not working
*  at all for other cases
*/
int backward_with_time();

/* This is the function that passed argument to turnLeft function that will tell Obedient
*  to move forward for that seconds of time
*  This is only work if we passed the approriate idx's, which is 0-19, and not working
*  at all for other cases
*/
int turnLeft_with_degree();

/* This is the function that passed argument to turnRight function that will tell Obedient
*  to move forward for that seconds of time
*  This is only work if we passed the approriate idx's, which is 0-19, and not working
*  at all for other cases
*/
int turnRight_with_degree();

/* This is the function that passed argument to action that where the Obedient will take the input from users
*  With the help of switch statement based on group, it will direct the flow to the right place
*  at which, the appropriate function will get call and carry out the action.
*  This is will take two arguments group, and idx. The group will direct the flow to where the function lies, 
*  then the function get call with the idx. 
*/
int action(int group, int idx);

/* mainMenu function
 *  This is the function that handle the user's choices between basic or advanced commands
 * then it will direct the flow to the corresponding place to tell what Obedient should obey
 * This is only work if we passed the right idx, which is 0 for "basic" and 1 for "advanced"
 * it will set the group to the value corresponding to basic and advanced group of commands.
 * @param {integer} idx - the idx stores value that easyvr passes when it recognize a word from user
 */
int mainMenu(int idx);

/*
 * sensorOrBasicOrList function
 * Since the three module `sensor`, `basic` and `list` will use the same command library since they will direct the Obedient with the same movement.
 * I decided to use the three module with the same command group id, that is the reason we need this function to actually determine what module we really want
 * to call at the time.
 * @param {integer} choice - that will tell which module to be loaded.
 */
int sensorOrBasicOrList(int choice);

/* This is the function that determine what unit we will use for function in advanced group
*     0 - all functions work with unit of seconds
*     1 - all functions work with unit of metric, in this case is inch
*  @param {integer} idx - the idx of the command that the shield recognized.
*  The function will return nothing, but set `unit` variable to corresponding unit.
*/
int pickUnit(int idx);

/* This is the function that will help numberRecognized function to determine what unit it should call with the foward and backward function.
 * @param {integer} val - the value that spoken to numberRecognized function and will be the value that will call with fowardSecond or fowardDistance
 * @param {integer} unit - the value that determines what unit we are going to use
 * The function will return nothing but will call an approriate function that will directs Obedient.
 */
int fowardWithUnit(int val, int unit);

/* This is the function that will help numberRecognized function to determine what unit it should call with the backward function.
 * @param {integer} val - the value that spoken to numberRecognized function and will be the value that will call with backward or backwardDistance
 * @param {integer} unit - the value that determines what unit we are going to use
 * The function will return nothing but will call an approriate function that will directs Obedient.
 */
int backwardWithUnit(int val, int unit);

/* The sensor function that will take one parameter of idx indicator and based on the value of idx to determine which function will be called inside itself.
 * The sensor function also call tonePlay(1000, 1000) inside it to annouce that it gets the word from the user.
 * The idx will then determine which movement the Obedient will carry out
 *     if idx = SENSOR_FOWARD, then call foward function, and set current state to 0
 *     if idx = SENSOR_BACKWARD, then call backward function, and set current state to 1
 *     if idx = SENSOR_LEFTTURN, then call turnLeft function, DO NOT set current state when call with LEFTTURN
 *     if idx = SENSOR_RIGHTTURN, then call turnRight function, DO NOT set current state when call with RIGHTTURN
 *     if idx = SENSOR_TURNBACKLEFT, then call turnBackLeft function, DO NOT set currentState when call with TURNBACKLEFT
 *     if idx = SENSOR_TURNBACKRIGHT, then call turnBackRight function, DO NOT set current state when call with TURNBACKRIGHT
 *     if idx = SENSOR_STOP, then call stop function to freeze Obedient, set currentState to 2 
 *     if idx = SENSOR_MAIN, set group back to list of option (GROUP_4)
 * We will use switch structure to recognize each case based on the value of idx.
 * Because we want the Obedient will keep doing what it was doing after being discontinued we will use fowardSecond and backwardSecond instead of default foward and backward
 * The function will return nothing.     
 */ 
int sensor(int idx);

/*
 * resumeToCurrentState.
 * 
 * Function will direct the Obedient back to its current when it hears the command for turnning left or right, or back.
 * @param {integer} current - this will hold the id of the current state and based on it to get the `Obedient` back to
 * its origial states.
 */
int resumeToCurrentState(int current);

#endif
