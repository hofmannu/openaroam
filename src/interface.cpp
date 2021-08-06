#include "interface.h"

interface::interface()
{
	// get all subdefinitions of saft objects as pointers
	
}

// displays a small help marker next to the text
static void HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
	return;
}

// setup the initial window for the scan procedure
void interface::InitWindow(int *argcp, char**argv)
{

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
	{
	  printf("Error: %s\n", SDL_GetError());
		return;
	}
	// main_display_function goes somewhere here
	const char* glsl_version = "#version 140";
	// to find out which glsl version you are using, run glxinfo from terminal
	// and look for "OpenGL shading language version string"
	// https://en.wikipedia.org/wiki/OpenGL_Shading_Language

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	SDL_Window* window = SDL_CreateWindow(windowTitle, 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1900, 1080, window_flags);
	SDL_GLContext gl_context = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window, gl_context);
	SDL_GL_SetSwapInterval(1); // Enable vsync

	bool err = glewInit() != GLEW_OK;
	if (err)
	{
		printf("Failed to initialize OpenGL loader!");
	  throw "FailedOpenGLLoader";
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForOpenGL(window, gl_context);

	ImGui_ImplOpenGL3_Init(glsl_version);
	bool done = false;
	while (!done)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT)
				done = true;
		}
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();
		MainDisplayCode();

		// Rendering
		ImGui::Render();
		
		glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		//glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		SDL_GL_SwapWindow(window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(gl_context);
 	SDL_DestroyWindow(window);
 	SDL_Quit();
	return;
}

// main loop which we run through to update ImGui
void interface::MainDisplayCode()
{
	HardwareConnection();
	SNRScope();
	ScanProcedure();
	return;
}

// define properties of a stage
static void stageDialog(stage* currStage)
{
	// read current stage properties
	float xPos = currStage->get_pos();
	float xVel = currStage->get_vel();
	float xAcc = currStage->get_acc();

	// generate user dialog to modify properties
	ImGui::InputFloat("pos [mm]", &xPos);
	ImGui::InputFloat("vel [mm/s]", &xVel);
	ImGui::InputFloat("acc [mm/s2]", &xAcc);
	
	// push properties back to stage
	currStage->set_pos(xPos);
	currStage->set_vel(xVel);
	currStage->set_acc(xAcc);

	ImGui::Columns(3);

	bool isXConnected = currStage->get_isConnected();
	ImGui::Checkbox("Connect", &isXConnected);
	currStage->set_isConnected(isXConnected);

	ImGui::NextColumn();

	bool isXEnabled = currStage->get_isEnabled();
	ImGui::Checkbox("Enable", &isXEnabled);
	currStage->set_isEnabled(isXEnabled);
	ImGui::NextColumn();


	if (ImGui::Button("Home"))
	{
		currStage->Home();
	}
	ImGui::Columns(1);

	ImGui::Separator();
	return;
}

void interface::HardwareConnection()
{
	ImGui::Begin("Hardware manager");

	if (ImGui::CollapsingHeader("Stages"))
	{

		ImGui::Text("x stage");
		ImGui::PushID(1);
		stageDialog(mic.get_pxStage());
		ImGui::PopID();

		ImGui::Text("y stage");
		ImGui::PushID(2);
		stageDialog(mic.get_pyStage());
		ImGui::PopID();

		ImGui::Text("z stage");
		ImGui::PushID(3);
		stageDialog(mic.get_pzStage());
		ImGui::PopID();
	}

	if (ImGui::CollapsingHeader("Lasers"))
	{
		ImGui::Text("Laser connection and handling");
	}

	ImGui::Text("Nothing here yet");

	ImGui::End();
	return;
	return;
}

void interface::SNRScope()
{
	ImGui::Begin("SNRScope");
	ImGui::Text("Nothing here yet");
	
	ImGui::End();
	return;
	return;
}

// defines all the settings for the scan procedure and allows user to 
// start a scan
void interface::ScanProcedure()
{
	ImGui::Begin("Scan procedure");
	
	if (ImGui::CollapsingHeader("Settings"))
	{
		ImGui::Checkbox("Expert mode", scan.get_pisExpertMode());
		ImGui::Text("Geometry and scan pattern");
		ImGui::InputFloat2("width [mm]", scan.get_pwidth());
		ImGui::InputFloat2("resolution [mm]", scan.get_pres());
		ImGui::InputFloat2("center [mm]", scan.get_pcenter());
		if (scan.get_isExpertMode())
		{
			ImGui::InputFloat2("velocity [mm/s]", scan.get_pvel());
			ImGui::InputFloat2("acceleration [mm/s2", scan.get_pacc());
		}	
		ImGui::Separator();
		ImGui::Text("DAC settings");
		int usCrop[2] = {scan.get_usCropLow(), scan.get_usCropHigh()};
		ImGui::InputInt2("US Crop [1]", &usCrop[0]);
		scan.set_usCrop(usCrop[0], usCrop[1]);	
		int nSamples = scan.get_nSamples();
		ImGui::InputInt("nSamples", &nSamples);
		scan.set_nSamples(nSamples);
		if (scan.get_isExpertMode())
		{
			ImGui::InputFloat("fSampling [Hz]", scan.get_pfSampling());
		}
	}


	// put down estimated required scan time
	float estimScanTime = scan.estimateScanTime(); // in seconds
	if (estimScanTime < 60)
	{
		ImGui::Text("Estimated scan time: %.2f sec", estimScanTime);
	}
	else if (estimScanTime < 3600)
	{
		const float estimScanTimeMin = (int) estimScanTime / 60;
		estimScanTime = estimScanTime - estimScanTimeMin * 60;
		ImGui::Text("Estimated scan time: %.0f min %.2f sec", 
			estimScanTimeMin, estimScanTime);
	}
	else
	{
		const float estimScanTimeH = (int) estimScanTime / 3600;
		estimScanTime = estimScanTime - estimScanTimeH * 3600;
		const float estimScanTimeMin = (int) estimScanTime / 60;
		estimScanTime = estimScanTime - estimScanTimeMin * 60;
		ImGui::Text("Estimated scan time: %.0f h %.0f min %.2f sec", 
			estimScanTimeH, estimScanTimeMin, estimScanTime);
	}

	// put down estimated required memory
	float estimMem = scan.estimateRequiredMemory();
	if (estimMem < 1024) // 
	{
		ImGui::Text("Required memory on HD: %f bytes", estimMem);
	}
	else if (estimMem < (1024 * 1024))
	{
		ImGui::Text("Required memory on HD: %.2f Kb", estimMem / 1024);
	}
	else if (estimMem < (1024 * 1024 * 1024))
	{
		ImGui::Text("Required memory on HD: %.2f Mb", 
			estimMem / 1024 / 1024);
	}
	else
	{
		ImGui::Text("Required memory on HD: %.2f Gb", 
			estimMem / 1024 / 1024 / 1024);
	}

	if (!scan.get_isRunning())
	{
		// if scan intenal counting is done but app not yet, we just finishe
		// the scna, time to join the thread
		if (isRunning == 1)
		{
			isRunning = 0;
			scanThread.join();
		}
		
		if (ImGui::Button("Run"))
		{	
			// scan.run(&mic);

			scanprocedure* scanPtr = &scan;
			scanThread = scanPtr->run2thread(&mic);
			isRunning = 1;
		}
	}
	else
	{
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
		if (ImGui::Button("Run"))
		{
			//nbothing to be done
		}
		ImGui::PopStyleVar();

		//ImGui::Text("Scan is currently running: %.1f percent", scan.get_percDone());
		ImGui::ProgressBar(scan.get_percDone() / 100);
	}

	ImGui::End();
	return;
}

// preview of the scan performed so far (only triggered if scan is running)
void interface::ScanLivePreview()
{

}