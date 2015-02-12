#pragma once

#include <fstream>
#include <iostream>
#include <limits>
#include <iomanip>

namespace YuEngine {

class BinaryManager
{
public:
	BinaryManager(void) {




	};
	~BinaryManager(void) {

	}


	void test() {



		std::string stdString("Y M C A");

		int stringSize = stdString.size() * sizeof(char) + 1;
		std::cout << "Stdstring : " << stdString.c_str() << std::endl;
		std::cout << "Stdstring Size : " << stringSize << std::endl;

		char* CString = (char*)stdString.c_str();

		std::ofstream file;
		file.open("binary/data.dat", std::ios::out | std::ios::binary);
		file.write((char*)CString, stringSize);
		file.close();

		std::fstream wr;
		wr.open("binary/data.dat", std::ios::in | std::ios::out | std::ios::binary);
		wr.seekg(0);
		char *CStringR = new char[stdString.size()];
		wr.read((char*)CStringR, stringSize);

		wr.close();

		std::string endString(CStringR);
		
		std::cout << "STRING : " << endString.c_str() << std::endl;

		std::cout << "SIZE : " << sizeof(CStringR) << std::endl;


		//float number = 1509.1104;

		//std::cout << number << std::endl;


		//std::ofstream file;
		//file.open("binary/data.dat", std::ios::out | std::ios::binary);
		//file.write((char*)&number, sizeof(number));
		//file.close();

		//std::fstream wr;
		//wr.open("binary/data.dat", std::ios::in | std::ios::out | std::ios::binary);
		//wr.seekg(0);
		//char *CStringR = new char[sizeof(number)];
		//wr.read((char*)CStringR, sizeof(number));

		//wr.close();

		//float numberR = 
		//
		//std::cout << "STRING : " << endString.c_str() << std::endl;

		//std::cout << "SIZE : " << sizeof(CStringR) << std::endl;



		unsigned char* ar = getBytes(54);
		std::cout << ar << std::endl;


		int b = 0;
		memcpy(&b, ar, sizeof(int));

		std::cout << b << std::endl;
	};


	unsigned char* getBytes(int a) {

		//int a = 54;
		unsigned char ar[sizeof(int)];

		
		
		memcpy(ar, &a, sizeof(a));
		return ar;
	};
};

}