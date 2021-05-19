#include "scanprocedure.h"

scanprocedure::scanprocedure()
{


}

scanprocedure::~scanprocedure()
{
	free_memory();
}

void scanprocedure::free_memory()
{
	if (isRawDataAllocated)
		delete[] rawDataUs;

	return;
}

void scanprocedure::set_usCrop(const uint32_t usCropLow, const uint32_t usCropHigh)
{
	usCrop[0] = usCropLow;
	usCrop[1] = usCropHigh;
	return;
}

void scanprocedure::set_nSamples(const uint32_t _nSamples)
{
	nSamples = _nSamples;
	return;
}

// returns the estimated scan time defined through the stage velocities
float scanprocedure::estimateScanTime()
{
	float tReq[2]; 
	for (int iStage = 0; iStage < 2; iStage++)
	{
		const float tAcc = vel[iStage] / acc[iStage];
		const float distCrit = 2 * 0.5 * acc[iStage] * tAcc * tAcc;
		if (width[iStage] < distCrit) // still in acceleration when arriving
		{
			tReq[iStage] = 2 * pow(width[iStage] / acc[iStage], 0.5);
		}
		else
		{
			float distLin = width[iStage] - distCrit;
			tReq[iStage] = distLin / vel[iStage] + 2 * tAcc;
		}
	}

	uint32_t nX = width[0] / res[0] + 1;
	uint32_t nY = width[1] / res[1] + 1;
	float tGes = (float) nX * tReq[0] + (float) nY * tReq[1];
	return tGes;
}

// returns the estimate required memory in byte
float scanprocedure::estimateRequiredMemory()
{

	uint32_t nSamplesTot = nSamples * nAverages * get_nX() * get_nY();
	float reqMem = ((float) nSamplesTot * 2); 
	return reqMem;
}

uint32_t scanprocedure::get_nX() const
{
	return ((int) width[0] / res[0] + 1);
}

uint32_t scanprocedure::get_nY() const
{
	return ((int) width[1] / res[1] + 1);
}

uint32_t scanprocedure::get_nShots() const
{
	return get_nY() * get_nX() * nAverages;
}

void scanprocedure::run(microscope* mic)
{
	isRunning = 1;
	nameHandler.get_new_count(); // generate new counter for file
	save_settings();

	// for readability and save settings from start
	uint32_t nY = get_nY();
	uint32_t nX = get_nX();
	uint32_t nAverages = get_nAverages();
	uint32_t nSamples = get_nSamples();

	stage* xStage = mic->get_pxStage();
	stage* yStage = mic->get_pyStage();
	float origin[2];
	origin[0] = center[0] - width[0] / 2;
	origin[1] = center[1] - width[1] / 2;

	// we save the settings here already because the user might adapt them during the scan
	save_settings();

	// allocate memory for scan
	if (isRawDataAllocated)
		delete[] rawDataUs;

	uint32_t nBScan = nX * nAverages * nSamples;
	rawDataUs = new float[nBScan];


	for (uint32_t iY = 0; iY < nY; iY++)
	{
		// move to next y position
		yStage->set_pos(origin[1] + ((float) iY) * res[1]);

		if (!(iY % 2)) // forward scan
			xStage->set_pos(origin[0]);
		else
			xStage->set_pos(origin[0] + res[0] * ((float) nX));

		// for now acquire data by filling array up with random numbers
		for (uint32_t iSample = 0; iSample < nBScan; iSample++)
		{
			rawDataUs[iSample] = rand();
		}

		// update the percentage we finished already
		percDone = ((float) iY) / ((float) nY) * 100;

		// save data to file if flag was enabled
		if (flagSaveData)
			save_data(iY);
	}


	// reset running flag and percentage done value
	isRunning = 0;
	percDone = 0;
}

std::thread scanprocedure::run2thread(microscope* mic)
{
	return std::thread([=] { run(mic);} );
}

// set the flag to either save or not save data to file
void scanprocedure::set_flagSaveData(const bool _flagSaveData)
{
	flagSaveData = _flagSaveData;
	return;
}

// this function is called during the scan and saves the b scans to a file
void scanprocedure::save_data(const uint32_t ySlice)
{
	cout << "sving data is not implemented yet" << endl;
	// save 
	return;
}

// this function is called at the beginning of the scan and saves the 
// settings to the file
void scanprocedure::save_settings()
{

	cout << "saving settings is not implemented yet" << endl;
	

	return;
}


void scanprocedure::set_nAverages(const uint32_t _nAverages)
{
	nAverages = _nAverages;
	return;
}