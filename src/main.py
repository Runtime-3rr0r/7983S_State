# ------------------------------------------------------------------- #
#                                                                     #
# 	Module:       main.py                                             #
# 	Author:       Christian Mills                                     #
# 	Created:      1/25/2023, 10:03:36 PM                              #
# 	Description:  Cata-Bot                                            #
#                                                                     #
# ------------------------------------------------------------------- #

# Library imports
from vex import *

# Define electronics
brain = Brain()
controller = Controller(PRIMARY)

# Define limit switch
limit = Limit(brain.three_wire_port.a)

# Define lights
catapult_side = Optical(Ports.PORT10)
intake_side = Optical(Ports.PORT20)

# Define pnuematics
expansion = DigitalOut(brain.three_wire_port.b)

# Define motors
catapult = Motor(Ports.PORT7, GearSetting.RATIO_36_1)

intake = Motor(Ports.PORT8,GearSetting.RATIO_36_1)

left1 = Motor(Ports.PORT1, GearSetting.RATIO_36_1)
left2 = Motor(Ports.PORT2, GearSetting.RATIO_36_1, True)
left3 = Motor(Ports.PORT3, GearSetting.RATIO_36_1)
left_drive = MotorGroup(left1, left2, left3)
right1 = Motor(Ports.PORT4, GearSetting.RATIO_36_1)
right2 = Motor(Ports.PORT5, GearSetting.RATIO_36_1, True)
right3 = Motor(Ports.PORT6, GearSetting.RATIO_36_1)
right_drive = MotorGroup(right1, right2, right3)


# "Pre-Auton" is a setup function for our program

def preAuton():
    
    # Set global variables
    global Drive
    global Lastpress
    global Currenttime
    global Drivemultiplier
    global Turnspeed
    global Fwd
    global Trn

    # User control variables
    Drive = True
    Lastpress = 0
    Currenttime = 0
    Drivemultiplier = 1
    Turnspeed = -0.5
    Fwd = 0
    Trn = 0

    # Set pnuematics
    expansion.set(True)

    # Electronics setup
    left_drive.set_velocity(100, PERCENT)
    right_drive.set_velocity(100, PERCENT)
    intake.set_velocity(100, PERCENT)
    catapult.set_velocity(100, PERCENT)
    catapult_side.set_light_power(100)
    intake_side.set_light_power(100)
    catapult.set_timeout(2, SECONDS)
    catapult.set_max_torque(100, PERCENT)

    # Display setup
    controller.screen.clear_screen()
    brain.screen.draw_image_from_file("vex.bmp", 1, 1)


# "Auton" contains the autonomous portion code

def auton():
    
    print("Hello World!")


# "Toggle-Drive" toggles the current drive state

def toggleDrive():
    
    # Pull drive direction
    global Drive

    # Invert current drive direction
    Drive = not Drive


# "User-Control" contains the user-control portion code

def userControl():

    # Pull global variables
    global Lastpress
    global Currenttime
    global Drivemultiplier
    global Turnspeed
    global Fwd
    global Trn

    # Main user control loop
    while True:
        
        # Toggle drive
        if controller.buttonRight.pressing():
            
            if Currenttime - Lastpress > 100:
                
                toggleDrive()
                Lastpress = Currenttime
        

        # Toggle lights, display, drive direction, and turn speed
        if Drive:
            
            Drivemultiplier = 1
            catapult_side.set_light(LedStateType.OFF)
            intake_side.set_light(LedStateType.ON)
            controller.screen.set_cursor(1, 1)
            controller.screen.print("INTAKE MODE")
            Turnspeed = -0.5

        else:
            
            Drivemultiplier = -1
            catapult_side.set_light(LedStateType.ON)
            intake_side.set_light(LedStateType.OFF)
            controller.screen.set_cursor(1, 1)
            controller.screen.print("LAUNCH MODE")
            Turnspeed = -0.25


        # Expansion
        if controller.buttonDown.pressing():
            
            expansion.set(False)


        # Intake
        if controller.buttonR2.pressing():
            
            intake.spin(FORWARD)

        elif controller.buttonY.pressing():
            
            intake.spin(REVERSE)

        else:
            
            intake.stop()


        # Catapult
        if controller.buttonR1.pressing():
            
            catapult.spin_for(FORWARD, 0.4, TURNS)
        

        # Autowind catapult
        if not limit.pressing():
            
            catapult.spin(FORWARD)
        
        else:
            
            catapult.stop()

        
        # Turning control with parabolic drive and deadzone
        if abs(controller.axis1.position()) > 1:
            
            Trn = controller.axis1.position()

            if Trn < 0:

                left_drive.spin(REVERSE)
                right_drive.spin(REVERSE)

            else:

                left_drive.spin(FORWARD)
                right_drive.spin(FORWARD)


            Trn = (100 - (Trn ** 2 / 100)) * Turnspeed # Change back

        else:

            Trn = 0


        # Forward control with parabolic drive and deadzone
        if abs(controller.axis3.position()) > 5:

            Fwd = controller.axis3.position()

            if Fwd < 0:

                left_drive.spin(REVERSE)
                right_drive.spin(REVERSE)

            else:

                left_drive.spin(FORWARD)
                right_drive.spin(FORWARD)

            
            Fwd = (100 - (Fwd ** 2 / 100)) * Drivemultiplier # Change back

        else:

            Fwd = 0


        # Set motor speeds
        left_drive.set_velocity(Trn + Fwd, PERCENT)
        right_drive.set_velocity(Trn - Fwd, PERCENT)

        # wait and add time to timer
        Currenttime += 20
        wait(20, MSEC)

# Call competition function
comp = Competition(userControl, auton)
preAuton()