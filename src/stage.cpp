#include "stage.h"

// estimate the time required for a movement between two positions
float stage::estimTRequired(const float oldPos, const float newPos)
{
	const float dist = fabs(oldPos - newPos);
	const float tAcc = vel / acc;
	const float distCrit = 2 * 0.5 * acc * tAcc * tAcc;
	float tMove;
	if (dist < distCrit) // still in acceleration when arriving
	{
		tMove = 2 * pow(dist / acc, 0.5);
	}
	else
	{
		float distLin = dist - distCrit;
		tMove = distLin / vel + 2 * tAcc;
	}
	return tMove;
}

// define the position of the stage
void stage::set_pos(const float _pos)
{
	if (isConnected)
	{
		if (isEnabled)
		{
			if (isHomed)
			{
				float correctedPos = _pos;
				if (_pos > maxPos)
					correctedPos = maxPos;

				if (_pos < minPos)
					correctedPos = minPos;

				if (correctedPos != pos)
				{
					float tRequired = estimTRequired(pos, correctedPos);
					cout << "Moving to a new stage position in " << tRequired << " s" << endl;
					// simulating movement delay
					int tRequiredMs = (int) (tRequired * 1000 + 0.5);
					std::this_thread::sleep_for(std::chrono::milliseconds(tRequiredMs));
					pos = correctedPos;
				}
			}
			else
			{
				printf("[stage] Cannot be moved because stage is not homed\n");
			}
		}
		else
		{
			printf("[stage] Cannot be moved because stage is not enabled.\n");
		}
	}
	else
	{
		printf("[stage] Cannot be moved because stage is not connected.\n");
	}
	return;
}

void stage::set_vel(const float _vel)
{
	float velCorrected = _vel;
	if (_vel > maxVel)
		velCorrected = maxVel;

	if (_vel < minVel)
		velCorrected = minVel;

	vel = velCorrected;
	return;
}

void stage::set_acc(const float _acc)
{	
	float accCorrected = _acc;
	if (_acc > maxAcc)
		accCorrected = maxAcc;

	if (_acc < minAcc)
		accCorrected = minAcc;

	acc = accCorrected;
	return;
}

void stage::Home()
{
	isHomed = 1;
	return;
}

void stage::Connect()
{
	isConnected = 1;
	return;
}

void stage::Disconnect()
{
	isConnected = 0;
	return;
}

void stage::set_isConnected(const bool _isConnected)
{
	if (_isConnected != isConnected)
	{
		if (_isConnected)
			Connect();
		else
			Disconnect();
	}
	return;
}

void stage::Enable()
{
	isEnabled = 1;
	return;
}

void stage::Disable()
{
	isEnabled = 0;
	return;
}

void stage::set_isEnabled(const bool _isEnabled)
{
	if (_isEnabled != isEnabled)
	{
		if (_isEnabled)
			Enable();
		else
			Disable();
	}
	return;
}

