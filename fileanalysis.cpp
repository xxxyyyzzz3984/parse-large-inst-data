#include "fileanalysis.h"

using namespace std;

FileAnalysis::FileAnalysis()
{
}

void FileAnalysis::init_file(string filepath) 
{
	m_mmap.open(filepath.c_str(), boost::iostreams::mapped_file::readonly);

	m_filepath = filepath;

}

int FileAnalysis::countline()
{
	auto f = m_mmap.const_data();
	auto l = f + m_mmap.size();
	uintmax_t numLines = 0;
	while (f && f!=l)
	{
		if ((f = static_cast<const char*>(memchr(f, '\n', l-f))))
		{
			numLines++, f++;
		}
	}

	return numLines;
}

vector<string> FileAnalysis::get_content_by_partialusername(string username)
{
	vector<string> results;
	auto f = m_mmap.const_data();
	auto l = f + m_mmap.size();

	while (f && f!=l)
	{


		if ((f = static_cast<const char*>(memchr(f, '\n', l-f))))
		{
			//cout << f << endl;
			string s(f, 50);
			//cout << s << endl;
			//cout << f << endl;
				       //std::cout << "user found!" <<endl;
			stringstream ss(s);
			char c;
			string name;
			int count = 0;
			while (ss >> c)
			{
				if(c == ',' && count == 0)
				{
					count += 1;
					continue;
				}
				if (c == ',' && count > 0)
				{
					break;
				}

				if (count > 0)
				{
					name += c;
				}
			}
			
			if (name.find(username) != std::string::npos) 
			{	
			    cout << "found similar name " << name << endl;
			    results.push_back(name);
			}	
		}

		f++;
		
	}
	cout << endl<<"complete for file " << m_filepath << endl;
	return results; 
}

void FileAnalysis::close_file()
{
	m_mmap.close();
}

