/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Christian Mills                                           */
/*    Created:      Tue Jan 31 2023                                           */
/*    Description:  7983S Cata-Bot                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Limit                bumper        A               
// Controller1          controller                    
// left_drive           motor_group   1, 2            
// left3                motor         3               
// right_drive          motor_group   4, 5            
// right3               motor         6               
// catapult_side        optical       10              
// intake_side          optical       20              
// catapult             motor         7               
// intake               motor         8               
// expansion            digital_out   B               

#include "vex.h"
#include "gifclass.h"

using namespace vex;

// Global Instances
competition Competition;

bool Drive = true;
int  Lastpress = 0;
int  Drivemultiplier = 1;
int  Currenttime = 0;
int  Screentype = 1;
int  Fwd = 0;
int  Trn = 0;
int  AxsF = 0;
int  AxsT = 0;
int  Auton;

// 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17

/*----------------------START DISPLAY CODE--------------------*/

// Cancel Button Parameters
int Cancelx = 0;
int Cancely = 0;
int Cancelw = 155;
int Cancelh = 50;

// Auton Title Parameters
int Autonx = 160;
int Autony = 0;
int Autonw = 155;
int Autonh = 50;

// Red Button Parameters
int Redx = 190;
int Redy = 57;
int Redw = 100;
int Redh = 25;

// Blue Button Parameters
int Bluex = 352;
int Bluey = 57;
int Bluew = 100;
int Blueh = 25;

// None Button Parameters
int Nonex = 28;
int Noney = 57;
int Nonew = 100;
int Noneh = 25;

// Confirm Button Parameters
int Confirmx = 315;
int Confirmy = 30;
int Confirmw = 155;
int Confirmh = 50;

// Near Button Parameters
int Nearx = 0;
int Neary = 0;
int Nearw = 0;
int Nearh = 0;

// Store Button Parameters
int Storex = 0;
int Storey = 0;
int Storew = 0;
int Storeh = 0;

// Shoot Button Parameters
int Shootx = 0;
int Shooty = 0;
int Shootw = 0;
int Shooth = 0;

// Far Button Parameters
int Farx = 0;
int Fary = 0;
int Farw = 0;
int Farh = 0;

void screen1(void) {
  
  // Auton Panel Button
  Brain.Screen.clearScreen();
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(135, 197, 215, 30);
  Brain.Screen.setCursor(11, 15);
  Brain.Screen.print("Open Auton-Selection");

  // Motor Detail Screen
  Brain.Screen.drawRectangle(0, 75, 125, 30);
  Brain.Screen.setCursor(5, 2);
  Brain.Screen.print("See Details");

  // Motor Temps
  Brain.Screen.setFillColor(transparent);
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Drive: ");
  Brain.Screen.setCursor(2, 1);
  Brain.Screen.print("Cata: ");
  Brain.Screen.setCursor(3, 1);
  Brain.Screen.print("Intake: ");

}
void screen2(void) {
  
  // Motor Names
  Brain.Screen.clearScreen();
  Brain.Screen.setFillColor(transparent);
  Brain.Screen.setPenColor(white);
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Left Front: ");
  Brain.Screen.setCursor(2, 1);
  Brain.Screen.print("Left Mid: ");
  Brain.Screen.setCursor(3, 1);
  Brain.Screen.print("Left Rear: ");
  Brain.Screen.setCursor(5, 1);
  Brain.Screen.print("Right Front: ");
  Brain.Screen.setCursor(6, 1);
  Brain.Screen.print("Right Mid: ");
  Brain.Screen.setCursor(7, 1);
  Brain.Screen.print("Right Rear: ");
  Brain.Screen.setCursor(9, 1);
  Brain.Screen.print("Cata: ");
  Brain.Screen.setCursor(10, 1);
  Brain.Screen.print("Intake: ");

  // Return Home button
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(224, 98, 35, 25);
  Brain.Screen.setPenColor(white);
  Brain.Screen.setCursor(6, 24);
  Brain.Screen.print("Ok");
}
void screen3(void) {
  
  // Cancel button
  Brain.Screen.clearScreen();
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(Cancelx, Cancely, Cancelw, Cancelh);
  Brain.Screen.setCursor(1, 6);
  Brain.Screen.print("Cancel");

  // Auton Selection Title
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(Autonx, Autony, Autonw, Autonh);
  Brain.Screen.setCursor(1, 19);
  Brain.Screen.print("Auton-Select");

  // None Button
  Brain.Screen.setFillColor(white);
  Brain.Screen.setPenColor(black);
  Brain.Screen.drawRectangle(Nonex, Noney, Nonew, Noneh);
  Brain.Screen.setCursor(4, 7);
  Brain.Screen.print("None");

  // Red Button
  Brain.Screen.setFillColor(red);
  Brain.Screen.setPenColor(white);
  Brain.Screen.drawRectangle(Redx, Redy, Redw, Redh);
  Brain.Screen.setCursor(4, 23);
  Brain.Screen.print("Red");

  // Blue Button
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(Bluex, Bluey, Bluew, Blueh);
  Brain.Screen.setCursor(4, 39);
  Brain.Screen.print("Blue");
}
void screen4(void) {
 
  // Cancel button
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(Cancelx, Cancely, Cancelw, Cancelh);
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Cancel");

  // Auton Selection Title
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(Autonx, Autony, Autonw, Autonh);
  Brain.Screen.setCursor(1, 24);
  Brain.Screen.print("Auton-Selection");

  // Red Button
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(Redx, Redy, Redw, Redh);
  Brain.Screen.setCursor(3, 1);
  Brain.Screen.print("Red");

  // Near Button

  // Far Button

}
void screen5(void) {
 
  // Cancel button
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(Cancelx, Cancely, Cancelw, Cancelh);
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Cancel");

  // Auton Selection Title
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(Autonx, Autony, Autonw, Autonh);
  Brain.Screen.setCursor(1, 24);
  Brain.Screen.print("Auton-Selection");

  // Red Button
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(Redx, Redy, Redw, Redh);
  Brain.Screen.setCursor(3, 1);
  Brain.Screen.print("Red");
  
  // Far Button

  // Store Button

  // Score Button

}
void screen6(void) {
  
  // Cancel button
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(Cancelx, Cancely, Cancelw, Cancelh);
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Cancel");

  // Auton Selection Title
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(Autonx, Autony, Autonw, Autonh);
  Brain.Screen.setCursor(1, 24);
  Brain.Screen.print("Auton-Selection");

  // Red Button
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(Redx, Redy, Redw, Redh);
  Brain.Screen.setCursor(3, 1);
  Brain.Screen.print("Red");
  
  // Near Button

  // Store Button

  // Score Button

}
void screen7(void) {
 
  // Cancel button
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(Cancelx, Cancely, Cancelw, Cancelh);
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Cancel");

  // Auton Selection Title
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(Autonx, Autony, Autonw, Autonh);
  Brain.Screen.setCursor(1, 24);
  Brain.Screen.print("Auton-Selection");

  // Red Button
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(Redx, Redy, Redw, Redh);
  Brain.Screen.setCursor(3, 1);
  Brain.Screen.print("Red");

  // Confirm Button
  Brain.Screen.setFillColor(green);
  Brain.Screen.drawRectangle(315, 30, 155, 50);
  Brain.Screen.setCursor(1, 40);
  Brain.Screen.print("Confirm");

  // Near Button

  // Store Button

}
void screen8(void) {

  // Cancel button

  // Auton Selection Title

  // Confirm Button

  // Red Button

  // Near Button

  // Score Button

}
void screen9(void) {

  // Cancel button

  // Auton Selection Title

  // Confirm Button

  // Red Button

  // Far Button

  // Store Button

}
void screen10(void) {

  // Cancel button

  // Auton Selection Title

  // Confirm Button

  // Red Button

  // Far Button

  // Score Button

}
void screen11(void) {
  
  // Cancel button

  // Auton Selection Title

  // Confirm Button

  // Blue Button

  // Near Button

  // Far Button

}
void screen12(void) {
  
  // Cancel button

  // Auton Selection Title

  // Confirm Button

  // Blue Button

  // Near Button

  // Store Button

  // Score Button

}
void screen13(void) {

  // Cancel button

  // Auton Selection Title

  // Confirm Button

  // Blue Button

  // Far Button

  // Store Button

  // Score Button

}
void screen14(void) {

  // Cancel button

  // Auton Selection Title

  // Confirm Button

  // Blue Button

  // Far Button

  // Store Button

}
void screen15(void) {

  // Cancel button

  // Auton Selection Title

  // Confirm Button

  // Blue Button

  // Far Button

  // Score Button

}
void screen16(void) {
  
  // Cancel button

  // Auton Selection Title

  // Confirm Button

  // Blue Button

  // Near Button

  // Store Button

}
void screen17(void) {

  // Cancel button

  // Auton Selection Title

  // Confirm Button

  // Blue Button

  // Near Button

  // Score Button

}
void screen18(void) {

  // Cancel button
  Brain.Screen.clearScreen();
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(Cancelx, Cancely, Cancelw, Cancelh);
  Brain.Screen.setCursor(1, 6);
  Brain.Screen.print("Cancel");

  // Auton Selection Title
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(Autonx, Autony, Autonw, Autonh);
  Brain.Screen.setCursor(1, 19);
  Brain.Screen.print("Auton-Select");

  // None Button
  Brain.Screen.setFillColor(white);
  Brain.Screen.setPenColor(black);
  Brain.Screen.drawRectangle(Nonex, Noney, Nonew, Noneh);
  Brain.Screen.setCursor(4, 7);
  Brain.Screen.print("None");
  
  // Confirm Button
  Brain.Screen.setFillColor(green);
  Brain.Screen.setPenColor(white);
  Brain.Screen.drawRectangle(Confirmx, Confirmy, Confirmw, Confirmh);
  Brain.Screen.setCursor(1, 40);
  Brain.Screen.print("Confirm");

}
void screen19(void) {

  // Auton Panel Button
  Brain.Screen.clearScreen();
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFillColor(green);
  Brain.Screen.drawRectangle(135, 197, 215, 30);
  Brain.Screen.setCursor(11, 15);
  Brain.Screen.print("Open Auton-Selection");

  // Motor Detail Screen
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(0, 75, 125, 30);
  Brain.Screen.setCursor(5, 2);
  Brain.Screen.print("See Details");

  // Motor Temps
  Brain.Screen.setFillColor(transparent);
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Drive: ");
  Brain.Screen.setCursor(2, 1);
  Brain.Screen.print("Cata: ");
  Brain.Screen.setCursor(3, 1);
  Brain.Screen.print("Intake: ");

}
void check_buttons(void) {
  if (Screentype == 1 or Screentype == 19) {
    if (Brain.Screen.pressing()) {
      
      // Auton-Selection Panel Button
      if (Brain.Screen.xPosition() >= 130 and Brain.Screen.xPosition()
          >= 192 and Brain.Screen.xPosition() <= 355 and Brain.Screen.yPosition() <= 232) {
        Screentype = 3;
        screen3();
      }

      // See Details Button
      if (Brain.Screen.xPosition() >= -5 and Brain.Screen.xPosition()
          >= 70 and Brain.Screen.xPosition() <= 130 and Brain.Screen.yPosition() <= 110) {
        Screentype = 2;
        screen2();
      }
    }
  }
  if (Screentype == 2) {
    if (Brain.Screen.pressing()) {

      // Ok Button
      if (Brain.Screen.xPosition() >= 219 and Brain.Screen.xPosition()
          >= 93 and Brain.Screen.xPosition() <= 264 and Brain.Screen.yPosition() <= 128) {
        Screentype = 1;
        screen1();
      }
    }
  }
  if (Screentype == 3) {
    if (Brain.Screen.pressing()) {
      
      // Red Button
      if (Brain.Screen.xPosition() >= 185 and Brain.Screen.xPosition()
          >= 52 and Brain.Screen.xPosition() <= 295 and Brain.Screen.yPosition() <= 87) {
        Screentype = 4;
        screen4();
      }

      // Blue Button
      if (Brain.Screen.xPosition() >= 347 and Brain.Screen.xPosition()
          >= 52 and Brain.Screen.xPosition() <= 457 and Brain.Screen.yPosition() <= 87) {
        Screentype = 11;
        screen11();
      }

      // None Button
      if (Brain.Screen.xPosition() >= 23 and Brain.Screen.xPosition()
          >= 52 and Brain.Screen.xPosition() <= 132 and Brain.Screen.yPosition() <= 87) {
        Screentype = 18;
        screen18();
      }

      // Cancel Button
      if (Brain.Screen.xPosition() >= -5 and Brain.Screen.xPosition()
          >= -5 and Brain.Screen.xPosition() <= 160 and Brain.Screen.yPosition() <= 55) {
        Screentype = 1;
        screen1();
      }

    }
  }
  if (Screentype == 18) {
    if (Brain.Screen.pressing()) {

      // Cancel Button
      if (Brain.Screen.xPosition() >= -5 and Brain.Screen.xPosition()
          >= -5 and Brain.Screen.xPosition() <= 160 and Brain.Screen.yPosition() <= 55) {
        Screentype = 1;
        screen1();
      }

      // Confirm Button
      if (Brain.Screen.xPosition() >= 310 and Brain.Screen.xPosition()
          >= 25 and Brain.Screen.xPosition() <= 475 and Brain.Screen.yPosition() <= 85) {
        Screentype = 19;
        screen19();
        Auton = 0;
      }
    }
  }
}
void update_screen(void) {
  if (Screentype == 1 or Screentype == 19) {
    
    // Drive Temp
    if (left1.temperature() < 40 and left2.temperature() < 40 and left3.temperature()
        < 40 and right1.temperature() < 40 and right2.temperature() < 40 and
        right3.temperature() < 40) {
      Brain.Screen.setPenColor(green);
      Brain.Screen.setCursor(1, 7);
      Brain.Screen.print("OK");
    } else {
      Brain.Screen.setPenColor(red);
      Brain.Screen.setCursor(1, 7);
      Brain.Screen.print("HOT");
    }

    // Cata Temp
    if (catapult.temperature() < 40) {
      Brain.Screen.setPenColor(green);
      Brain.Screen.setCursor(2, 6);
      Brain.Screen.print("OK");
    } else {
      Brain.Screen.setPenColor(red);
      Brain.Screen.setCursor(2, 6);
      Brain.Screen.print("HOT");
    }

    // Intake Temp
    if (intake.temperature() < 40) {
      Brain.Screen.setPenColor(green);
      Brain.Screen.setCursor(3, 8);
      Brain.Screen.print("OK");
    } else {
      Brain.Screen.setPenColor(red);
      Brain.Screen.setCursor(2, 6);
      Brain.Screen.print("HOT");
    }
  }
  if (Screentype == 2) {
    
    // Numerical Front Left Temp
    if (left1.temperature() < 40) {
      Brain.Screen.setPenColor(green);
      Brain.Screen.setCursor(1, 12);
      Brain.Screen.print(left1.temperature());
    } else {
      Brain.Screen.setPenColor(red);
      Brain.Screen.setCursor(1, 12);
      Brain.Screen.print(left1.temperature());
    }

    // Numerical Mid Left Temp
    if (left2.temperature() < 40) {
      Brain.Screen.setPenColor(green);
      Brain.Screen.setCursor(2, 10);
      Brain.Screen.print(left2.temperature());
    } else {
      Brain.Screen.setPenColor(red);
      Brain.Screen.setCursor(2, 10);
      Brain.Screen.print(left2.temperature());
    }

    // Numerical Rear Left Temp
    if (left3.temperature() < 40) {
      Brain.Screen.setPenColor(green);
      Brain.Screen.setCursor(1, 11);
      Brain.Screen.print(left3.temperature());
    } else {
      Brain.Screen.setPenColor(red);
      Brain.Screen.setCursor(1, 11);
      Brain.Screen.print(left3.temperature());
    }

    // Numerical Front Right Temp
    if (right3.temperature() < 40) {
      Brain.Screen.setPenColor(green);
      Brain.Screen.setCursor(5, 13);
      Brain.Screen.print(right3.temperature());
    } else {
      Brain.Screen.setPenColor(red);
      Brain.Screen.setCursor(5, 13);
      Brain.Screen.print(right3.temperature());
    }

    // Numerical Mid Right Temp
    if (right2.temperature() < 40) {
      Brain.Screen.setPenColor(green);
      Brain.Screen.setCursor(6, 11);
      Brain.Screen.print(right2.temperature());
    } else {
      Brain.Screen.setPenColor(red);
      Brain.Screen.setCursor(6, 11);
      Brain.Screen.print(right2.temperature());
    }

    // Numerical Rear Right Temp
    if (right3.temperature() < 40) {
      Brain.Screen.setPenColor(green);
      Brain.Screen.setCursor(7, 12);
      Brain.Screen.print(right3.temperature());
    } else {
      Brain.Screen.setPenColor(red);
      Brain.Screen.setCursor(7, 12);
      Brain.Screen.print(right3.temperature());
    }

    // Numerical Cata Temp
    if (catapult.temperature() < 40) {
      Brain.Screen.setPenColor(green);
      Brain.Screen.setCursor(9, 6);
      Brain.Screen.print(catapult.temperature());
    } else {
      Brain.Screen.setPenColor(red);
      Brain.Screen.setCursor(9, 6);
      Brain.Screen.print(catapult.temperature());
    }

    // Numerical Intake Temp
    if (intake.temperature() < 40) {
      Brain.Screen.setPenColor(green);
      Brain.Screen.setCursor(10, 8);
      Brain.Screen.print(intake.temperature());
    } else {
      Brain.Screen.setPenColor(red);
      Brain.Screen.setCursor(10, 8);
      Brain.Screen.print(intake.temperature());
    }
  }
}
/*----------------------END DISPLAY CODE--------------------*/

void pre_auton(void) {

  // Electronics setup
  vexcodeInit();
  expansion.set(true);
  intake_side.setLightPower(100, percentUnits::pct);
  catapult_side.setLightPower(100, percentUnits::pct);
  catapult.setTimeout(2, timeUnits::sec);
  catapult.setStopping(coast);

  // Display setup
  Controller1.Screen.clearScreen();
  screen1();
}

void autonomous(void) {
}

void usercontrol(void) {
  //vex::Gif gif("Rock.gif", 120, 0);

  while (true) {

      // Toggle drive
      if (Controller1.ButtonRight.pressing()) {
        if (Currenttime - Lastpress > 300) {
          Drive = !Drive;
          Lastpress = Currenttime;
        }
      }

      // Toggle lights/display/drive direction
      if (Drive) {
        Drivemultiplier = 1;
        catapult_side.setLight(ledState::off);
        intake_side.setLight(ledState::on);
      } else {
        Drivemultiplier = -1;
        catapult_side.setLight(ledState::on);
        intake_side.setLight(ledState::off);
      }

      // Expansion
      if (Controller1.ButtonDown.pressing()){
        expansion.set(false);
      } else {
        expansion.set(true);
      }

      // Intake
      if (Controller1.ButtonR2.pressing()) {
        intake.spin(forward, 100, pct);
      } else if (Controller1.ButtonY.pressing()) {
        intake.spin(reverse);
      } else {
        intake.stop();
      }

      // Catapult
      if (Controller1.ButtonR1.pressing()) {
        catapult.spinFor(forward, 0.4, turns);
      }

      // Autowind catapult
      if (not Limit.pressing()) {
        catapult.spin(forward);
      } else {
        catapult.stop();
      }

      // Turning with exponential drive/deadzone
      if (abs(Controller1.Axis1.position()) > 1) {
        AxsT = Controller1.Axis1.position();
        Trn = (AxsT * AxsT) / 100 * -1;
        
        if (AxsT < 0) {
          Trn *= -1;
        }
      } else {
        Trn = 0;
      }

      // Forward with exponential drive/deadzone
      if (abs(Controller1.Axis3.position()) > 1) {
        AxsF = Controller1.Axis3.position();
        Fwd = (AxsF * AxsF) / 100;

        if (AxsF < 0) {
          Fwd *= -1;
        }
        Fwd *= Drivemultiplier;
      } else {
        Fwd = 0;
      }

      // Enable motors
      left_drive.setVelocity(Trn + Fwd, percentUnits::pct);
      right_drive.setVelocity(Trn - Fwd, percentUnits::pct);

      left_drive.spin(forward);
      right_drive.spin(forward);

      // Wait and update program
      check_buttons();
      Currenttime += 20;
      wait(20, msec);
  }
}

int main() {
  // Run the pre-autonomous function.
  pre_auton();

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
