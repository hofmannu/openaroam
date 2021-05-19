/*
	simple helper class taking care of name and path handling
	Author: Urs Hofmann
	Mail: hofmannu@ethz.ch
	Date: 19.05.2021
*/

#ifndef PATHHANDLER_H
#define PATHHANDLER_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <cstdint>
#include <cstdlib>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

class pathhandler
{
private:
	string basePath = "/home/hofmannu/ScanData/";
	string scanName = "unnamed";
	string dateString;
	uint64_t count = 0;

	string get_date_string();
	string get_full_path();
	string get_counter_file();
	void generate_scan_folder();
	void generate_today_folder();

public:
	pathhandler();
	void get_new_count();
	string get_raw_data_name();

	// scan name setting and getting
	void set_scanName(const string _scanName);
	string get_scanName() const {return scanName;};
};

#endif