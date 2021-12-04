/*
    Includes all needed values to execute yt-dlp for one link + the systemcall to execute yt-dlp
*/

#ifndef __YDL_DATA_HPP__
#define __YDL_DATA_HPP__

#include <string>
#include <filesystem>

using namespace std;

class YDLdata
{
public:
    #if _WIN32
        YDLdata(filesystem::path _path, string _link, string _command = "yt-dlp -q -i --download-archive \"$Download_Path/downloaded.txt\" --no-post-overwrites -f "
                                "\"bestvideo[vcodec!^=av0]+bestaudio\" --merge-output-format mp4 \"$Video_ID\" -o \"$Download_Path/%(title)s.%(ext)s\" 2>NUL");
    #endif
    #if __unix__
        YDLdata(filesystem::path _path, string _link, string _command = "yt-dlp -q -i --download-archive \"$Download_Path/downloaded.txt\" --no-post-overwrites -f "
                                "'bestvideo[vcodec!^=av0]+bestaudio' --merge-output-format mp4 \"$Video_ID\" -o \"$Download_Path/%(title)s.%(ext)s\" 2>/dev/null");
    #endif
    
    // Execute a system call [system()] with the command variable.
    void download();

    // returns the link
    string get_Link();
    
private:
    // Replaces the variables in the "command"-string with the "path" and "link". [throws "invalid_argument" if one of both variables was not found]
    void replace();

    filesystem::path path;
    string link;
    string command;
};

#endif