#include "st_ydl.hpp"
#include "ydl_data.hpp"

#include <fstream>
#include <iostream>
#include <thread>
#include <queue>

#include <boost/thread.hpp>

using namespace std;

STydl::STydl(string _file)
: file_name(_file)
{
    try
    {
        read_file();
    }
    catch(const runtime_error &run_err)
    {
        cerr << run_err.what();
        exit(EXIT_FAILURE);
    }
    catch(const bad_alloc &ba)
    {
        cerr << ba.what();
        exit(EXIT_FAILURE);
    }
    catch(const exception &exc)
    {
        cerr << exc.what();
        exit(EXIT_FAILURE);
    }
    catch(...)
    {
        cerr << "ERROR (Unknown): while reading file and preparing data structure.";
        exit(EXIT_FAILURE);
    }
}

STydl::~STydl()
{
    for (auto [key, value] : progress)
    {
        delete key;
    }
}

void STydl::read_file()
{
    ifstream in_file(file_name);
    if (!in_file.is_open())
    {
        throw runtime_error("file handling error: Could not open file: " + file_name);
    }

    YDLdata *new_YDLdata;
    string command;
    string path;

    // Create for every link an object and push it in to the "data"-vector.
    // "command" and "path" might be the same over multiple links that's why they are saved in variables.
    string line;
    while (getline(in_file, line))
    {
        // Ignore empty lines and do nothing if the line starts with a " " (space).
        if (line != "")
        {
            switch (line.at(0))
            {
            case '>':
                line.erase(0, 1);
                command = line;
                break;
            
            case '#':
                line.erase(0, 1);
                path = line;
                break;

            case 'h':
                if (!command.empty())
                    new_YDLdata = new YDLdata(path, line, command);
                else
                    new_YDLdata = new YDLdata(path, line);

                // data.push_back(new_YDLdata);
                // push data in map first
                progress[new_YDLdata] = 2;
                
                break;
            
            default:
                break;
            }
        }
    }    
}

#if _WIN32
void STydl::printProgress(bool firstRun)
{
    system("cls");

    int i = 0;
    for (auto [key, value] : progress)
    {
        enum status {Finished, Downloading, Queued};
        
        switch (value)
        {
        case Finished:
            cout << "\033[1;32m" << "Finished -> " << "\033[0m";
            break;

        case Downloading:
            cout << "\033[1;33m" << "Downloading -> " << "\033[0m";
            break;

        case Queued:
            cout << "\033[1;34m" << "Queued -> " << "\033[0m";
            break;

        default:
            break;
        }

        cout << "[" << i++ << "] - " << key->get_Link() << endl;
    }
}

#else
void STydl::printProgress(bool firstRun)
{
    if (!firstRun)
        for (int i = 0; i < progress.size(); ++i)
        {
            cout << "\33[2K\r" << flush;
            cout << "\33[A" << flush;
        }

    int i = 0;
    for (auto [key, value] : progress)
    {
        enum status {Finished, Downloading, Queued};
        
        switch (value)
        {
        case Finished:
            cout << "\033[1;32m" << "Finished -> " << "\033[0m";
            break;

        case Downloading:
            cout << "\033[1;33m" << "Downloading -> " << "\033[0m";
            break;

        case Queued:
            cout << "\033[1;34m" << "Queued -> " << "\033[0m";
            break;

        default:
            break;
        }

        cout << "[" << i++ << "] - " << key->get_Link() << endl;
    }
}
#endif

void STydl::download_multithreading(int _threads_to_use)
{
    try
    {
        int numer_of_threads = _threads_to_use;

        // all pointer to YDLdata which are going to be downloaded
        queue<YDLdata *> YDLdata_queue;
        // queue of all available threads
        queue<boost::thread *> thread_queue;
        // thread YDLdata mapping
        map<boost::thread *, YDLdata *> thread_data_map;

        // push YDLdata to queue
        for (auto [key, value] : progress)
            YDLdata_queue.push(key);

        // create threads and add them to the queue
        for (int i = 0; i < numer_of_threads; ++i)
        {
            boost::thread *temp_thread = nullptr;
            thread_queue.push(temp_thread);
        }

        // used for "printProgress"
        bool first_run = true;

        while (!YDLdata_queue.empty() || (thread_queue.size() != numer_of_threads))
        {
            printProgress(first_run);
            first_run = false;

            if (!thread_queue.empty() && !YDLdata_queue.empty())
            {
                boost::thread *thread_to_use = thread_queue.front();
                thread_queue.pop();

                YDLdata *ydl_temp = YDLdata_queue.front();
                YDLdata_queue.pop();

                thread_to_use = new boost::thread(boost::bind(&YDLdata::download, ydl_temp));

                progress[ydl_temp] = 1;
                thread_data_map[thread_to_use] = ydl_temp;
            }
            else
            {
                bool free_thread = false;
                for (auto [key, value] : thread_data_map)
                {
                    if (key != nullptr)
                    {
                        if (key->try_join_for(boost::chrono::seconds(5)))
                        {
                            progress[value] = 0;

                            boost::thread *temp_thread = key;

                            // delete of thread not needed
                            temp_thread = nullptr;
                            thread_queue.push(temp_thread);
                            free_thread = true;
                        }
                    }
                }
            }
            printProgress(first_run);
        }
        printProgress(false);

        // clean thread queue
        while (!thread_queue.empty())
        {
            boost::thread *temp = thread_queue.front();
            thread_queue.pop();
            delete temp;
        }   
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

int STydl::get_all_downloads()
{
    return progress.size();
}
