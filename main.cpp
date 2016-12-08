#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "fileanalysis.h"

using namespace std;

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
       	char ** itr = std::find(begin, end, option);
       	if (itr != end && ++itr != end)
	{
		return *itr;
	}
	return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
	return std::find(begin, end, option) != end;
}

int main(int argc, char *argv[])
{
	//usage: -s source name files, -o output files, -l lookup file
	
	if(!cmdOptionExists(argv, argv + argc, "-s") || 
			!cmdOptionExists(argv, argv + argc, "-o")||
			!cmdOptionExists(argv, argv + argc, "-l"))
	{
		cout << "/usage: -s source name files, -o output files, -l lookup file" << endl;
		return 0;
	}

	//name source file generated by python
	char * name_source_filepath = getCmdOption(argv, argv+argc, "-s");
	//output the lookup results
	char * output_filepath = getCmdOption(argv, argv+argc, "-o");

	//lookup file
	char * lookup_filepath = getCmdOption(argv, argv+argc, "-l");
	vector<string> results;
	FileAnalysis file_analyzor;

	ifstream name_source_file(name_source_filepath);
	ofstream output_file;
	output_file.open(output_filepath, std::ios_base::app);

        string name_source;

	file_analyzor.init_file(lookup_filepath);
	//loop the name source file
        while (getline(name_source_file, name_source))
	{

		results = file_analyzor.get_content_by_partialusername(name_source);
	        for (vector<string>::const_iterator i = results.begin(); i != results.end(); ++i)
		{
			output_file << *i << endl;
		}	
	}

	file_analyzor.close_file();

    return 1;

}