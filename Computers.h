#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Computers
{
private:
	string Client;
	int Number;
	int Profit;
	TimeUtil AllTime;
	int CPrice;
	TimeUtil StTime;

public:
	Computers() {
		Client = "free";
		Profit = 0;
		StTime = TimeUtil(0, 0);
		AllTime = TimeUtil(0, 0);
		Number = 0;
	}
	bool IsFree() {
		if (Client == "free") {
			return true;
		}
		else {
			return false;
		}
	}
	void CountProfit(int pr) {
		if(AllTime.min == 0){
			Profit += AllTime.hour * pr;
		}
		else {
			Profit += (AllTime.hour + 1) * pr;
		}
	}
	void SetNumber(int n) {
		Number = n;
	}
	void SetCPrice(int n) {
		CPrice = n;
	}
	int GetNumber() {
		return Number;
	}
	void ClientSat(string ClientName, TimeUtil t) {
		Client = ClientName;
		StTime = t;
	}
	void ClientLeft(TimeUtil t, int pr) {
		Client = "free";
		TimeUtil n = t - StTime;
		AllTime = n + AllTime;
		if (n.min == 0) {
			Profit += n.hour * pr;
		}
		else {
			Profit += (n.hour + 1) * pr;
		}
	}
	void PrintResults() {
		cout << Number + 1 << " " << Profit << " " << AllTime << endl;
	}
};
