#pragma once

extern bool tilter_up;

void set_tilter(int input);
void zero_tilter();
int get_tilter();
int get_tilter_vel();

bool timeout(int target, int vel, int current);
void set_tilter_position(int target, int speed, bool hold = false);

void tilter_in  (bool hold = false);
void tilter_down(bool hold = false);
void tilter_out (bool hold = false);

void tilter_control();
