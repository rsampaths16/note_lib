#include<iostream>
#include<fstream>
#include<ctime>
#include<cstdio>
const std::string currentDateTime() 
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%d-%m-%Y.%X", &tstruct);
	return buf;
}
using namespace std;
void cpy(char out[])
{
	ofstream fout(out);
	fout << "/*" << endl;
	fout << "\tCoder\t: R Sampath Sukesh." << endl;
	fout << "\tHandle\t: rsampaths16." << endl;
	fout << "\tEmail\t: rsampaths16@gamil.com." << endl;
	fout << "\tCountry\t: India." << endl;
	fout << "\tTStamp\t: " << currentDateTime() << endl;
	fout << "*/" << endl << endl << endl;
	fout << "#pragma comment(linker, \"/STACK:36777216\")" << endl;
	fout << "#include<bits/stdc++.h>" << endl;
	fout << "using namespace std;" << endl;
	fout << "typedef long long ll;" << endl << endl << endl;
	fout << "/*==================!!-Code-Starts-From-Here-!!==================*/" << endl << endl << endl;
	fout << "/*=======================!!-End-Of-Code-!!=======================*/" << endl;

	fout.close();
	return;
}

int main(int argc,char *argv[])
{
	if(argc<2)
	{
		cerr << "No Input File's specified!!"<<endl;
		return 1;
	}
	for(int i=1;i<argc;i++)
		cpy(argv[i]);
	return 0;
}
