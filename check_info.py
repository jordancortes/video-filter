import sys
import os
import json
import subprocess

paramFile = 'params.json' # filename for parameters
params = json.loads(open(paramFile).read())

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

print str(duration) + "," + str(frames)