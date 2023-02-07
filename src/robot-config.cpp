#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

brain  Brain;

bumper Limit = bumper(Brain.ThreeWirePort.A);
controller Controller1 = controller(primary);

motor left1 = motor(vex::PORT1, vex::gearSetting::ratio36_1, false);
motor left2 = motor(vex::PORT2, vex::gearSetting::ratio36_1, true);
motor left3 = motor(vex::PORT3, vex::gearSetting::ratio36_1, false);
motor_group left_drive = motor_group(left1, left2, left3);

motor right1 = motor(vex::PORT4, vex::gearSetting::ratio36_1, false);
motor right2 = motor(vex::PORT5, vex::gearSetting::ratio36_1, true);
motor right3 = motor(vex::PORT6, vex::gearSetting::ratio36_1, false);
motor_group right_drive = motor_group(right1, right2, right3);

optical catapult_side = optical(vex::PORT10);
optical intake_side = optical(vex::PORT20);

motor catapult = motor(vex::PORT7, vex::gearSetting::ratio36_1, false);
motor intake = motor(vex::PORT8, vex::gearSetting::ratio36_1, false);

digital_out expansion = digital_out(Brain.ThreeWirePort.B);

bool RemoteControlCodeEnabled = true;

void vexcodeInit( void ) {}
