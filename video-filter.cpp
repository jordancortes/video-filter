#include <stdio.h>
#include <stdlib.h>
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

int main( int argc, char* argv[] )
{
    if ( 1 == argc )
    {
        printf( "Missing video source.\n" );
        printf( "Usage: %s [ parameters ] <VIDEO_NAME>\n", argv[0] );
    }
    else if ( 7 <= argc )
    {
        printf( "Too much arguments!\n" );
    }
    else if ( 2 == argc )
    {
        // the last parameter is the video path
        extract_images( argv[argc - 1] );
    }
    else
    {
        bool parameters_correct = true;
        std::string actual_parameter;
        int param = 1;

        // check for paratemers
        while ( parameters_correct &&
               param < argc - 1 )
        {
            actual_parameter = std::string( argv[param] );

            if ( 0 == actual_parameter.compare( "--filter" ) )
            {
                /* code */
            }
            else if ( 0 == actual_parameter.compare( "--video-threads" ) )
            {
                /* code */
            }
            else
            {
                parameters_correct = false;
            }

            param += 2;
        }

        if ( !parameters_correct )
        {
            printf( "Argument %s is invalid!\n", actual_parameter.c_str() );
            return 1;
        }

        // the last parameter is the video path
        extract_images( argv[argc - 1] );
    }

    return 0;
}