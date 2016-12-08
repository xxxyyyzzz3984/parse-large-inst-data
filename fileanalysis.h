#ifndef FILEANALYSIS_H
#define FILEANALYSIS_H
#include <iostream>
#include <algorithm>
#include <boost/iostreams/device/mapped_file.hpp>
#include <vector>
#include <sstream>
#endif // FILEANALYSIS_H


class FileAnalysis
{
public:
    FileAnalysis();
    //must be called prior to any other functions
    void init_file(std::string filepath);
    void close_file();

    int countline();
    
    std::vector<std::string> get_content_by_partialusername(std::string username);

private:
    boost::iostreams::mapped_file m_mmap;
    std::string m_filepath;
};

