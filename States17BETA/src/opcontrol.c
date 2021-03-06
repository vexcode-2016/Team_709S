/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any
 * functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "ethanlib.h"
#include "constants.h"

void operatorControl() {
  bool HANGHOOKSet = true;
  /*
  for (size_t i = 0; i < 6; i++) {
    motorSet(driveMotorList[i], 100);
    delay(500);
    motorSet(driveMotorList[i], 0);
    delay(1000);
  }
  driveSet(100, 100);
  delay(1000);
  driveSet(0, 0);
  //*/
  //driveSet(100, 100);
  //TaskHandle stopTask = taskCreate(stopDriveAfter, TASK_DEFAULT_STACK_SIZE, (void*)1000, TASK_PRIORITY_DEFAULT + 1);
  while (isEnabled()) {
    if (joystickGetDigital(1, 6, JOY_UP) && analogReadCalibrated(POT) < POTTOP) {
      liftSet(100);
    } else if (joystickGetDigital(1, 6, JOY_DOWN) && analogReadCalibrated(POT) > POTBOTTOM) {
      liftSet(-100);
    } else {
      liftSet(LIFTZERO);
    }
    /*
    if (analogReadCalibrated(POT) < POTBOTTOM) {
      liftSet(50);
    }
    */
    if (joystickGetDigital(1, 5, JOY_UP)) {
      digitalWrite(HANGLOCKLEFT, true);
    } else if (joystickGetDigital(1, 5, JOY_DOWN)) {
      digitalWrite(HANGLOCKLEFT, false);
      delay(75);
    }
    if (joystickGetDigital(1, 7, JOY_DOWN) && joystickGetDigital(1, 7, JOY_DOWN)) {
      if (HANGHOOKSet == true) {
        HANGHOOKSet = false;
      } else {
        HANGHOOKSet = true;
      }
      digitalWrite(HANGHOOK, HANGHOOKSet);
      delay(150);
    }
    driveSet(joystickGetAnalog(1, 3) * 0.8, joystickGetAnalog(1, 2) * 0.8);
    if (lcdReadButtons(uart1) == 7) taskDelete(NULL);
    printValues();
    delay(20);
	}
}
