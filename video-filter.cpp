#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string>

std::string _code;
std::string _filter;
int _num_threads;

/**
 Convert video file to a sequence of JPEG images (30fps)

 @param video_path
   Path to the video file.
 */
void extract_images( char *video_path )
{
    // make command code
    _code = std::string( "ffmpeg -i " ) +
            video_path +
            std::string( " -qscale 1 -qcomp 0 -qblur 0 -r 30 " ) +
            std::string( "video-filter-\%03d.jpeg" );

    // run code
    system( _code.c_str() );
}

int checkParamters( int argc, char* argv[] )
{
    bool parameters_correct = true;
    std::string actual_parameter;
    int param = 1;

    // check for paratemers while these are correct
    while ( parameters_correct &&
           param < argc - 1 )
    {
        // parse parameter at index param
        actual_parameter = std::string( argv[param] );

        // convert parameter to lower case for comparison
        std::transform( actual_parameter.begin(),
                        actual_parameter.end(),
                        actual_parameter.begin(),
                        ::tolower);

        // if parameter is for filter
        if ( 0 == actual_parameter.compare( "--filter" ) )
        {
            /* code */
        }
        // if parameter is for video-threads
        else if ( 0 == actual_parameter.compare( "--video-threads" ) )
        {
            /* code */
        }
        // if parameter is unavailable
        else
        {
            parameters_correct = false;
        }

        // jump to next parameter
        param += 2;
    }

    // if some parameter were wrong
    if ( !parameters_correct )
    {
        printf( "Argument %s is invalid!\n", actual_parameter.c_str() );
        return 1;
    }

    return 0;
}

int main( int argc, char* argv[] )
{
    // if no arguments were given
    if ( 1 == argc )
    {
        printf( "Missing video source.\n" );
        printf( "Usage: %s [ parameters ] <VIDEO_NAME>\n", argv[0] );
    }
    // if too much arguments were given
    else if ( 7 <= argc )
    {
        printf( "Too much arguments!\n" );
    }
    // if just the video path was given as parameter
    else if ( 2 == argc )
    {
        // the last parameter is the video path
        extract_images( argv[argc - 1] );
    }
    // if one or more extra parameters were given
    else
    {
        if ( 1 == checkParamters( argc, argv ) )
        {
            return 1;
        }

        // the last parameter is the video path
        extract_images( argv[argc - 1] );
    }

    return 0;
}