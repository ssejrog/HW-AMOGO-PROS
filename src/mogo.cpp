#include "main.h"


const int MOGO_OUT  = 575; // Intaking mogos
const int MOGO_NEUT = 360; // Neutral mogo


// Driver Control Variables
bool mogo_up = true;
bool is_at_neut = false;
int mogo_lock   = 0;
int controller_mogo_timer = 0;
int mogo_out_timer = 0;

bool is_up = false;
bool is_neut = false;
bool is_out = false;


pros::Motor mogo(18, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);


void set_mogo(int input)  { mogo = input; }

void zero_mogo()    { mogo.tare_position(); }
int  get_mogo()     { return mogo.get_position(); }
int  get_mogo_vel() { return mogo.get_actual_velocity(); }

void
set_mogo_position(int target, int speed) {
  mogo.move_absolute(target, speed);
}


///
// Mogo Control
//  - we like to use the same functions for autonomous and driver,
//  - so these functions are used for both.
///

// Mogo In
void
mogo_in (bool hold) {
  // If mogo lift is almost at 0...
  if (get_mogo()<150) {
    // If velocity is zero or the position is < 0, then stop the mogo
    if (get_mogo_vel()==0 || get_mogo()<0) {
      is_up = true;
      set_mogo(0);
    }
    // Otherwise, come up slowly
    else {
      set_mogo(is_up?0:-60);
    }
  }
  // Otherwise, run mogo lift at full speed in
  else {
    is_up = false;
    set_mogo(-127);
  }

  // If running during autonomous,
  if (hold) {
    // Set states so the mogo will be in the last position in driver it was in during auto
    mogo_up = true;
    is_at_neut = false;
    // Loop if robot isn't there yet
    pros::delay(DELAY_TIME);
    mogo_in(!is_up);
  }
}

// Mogo Neut
void
mogo_neut(bool hold) {
  // Run built in PID to bring mogo lift to MOGO_NEUT
  set_mogo_position(MOGO_NEUT, 127);
  is_neut = timeout(MOGO_NEUT, get_mogo_vel(), get_mogo());

  // If running during autonomous,
  if (hold) {
    // Set states so the mogo will be in the last position in driver it was in during auto
    is_at_neut = true;
    // Loop if robot isn't there yet
    pros::delay(DELAY_TIME);
    mogo_neut(!is_neut);
  }
}

// Mogo Out
void
mogo_out(bool hold) {
  // If mogo lift is almost at MOGO_OUT...
  if (get_mogo() > (MOGO_OUT-100)) {
    // If velocity is 0, turn motor off
    if (get_mogo_vel()==0) {
      set_mogo(0);
      is_out = true;
    }
    // Otherwise, start a timer for 500ms, and then turn the motors off
    else {
      mogo_out_timer+=DELAY_TIME;
      if (mogo_out_timer<500) {
        set_mogo(20);
        is_out = false;
      }
      else {
        set_mogo(0);
        is_out = true;
      }
    }
  }
  // Otherwise, run the mogo lift out at full speed
  else {
    set_mogo(127);
    mogo_out_timer = 0;
    is_out = false;
  }

  // If running during autonomous,
  if (hold) {
    // Set states so the mogo will be in the last position in driver it was in during auto
    mogo_up = false;
    is_at_neut = false;
    // Loop if robot isn't there yet
    pros::delay(DELAY_TIME);
    mogo_out(!is_out);
  }
}


///
// Driver Control
//  - when L1 is pressed, toggle between in and out.
//  - when L1 is held and the mogo lift is out, bring the mogo lift to neutral position
///
void
mogo_control() {
  // Toggle for mogo
  if (master.get_digital(DIGITAL_L1) && mogo_lock==0) {
    if (is_at_neut)
      mogo_up = false;
    else
      mogo_up = !mogo_up;

    is_at_neut = false;
    mogo_lock = 1;
  }
  // If mogo is held while the mogo lift is out, bring the mogo lift to neut position
  else if (master.get_digital(DIGITAL_L1)) {
    if (mogo_up) {
      controller_mogo_timer+=DELAY_TIME;
      if (controller_mogo_timer>=300)
        is_at_neut = true;
    }
  }
  // Reset when button is let go
  else if (!master.get_digital(DIGITAL_L1)) {
    mogo_lock  = 0;
    controller_mogo_timer = 0;
  }

  // Bring mogo to position based on is_at_neut and mogo_up
  if (is_at_neut)
    set_mogo_position(MOGO_NEUT, 127);
  else if (mogo_up)
    mogo_in();
  else if (!mogo_up)
    mogo_out();
}
