#pragma once
#ifndef _COMPCLUB_H_
#define _COMPCLUB_H_

#include "TimeUtil.h"
#include "Computers.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include<list>
#include <regex>
#include <string>
using namespace std;

class CompClub
{
private:
	int Price;
	int TableNum;
	TimeUtil StartTime;
	TimeUtil EndTime;

	map<string, int> ClientsClub;
	vector<Computers> ComputerTables;
	list<string> queue;

public: 
	CompClub();
	void CreateComputerTables(int n);
	int GetPrice();
	TimeUtil GetStartTime();
	TimeUtil GetEndTime();
	void SetStartTime(TimeUtil st);
	void SetEndTime(TimeUtil et);
	int GetCompNum();
	void SetPrice(int p);
	void SetTableNum(int tn);
	void EventId1(TimeUtil t, string ClientName);
	void EventId2(TimeUtil t, string ClientName, int CompNum);
	void EventId3(TimeUtil t, string ClientName);
	void EventId4(TimeUtil t, string ClientName);
	void EventId11();
	bool CheckCompIsFree();
	void ShowResult();
};

void ReadFile(string FileName, CompClub& c);
void CheckFile(string fileName);
TimeUtil StringToTime(string s);
vector<string> SplitString(string s);


#endif