#include <fstream>
#include <iostream>

#include "config.hpp"

void config::read(std::string _file)
{
    std::ifstream conf_file;
    std::string line;
    std::string save_path;
    std::vector<std::string> links;

    // open the file
    conf_file.open(_file);

    int temp = 0;
    while (std::getline(conf_file, line))
    {
        // get command if existing
        if (line.at(0) == '>')
        {
            command = line;
            command.erase(0, 1);
        }
        // get path
        else if (line.at(0) == '#')
        {
            // every time a new path is found, 
            // push the old vector "links" in to the "_data" vector
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
    // push the last vector "links" in to "_data"
    _data.push_back(links);
    
    // close file
    conf_file.close();

}

void config::replace(std::string *_orig_string, std::string to_replace, std::string replacement)
{
    for (size_t index = 0; (index = _orig_string->find(to_replace)) != std::string::npos;)
        _orig_string->replace(index, to_replace.size(), replacement);
}