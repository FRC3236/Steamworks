#ifndef ROBOTMAP_H
#define ROBOTMAP_H

//CAN PORTS
#define FrontLeftCANPort 1
#define BackLeftCANPort 2
#define BackRightCANPort 3
#define FrontRightCANPort 4
#define SolenoidICANPort 5
#define SolenoidIICANPort 6
#define SolenoidIIICANPort 7
#define SolenoidIVCANPort 8
#define PCMCANPort 11

//PWM PORTS
#define FrontLeftPWMPort 0
#define BackLeftPWMPort 1
#define BackRightPWMPort 2
#define FrontRightPWMPort 3
#define ClimberLeftPWMPort 4
#define ClimberRightPWMPort 5

//TURN INFORMATION
#define TURNMARGINOFERROR 0.004125
#define TURNVELOCITY 0.8

//JOYSTICK INFORMATION
#define RIGHTSTICKPORT 3
#define LEFTSTICKPORT 2

#define JOYSTICKDEADZONE 0.25

//DRIVER STICK
#define TRAVERSEBUTTON 1
#define SPINBUTTON 2
#define RESETBUTTON 11

//OPERATOR STICK
#define CLIMBERBUTTON 1


#endif  // ROBOTMAP_H
