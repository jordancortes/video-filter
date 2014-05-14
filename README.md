# Video Filter
Final project for the class Concurrent & Parallel Programming. The goal is to get
from a video a sequence of images, which the system will apply a certain filter
using threads to accelerate the process. Finally, these images will be converted
to the video, with the filter already applied.

## Installation
1. Install Brew:

        ruby -e "$(curl -fsSL https://raw.github.com/Homebrew/homebrew/go/install)"

2. Install ffmpeg:

    The shorter way is with `brew install ffmpeg` or with all the attributes:

        brew install ffmpeg --with-fdk-aac --with-ffplay --with-freetype --with-frei0r --with-libass --with-libvo-aacenc --with-libvorbis --with-libvpx --with-opencore-amr --with-openjpeg --with-opus --with-rtmpdump --with-schroedinger --with-speex --with-theora --with-tools

## Filters available
| Name  | Preview |
| ----- | ------- |
| Sepia | a       |

## How to use

1. Run the MAKE to compile:

        make

2. To run the program:

        ./video-filter

## Third Party Software
* [JZON](https://code.google.com/p/jzon/) to parse JSON files.

## License
Video Filter is provided under the [MIT License](LICENSE.md).