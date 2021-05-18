#ifndef MICROSCOPE_H
#define MICROSCOPE_H

#include "stage.h"

class microscope
{
private:
	// three motorized stages to move x y z
	stage xStage; // previously called fast moving stage
	stage yStage; // previously called slow moving stage
	stage zStage; 

public:
	// class constructor and destructor
	microscope();
	~microscope();

	stage* get_pxStage() {return &xStage;};
	stage* get_pyStage() {return &yStage;};
	stage* get_pzStage() {return &zStage;};

};

#endif