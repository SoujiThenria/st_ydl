#ifndef __YDL_DATA_HPP__
#define __YDL_DATA_HPP__

#include <string>

using namespace std;

class YDLdata
{
    friend ostream &operator<<(ostream &input, const YDLdata &a);
public:
    #if _WIN32
        YDLdata(string _path, string _link, string _command = "youtube-dl -q -i --download-archive \"$Download_Path/downloaded.txt\" --no-post-overwrites "
                                "-f \"bestvideo[ext=mp4, vcodec!^=av0]+bestaudio[ext=m4a]/bestvideo+bestaudio\" --merge-output-format mp4 "
                                "\"$Video_ID\" -o \"$Download_Path/%(title)s.%(ext)s\"");
    #endif
    #if __unix__
        YDLdata(string _path, string _link, string _command = "youtube-dl -q -i --download-archive \"$Download_Path/downloaded.txt\" --no-post-overwrites "
                                "-f 'bestvideo[ext=mp4, vcodec!^=av0]+bestaudio[ext=m4a]/bestvideo+bestaudio' --merge-output-format mp4 "
                                "\"$Video_ID\" -o \"$Download_Path/%(title)s.%(ext)s\"");
    #endif
    
    // Execute a system call [system()] with the command.
    void download();

private:
    // Replaces the variables in the "command"-string with the "path" and "link". [throw]
    void replace();
    // Creates the download path if not existing. [throw]
    void test_obj();

    string path;
    string link;
    string command;
};

#endif