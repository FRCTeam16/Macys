// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "OI.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/SetWheelOffsets.h"
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
OI::OI() {
	// Process operator interface input here.
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	driverJoystick = new Joystick(1);
	
     
        // SmartDashboard Buttons
	SmartDashboard::PutData("SetWheelOffsets", new SetWheelOffsets());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
void OI::setOIDigitalOutput8(bool value) {
	DriverStation::GetInstance()->SetDigitalOut(8, value);
}
void OI::setOIDigitalOutput7(bool value) {
	DriverStation::GetInstance()->SetDigitalOut(7, value);
}
void OI::setOIDigitalOutput6(bool value) {
	DriverStation::GetInstance()->SetDigitalOut(6, value);
}
void OI::setOIDigitalOutput5(bool value) {
	DriverStation::GetInstance()->SetDigitalOut(5, value);
}
void OI::setOIDigitalOutput4(bool value) {
	DriverStation::GetInstance()->SetDigitalOut(4, value);
}
void OI::setOIDigitalOutput3(bool value) {
	DriverStation::GetInstance()->SetDigitalOut(3, value);
}
void OI::setOIDigitalOutput2(bool value) {
	DriverStation::GetInstance()->SetDigitalOut(2, value);
}
void OI::setOIDigitalOutput1(bool value) {
	DriverStation::GetInstance()->SetDigitalOut(1, value);
}
bool OI::getGyroReset() {
	return DriverStation::GetInstance()->GetDigitalIn(5);
}
bool OI::getWheelOffset() {
	return DriverStation::GetInstance()->GetDigitalIn(6);
}
Joystick* OI::getDriverJoystick() {
	return driverJoystick;
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
double OI::getScaledJoystickRadians() {
	double pi = 3.14159;
	double scaledRadians = pi/2;
	double scalingFactor = 1;
	double steerAngle = pi/2;
	double bottomScaling = 1.15;
	double topScaling = 1.75;
	
	
	steerAngle = driverJoystick->GetDirectionRadians();
	if(steerAngle > pi)
		steerAngle = pi;
	if(steerAngle < -pi)
		steerAngle = -pi;
	
	if(steerAngle < -pi/2)
		steerAngle = -pi/2 - steerAngle;
	else if(steerAngle < pi/2)
		steerAngle = pi/2 + steerAngle;
	else
		steerAngle = 3*pi/2 - steerAngle;
//	scalingFactor = driverJoystick->GetTwist()/2+1.5;
	
	scalingFactor = bottomScaling + driverJoystick->GetMagnitude()*(topScaling - bottomScaling);
	
	if(steerAngle <= pi/2)
		scaledRadians = (-(pi/2)/pow(pow(-pi/2,2),scalingFactor/2))*pow(pow(steerAngle-pi/2,2),scalingFactor/2) + pi/2;
	else //if(steerAngle <= pi)
		scaledRadians = ((pi/2)/pow((pi/2),scalingFactor))*pow(steerAngle-pi/2,scalingFactor) + pi/2;
	
	return scaledRadians;
}
