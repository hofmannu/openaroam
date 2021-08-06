#ifndef INTERFACE_H
#define INTERFACE_H

#include <SDL2/SDL.h>
#include <GL/glew.h>    // Initialize with gl3wInit()

#include <thread> 

#include "../lib/imgui/imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "microscope.h"
#include "stage.h"
#include "scanprocedure.h"


class interface
{
private:

	void MainDisplayCode();
	const char* windowTitle = "opensaft";
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 0.10f); // bg color


	void HardwareConnection(); // direct access to manipulate the hardware
	
	void ScanProcedure(); // scan procedure to acquire images
	void ScanLivePreview(); // live preview while the actual scan is running

	void SNRScope();

	microscope mic;
	scanprocedure scan;

	bool isRunning = 0;
	std::thread scanThread;

public:
	interface(); // class constructor

	void InitWindow(int *argcp, char**argv);

};

#endif