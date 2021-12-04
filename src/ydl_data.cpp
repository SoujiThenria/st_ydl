#include "ydl_data.hpp"

#include <iostream>

using namespace std;


YDLdata::YDLdata(filesystem::path _path, string _link, string _command)
: path(_path), link(_link), command(_command)
{
    try
    {
        replace();
        filesystem::create_directories(path);
    }
    catch(const invalid_argument &inv_a)
    {
        cerr << "Invalid argument ERROR:\n\t" << inv_a.what() << endl;
        exit(EXIT_FAILURE);
    }
    catch(const filesystem::filesystem_error &fe)
    {
        cerr << fe.what() << endl
             << fe.path1() << endl;
        exit(EXIT_FAILURE);
    }
    catch(const exception &exc)
    {
        cerr << "Exception ERROR:\n\t" << exc.what() << endl;
        exit(EXIT_FAILURE);
    }
    catch(...)
    {
        cerr << "Unknown ERROR:\n\tWhile trying to start 'yt-dlp' for:\n\tCommand: " + command + "\n\tLink: " + link;
        exit(EXIT_FAILURE);
    }
}

void YDLdata::download()
{
    system(command.c_str());
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
        command.replace(index, Download_Path.size(), path.string());
        replace_test = true;
    }
    
    if (!replace_test)
    {
        throw invalid_argument("The required variable '" + Download_Path + "' was not found in the specified command (" + command + ")\n\tfor the link: " + link);
    }
    
    replace_test = false;

    // Replace "Video_ID"
    for (size_t index = 0; (index = command.find(Video_ID)) != string::npos;)
    {
        command.replace(index, Video_ID.size(), link);
        replace_test = true;
    }

    if (!replace_test)
    {
        throw invalid_argument("The required variable '" + Video_ID + "' was not found in the specified command (" + command + ")");
    }
}

string YDLdata::get_Link()
{
    return link;
}

