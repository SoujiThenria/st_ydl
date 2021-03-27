#include <iostream>
#include <string.h>

#include "config.hpp"

int main(int argc, const char **argv)
{
    if (argc != 2)
    {
        std::cout << "Error: Unexpected number of cli arguments." << std::endl;
        exit(EXIT_FAILURE);
    }
    
    config conf;
    // read data from file
    conf.read(argv[1]);

    // get command
    for (unsigned int i = 0; i < (unsigned)conf._data.size(); ++i)
    {
        for (unsigned int j = 1; j < (unsigned)conf._data[i].size(); ++j)
        {
            std::string P1 = "/usr/local/bin/youtube-dl -i --download-archive \"$DIR_PATH/downloaded.txt\" --no-post-overwrites "
                            "-f 'bestvideo[ext=mp4, vcodec^=avc1]+bestaudio[ext=m4a]/bestvideo+bestaudio' --merge-output-format mp4 \"$SAVE_ID\" -o \"$DIR_PATH/%(title)s.%(ext)s\"";
            if (conf.command.length() != 0)
                P1 = conf.command;
            conf.replace(&P1,"$DIR_PATH", conf._data[i][0]);
            conf.replace(&P1,"$SAVE_ID", conf._data[i][j]);
            //std::cout << P1 << std::endl;

            // execute command
            char command[1000];
            strcpy(command, P1.c_str());
            system(command);
        }
    }

    exit(EXIT_SUCCESS);
}