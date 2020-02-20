#!/usr/bin/env python3
# Read in the file
with open('autoconf.h', 'r') as file :
  filedata = file.read()

# Replace the target string
filedata = filedata.replace('"', '')

# Write the file out again
with open('autoconf.h', 'w') as file:
  file.write(filedata)   

print('remove strings from autoconf.h')