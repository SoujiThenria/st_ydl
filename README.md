# st_ydl

The program *st_ydl* can be used to automate *yt-dlp* downloads on *Linux* and *Windows* platforms.  
In order to use it out of the box, in a unix like environment, you need to have downloaded *yt-dlp* in to `/usr/local/bin/` and have *ffmpeg* installed.  

## Installation
### Linux

```bash
git clone https://github.com/SoujiThenria/st_ydl.git
cd st_ydl && mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install
````
After that *st_ydl* is installed in `/usr/local/bin`.

### Windows

I have not build for Windows on Windows by now, but the procedure should be similar to the one described below.  
I only cross build it for windows using the *mingw*-toolchain.  
In order to do that you have to install the *mingw*-toolchain and the *boost*-library for *mingw*. If you want to link static change following line in the `CMakeLists.txt` in the root directory:
`set(Boost_USE_STATIC_LIBS OFF) -> set(Boost_USE_STATIC_LIBS ON)` . Moreover if you want to link the standard libs static too you can add to your cmake call `-DCMAKE_EXE_LINKER_FLAGS="-static"`.

After that you can build *st_ydl*:
```bash
git clone https://github.com/SoujiThenria/st_ydl.git
cd st_ydl && mkdir build && cd build
mingw64-cmake -DCMAKE_BUILD_TYPE=Release ..
mingw64-make
```
*st_ydl.exe* can be found in the `build/src` directory.  

In my opinion the easiest way to use *yt-dlp.exe*(, *ffmpeg.exe*) and *st_ydl.exe* is to copy all in one folder and use them from there.

## Usage

You have to create a file which contains your *links*, *paths* where the downloaded files should be stored, additionally you can specify a *command* which should be used. 
At the end of the command I recommend to define where stderr should be logged, otherwise it can and will mess with the cli output.

Example 1:
```text
>C:\Users\your_user\Desktop\st_ydl\yt-dlp.exe -i "$Video_ID" -o "$Download_Path\%(title)s.%(ext)s 2>/dev/null"
#/path/to/directory
https://whateverlink.com
https://whateverlink2.com
#/path/to/next/directory
https://anotherlink.com
````

Example 2:
```text
>C:\Users\your_user\Desktop\st_ydl\yt-dlp.exe -i "$Video_ID" -o "$Download_Path\%(title)s.%(ext)s 2>st_ydl_error.log"
#/path/to/directory
    This line will be ignored
https://whateverlink2.com
#/path/to/next/directory
https://anotherlink.com

>Some new command
https://some_other_link which is stored in the last defined path
````

Empty lines and lines that don't start with a ">"(for the command), "#"(for the path) or "h"(for the http(s) request) are ignored. 

You have to create the directories by your own if they don't exists. And then you have to run the program with the path to your created file.  

`/usr/local/bin/st_ydl /home/your_file.txt`

## Info
The command you specified in the file is optional, if none is specified, the following command is executed:   

#### Linux
```
yt-dlp -q -i --download-archive "$Download_Path/downloaded.txt" --no-post-overwrites -f 'bestvideo[ext=mp4][vcodec!^=av0]+bestaudio[ext=m4a]/bestvideo+bestaudio' --merge-output-format mp4 "$Video_ID" -o "$Download_Path/%(title)s.%(ext)s" 2>/dev/null
```
#### Windows
```
yt-dlp -q -i --download-archive "$Download_Path/downloaded.txt" --no-post-overwrites -f "bestvideo[ext=mp4][vcodec!^=av0]+bestaudio[ext=m4a]/bestvideo+bestaudio" --merge-output-format mp4 "$Video_ID" -o "$Download_Path/%(title)s.%(ext)s" 2>NUL
```

This command downloads the video(s) in to `$Download_Path`, removes the video id from the file name, saves the video id in `$Download_Path/download.txt`. The best mp4 video (that don't have the av01 codec) and the best m4a audio file gets downloaded and merged with e.g. *ffmpeg*.

If you want to specify your own command, keep in mind that `$Download_Path` and `$Video_ID` are replaced with the path and the links from the specified file. Errors are not logged and dumped in the null device.  

## Links
[Download yt-dlp](https://github.com/yt-dlp/yt-dlp)  
[Download ffmpeg](https://ffmpeg.org/download.html)
