#include<iostream>
#include<fstream>
using namespace std;
void cpy(char out[])
{
	ifstream ob("/home/sampath/repo/note_lib/sampath.s16");
	ofstream o(out);
	char ch;
//	printf("%s\n",out);
	while(ob.eof()==0)
	{
		ob.get(ch);
		o.put(ch);
//		cout << ch;
	}
	o.close();
	ob.close();
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
