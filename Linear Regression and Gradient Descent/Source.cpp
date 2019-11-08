#include"FileAccessHelper.h"
#include"UIHelper.h"
//#include"DataAccessHelper.h"
#include"ParameterUpdater.h"

#define NUM_OF_SAMPLES -1
#define NUM_OF_FEATURES 13

#define TEST_HELPER 0

using namespace std;

static const string TrainingSetFileName = "housing_scale.txt";
static const string ValidatingSetFileName = "validate.txt";
static const string ParameterFileName = "model.txt";
static const string LossFileName = "loss.txt";

static const float LearningRate = 0.01;
static const float NormParameter = 0;

int main()
{
	UIHelper::prompt("Initialzing training set...\n");
	FileAccessHelper *file;
	file = new FileAccessHelper(TrainingSetFileName, ios::in);
	if (!file->is_open())
	{
		UIHelper::prompt("Cannot open file " + TrainingSetFileName + "\n");
		UIHelper::exit();
	}
	UIHelper::prompt("Training model...\n");

#if TEST_HELPER
	string line;
	float num;
	num = 0;
	line = file->getLine();
	while (!line.empty())
	{
		DataAccessHelper data(line);
		num = 0;
		while (num != NULL_FLAG)
		{
			num = data.getFloat();
			UIHelper::prompt(to_string(num) + " ");
		}
		UIHelper::prompt("\n");
		line = file->getLine();
	}
#endif
	FileAccessHelper *validatingSetFile = new FileAccessHelper(ValidatingSetFileName, ios::in);
	ParameterUpdater *updater = new ParameterUpdater(file, NUM_OF_FEATURES, LearningRate, NormParameter, NUM_OF_SAMPLES, ParameterFileName);
	float loss = 1.2;
	while (loss > 0.0005)
	{
		updater->updateParameter();
		updater->updateTempParameter();
		loss = updater->calculateCost(validatingSetFile);
		UIHelper::prompt("Current Loss: " + to_string(loss) + "\n");
		FileAccessHelper *lossInfo = new FileAccessHelper(LossFileName, ios::app);
		lossInfo->putLine(to_string(loss) + "\n");
		delete(lossInfo);
	}
	delete(updater);
	delete(validatingSetFile);
	delete(file);

	UIHelper::exit();
}