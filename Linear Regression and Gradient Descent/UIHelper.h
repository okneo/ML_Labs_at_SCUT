#pragma once
#include<iostream>
#include<string>
#include<stdlib.h>
using namespace std;
class UIHelper
{
public:
	static int prompt(string message);
	static string getInput();
	static void exit();
};