
#ifndef SCANPROCEDURE_H
#define SCANPROCEDURE_H

#include <cstdint>
#include <iostream>
#include <math.h>
#include "microscope.h"
#include "pathhandler.h"
#include "dataprocessor.h"
#include <thread>
#include <cstring>

using namespace std;

class scanprocedure
{
private:
	// geometric configuration of our field of view
	float width[2] = {5, 5}; // width of our field of view
	float res[2] = {0.05, 0.05}; // resolution of our field of view
	float center[2] = {25, 25}; // center of the defined field of view
	float vel[2] = {500, 100}; // velocity of the stages for scan pattern
	float acc[2] = {3600, 500}; //acceleration of the stages
	float fSampling = 250e6; // sampling frequency used
	uint32_t usCrop[2] = {500, 2048}; // cropping applied to us data before saving
	uint32_t nSamples = 2048; // number of samples acquired
	uint32_t nAverages = 1; // number of averages acquired at each grid position
	bool isExpertMode = 0;
	string scanName = "unknown";

	float* rawDataUs; // raw measured data (stored to disc not RAM)
	float* procUs; // processed data (stored to RAM)
	bool isRawDataAllocated = 0;

	void free_memory();
	void save_data(const uint32_t ySlice);
	void proc_data(const uint32_t ySlice);
	void save_settings();
	uint32_t get_nX() const; // number of lines along x
	uint32_t get_nY() const; // number of lines along y
	uint32_t get_nShots() const; // number of shots in total

	float percDone = 0;
	bool isRunning = 0;

	bool flagSaveData = 1;

	pathhandler nameHandler;
	dataprocessor dataProc;

	thread saveThread; // thread responsible to save data to disc
	thread processThread; // thread responsible to process everything
public:
	scanprocedure();
	~scanprocedure();

	void run(microscope* mic); // starts actual scan
	std::thread run2thread(microscope* mic);

	float* get_pwidth() {return &width[0];};
	float* get_pres() {return &res[0];};
	float* get_pcenter() {return &center[0];};
	float* get_pvel() {return &vel[0];};
	float* get_pacc() {return &acc[0];};
	float* get_pfSampling() {return &fSampling;};
	string* get_pscanName() {return &scanName;};
	bool* get_pisExpertMode() {return &isExpertMode;};
	bool get_isExpertMode() {return isExpertMode;};

	// get and set of us crop
	uint32_t* get_pusCrop() {return &usCrop[0];};
	uint32_t get_usCropLow() const {return usCrop[0];};
	uint32_t get_usCropHigh() const {return usCrop[1];};
	void set_usCrop(const uint32_t usCropLow, const uint32_t usCropHigh);

	// get and set of nSamples
	uint32_t get_nSamples() const {return nSamples;};
	void set_nSamples(const uint32_t _nSamples);
	uint32_t* get_pnSamples() {return &nSamples;};

	uint32_t get_nAverages() const {return nAverages;};
	uint32_t* get_pnAverages() {return &nAverages;};
	void set_nAverages(const uint32_t _nAverages);

	// get and set for nAverages

	float estimateScanTime();
	float estimateRequiredMemory(); // on harddrive to save data
	float estimateRequiredRam(); // in ram 

	float get_percDone() const {return percDone;};
	bool get_isRunning() const {return isRunning;};

	bool* get_pflagSaveData() {return &flagSaveData;};
	bool get_flagSaveData() const {return flagSaveData;};
	void set_flagSaveData(const bool _flagSaveData);


};


#endif