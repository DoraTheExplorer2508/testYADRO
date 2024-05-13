#include "CompClub.h"
#include "Computers.h"

CompClub::CompClub()
{
	Price = 0;
	TableNum = 0;
	StartTime = TimeUtil(0,0);
	EndTime = TimeUtil(0, 0);
	queue.resize(0);
}

int CompClub::GetPrice()
{
	return Price;
}

void CheckFile(string fileName)
{
	regex time("^(([0,1][0-9])|(2[0-3])):[0-5][0-9]\\s\(([0,1][0-9])|(2[0-3])):[0-5][0-9]$");
	regex number(R"(^\d*$)");
	string r;

	string line;
	unsigned int lineNum = 1;

	string ex;

	TimeUtil prevTime(0, 0);
	TimeUtil nowTime(0, 0);

	ifstream in(fileName);

	if (in.is_open())
	{
		while (getline(in, line))
		{
			if (lineNum == 1) {
				if (!regex_match(line, number)) {
					ex = "Error: invalid data in line " + to_string(lineNum) + ": " + line;
					throw(ex);
				}
				r = "^(([0,1][0-9])|(2[0-3])):[0-5][0-9]\\s\[1-4]\\s\[a-z0-9_-]+(\\s\[1-" + line + "]|$)$";

			}
			else if (lineNum == 2) {
				if (!regex_match(line, time)) {
					ex = "Error: invalid data in line " + to_string(lineNum) + ": " + line;
					throw(ex);
				}
			}
			else if (lineNum == 3) {
				if (!regex_match(line, number)) {
					ex = "Error: invalid data in line " + to_string(lineNum) + ": " + line;
					throw(ex);
				}
			}
			else {
				if (!regex_match(line, std::regex(r))) {
					ex = "Error: invalid data in line " + to_string(lineNum) + ": " + line;
					throw(ex);
				}
				else {
					nowTime = TimeUtil(StringToTime(line));
					if (nowTime < prevTime) {
						ex = "Error: invalid data in line (previous time is greater than current time) " + to_string(lineNum) + ": " + line;
						throw(ex);
					}
					prevTime = nowTime;
				}
			}

			lineNum++;
		}

	}
	else {
		cout << "Error: cannot open input file " << fileName << std::endl;
	}
	in.close();
}

TimeUtil StringToTime(string s) {

	regex regex1(":");
	vector<string> out(
		sregex_token_iterator(s.begin(), s.end(), regex1, -1),
		sregex_token_iterator()
	);

	int min = 0, hour = 0;
	vector<TimeUtil> SplittingTime;

	for (int i = 0; i != out.size(); i++) {

		int tmp = stoi(out[i]);

		if (i % 2 == 0) hour = tmp;
		else min = tmp;

		if (i % 2 == 1 && i != 0) return TimeUtil(hour, min);


	}
	return TimeUtil();
}

vector<string> SplitString(string s)
{
	regex regex1(" ");
	vector<string> out(
		sregex_token_iterator(s.begin(), s.end(), regex1, -1),
		sregex_token_iterator()
	);

	return out;
}

TimeUtil CompClub::GetStartTime()
{
	return StartTime;
}

TimeUtil CompClub::GetEndTime()
{
	return EndTime;
}

void CompClub::SetStartTime(TimeUtil st)
{
	StartTime = st;
}

void CompClub::SetEndTime(TimeUtil et)
{
	EndTime = et;
}


int CompClub::GetCompNum()
{
	return TableNum;
}

void CompClub::SetPrice(int p)
{
	Price = p;
}

void CompClub::SetTableNum(int tn)
{
	TableNum = tn;
}

void CompClub::CreateComputerTables(int n) {
	ComputerTables = vector<Computers>(n);
	for (int i = 0; i != ComputerTables.size(); i++) {
		ComputerTables[i].SetNumber(i);
	}
}

void ReadFile(string fileName, CompClub& c) {
	string line;
	unsigned int lineNum = 0;
	TimeUtil time = TimeUtil(0, 0);

	std::ifstream in(fileName);
	if (in.is_open())
	{
		while (getline(in, line))
		{
			if (lineNum == 0) {
				int tableNum = stoi(line);
				c.SetTableNum(tableNum);
				c.CreateComputerTables(tableNum);

			}
			else if (lineNum == 1) {

				c.SetStartTime(StringToTime((SplitString(line))[0]));
				c.SetEndTime(StringToTime(SplitString(line)[1]));
				cout << c.GetStartTime() << endl;
			}
			else if (lineNum == 2) {
				c.SetPrice(stoi(line));
			}
			else {
				cout << line << endl;
				vector<string> data = SplitString(line);
				int id = stoi(data[1]);
				if (id == 1) {
					c.EventId1(StringToTime(data[0]), data[2]);
				}
				else if (id == 2) {
					c.EventId2(StringToTime(data[0]), data[2], stoi(data[3]));
				}
				else if (id == 3) {
					c.EventId3(StringToTime(data[0]), data[2]);
				}
				else if (id == 4) {
					c.EventId4(StringToTime(data[0]), data[2]);
				}

			}

			lineNum++;
		}
		c.EventId11();
		c.ShowResult();
	}
	in.close();
}

void CompClub::EventId1(TimeUtil t, string ClientName) {
	if (t < StartTime || t > EndTime) {
		cout << t << "13 " << "NotOpenYet" << endl;
	}
	else if (ClientsClub.find(ClientName)!= ClientsClub.end()) {
		cout << t << "13 " << "YouShallNotPass" << endl;
	}
	else {
		ClientsClub[ClientName] = 0;
	}
}

void CompClub::EventId2(TimeUtil t, string ClientName, int CompNum) {
	
	if (!(ClientsClub.find(ClientName) != ClientsClub.end())) {
		cout << t << "13 " << "ClientUnknown" << endl;
	}
	else if ((ClientsClub[ClientName] == CompNum) || !ComputerTables[CompNum-1].IsFree()) {
		cout << t << "13 " << " Places busy" << endl;
	}
	else if ((ClientsClub.find(ClientName) != ClientsClub.end()) && (ClientsClub[ClientName] != 0)) {
		int n = ClientsClub[ClientName];
		ComputerTables[n - 1].ClientLeft(t, Price);
		ClientsClub[ClientName] = CompNum;
		ComputerTables[CompNum - 1].ClientSat(ClientName, t);
	}
	else {
		ClientsClub[ClientName] = CompNum;
		ComputerTables[CompNum - 1].ClientSat(ClientName, t);
	}
}

void CompClub::EventId3(TimeUtil t, string ClientName) {
	if (!(ClientsClub.find(ClientName) != ClientsClub.end())) {
		cout << t << "13 " << "ClientUnknown" << endl;
	}
	else if (queue.size() >= TableNum){
		cout << t << "11 " << ClientName << endl;
		ClientsClub.erase(ClientName);
	}
	else {
		bool isfree = false;
		for (int i = 0; i < ComputerTables.size(); i++){
			if (ComputerTables[i].IsFree()) {
				isfree = true;
				break;
			}
		}
		if (isfree == true) {
			cout << t << "13 " << "ICanWaitNoLonger!" << endl;
		}
		else { 
			queue.push_back(ClientName); 
		}
	}
}

void CompClub::EventId4(TimeUtil t, string ClientName) {
	if (!(ClientsClub.find(ClientName) != ClientsClub.end())) {
		cout << t << "13 " << "ClientUnknown" << endl;
	}
	else if (ClientsClub[ClientName] == 0) {
		ClientsClub.erase(ClientName);
	}
	else if (queue.size() == 0 && ClientsClub[ClientName] != 0) {
		ComputerTables[ClientsClub[ClientName] - 1].ClientLeft(t, Price);
		ClientsClub.erase(ClientName);
	}
	else {
		ComputerTables[ClientsClub[ClientName] - 1].ClientLeft(t, Price);
		string NewClient = queue.front();
		ComputerTables[ClientsClub[ClientName] - 1].ClientSat(NewClient, t);
		cout << t << "12 " << NewClient << " " << ClientsClub[ClientName] << endl;
		queue.pop_front();
		ClientsClub[NewClient] = ClientsClub[ClientName];
		ClientsClub.erase(ClientName);
	}
	/*else {
		int cm = ClientsClub[ClientName] - 1;
		ComputerTables[cm].ClientLeft(t, Price);
		if (!queue.empty()) {
			string NewClient = queue.front();
			int n = ComputerTables[cm].GetNumber() + 1;
			ComputerTables[cm].ClientSat(NewClient, t);
			ClientsClub[NewClient] = n;
			cout << t << "12 " << NewClient << " " << n << endl;
			queue.pop_front();
		}
		ClientsClub.erase(ClientName);
	}*/
}

void CompClub::EventId11() {
	if (!(ClientsClub.empty())) {
		for (auto it = ClientsClub.begin(); it != ClientsClub.end(); it++) {
			cout << EndTime << "11 " << it->first << endl;
			if (it->second != 0) {
				ComputerTables[it->second - 1].ClientLeft(EndTime, Price);
			}
		}
		ClientsClub.clear();
		cout << EndTime << endl;
	}
	else {
		cout << EndTime << endl;
	}
}

void CompClub::ShowResult() {
	for (int i = 0; i < TableNum; i++) {
		ComputerTables[i].PrintResults();
	}
}

bool CompClub::CheckCompIsFree() {
	bool n = false;
	for (int i = 0; i < TableNum; i++) {
		if (ComputerTables[i].IsFree()) {
			n = true;
		}
	}
	return n;
}
