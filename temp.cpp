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
	fout << "#define ONLINE" << endl;
	fout << "#ifndef ONLINE" << endl;
	fout << "\t#define TRACE" << endl;
	fout << "\t#define DEBUG" << endl;
	fout << "#endif" << endl<<endl;

	fout << "#ifdef TRACE" << endl;
	fout << "\t#define trace()             cerr<<__FUNCTION__<<\" : \"<<__LINE__<<endl" << endl;
	fout << "\t#define trace1(a)           cerr<<__FUNCTION__<<\" : \"<<__LINE__<<\" | \"<<#a<<'='<<a<<endl" << endl;
	fout << "\t#define trace2(a,b)         cerr<<__FUNCTION__<<\" : \"<<__LINE__<<\" | \"<<#a<<'='<<a <<\" | \"<<#b<<'='<<b<<endl" << endl;
	fout << "\t#define trace3(a,b,c)       cerr<<__FUNCTION__<<\" : \"<<__LINE__<<\" | \"<<#a<<'='<<a <<\" | \"<<#b<<'='<<b<<\" | \"<<#c<<'='<<c<<endl" << endl;
	fout << "\t#define trace4(a,b,c,d)     cerr<<__FUNCTION__<<\" : \"<<__LINE__<<\" | \"<<#a<<'='<<a <<\" | \"<<#b<<'='<<b<<\" | \"<<#c<<'='<<c<<\" | \"<<#d<<'='<<d<<endl" << endl;
	fout << "\t#define trace5(a,b,c,d,e)   cerr<<__FUNCTION__<<\" : \"<<__LINE__<<\" | \"<<#a<<'='<<a <<\" | \"<<#b<<'='<<b<<\" | \"<<#c<<'='<<c<<\" | \"<<#d<<'='<<d<<\" | \"<<#e<<'='<<e<<endl" << endl;
	fout << "\t#define trace6(a,b,c,d,e,f) cerr<<__FUNCTION__<<\" : \"<<__LINE__<<\" | \"<<#a<<'='<<a <<\" | \"<<#b<<'='<<b<<\" | \"<<#c<<'='<<c<<\" | \"<<#d<<'='<<d<<\" | \"<<#e<<'='<<e<<\" | \"<<#f<<'='<<f<<endl" << endl;
	fout << "#else" << endl;
	fout << "\t#define trace()" << endl;
	fout << "\t#define trace1(a)" << endl;
	fout << "\t#define trace2(a,b)" << endl;
	fout << "\t#define trace3(a,b,c)" << endl;
	fout << "\t#define trace4(a,b,c,d)" << endl;
	fout << "\t#define trace5(a,b,c,d,e)" << endl;
	fout << "\t#define trace6(a,b,c,d,e,f)" << endl;
	fout << "#endif" << endl << endl;

	fout << "#ifdef DEBUG" << endl;
	fout << "\t#define pause system(\"sleep 0.5s\")" << endl;
	fout << "\t#define putx(x) x" << endl;
	fout << "\t#define msg(MSG) cerr <<__FUNCTION__<<\" : msg :- \"<< MSG <<endl" << endl;
	fout << "\t#define debug(x) cerr << '>' << #x << ':' << x << endl" << endl;
	fout << "#else" << endl;
	fout << "\t#define pause" << endl;
	fout << "\t#define putx(x)" << endl;
	fout << "\t#define msg(MSG)" << endl;
	fout << "\t#define debug(x)" << endl;
	fout << "#endif" << endl << endl;

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
