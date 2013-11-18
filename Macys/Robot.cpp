// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "Robot.h"
#include "Math.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
DriveTrain* Robot::driveTrain = 0;
Shooter* Robot::shooter = 0;
OI* Robot::oi = 0;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
void Robot::RobotInit() {
	RobotMap::init();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	driveTrain = new DriveTrain();
	shooter = new Shooter();
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi = new OI();
	lw = LiveWindow::GetInstance();
	// instantiate the command used for the autonomous period
	File = RAWCConstants::getInstance();
	Robot::driveTrain->SetWheelbase(9.5, 22, 9.5);
	FLOffset = File->getValueForKey("FLOff");
	FROffset = File->getValueForKey("FROff");
	RLOffset = File->getValueForKey("RLOff");
	RROffset = File->getValueForKey("RROff");
	Robot::driveTrain->SetOffsets(FLOffset, FROffset, RLOffset, RROffset);
	
	Robot::driveTrain->frontLeftPos->SetAverageBits(256);
	Robot::driveTrain->frontRightPos->SetAverageBits(256);
	Robot::driveTrain->rearLeftPos->SetAverageBits(256);
	Robot::driveTrain->rearRightPos->SetAverageBits(256);
		
	Robot::driveTrain->frontLeft->Enable();
	Robot::driveTrain->frontRight->Enable();
	Robot::driveTrain->rearLeft->Enable();
	Robot::driveTrain->rearRight->Enable();
	Robot::shooter->comp->Start();
	
	prevTrigger = false;
	
	fireLeftTimer = GetClock();
	fireRightTimer = GetClock();
	leftArmTimer = GetClock();
	rightArmTimer = GetClock();
	leftFireFlag = false;
	rightFireFlag = false;
	leftArmFlag = false;
	rightArmFlag = false;
 }
	
void Robot::AutonomousInit() {
}
	
void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}
void Robot::DisabledPeriodic() {
	if(Robot::oi->getDriverJoystick()->GetRawButton(7))
		SMDB();
	
	Scheduler::GetInstance()->Run();
}
	
void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to 
	// continue until interrupted by another command, remove
	// this line or comment it out.
}
	
void Robot::TeleopPeriodic() {
	double pi = 3.14159;
//Starts updating smartdashboard variables	
	if(Robot::oi->getDriverJoystick()->GetRawButton(7))
		SMDB();
	
/******************************DRIVETRAIN CODE********************************/	
	
//Resets gyro to zero when crab starts
	if (!prevTrigger && Robot::oi->getDriverJoystick()->GetRawButton(1))
		Robot::driveTrain->gyroscope->Reset();
	prevTrigger = Robot::oi->getDriverJoystick()->GetRawButton(1);

	if(Robot::oi->getDriverJoystick()->GetRawButton(1))
	{//Crab	
		Robot::driveTrain->Crab(Robot::oi->getJoystickTwist(),-Robot::oi->getJoystickY(),Robot::oi->getJoystickX(),true);	
	}
	else 
	{//Steering
		Robot::driveTrain->Steer(Robot::oi->getScaledJoystickRadians(),Robot::oi->getJoystickMagnitude(),0.5);
	}
	
/************************SHOOTER CODE********************************/	
	
	
/***LEFT***/	
//Arms the left shooter.  Solenoid will stay open while button is pressed.
	if(Robot::oi->getDriverJoystick()->GetRawButton(11) && !leftArmFlag)
	{
		Robot::shooter->leftArm->Set(true);
		leftArmTimer = GetClock();
		leftArmFlag = true;
	}
	if(!Robot::oi->getDriverJoystick()->GetRawButton(11) && fireLeftTimer + .5 < GetClock())
	{
		Robot::shooter->leftArm->Set(false);
		leftArmTimer = GetClock();
		leftArmFlag = false;
	}
	
	
//Fires the left shooter.  Solenoid will stay open for 1 sec after button is pressed.
	if(Robot::oi->getDriverJoystick()->GetRawButton(3) && !leftFireFlag && leftArmTimer + 1 < GetClock())
	{
		Robot::shooter->fireLeft->Set(true);
		fireLeftTimer = GetClock();
		leftFireFlag = true;
	}
	
	if(fireLeftTimer + .5 < GetClock())
	{
		Robot::shooter->fireLeft->Set(false);
	}
	if(!Robot::oi->getDriverJoystick()->GetRawButton(3))
	{
		leftFireFlag = false;
	}
	
/***RIGHT***/	
//Arms the right shooter.  Solenoid will stay open while button is pressed.
	if(Robot::oi->getDriverJoystick()->GetRawButton(12) && !rightArmFlag)
	{
		Robot::shooter->rightArm->Set(true);
		rightArmTimer = GetClock();
		rightArmFlag = true;
	}
	
	if(!Robot::oi->getDriverJoystick()->GetRawButton(12) && fireRightTimer + .5 < GetClock())
	{
		Robot::shooter->rightArm->Set(false);
		rightArmTimer = GetClock();
		rightArmFlag = false;
	}
	
//Fires the right shooter.  Solenoid will stay open for 1 sec after button is pressed.
	if(Robot::oi->getDriverJoystick()->GetRawButton(4) && !rightFireFlag && rightArmTimer + 1 < GetClock())
	{
		Robot::shooter->fireRight->Set(true);
		fireRightTimer = GetClock();
		rightFireFlag = true;
	}
	
	if(fireRightTimer + .5 < GetClock())
	{
		Robot::shooter->fireRight->Set(false);
		rightFireFlag = false;
	}	
	
	if(!Robot::oi->getDriverJoystick()->GetRawButton(4))
	{
		rightFireFlag = false;
	}
		
		
}
void Robot::TestPeriodic() {
	lw->Run();
}
void Robot::SMDB() {
	//Joystick Variables
	SmartDashboard::PutNumber("StickMagnitude",Robot::oi->getDriverJoystick()->GetMagnitude());
	SmartDashboard::PutNumber("StickDirection",Robot::oi->getDriverJoystick()->GetDirectionRadians());
	SmartDashboard::PutNumber("StickTwist",Robot::oi->getDriverJoystick()->GetTwist());
	SmartDashboard::PutNumber("StickVelocity", (fabs(Robot::oi->getDriverJoystick()->GetY())+fabs(Robot::oi->getDriverJoystick()->GetX()))/2);
	SmartDashboard::PutNumber("GyroAngle", Robot::driveTrain->gyroscope->GetAngle());
	SmartDashboard::PutNumber("ScaledRadians",Robot::oi->getScaledJoystickRadians());
	SmartDashboard::PutNumber("ScalingFactor",Robot::oi->getDriverJoystick()->GetTwist()/2+1.5);
	//Wheel Module Voltages
	SmartDashboard::PutNumber("FrontLeftVol",Robot::driveTrain->frontLeftPos->GetAverageVoltage());
	SmartDashboard::PutNumber("FrontRightVol",Robot::driveTrain->frontRightPos->GetAverageVoltage());
	SmartDashboard::PutNumber("RearLeftVol",Robot::driveTrain->rearLeftPos->GetAverageVoltage());
	SmartDashboard::PutNumber("RearRightVol",Robot::driveTrain->rearRightPos->GetAverageVoltage());
	//Wheel Module Values
	SmartDashboard::PutNumber("FrontLeftValue",Robot::driveTrain->frontLeftPos->GetAverageValue());
	SmartDashboard::PutNumber("FrontRightValue",Robot::driveTrain->frontRightPos->GetAverageValue());
	SmartDashboard::PutNumber("RearLeftValue",Robot::driveTrain->rearLeftPos->GetAverageValue());
	SmartDashboard::PutNumber("RearRightValue",Robot::driveTrain->rearRightPos->GetAverageValue());
	
	//Wheel Module Errors
	SmartDashboard::PutNumber("FLError", Robot::driveTrain->frontLeft->GetError());
	SmartDashboard::PutNumber("FRError", Robot::driveTrain->frontRight->GetError());
	SmartDashboard::PutNumber("RLError", Robot::driveTrain->rearLeft->GetError());
	SmartDashboard::PutNumber("RRError", Robot::driveTrain->rearRight->GetError());
	//Wheel Module Setpoints
	SmartDashboard::PutNumber("FLSetPoint", Robot::driveTrain->frontLeft->GetSetpoint());
	SmartDashboard::PutNumber("FRSetPoint", Robot::driveTrain->frontRight->GetSetpoint());
	SmartDashboard::PutNumber("RLSetPoint", Robot::driveTrain->rearLeft->GetSetpoint());
	SmartDashboard::PutNumber("RRSetPoint", Robot::driveTrain->rearRight->GetSetpoint());
}
START_ROBOT_CLASS(Robot);
