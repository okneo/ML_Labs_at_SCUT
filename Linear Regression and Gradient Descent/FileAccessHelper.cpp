#include "FileAccessHelper.h"

FileAccessHelper::FileAccessHelper(string fileName, int mode)
{
	file.open(fileName, mode);
	file_is_open = file.is_open();
}

string FileAccessHelper::getLine()
{
	string line;
	if (!file.eof())
	{
		getline(file, line);
		data = line;
		dataLength = line.length();
		dataPointer = 0;
		return line;
	}
	else
		return "";
}

int FileAccessHelper::putLine(string line)
{
	file << line;
	return 0;
}

bool FileAccessHelper::is_open()
{
	return file_is_open;
}

void FileAccessHelper::resetFilePointer()
{
	file.clear(ios::goodbit);
	file.seekg(ios::beg);
}

FileAccessHelper::~FileAccessHelper()
{
	file.close();
}

int FileAccessHelper::getInt()
{
	if (dataPointer >= dataLength)
		return NULL_FLAG;
	int result = 0;
	char current = data[dataPointer];
	while ((current<'0' || current>'9') && (current != '+'&&current != '-'))
	{
		dataPointer++;
		if (dataPointer >= dataLength)
			return NULL_FLAG;
		current = data[dataPointer];
	}
	bool is_positive = 1;
	if (current == '-')
	{
		is_positive = 0;
		dataPointer++;
	}
	else if (current == '+')
	{
		dataPointer++;
	}
	bool has_num = 0;
	while (dataPointer < dataLength)
	{
		current = data[dataPointer];
		if (current >= '0'&&current <= '9')
		{
			result += current - '0';
			result *= 10;
			has_num = 1;
		}
		else
		{
			break;
		}
		dataPointer++;
	}
	if (has_num)
	{
		if (!is_positive)
			result *= -1;
		return result / 10;
	}
	else
		return NULL_FLAG;
}

float FileAccessHelper::getFloat()
{
	if (dataPointer >= dataLength)
		return NULL_FLAG;
	float result = 0;
	char current = data[dataPointer];
	while ((current<'0' || current>'9') && (current != '+'&&current != '-'))
	{
		dataPointer++;
		if (dataPointer >= dataLength)
			return NULL_FLAG;
		current = data[dataPointer];
	}
	bool is_positive = 1;
	if (current == '-')
	{
		is_positive = 0;
		dataPointer++;
	}
	else if (current == '+')
	{
		dataPointer++;
	}
	bool has_num = 0;
	while (dataPointer < dataLength)
	{
		current = data[dataPointer];
		if (current >= '0'&&current <= '9')
		{
			result += current - '0';
			result *= 10;
			has_num = 1;
			dataPointer++;
		}
		else if (current == '.')
		{
			dataPointer++;
			float pow = 1;
			while (dataPointer < dataLength)
			{
				current = data[dataPointer];
				if (current >= '0'&&current <= '9')
				{
					result += (current - '0') / pow;
					pow *= 10;
					has_num = 1;
					dataPointer++;
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	if (has_num)
	{
		if (!is_positive)
			result *= -1;
		return result / 10;
	}
	else
		return NULL_FLAG;
}
