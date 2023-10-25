# post processing hex file by padding, aligning and inserting crc-32 at last 4 bytes

# set PATH=%PATH%;C:\Users\AsusV\AppData\Local\Programs\Python\Python311\Scripts
# py -m pip install --upgrade pip
# pip install crcmod

import os
from sys import argv
import crcmod
from intelhex import IntelHex

print("Postprocessing files... ")

# parse arguments and concartinate normalized absolute path to hex file
proj_loc_rel_path = argv[1]
hex_file_rel_path = argv[2]
padding = int(argv[3],16)
   
hex_file_in_abs_path = os.path.join(proj_loc_rel_path, hex_file_rel_path).replace("/","\\")

# Read the Hex file
hex_file = IntelHex()
hex_file.loadhex(hex_file_in_abs_path)
crc_start, crc_end = hex_file._get_start_end()

if len(argv) > 4:
    hex_file_crc_addr = int(argv[4], base=16)
else:
    hex_file_crc_addr = crc_end-3

# Padding required
if crc_end+1 < hex_file_crc_addr:
    for byte_idx in range(crc_end+1, hex_file_crc_addr):
        hex_file[byte_idx] = padding
        
crc_range = hex_file_crc_addr-crc_start

# set the algorithm to be used for crc calculation
crc32 = crcmod.predefined.Crc('crc-32')

# calculate the crc over application hex footprint
crc32.update(hex_file.tobinstr(start=crc_start, size=crc_range))

print("Application crc-32: " + str(hex(crc32.crcValue)))

crc_hex = int(crc32.crcValue)

print("CRC address: " + str(hex(hex_file_crc_addr)))

hex_file[hex_file_crc_addr] = crc_hex & 0xFF
hex_file[hex_file_crc_addr+1] = (crc_hex >> 8) & 0xFF
hex_file[hex_file_crc_addr+2] = (crc_hex >> 16) & 0xFF
hex_file[hex_file_crc_addr+3] = (crc_hex >> 24) & 0xFF

hex_file.write_hex_file(hex_file_in_abs_path)
