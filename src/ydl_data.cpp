#include "ydl_data.hpp"

#include <iostream>
#include <filesystem>

using namespace std;


YDLdata::YDLdata(string _path, string _link, string _command)
: path(_path), link(_link), command(_command)
{}

void YDLdata::download()
{
    try
    {
        test_obj();
        replace();
        system(command.c_str());   
    }
    catch(const string &s)
    {
        cerr << "Error:\t" << s << endl;
        exit(EXIT_FAILURE);
    }
}

void YDLdata::replace()
{
    // Strings to search and to replace.
    string Download_Path = "$Download_Path";
    string Video_ID = "$Video_ID";

    // The "replace_test" is needed to identify if the variable was found or not.
    bool replace_test = false;

    // Replace "Download_Path"
    for (size_t index = 0; (index = command.find(Download_Path)) != string::npos;)
    {
        command.replace(index, Download_Path.size(), path);
        replace_test = true;
    }
    
    if (!replace_test)
        throw "No variable '" + Download_Path + "' in the command";
    
    replace_test = false;

    // Replace "Video_ID"
    for (size_t index = 0; (index = command.find(Video_ID)) != string::npos;)
    {
        command.replace(index, Video_ID.size(), link);
        replace_test = true;
    }

    if (!replace_test)
        throw "No variable '" + Video_ID + "' in the command";
}

void YDLdata::test_obj()
{
    if (path.empty())
        throw "There is no path set for this Link: " + link;

    if (!filesystem::is_directory(path))
        if (!filesystem::create_directory(path))
            throw "Could not create missing directory " + path;

}

ostream &operator<<(ostream &input, const YDLdata &a)
{
    input << "Path: " << a.path << endl
          << "Link: " << a.link << endl
          << "Command: " << a.command << endl;

    return input;
}