#include "../src/pathhandler.h"
#include <cstring>
#include <iostream>

using namespace std;

int main()
{

	pathhandler myHand;
	
	myHand.get_new_count();
	std::string name = myHand.get_raw_data_name();
	cout << name << endl;;
	name = myHand.get_raw_data_name();
	cout << name << endl;;
	
	myHand.get_new_count();
	name = myHand.get_raw_data_name();
	cout << name << endl;;
	
	return 0;
}