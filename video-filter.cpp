#include "Jzon.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

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


std::string exec(const char* cmd)
{
    char buffer[128];
    FILE* pipe;
    std::string result = "";

    pipe = popen(cmd, "r");

    if (!pipe)
    {
        return "ERROR";
    }

    while(!feof(pipe))
    {
        if(fgets(buffer, 128, pipe) != NULL)
        {
            result += buffer;
        }
    }

    pclose(pipe);

    return result;
}


std::vector<std::string> &split(const std::string &s,
                                char delim,
                                std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }

    return elems;
}


std::vector<std::string> split(const std::string &s,
                               char delim)
{
    std::vector<std::string> elems;

    split(s, delim, elems);

    return elems;
}


void checkVideInfo(Jzon::Object params, float *duration, float *frames)
{
    const char *check_info_cmd;
    std::vector<std::string> info_result, times;
    std::string::size_type string_size_type;

    check_info_cmd = "python check_info.py";

    info_result = split(exec(check_info_cmd), ',');

    // set duration (in seconds)
    times = split(info_result[0], ':');
    *duration += std::stof(times[0], &string_size_type) * 3600; // hours
    *duration += std::stof(times[1], &string_size_type) * 60; // minutes
    *duration += std::stof(times[2], &string_size_type); // seconds

    // set frames
    *frames = std::stof(info_result[1], &string_size_type);
}


int main(int argc, char* argv[])
{
    Jzon::Object params;
    float duration = 0.0;
    float frames = 0.0;

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