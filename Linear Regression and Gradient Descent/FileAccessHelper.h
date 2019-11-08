#pragma once
#include<string>
#include<fstream>
#include"UIHelper.h"

#define NULL_FLAG -5

using namespace std;
class FileAccessHelper
{
public:
	FileAccessHelper(string fileName, int mode);
	string getLine();
	int putLine(string line);
	bool is_open();
	void resetFilePointer();
	~FileAccessHelper();

	int getInt();
	float getFloat();
private:
	FileAccessHelper();
	fstream file;
	bool file_is_open;

	string data;
	int dataPointer = 0;
	int dataLength;
};