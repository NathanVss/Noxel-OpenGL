#pragma once
#include <string>
#include <sstream>
#include <Windows.h>
#include <Psapi.h>




std::string operator+(std::string a, int b);

std::string operator+(int a, std::string b);

std::string operator+(std::string a, double b);
std::string operator+(double b, std::string a);
void debug(double);
void debug(std::string);
int round(double);
int round(float);

namespace YuEngine {


class Utils
{
public:
	static std::string concat(std::string base, int nbr);
	static std::string concat(std::string base, double nbr);

	static std::string getString(int nbr);
	static float getMemoryUsage();

	static PROCESS_MEMORY_COUNTERS* ProcessMemoryCounters;

	Utils(void);
	~Utils(void);
};

}