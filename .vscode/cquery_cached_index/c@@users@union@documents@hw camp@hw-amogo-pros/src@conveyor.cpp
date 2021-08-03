#include "main.h"


const int JAMMED_IF_VEL_FOR = 100; // Conveyor needs to be jammed for this long before it tries to unjam (ms)
const int CONVEYOR_REVERSE_STUCK = 100; // When the conveyor jams, conveyor will run backwards for this amount of time (ms)
const int CONVEYOR_WAS_STUCK   = 250; // After getting jammed, the code cannot get stuck again for this amount of time (ms)


pros::Motor conveyor(12, true);
pros::Motor intake(17, true);


int get_conveyor_velocity() { return conveyor.get_actual_velocity(); }
int get_intake_velocity  () { return intake.  get_actual_velocity(); }


///
// Conveyor Anti jam
//  - check if a ring jammed the conveyor.  If it did, run the conveyor the opposite direction for a short amount of time.
///
void
set_conveyor(int input)  {
  int output;
  static int almost_stuck_timer = 0;
  static int stuck_timer = 0;
  static int was_stuck_timer = 0;
  static bool is_stuck = false;
  static bool was_stuck = false;

  // If the velocity of intake or conveyor is 0 for X amount of time, set is_stuck to true
  if ((get_conveyor_velocity()==0||get_intake_velocity()==0) && input>100 && !was_stuck) {
    almost_stuck_timer+=DELAY_TIME;
    if (almost_stuck_timer>JAMMED_IF_VEL_FOR) {
      is_stuck = true;
      almost_stuck_timer = 0;
    }
  }

  // If conveyor is stuck, run the conveyor backwards until stuck_timer is equal to CONVEYOR_REVERSE_STUCK
  if (is_stuck) {
    output = -input;
    stuck_timer += DELAY_TIME;
    if (stuck_timer >= CONVEYOR_REVERSE_STUCK) {
      stuck_timer = 0;
      is_stuck = false;
      was_stuck = true;
    }
  }
  // After unjamming, the conveyor cannot get stuck again for CONVEYOR_WAS_STUCK
  else {
    if (was_stuck) {
      was_stuck_timer+= DELAY_TIME;
      if (was_stuck_timer>CONVEYOR_WAS_STUCK) {
        was_stuck = false;
        was_stuck_timer = 0;
      }
    }
    output = input;
  }
  conveyor = output;
  intake = output;
}


///
// Driver Control
//  - when R1 is pressed, run the conveyor in
//  - when R2 is pressed, run the conveyor out
///
void
conveyor_control() {
  if (master.get_digital(DIGITAL_R1))
    set_conveyor(127);
  else if (master.get_digital(DIGITAL_R2))
    set_conveyor(-127);
  else
    set_conveyor(0);
}
