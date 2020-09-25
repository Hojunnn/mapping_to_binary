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
using std::pair;
using namespace boost;

//int main() {
//
//	string TBPath = "C:\\Users\\Seong\\source\\Practice_C++\\GraduateProject\\Testbed.txt";
//	string str = " ";
//	//seperate txt file by 'SORTED BY Symbol Address'
//	//cout << in.is_open() << endl;
//	vector <string> target_file;
//	int tf_length = target_file.size();
//	ifstream in(TBPath);
//
//	if (in.is_open())
//	{
//		cout << "file open successful" << endl;
//	}
//
//	do {
//		getline(in, str, '\n');
//	} while (str.find("GLOBAL SYMBOLS: SORTED BY Symbol Address ") == std::string::npos);
//
//	while (!in.eof())
//	{
//		getline(in, str, '\n');
//		target_file.push_back(str);
//	}
//
//	cout << "---------------------------------------------------------------------------------" << endl;
//	cout << "" << endl;
//
//	//##Delete index 0,1 contents## -> 
//
//	for (int i = 0; i < 3; i++) {
//		for (int i = 0; i < tf_length - 1; i++) {
//			target_file[i] = target_file[i + 1];
//
//		} --tf_length;
//	}
//	cout << tf_length << endl;
//	cout << "string on 480 :" << " " << target_file[480] << endl;
//
//	//##Delete finish##
//
//	string targetfile_api[485];
//
//	for (int i = 0; i < tf_length; i++) {
//
//		if (target_file[i] == "\0") break;
//
//		else targetfile_api[i] = target_file[i].substr(16, 30);
//
//		trim(targetfile_api[i]);
//	}
//
//	cout << "string on 479 :" << " " << targetfile_api[479] << endl;//output : last name
//	cout << "string on 480 :" << " " << targetfile_api[480] << endl;//output : X
//	/* note : Error can be occur on here*/
//
//
//	////extract each address, name
//	//string adr_save[2][sizeof(target_file)/sizeof(string)]{};
//	map<string, string> m_apiaddr;
//
//	for (int i = 0; i < tf_length; i++) {
//		//cout<<target_file[i].substr(6, 8)<<endl;
//		if (target_file[i] == "\0") break;
//
//		else m_apiaddr[targetfile_api[i]] = (target_file[i].substr(6, 8));//addr
//	//	//adr_save[1][i] = target_file[i].substr(16, 30);//api name
//	}
//	//

int main() {

	string TBPath = "C:\\Users\\Seong\\source\\Practice_C++\\GraduateProject\\Testbed.txt";
	string str;
	//seperate txt file by 'SORTED BY Symbol Address'
	//cout << in.is_open() << endl;

	ifstream in(TBPath);
	vector <string> target_file;


	if (in.is_open())
		cout << "file open successful" << endl;

	do {
		getline(in, str, '\n');
	} while (str.find("GLOBAL SYMBOLS: SORTED BY Symbol Address ") == string::npos);

	while (!in.eof())
	{
		getline(in, str, '\n');
		target_file.push_back(str);
	}

	int tf_length = target_file.size();

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

	//cout << "string on 479 :" << " " << targetfile_api[479] << endl;//output : last name
	//cout << "string on 480 :" << " " << targetfile_api[480] << endl;//output : X
	/* note : Error can be occur on here*/


	////extract each address, name
	//string adr_save[2][sizeof(target_file)/sizeof(string)]{};
	map<string, string> m_apiaddr;

	for (int i = 0; i < tf_length; i++) {
		if (target_file[i].size() >= 15)
		{
			m_apiaddr[targetfile_api[i]] = target_file[i].substr(6, 8);//addr
		}
	}
	cout << "-------------------------------------------------finish----------------------------" << endl;
	cout << m_apiaddr["_OSInit"] << endl; // success!!
	cout << m_apiaddr["_OSTaskReturnHook"] << endl; // success!!
	cout << m_apiaddr["_OSTaskStatHook"] << endl; // success!!
	cout << m_apiaddr["_OSTaskStkInit"] << endl; // success!!
	cout << m_apiaddr["___TI_readmsg"] << endl; // success!!
	cout << m_apiaddr["_ECap1Regs"] << endl; // success!!

	cout << "--------------------open call graph-------------------------------------------------" << endl;

	//--------------------------------------call graph loading--------------------------------//

	string CGPath = "C:\\Users\\Seong\\source\\Practice_C++\\grdaduateproject2\\Testbed_cg.txt";
	
	vector <string> CG_storage; // temporary space for txt reading -> warning!! static size of txt file
	string CG_str;
	int CG_length = CG_storage.size();

	ifstream ifile_cg(CGPath);

	if (ifile_cg.is_open())
	{
		cout << "file open successful" << endl;
	}

	do {
		getline(ifile_cg, CG_str, '\n');
	} while (CG_str.find("======================================================================") == string::npos);

	while (!in.eof())
	{
		getline(ifile_cg, CG_str, '\n');
		CG_storage.push_back(CG_str);
	}
	//CG file store in CG_storage string array
	//while (!ifile_cg.eof())// file loading except '|" mark 
	//{
	//	getline(ifile_cg, CG_str);
	//	if (!CG_str.find("======================================================================"))
	//	{
	//		
	//		cout << "Find located the symbol" << endl;
	//		cout << " " << endl;
	//		
	//		
	//		for (int i = 0; i < CG_length; i++) {
	//			
	//			getline(ifile_cg, CG_storage[i]);
	//			
	//			replace_all(CG_storage[i], "|", "");
	//			
	//			if (!CG_storage[i].find("The following functions are known to contain indirect function calls, but"))
	//				break;

	//			cout << CG_storage[i] << "\n";
	//			/*if (!CG_storage[i].find("======================================================================"))
	//				break;*/
	//		}break;

	//	}
	//	
	//}ifile_cg.close();

	//cout << "=======check=========" << endl;
	//for (int i = 0; i < CG_length; i++)
	//{
	//	cout << CG_storage[i] << "\n";
	//}
	
	//before comparing, pasrsing CG_storage[]
	//'_' 찾으면 그걸 시작으로 ':' 나오기 전-1 까지 자르기
	//error!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	/*for (int i = 0; i < CG_length; i++)
	{
		if (CG_storage[i].size() == 0)
			cout << "size = 0" << "\n" << endl;

		else if (CG_storage[i].find('_'))
			CG_storage[i] = CG_storage[i].substr(CG_storage[i].find('_'), (CG_storage[i].find(':') - CG_storage[i].find('_') - 1));

		else if (CG_storage[i].find('|'))
			CG_storage[i] = "";			
		else if (CG_storage[i].find("$$MOD : wcs = 0")&& CG_storage[i].find("$$DIV : wcs = 0"))
			CG_storage[i] = "";
		else if (CG_storage[i].find("<repeat ...>"))
			CG_storage[i] = "";
		else
			continue;
	}*/
	
	/*for (int i = 0; i < CG_length; i++)
		cout << CG_storage[i];*/
	





	//find strings with comparing based api names
	
	//for (int i = 0; i < CG_length; i++) {
	//	m_apiaddr[CG_storage[i]] = //address storage
	//}
	
	   
	//change to binary file


	/*const unsigned long long size = 8ULL * 1024ULL * 1024ULL;
	unsigned long long a[size];*/

	
	//FILE* pFile;
	//pFile = fopen("file.binary", "wb");
	//for (unsigned long long j = 0; j < 1024; ++j) {
	//	//Some calculations to fill a[]
	//	fwrite(a, 1, size * sizeof(unsigned long long), pFile);
	//}
	//fclose(pFile);
	//return 0;
		
}



	
	/*vector<string> Split(string str, char delimiter)
	{
		vector<string> internal;
		stringstream ss(str);
		string temp;


		while (getline(ss, temp, delimiter))
		{
			internal.push_back(temp);
		}

		return internal;
	}*/
	/*string index = "";

	for (int i = 0; i < sizeof(target_file) / sizeof(string); i++) {
		index.append(target_file[i]);
	}
	cout << index << endl;*/



	/*cout << target_file[3].size() << endl;
	cout << target_file[4].size() << endl;

	cout << target_file[4].substr(17,30)<< endl;
	cout << target_file[3].substr(6, 8)<< endl;*/

/*cout << "************************************************************************" << endl;
string str_arr[ARR_SIZE];
int str_cnt=0;

char *str_buff = new char[ARR_SIZE];
strcpy(str_buff, index.c_str());

cout << str_buff << endl;

char *tok = strtok(str_buff, " ");
while (tok != nullptr) {
	str_arr[str_cnt++] = string(tok);
	tok = strtok(nullptr, " ");
}

cout << "-----------------------------string split----------------------------------" << endl;

for (int n = 0; n < str_cnt; n++) {
	cout << str_arr[n] << endl;
}*/

//	for (int i = 0; i < sizeof(target_file) / sizeof(string); i++) {
//
//		cout << target_file[i];
//		Split(target_file[i],' ');
//		for(int j = 0; j< internal.size();i++)
//		//각 배열의 원소인 문자열을 잘라서 주소, symbol로 나눠서 이차원 배열 저장
//	}
//
//	return 0;
//}

	/*while (findSA != string::npos) {
		string substring = index.substr(findSA,  - );
	}*/
	//if (index.find("GLOBAL SYMBOLS: SORTED BY Symbol Address"))
	//{
	//	cout << " Find first located symbol" << endl;
	//	cout << "-----------------------------------------------------------------" << endl;

	//	if (index.find(".text"))
	//	{
	//		cout << "Find .text symbol" << endl;
	//		cout << "-------------------------------------------------------------" << endl;

	//		for (int i = 0; i < sizeof(target_file) / sizeof(string); i++)
	//		{
	//			getline(in, target_file[i]);
	//			//cout << target_file[i];
	//		}
	//	}
	//				
	//}

//}
//cout << in.eof() << endl;

//while (!in.eof() && position < array_size)
//{
//	in.get(array[position]);
//	position++;
//}
//array[position - 1] = '\0';

//cout << "Display Array" << endl;
//cout << "             " << endl;
// 
//*while (getline(in, in_line)) {
//	cout << in_line << endl;
//}
//in.close();*/
//for (int i = 0; array[i] != '\0'; i++)
//{
//	cout << array[i] << endl;
//}
//
//cout << "------------------------------------------" << endl;
//cout << array << endl;
//
//int k = 0;

//char cpr_array1[] = "SORTED BY Symbol Address";

//int sz_cpr_array1 = sizeof(cpr_array1) / sizeof(char);
////cout << sz_cpr_array1 << endl;
//   

//for (int mainarray_position = 0; array[mainarray_position] != '\0'; mainarray_position++) {
//	for (k; k < sz_cpr_array1; k++) {
//		char check_char = cpr_array1[k];
//		if (check_char == array[mainarray_position])
//			cout << "one character complete" << endl;
//			
//			//if()


//	}
//	
//		
//		
//}




