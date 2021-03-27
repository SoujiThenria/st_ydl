# st_ydl

The program *st_ydl* can be used to automate *youtube-dl* downloads on *linux* platforms.  
In order to use it out of the box you need to have downloaded *youtube-dl* in to `/usr/local/bin/` and have *ffmpeg* installed.  

## Installation

```bash
git clone https://github.com/SoujiThenria/st_ydl.git
cd st_ydl && mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install
````
After that *st_ydl* is installed in `/usr/local/bin`.

## Usage

You have to create a file which contains your links and paths where the downloaded files should be stored.

```text
#/path/to/directory
https://whateverlink.com
https://whateverlink2.com
#/path/to/next/directory
https://anotherlink.com
````

You have to create the directories by your own if they don't exists. And then you have to run the program with the path to your created file.  

`/usr/local/bin/st_ydl /home/yourfile.txt`

## Info
The command which gets executed looks like this:  
```
/usr/local/bin/youtube-dl -i --download-archive "$DIR_PATH/downloaded.txt\" --no-post-overwrites -f 'bestvideo[ext=mp4, vcodec^=avc1]+bestaudio[ext=m4a]/bestvideo+bestaudio' --merge-output-format mp4 "$SAVE_ID" -o "$DIR_PATH/%(title)s.%(ext)s"
```
This command downloads the video(s) in to `$DIR_PATH`, removes the video id from the file name, saves the video id in `$DIR_PATH/download.txt`. The best mp4 video (that dont have the avc1 codec) and the best m4a audio file gets downloaded and merched with e.g. *ffmpeg*.

If you want to change this command, you can do that in *main.cpp*. Keep in mind that `$DIR_PATH` and `$SAVE_ID` are replaced with the path and the links from the specified file.