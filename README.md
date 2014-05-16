# Video Filter
Final project for the class Concurrent & Parallel Programming. The goal is to get from a video a sequence of images, which the system will apply a certain filter using threads to accelerate the process. Finally, these images will be converted to the video, with the filter already applied.

## Preinstallation
1. The program uses [ffmpeg](http://www.ffmpeg.org/download.html). On their site are the instructions to install it depending of the OS.
2. For compilation we used [Intel® C++ Composer XE 2013](https://software.intel.com/en-us/intel-composer-xe/). You can download the 30 day trial.

## Filters available
| Name          | Code |Preview |
|:-------------:|:----:|:------:|
| Original      | -    | ![Original Photo](http://cl.ly/image/0z2y243O273W/test_original.png) |
| Sepia         | 0    | ![Sepia Photo](http://cl.ly/image/3B36190H192E/test_sepia.png) |
| Black / White | 1    | ![Black & White Photo](http://cl.ly/image/3u2h3Y0Q1B2j/test_bw.png) |
| Inverted      | 2    | N/A |

## How to use

**1. Set parameters**

* *filename* : Sets path (absolute or relative to the project) where the source video is located.
* *images-sufix* : Sets the sufix for the images (for a perfect conversion, images must be PNG).
* *filter* : Sets the filter type according to the table above.
* *threads-video* : (Pending) Sets the threads used to decompressed the video.
* *threads-images* : Sets the threads used to apply the filter on the PNGs.

**2. Run the MAKE to compile**

    make

**3. After the compilation finish, run the program**

    ./video-filter

**4. The software requires the next structure of folders to work**

    --- video-filter
        |
        |--- resources
             |
             |--- tmp

    video-filter : main folder.
    resources : folder where output video will be stored.
    tmp : folder where temp images will be stored.

## Third Party Software
* [LodePNG](http://lodev.org/lodepng/) for decoding the PNGs.
* [JZON](https://code.google.com/p/jzon/) to parse JSON files.
* [ffmpeg](http://www.ffmpeg.org/download.html) to extract the frames from the video and to recompile the video.
* [Intel® C++ Composer XE 2013](https://software.intel.com/en-us/intel-composer-xe/) to vectorize most of the loops.

## License
Video Filter is provided under the [MIT License](LICENSE.md).