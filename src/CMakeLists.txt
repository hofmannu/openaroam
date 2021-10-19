set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(OpenGL_GL_PREFERENCE GLVND)
cmake_policy(SET CMP0079 NEW)
find_package( Threads )


add_library(Interface interface.cpp)
target_link_libraries(Interface PUBLIC
	# ImGuiPlot 
	GLEW 
	ImGuiImplSdl 
	ImGuiImplOpenGL3
	Stage
	Microscope
	Scanprocedure
	${CMAKE_THREAD_LIBS_INIT}
	# ImGuiFileDialog
)

add_library(DataDefs datadefs.cpp)


# add_library(ImGuiFileDialog ImGuiFileDialog.cpp)
# target_link_libraries(ImGuiFileDialog PUBLIC ImGui)

# add_library(ImGuiPlot imgui_plot.cpp)

add_library(ImGuiImplOpenGL3 imgui_impl_opengl3.cpp)
target_link_libraries(ImGuiImplOpenGL3 PUBLIC ImGui OpenGL)

find_package(SDL2 REQUIRED)
add_library(ImGuiImplSdl imgui_impl_sdl.cpp)
target_link_libraries(ImGuiImplSdl PUBLIC ImGui SDL2 OpenGL)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

find_package(glfw3 REQUIRED)
include_directories(${GLFW3_INCLUDE_DIR})
link_libraries(${GLFW_LIBRARY_DIRS})

add_library(Stage stage.cpp)

add_library(Microscope microscope.cpp)
target_link_libraries(Microscope PUBLIC
	Stage)

add_library(Scanprocedure scanprocedure.cpp)
target_link_libraries(Scanprocedure PUBLIC
	Stage
	Microscope
	PathHandler
	${CMAKE_THREAD_LIBS_INIT})

add_library(PathHandler pathhandler.cpp)
target_link_libraries(PathHandler stdc++fs)