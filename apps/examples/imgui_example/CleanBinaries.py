import os
from os import listdir
from os.path import isfile, join
import re

cwd = os.getcwd()
artifactsDir = cwd + "/build/Debug/"
print("Cleaning: " + artifactsDir)

files = [f for f in listdir(artifactsDir) if isfile(join(artifactsDir, f))]

for (file) in files:
	pattern = '\S*\.\d{4}\.dll'
	result = re.match(pattern, file)

	if result:
		print("Deleting: " + file)
		if os.path.exists(artifactsDir + file): 
			os.remove(artifactsDir + file)
