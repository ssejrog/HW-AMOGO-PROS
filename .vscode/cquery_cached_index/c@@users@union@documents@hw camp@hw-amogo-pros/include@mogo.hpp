#pragma once

extern bool mogo_up;

void set_mogo(int input);
void zero_mogo();
int get_mogo();
int get_mogo_vel();
void set_mogo_position(int target, int speed);

void mogo_in  (bool hold = false);
void mogo_neut(bool hold = false);
void mogo_out (bool hold = false);

void mogo_control();
