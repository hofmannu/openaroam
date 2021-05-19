#include "pathhandler.h"

pathhandler::pathhandler()
{
	std::string name;
	name = getenv("USER");
	cout << "System revealed username as: " << name << endl;

	basePath = "/home/" + name + "/ScanData/";
	generate_scan_folder();
}

string pathhandler::get_date_string()
{
	time_t rawtime;
  struct tm * timeinfo;
  char buffer[80];

  time (&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer,sizeof(buffer),"%Y-%m-%d",timeinfo);
  std::string dateStr(buffer);
  return dateStr;
}

string pathhandler::get_full_path()
{
	std::string fullPath = basePath + get_date_string() + "/";
	return fullPath;
}

string pathhandler::get_counter_file()
{
	std::string counterFile = get_full_path() + ".counter";
	// cout << counterFile << endl;
	return counterFile;
}

void pathhandler::generate_scan_folder()
{
	if (!std::filesystem::exists(basePath))
	{
		cout << "Generating folder since it does not exist yet" << endl;
		std::filesystem::create_directories(basePath);
	}
	return;
}

void pathhandler::generate_today_folder()
{
	if (!std::filesystem::exists(get_full_path()))
	{
		cout << "Generating folder since it does not exist yet" << endl;
		std::filesystem::create_directories(get_full_path());

		// generate counter file with content 0
		ofstream counterFile(get_counter_file());
		if (counterFile.is_open())
		{
			counterFile << 0;
		}
		else
		{
			cout << "still cannot open the fucking file" << endl;
		}
		counterFile.close();	
	}
	
	return;
}

void pathhandler::get_new_count()
{
	generate_today_folder();
	ifstream counterFile;
	counterFile.open(get_counter_file());
	if (counterFile.is_open())
	{
		counterFile >> count;
		count = count + 1;
		counterFile.close();
		
		ofstream counterFileOut(get_counter_file());
		counterFileOut << count;
		counterFileOut.close();
	}
	else
	{
		cout << "could not even open the file" << endl;
	}

	return;
}

string pathhandler::get_raw_data_name()
{
	generate_today_folder();
	std::string simpleNumber = to_string(count);
	std::string numberString = std::string(3 - simpleNumber.length(), '0') + simpleNumber;
	// String formatted = String.format("%08d", number);
	string rawName = get_full_path() + numberString + "_" + scanName + "_raw.h5";
	return rawName;
}