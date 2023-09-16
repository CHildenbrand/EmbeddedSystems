# post processing hex file by padding, aligning and inserting crc-32 at last 4 bytes

# set PATH=%PATH%;C:\Users\AsusV\AppData\Local\Programs\Python\Python311\Scripts
# py -m pip install --upgrade pip

import subprocess
from sys import argv
from glob import glob

print("Preprocessing files...")

# parse arguments and concartinate normalized absolute path to hex file
proj_root_dir = argv[1]
astyle_exe_path = argv[2]

pattern = ['source/**/*.c', "source/**/*.h"]
rel_paths = []

for item in pattern:
    rel_paths += glob(item, root_dir=proj_root_dir, recursive=True)

for item in rel_paths:
    proc = subprocess.run(args=[astyle_exe_path, '--style=allman', '-q', '-n', item], cwd=proj_root_dir)