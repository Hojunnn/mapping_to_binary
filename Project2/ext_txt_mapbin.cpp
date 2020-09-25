#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <cstring>
#include <sstream>
#include <map>
#include <vector>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/replace.hpp>

using namespace std;
using std::map;
using namespace boost;

//recursive function for CG's API name & number of '|'
int string_function(string st)
{
	if (st[0] != '|')
		return 0;
	if (st.empty())
		return 0;
	else
		return 1 + string_function(st.substr(3));
}

int main() {

	string TBPath = "C:\\Users\\Seong\\source\\Practice_C++\\GraduateProject\\Testbed.txt";
	string str;
	
	//cout << in.is_open() << endl;

	ifstream in(TBPath);
	vector <string> target_file;


	if (in.is_open())
		cout << "file open successful" << endl;

	do {
		getline(in, str, '\n');
	} while (str.find("GLOBAL SYMBOLS: SORTED BY Symbol Address ") == string::npos);
	
	//Extract after "GLOBAL SYMBOLS : SORTED BY Symbol Address"
	while (!in.eof())
	{
		getline(in, str, '\n');
		target_file.push_back(str);
	}

	int tf_length = target_file.size();
	
	//extract API name from Testbed.txt and stored in vector(targetfile_api)
	vector <string> targetfile_api;
	targetfile_api.resize(tf_length);
	target_file.resize(tf_length);

	for (int i = 0; i < tf_length; i++) {
		if (target_file[i].size() >= 15)
		{
			targetfile_api[i] = target_file[i].substr(16);
			trim(targetfile_api[i]);
		}
	}
	//
	map<string, string> m_apiaddr;
	//mapping address to API name from Testbed.txt and stored in map<key : apiname, value : addr>(m_apiaddr)

	for (int i = 0; i < tf_length; i++) {
		if (target_file[i].size() >= 15)
		{
			m_apiaddr[targetfile_api[i]] = target_file[i].substr(6, 8);//addr
		}
	}
	//validate mapping
	cout << "-------------------------------------------------finish----------------------------" << endl;
	cout << m_apiaddr["_OSInit"] << endl; // success!!
	cout << m_apiaddr["_OSTaskReturnHook"] << endl; // success!!
	cout << m_apiaddr["_OS_CPU_SR_Save"] << endl; // success!!
	cout << m_apiaddr["_OSTaskStkInit"] << endl; // success!!
	cout << m_apiaddr["___TI_readmsg"] << endl; // success!!
	cout << m_apiaddr["_ECap1Regs"] << endl; // success!!

	cout << "--------------------open call graph-------------------------------------------------" << endl;
	//extract between "===============" & "The following ~~" to CG_storage vector

	string CGPath = "C:\\Users\\Seong\\source\\Practice_C++\\grdaduateproject2\\Testbed_cg.txt";

	vector <string> CG_storage; //
	string CG_str;
	
	ifstream ifile_cg(CGPath);

	if (ifile_cg.is_open())
	{
		cout << "file open successful" << endl;
	}

	do {
		getline(ifile_cg, CG_str, '\n');
	} while (CG_str.find("======================================================================") == string::npos);

	do {
		getline(ifile_cg, CG_str, '\n');
		CG_storage.push_back(CG_str);
	} while (CG_str.find("The following functions are known to contain indirect function calls, but") == string::npos);

	int CG_length = CG_storage.size();
	
	vector<vector <string> > CG_info;
	vector < string> CG_info1;
	// CG_info is 2-dimension vector & consists of the number of '|', the name of the api, and the address of the api.
		
	for (int i = 0; i < CG_length; i++) {
		for (int j = 0; j < 1; ++j) {
			CG_info1.clear();
			int cnt = string_function(CG_storage[i]);
			string CG_apiname = CG_storage[i].substr(cnt * 3, CG_storage[i].find(':') - cnt * 3 - 1);
			if (CG_storage[i].size() > 0) {
				CG_info1.push_back(to_string(cnt));
				CG_info1.push_back(CG_apiname);
				CG_info1.push_back(m_apiaddr[CG_apiname]);
			}
			else
				continue;
		}
		CG_info.push_back(CG_info1);
	}
	//print CG_info vector
	for (int i = 0; i < CG_info.size(); i++) {
		for (int j = 0; j < CG_info[i].size(); j++) {
			cout << CG_info[i][j] << "\n";
		}
		cout << endl;
	}
	
	/*ofstream bin_out("C:\\Users\\Seong\\source\\Practice_C++\\grdaduateproject2\\TestbedOUT.dat", ios::out, ios::binary);
	bin_out.write('a'.)*/

	string path = "C:\\Users\\Seong\\source\\Practice_C++\\grdaduateproject2\\Project2\\CG_bin.bin";
	
	ofstream binwrite(path, ios::binary);
	if (binwrite.is_open())
	{
		cout << "file generate" << endl;
	}

	int space = 4; // if file size is over than 32767, you can fix this value
	// but, it's over than 3

	for (int i = 0; i < CG_info.size(); i++) {
		//if(CG_info[i].)
		if (!CG_info[i].empty()) {
			for (int j = 0; j < 3; j++) {
				binwrite.write(reinterpret_cast<const char*>(&CG_info[i][j]), CG_info[i][j].size()+space);
			}
		}

		else 
			continue;
	}
	binwrite.close();






}