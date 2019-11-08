#include "ParameterUpdater.h"

ParameterUpdater::ParameterUpdater(FileAccessHelper *trainingSetFile, int num_of_features, float learning_rate, float norm_parameter, int num_of_samples, string tempParameterFileName)
	:NUM_OF_FEATURES(num_of_features), NUM_OF_SAMPLES(num_of_samples), TempParameterFileName(tempParameterFileName)
{
	TrainingSetFile = trainingSetFile;
	normParameter = norm_parameter;
	learningRate = learning_rate;
	initializeTempParameter();
}

void ParameterUpdater::updateParameter()
{
	int count = 0;
	string line;
	float y;
	int index;
	float value;
	//DataAccessHelper *data;
	map<int, float> temp;
	TrainingSetFile->resetFilePointer();
	for (int i = 0; NUM_OF_SAMPLES == SAMPLE_NUM_UNDEFINED ? 1 : i < NUM_OF_SAMPLES; ++i)
	{
		x.clear();
		x.insert(pair<int, float>(NUM_OF_FEATURES + 1, 1));
		line = TrainingSetFile->getLine();
		if (line == "")
			break;
		//data = new DataAccessHelper(line);
		y = TrainingSetFile->getFloat();
		for (index = TrainingSetFile->getInt(), value = TrainingSetFile->getFloat(); index != NULL_FLAG; index = TrainingSetFile->getInt(), value = TrainingSetFile->getFloat())
		{
			x.insert(pair<int, float>(index, value));
		}
		//delete(data);
		temp = add(temp, divide(multiply(y, x), 1 + exp(y*multiply(w, x))));
		count++;
	}
	if (count == 0)
	{
		return;
	}
	w = add(multiply(1 - get_learningRate() * normParameter, w), multiply(get_learningRate() / count, temp));
}

bool ParameterUpdater::updateTempParameter()
{
	FileAccessHelper *tempOutputFile;
	tempOutputFile = new FileAccessHelper(TempParameterFileName, ios::out);
	if (!tempOutputFile->is_open())
	{
		delete(tempOutputFile);
		return true;
	}
	map<int, float>::iterator itr;
	for (itr = w.begin(); itr != w.end(); ++itr)
	{
		tempOutputFile->putLine(to_string(itr->first) + ":" + to_string(itr->second) + "\n");
	}
	delete(tempOutputFile);
	return false;
}

float ParameterUpdater::calculateCost(FileAccessHelper *validatingFile)
{
	float result = 0;
	int count = 0;
	string line;
	float y;
	int index;
	float value;
	//DataAccessHelper *data;
	validatingFile->resetFilePointer();
	for (int i = 0; NUM_OF_TESTS == TEST_NUM_UNDEFINED ? 1 : i < NUM_OF_TESTS; ++i)
	{
		x.clear();
		x.insert(pair<int, float>(NUM_OF_FEATURES + 1, 1));
		line = validatingFile->getLine();
		if (line == "")
			break;
		//data = new DataAccessHelper(line);
		y = validatingFile->getFloat();
		for (index = validatingFile->getInt(), value = validatingFile->getFloat(); index != NULL_FLAG; index = validatingFile->getInt(), value = validatingFile->getFloat())
		{
			x.insert(pair<int, float>(index, value));
		}
		//delete(data);
		//temp = add(temp, divide(multiply(y, x), 1 + exp(y*multiply(w, x))));
		result += log(1 + exp(-1 * y*multiply(w, x)));
		count++;
	}
	if (count == 0)
	{
		return 0;
	}
	return result / count;
}

bool ParameterUpdater::initializeTempParameter()
{
	FileAccessHelper *tempFile;
	tempFile = new FileAccessHelper(TempParameterFileName, ios::in);
	if (!tempFile->is_open())
	{
		delete(tempFile);
		return true;
	}
	else
	{
		int index;
		float value;
		while (!(tempFile->getLine()).empty())
		{
			index = tempFile->getInt();
			value = tempFile->getFloat();
			w.insert(pair<int, float>(index, value));
		}
		delete(tempFile);
		return false;
	}
}

map<int, float> ParameterUpdater::multiply(float a, map<int, float> temp)
{
	map<int, float>::iterator itr;
	for (itr = temp.begin(); itr != temp.end(); ++itr)
	{
		itr->second *= a;
	}
	return temp;
}

float ParameterUpdater::multiply(map<int, float> a, const map<int, float> &b)
{
	float result = 0;
	map<int, float>::iterator itr;
	map<int, float>::const_iterator tmp_itr;
	for (itr = a.begin(); itr != a.end(); ++itr)
	{
		result += b.end() != (tmp_itr = b.find(itr->first)) ? tmp_itr->second*itr->second : 0;
	}
	return result;
}

map<int, float> ParameterUpdater::divide(map<int, float> temp, float a)
{
	map<int, float>::iterator itr;
	for (itr = temp.begin(); itr != temp.end(); ++itr)
	{
		itr->second /= a;
	}
	return temp;
}

map<int, float> ParameterUpdater::add(map<int, float> a, const map<int, float> &b)
{
	map<int, float>::const_iterator itr;
	map<int, float>::iterator tmp_itr;
	for (itr = b.begin(); itr != b.end(); ++itr)
	{
		if (a.end() != (tmp_itr = a.find(itr->first)))
		{
			tmp_itr->second += itr->second;
		}
		else
		{
			a.insert(pair<int, float>(itr->first, itr->second));
		}
	}
	return a;
}

float ParameterUpdater::get_learningRate()
{
	return learningRate;
}

