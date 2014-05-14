import json
import multiprocessing
import sys
import subprocess
import os


CPUCoresCount = multiprocessing.cpu_count() # Get CPU Cores
numThreads = 1
paramFile = 'params.json' # filename for parameters
duration = ''
frames = ''

class myThread (threading.Thread):
    def __init__(self, threadID, name, counter):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.counter = counter
    def run(self):
        print self.name
        size = ( duration / numThreads )
        start = size * self.threadID
        end = ( size * self.threadID ) + size
        subprocess.call(
           ["ffmpeg",
           "-i", "./resources/drag_codekid.mov",
           "-r", frames, "-ss", start, "-t", end,
           "./resources/video-filter-%03d.jpeg"])

def checkParameters(params):
    if 'filename' not in params:
        print "Missing 'filename' parameter."
        sys.exit()
    elif 'filter' not in params:
        print "Missing 'filter' parameter."
        sys.exit()
    elif 'threads' not in params:
        print "Missing 'threads' list parameter."
        sys.exit()
    elif 'video' not in params["threads"]:
        print "Missing 'threads.video' parameter."
        sys.exit()
    elif 'images' not in params["threads"]:
        print "Missing 'threads.images' parameter."
        sys.exit()


def checkVideoInfo(params):
    global duration, frames

    # Save information into file
    file_info = open('file_info.txt', 'w');
    subprocess.call(
                    ['ffmpeg', '-i', params['filename']],
                    stderr=file_info)
    file_info.close()

    # Extract information from file
    file_info = open('file_info.txt', 'r');
    file_content = file_info.read()

    # Get duration of video file
    time_begin = file_content.index('Duration:')
    duration = file_content[time_begin + 10 : time_begin + 21]

    # Get FPS of video file
    frames_begin = file_content.index('fps')
    frames_line = file_content[frames_begin - 10 : frames_begin].split(' ')
    frames = frames_line[len(frames_line) - 2]

    # Close file and delete it
    file_info.close()
    os.remove('file_info.txt')

""" MAIN """

 # Read parameters from the JSON file
params = json.loads(open(paramFile).read())

# Check the parameters so the complete info is loaded
checkParameters(params)

# Grab the neccesary info from the video file
checkVideoInfo(params)

#call(
#    ["ffmpeg",
#    "-i", "./resources/drag_codekid.mov",
#    "-r", frames,
#    "./resources/video-filter-%03d.jpeg"])