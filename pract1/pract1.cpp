#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>

using namespace std;

int main() {
	string str[][3] = { {"0", "_HOSTlseek", "00302b63"},
	{"2", "_getdevice", "00302c2f"},
	{"5", "_OS_CPU_SR_Restore", "0030304c"},
	{"8", "_memcpy", "00302f59"},
	};

	for(int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			cout << str[i][j] << endl;
		}		

	}



	string path = "C:\\Users\\Seong\\source\\Practice_C++\\grdaduateproject2\\Project2\\data.bin";
	//cout << str.size() << endl;
	//cout << sizeof(string) << endl;
	ofstream os(path,  ios::binary);
	if (os.is_open())
	{
		cout << "file generate" << endl;
	}

	for (int i = 0; i < 4; i++) {
		
		for (int j = 0; j < 3; j++) {
			os.write(reinterpret_cast<const char*>(&str[i][j]), str[i][j].size() + 4);
			//size_t size = str[i][0].size() + str[i][1].size() + str[i][2].size();
		}
		
	}

	os.close();

	/*vector<string>b;

	ifstream is(path, ios::binary);
	for (int i = 0; i < str_length; i++) {
		int bW_byte = 0;
		bW_byte += b[i].size();
		os.write(reinterpret_cast<const char*>(&b[i]), bW_byte);
	}
	for (int i = 0; i < str_length; i++)
		cout << b[i];
	cout << endl;*/

}
	




	