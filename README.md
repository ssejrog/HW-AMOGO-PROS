# Harvard-Westlake's AMOGO - PROS
  
This was made on VEXos 1.0.13, PROS Kernel 3.5.0
---
AMOGO (alliance mobile goal) is a ring focused robot that can fill a goal with rings in autonomous, hold an alliance mobile goal, platform, lift tipped mobile goals, and hold a neutral goal to the side of the robot.
![](AMOGO-Render.png)   

## Controls
- `L1` Mogo Toggle.  When the lift is out and the button is held, the lift will come to a middle position.
- `L2` Tilter Toggle.  When held, the tilter comes all the way down
- `R1` Intake + Conveyor In
- `R2` Intake + Conveyor Out
- Tank Drive (by default)

## Useful File Descriptions:
 - `src/auton.cpp`: [Autonomous routines (Solo AWP)](https://youtu.be/p1lgbKy1ZBE).
 - `src/conveyor.cpp`: Conveyor functions for opcontrol and autonomous, with antijam function.
 - `src/main.cpp`: Main file with on screen autonomous selection.
 - `src/mogo.cpp`: Mogo functions for opcontrol and autonomous.
 - `src/tilter.cpp`: Tilter functions for opcontrol and autonomous.

## EZ-Template
This code uses EZ-Template, a simple PROS template that handles drive base functions for VEX robots. [That can be found here](https://github.com/Unionjackjz1/EZ-Template).

### Warning

EZ-Template uses a unique PROS kernel that makes the emulated LCD pink instead of green.  Using this with hot/cold linking enabled (it is by default) could possible delete other PROS projects in other slots on your brain. 

To disable hot/cold linking, open your `Makefile` and change `USE_PACKAGE:=1` to `USE_PACKAGE:=0`.  Doing this will make wireless downloading slower. 

[Read more about hot/cold linking on the PROS docs](https://pros.cs.purdue.edu/v5/tutorials/topical/wireless-upload.html). 

## External Links

[Reveal Video](https://youtu.be/mmhPOVIbJWI)  
[VEX Forum with CAD](https://www.vexforum.com/t/harvard-westlake-robotics-amogo-x-dogo-reveal/92670)  

Basic Code  
[DOGO VEXcode](https://github.com/Unionjackjz1/HW-DOGO-VEXCODE/)    
[AMOGO VEXcode](https://github.com/Unionjackjz1/HW-AMOGO-VEXCODE/)  

Advanced Code  
[DOGO PROS](https://github.com/Unionjackjz1/HW-DOGO-PROS/)  
[AMOGO PROS](https://github.com/Unionjackjz1/HW-AMOGO-PROS/) 

## Contributors
Thank you to the following for making this project come to life:
- Avi Dube
- Ben Ren
- Dru Reed
- Jake Futterman
- Jess Zarchi
- Tripp Reed
- Yuanyang Lu
