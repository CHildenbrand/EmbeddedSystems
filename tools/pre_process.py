
import subprocess
from sys import argv
from glob import glob

# parse arguments and concartinate normalized absolute path to hex file
proj_root_dir = argv[1]
astyle_exe_path = argv[2]
astyle_cfg = argv[3]

verbose = False
if len(argv) > 4:
    if (argv[4] == '--verbose') | (argv[4] == '-v'):
        verbose = True

pattern = ['source/**/*.c', "source/**/*.h"]
rel_paths = []

for item in pattern:
    rel_paths += glob(item, root_dir=proj_root_dir, recursive=True)

rel_paths.sort()

optionFile = '--options='
optionFile += astyle_cfg

for item in rel_paths:
    proc = subprocess.run(args=[astyle_exe_path, optionFile, item], cwd=proj_root_dir)
    
if verbose:
    print("Formatting List:")
    for item in rel_paths:
        print(item)