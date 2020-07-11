#include <iostream> 
#include <string.h>
#include <sstream>
#include <fstream>
using namespace std; 
  
string boomerang(){
	string ans = "";
    ans = ans + to_string(1) + " ("+to_string(0)+","+to_string(1)+")" + " ("+to_string(1)+","+to_string(1)+") " + " ("+to_string(0)+","+to_string(0)+") " + "\n"; //trailing spaces and endlines dont matter
    ans = ans + to_string(2)+" ("+to_string(0)+","+to_string(2)+")" + " ("+to_string(1)+","+to_string(3)+")  " + " ("+to_string(0)+","+to_string(3)+")" + "\n";
    ans = ans + to_string(3)+" ("+to_string(2)+","+to_string(1)+") " + " ("+to_string(2)+","+to_string(2)+")" + " ("+to_string(1)+","+to_string(2)+")" + "\n";
    ans = ans + to_string(4)+" ("+to_string(3)+","+to_string(1)+")" + " ("+to_string(2)+","+to_string(0)+")" + " ("+to_string(3)+","+to_string(0)+")" + "\n";
    ans = ans + to_string(5)+" ("+to_string(2)+","+to_string(3)+")" + " ("+to_string(3)+","+to_string(2)+")" + " ("+to_string(3)+","+to_string(3)+")  " + "\n\n\n";
    return ans;
}

int main(int argc, char** argv) 
{ 
	// string ans = boomerang();
	// cout<<ans;

    string file = argv[1];
	ifstream data(file);
	if(!data.is_open())
	{
		string ans = "Unable to open file";
		cout<<ans<<endl;
		return -1;
	}

	string line; //Variables for file reading
	string temp;
	string val;
	int size;

	getline(data,line);
	stringstream s1(line);
	s1 >> temp;	// read n
	s1 >> size;	// read n value

	string row = "";
	string col = "";

    int i = 1;
    char x = line.at(i);
    while(x != ',')
    {
    	row += line.at(i);
    	i++;
    	x = line.at(i);
    }
    i++;
    x = line.at(i);
    while(x != ')')
    {
    	col += line.at(i);
    	i++;
    	x = line.at(i);
    }

    cout<<row<<" "<<col;

    return 0; 
} 
