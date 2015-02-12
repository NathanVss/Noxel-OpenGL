#pragma once

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

namespace YuEngine {

class BinarySave
{
public:
	BinarySave(std::string _fileName) : fileName(_fileName) {
		writing = true;
	}
	BinarySave() {

	};
	~BinarySave(void) {

	}

	void setWritingMode() {
		writing  = true;
	}
	void setReadingMode() {
		writing = false;
	}

	void reset() {
		parsingMap.clear();
		intValues.clear();
		doubleValues.clear();
		floatValues.clear();
		stringValues.clear();
		boolValues.clear();
	}


	void addBoolVar(std::string str) {
		parsingMap[str] = "bool";
		boolValues[str] = false;
	}
	void addIntVar(std::string str) {
		parsingMap[str] = "int";
		intValues[str] = 0;
	}
	void addDoubleVar(std::string str) {
		parsingMap[str] = "double";
		doubleValues[str] = 0;
	}
	void addFloatVar(std::string str) {
		parsingMap[str] = "float";
		floatValues[str] = 0;
	}
	void addStringVar(std::string str) {
		parsingMap[str] = "string";
		stringValues[str] = ":)";
	}

	void setVar(std::string str, bool flag) {
		if(boolValues.find(str) != boolValues.end()) {
			boolValues[str] = flag;
		}
	}
	void setVar(std::string str, int value) {
		if(intValues.find(str) != intValues.end()) {
			intValues[str] = value;
		}
	}
	void setVar(std::string str, double value) {
		if(doubleValues.find(str) != doubleValues.end()) {
			doubleValues[str] = value;
		}
	}
	void setVar(std::string str, float value) {
		if(floatValues.find(str) != floatValues.end()) {
			floatValues[str] = value;
		}
	}
	void setStringVar(std::string str, std::string value) {
		if(stringValues.find(str) != stringValues.end()) {
			stringValues[str] = value;
		}
	}

	bool getBoolVar(std::string str) {
		return boolValues[str];
	}
	int getIntVar(std::string str) {
		return intValues[str];
	}
	double getDoubleVar(std::string str) {
		return doubleValues[str];
	}
	float getFloatVar(std::string str) {
		return floatValues[str];
	}
	std::string getStringVar(std::string str) {
		return stringValues[str];
	}

	void write(std::ofstream &file, char* ptr, int size) {
		file.write(ptr, size);
	}

	void save() {
		std::cout << stringValues["name"].c_str() << std::endl;
		std::ofstream file;
		file.open(fileName, std::ios::out | std::ios::binary);
		file.seekp(0);

		for(std::map<std::string, std::string>::iterator parsingIt = parsingMap.begin(); parsingIt != parsingMap.end(); ++parsingIt) {
		
			if(parsingIt->second == "int") {
				int value = intValues[parsingIt->first];
				file.write((char*)(&value), sizeof(int));
			}
			if(parsingIt->second == "float") {
				float value = floatValues[parsingIt->first];

				file.write((char*)(&value), sizeof(float));
			}
			if(parsingIt->second == "double") {
				double value = doubleValues[parsingIt->first];
				file.write((char*)(&value), sizeof(double));
			}
			if(parsingIt->second == "string") {
				std::string string = stringValues[parsingIt->first];
				char* cstring = (char*)string.c_str();
				int size = string.size() * sizeof(char) + 1;
				file.write(cstring, size);
			}
			if(parsingIt->second == "bool") {
				bool flag = boolValues[parsingIt->first];
				file.write((char*)(&flag), sizeof(bool));
			}

		}

		file.close();

	}

	void get() {

		std::ifstream file(fileName, std::ios::in | std::ios::out | std::ios::binary);
		file.seekg(0);

		for(std::map<std::string, std::string>::iterator parsingIt = parsingMap.begin(); parsingIt != parsingMap.end(); ++parsingIt) {
		
			if(parsingIt->second == "bool") {
				bool flag = false;
				file.read((char*)(&flag), sizeof(bool));
				boolValues[parsingIt->first] = flag;
			}
			if(parsingIt->second == "int") {
				int value = 0;
				file.read((char*)(&value), sizeof(int));
				intValues[parsingIt->first] = value;
			}
			if(parsingIt->second == "float") {
				float value = 0;
				file.read((char*)(&value), sizeof(float));
				floatValues[parsingIt->first] = value;
			}
			if(parsingIt->second == "double") {
				double value = 0;
				file.read((char*)(&value), sizeof(double));
				doubleValues[parsingIt->first] = value;
			}
			if(parsingIt->second == "string") {
				char curChar = ' ';
				std::vector<char> chars;
				while(curChar != '\0') {

					char* curCharPtr[1];
					file.read(&curChar, sizeof(char));
					chars.push_back(curChar);

				}
				std::string readString;
				
				for(int i = 0; i < chars.size(); i++) {
					readString.push_back(chars[i]);
				}

				std::cout << readString << std::endl;
				

			}
		}
		file.close();
	}
	

private:
	bool writing;
	std::string fileName;
	std::map<std::string, std::string> parsingMap;
	std::map<std::string, int> intValues;
	std::map<std::string, double> doubleValues;
	std::map<std::string, float> floatValues;
	std::map<std::string, bool> boolValues;
	std::map<std::string, std::string> stringValues;

};

}