#include "Jzon.h"
#include <string>
#include <iostream>

#define SUCCESS 0
#define ERROR   1
#define THREADS 1

int checkParameters(Jzon::Object params)
{
    // Search for parameter 'filename'
    try
    {
        params.Get("filename").ToString();
    }
    catch (Jzon::NotFoundException e)
    {
        std::cout << "Parameter 'filename' missing." << std::endl;
        return ERROR;
    }

    // Search for parameter 'filter'
    try
    {
        params.Get("filter").ToString();
    }
    catch (Jzon::NotFoundException e)
    {
        std::cout << "Parameter 'filter' missing." << std::endl;
        return ERROR;
    }

    // Search for parameter 'thread-video'
    try
    {
        params.Get("threads").Get("video").ToString();
    }
    catch (Jzon::NotFoundException e)
    {
        std::cout << "Parameter 'threads-video' missing." << std::endl;
        return ERROR;
    }

    // Search for parameter 'thread-images'
    try
    {
        params.Get("threads").Get("images").ToString();
    }
    catch (Jzon::NotFoundException e)
    {
        std::cout << "Parameter 'threads-images' missing." << std::endl;
        return ERROR;
    }

    return SUCCESS;
}

std::string exec(const char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    return result;
}

void checkVideInfo(Jzon::Object params, float *duration, float *frames)
{
    const char *command = "python check_info.py";

    std::cout << exec(command) << std::endl;
}

int main(int argc, char* argv[])
{
    Jzon::Object params;
    float duration, frames;

    // Read parameters from the JSON file
    Jzon::FileReader::ReadFile("params.json", params);

    // Check the parameters so the complete info is loaded
    if (ERROR == checkParameters(params))
    {
        return ERROR;
    }

    // Grab the neccesary info from the video file
    checkVideInfo(params, &duration, &frames);

    return SUCCESS;
}