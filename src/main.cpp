#include <iostream>
#include "interface.h"
#include "stage.h"

using namespace std;

int main(int *argcp, char**argv)
{
	
	interface GUI;
	GUI.InitWindow(argcp, argv);

	return 0;
}