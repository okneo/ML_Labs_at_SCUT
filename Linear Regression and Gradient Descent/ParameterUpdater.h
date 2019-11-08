#pragma once
#include<math.h>
#include<map>
#include<iterator>
#include"FileAccessHelper.h"
//#include"DataAccessHelper.h"

#define TEMP_OUTPUT_THRESHOLD 1000
#define SAMPLE_NUM_UNDEFINED -1
#define TEST_NUM_UNDEFINED -1

using namespace std;

class ParameterUpdater
{
public:
	ParameterUpdater(FileAccessHelper *trainingSetFile, int num_of_features, float learning_rate = 1, float norm_parameter = 0, int num_of_samples = SAMPLE_NUM_UNDEFINED, string tempParameterFileName = "model.txt.tmp");
	void updateParameter();
	bool updateTempParameter();
	float calculateCost(FileAccessHelper *validatingFile);
private:
	ParameterUpdater();
	bool initializeTempParameter();

	map<int, float> multiply(float, map<int, float>);
	float multiply(map<int, float>, const map<int, float> &);
	map<int, float> divide(map<int, float>, float);
	map<int, float> add(map<int, float>, const map<int, float> &);

	float get_learningRate();

	map<int, float> w;
	map<int, float> x;
	FileAccessHelper *TrainingSetFile;
	const int NUM_OF_FEATURES;
	float learningRate;
	float normParameter;
	const int NUM_OF_SAMPLES;
	const int NUM_OF_TESTS = TEST_NUM_UNDEFINED;
	const string TempParameterFileName;
};