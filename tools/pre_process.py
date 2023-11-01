
import subprocess
from sys import argv
from glob import glob

# parse arguments and concartinate normalized absolute path to hex file
proj_root_dir = argv[1]
astyle_exe_path = argv[2]

verbose = False
if len(argv) > 3:
    if (argv[3] == '--verbose') | (argv[3] == '-v'):
        verbose = True
   

pattern = ['source/**/*.c', "source/**/*.h"]
rel_paths = []

for item in pattern:
    rel_paths += glob(item, root_dir=proj_root_dir, recursive=True)

for item in rel_paths:
    proc = subprocess.run(args=[astyle_exe_path, '--style=allman', '-q', '-n', item], cwd=proj_root_dir)
    
if verbose:
    print("Formatting List: \n", rel_paths)