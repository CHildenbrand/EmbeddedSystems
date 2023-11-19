# post processing hex file by padding, aligning and inserting crc-32 at last 4 bytes

# set PATH=%PATH%;C:\Users\AsusV\AppData\Local\Programs\Python\Python311\Scripts
# py -m pip install --upgrade pip
# pip install crcmod

import os
from sys import argv
import crcmod
from intelhex import IntelHex
from datetime import datetime
from uuid import getnode
from hashlib import sha256

# parse arguments and concartinate normalized absolute path to hex file
proj_loc_rel_path = argv[1]
hex_file_rel_path = argv[2]

verbose = 0
if len(argv) > 3:
    if (argv[3] == '-v') | (argv[3] == '--verbose'):
        verbose = 1
        
hex_file_in_abs_path = os.path.join(proj_loc_rel_path, hex_file_rel_path).replace("/","\\")

currentTime = datetime.today().strftime('%Y-%m-%d %H:%M:%S')

hash = sha256()
currentMAC = str(getnode())
hash.update(currentMAC.encode())
hashValue = hash.digest()

# Read the Hex file
hex_file = IntelHex()
hex_file.loadhex(hex_file_in_abs_path)
hex_file.padding = 0

crc_start, crc_end = hex_file._get_start_end()

hex_file_crc_addr = crc_end - 3
hex_file_time_addr = crc_end - 32

for i in range(len(currentTime)):
    hex_file[hex_file_time_addr] = ord(currentTime[i])
    hex_file_time_addr+=1

hex_file_hash_addr = hex_file_time_addr


for i in range(hex_file_crc_addr - hex_file_hash_addr):
    hex_file[hex_file_hash_addr] = hashValue[i]
    hex_file_hash_addr +=1

crc_range = hex_file_crc_addr-crc_start

# set the algorithm to be used for crc calculation
crc32 = crcmod.predefined.Crc('crc-32')

# calculate the crc over application hex footprint
crc32.update(hex_file.tobinstr(start=crc_start, size=crc_range))


crc_hex = int(crc32.crcValue)

if verbose:
    print("Crc-32 Value: " + str(hex(crc32.crcValue)))
    print("Crc-32 Address: " + str(hex(hex_file_crc_addr)))

hex_file[hex_file_crc_addr] = crc_hex & 0xFF
hex_file[hex_file_crc_addr+1] = (crc_hex >> 8) & 0xFF
hex_file[hex_file_crc_addr+2] = (crc_hex >> 16) & 0xFF
hex_file[hex_file_crc_addr+3] = (crc_hex >> 24) & 0xFF

hex_file.write_hex_file(hex_file_in_abs_path)
