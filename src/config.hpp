#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include <string>
#include <vector>

class config
{
private:
protected:
public:
    config(){};
    ~config(){};
    // reads data from specified file in to the vector "_data"
    void read(std::string _file);

    // in "_orig_string" replaces "to_replace" with "replacement"
    void replace(std::string *_orig_string, std::string to_replace, std::string replacement);

    // command used for executing youtube-dl if specified in "_file"
    std::string command;

    // paths and corresponding links
    std::vector<std::vector<std::string>> _data;
};

#endif