/*
	general baseclass representing a stage
	Author: Urs Hofmann
	Mail: hofmannu@ethz.ch
	Date: 18.05.2021
*/

#ifndef STAGE_H
#define STAGE_H

#include <iostream>
#include <math.h>
#include <chrono>
#include <thread>

using namespace std;

class stage
{
private:
	float pos = 0;
	float vel = 100;
	float acc = 10;

	float minPos = 0; // minimum position allowed for stage
	float maxPos = 50; // maximum position allowed for stage

	float minVel = 1;
	float maxVel = 500;

	float minAcc = 1;
	float maxAcc = 5000;	

	bool isConnected = 0;
	bool isHomed = 0;
	bool isEnabled = 0;

	void Connect();
	void Disconnect();
	void Enable();
	void Disable();

	float estimTRequired(const float oldPos, const float newPos);
public: 
	
	// get and set functions
	void set_pos(const float _pos);
	void set_vel(const float _vel);
	void set_acc(const float _acc);
	float get_vel() const {return vel;};
	float get_acc() const {return acc;};
	float get_pos() const {return pos;};

	void set_isConnected(const bool _isConnected);
	bool get_isConnected() const {return isConnected;};

	void set_isEnabled(const bool _isEnabled);
	bool get_isEnabled() const {return isEnabled;};

	void Home();


};

#endif