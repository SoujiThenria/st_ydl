#include <fstream>
#include <iostream>

#include "config.hpp"

void config::read(std::string _file)
{
    std::ifstream conf_file;
    conf_file.open(_file);
    std::string line;

    int temp = 0;
    while (std::getline(conf_file, line))
    {
        if (line.at(0) == '#')
        {
            if (temp != 0)
            {
                _data.push_back(links);
                links.clear();
            }

            save_path = line;
            save_path.erase(0, 1);
            links.push_back(save_path);
            ++temp;
        }
        else
        {
            links.push_back(line);
        }
    }
    _data.push_back(links);
    
    conf_file.close();

}

void config::replace(std::string *_orig_string, std::string to_replace, std::string replacement)
{
    

    for (size_t index = 0; (index = _orig_string->find(to_replace)) != std::string::npos;)
        _orig_string->replace(index, to_replace.size(), replacement);
}