#include "Jzon.h"
#include "filters.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#define SUCCESS 0
#define ERROR   1
#define THREADS 1
#define MT_BEGIN 0
#define MT_END  1
#define SEPIA   0
#define BN      1

int main_thread_status = MT_BEGIN;
pthread_mutex_t mutex_frame;
int actual_frame = 1;
int filter_type;

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


void checkVideInfo(Jzon::Object params,
                   float *duration,
                   float *frames,
                   std::string *filetype,
                   std::string *image_sufix)
{
    const char *check_info_cmd;
    std::vector<std::string> info_result, file_result, times;
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

    // set filetype
    file_result = split(params.Get("filename").ToString(), '.');
    *filetype = file_result[file_result.size() - 1];

    // set image prefix
    *image_sufix = params.Get("images").Get("sufix").ToString();
}


void extractFrames(std::string filename, float frames, std::string image_sufix)
{
    std::string extract_frames_cmd;
    std::stringstream ss_frames;

    // Convert float to string
    ss_frames << frames;

    // Build code
    extract_frames_cmd = "ffmpeg -i " + filename +
                         " -r " + ss_frames.str() +
                         " ./resources/%03d." + image_sufix;

    exec(extract_frames_cmd.c_str());
}


void compileVideo(std::string filename, float frames, std::string image_sufix)
{
    std::string extract_frames_cmd;
    std::stringstream ss_frames;

    // Convert float to string
    ss_frames << frames;

    // Build code
    extract_frames_cmd = "ffmpeg -f image2 -r " + ss_frames.str() +
                         " -i \"./resources/%03d." + image_sufix + "\" " +
                         filename;

    exec(extract_frames_cmd.c_str());
}

void *applyFilter(void *threadID)
{
    long tID;
    double this_frame;
    tID = (long)threadID;

    while(main_thread_status != MT_END)
    {
        // Lock a mutex prior to updating the value
        pthread_mutex_lock (&mutex_frame);
        this_frame = actual_frame++;
        pthread_mutex_unlock (&mutex_frame);

        printf("%lf\n", this_frame);
    }

    pthread_exit(NULL);
}


int main(int argc, char* argv[])
{
    Jzon::Object params;
    float duration = 0.0;
    float frames = 0.0;
    std::string filetype = "";
    std::string image_sufix = "";
    pthread_t threads[THREADS];
    pthread_attr_t attr;
    int thread_result;
    void *status;

    // Read parameters from the JSON file
    Jzon::FileReader::ReadFile("params.json", params);

    // Check the parameters so the complete info is loaded
    if (ERROR == checkParameters(params))
    {
        return ERROR;
    }

    // Grab the neccesary info from the video file
    checkVideInfo(params,
                  &duration,
                  &frames,
                  &filetype,
                  &image_sufix);

    pthread_mutex_init(&mutex_frame, NULL);

    // Initialize and set thread detached attribute
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // With p_threads calls the filter method for each image
    for (int i = 0; i < THREADS; i++)
    {
        thread_result = pthread_create(&threads[i],
                                       &attr,
                                       applyFilter,
                                       NULL);
    }

    // Get frames of video
    extractFrames(params.Get("filename").ToString(), frames, image_sufix);

    // Set the end of the frames
    main_thread_status = MT_END;

    /* Free attribute and wait for the other threads */
    pthread_attr_destroy(&attr);
    for (int i = 0; i < THREADS; i++)
    {
        thread_result = pthread_join(threads[i], &status);
    }

    // Recompile the video
    compileVideo("./resources/output." + filetype, frames, image_sufix);

    /* Last thing that main() should do */
    pthread_mutex_destroy(&mutex_frame);
    pthread_exit(NULL);
}