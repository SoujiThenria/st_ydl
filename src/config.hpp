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
    void read(std::string _file);
    void replace(std::string *_orig_string, std::string to_replace, std::string replacement);

    std::string command;
    std::string save_path;
    std::vector<std::string> links;
    std::vector<std::vector<std::string>> _data;
};

#endif