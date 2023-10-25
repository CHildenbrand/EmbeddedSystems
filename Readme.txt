This example illustrates the prebuild and postbuild step.

Prebuild includes:
 # Astyling *.c and *.h files from \source folder
 # Doxygen generates documentation of symbols based on comments

Postbuild includes: 
 # Crc-32 calculation and injection over application footprint

Software Feature: Runtime Crc Calculation
 # Usage of CRC Perpheral
 # Usage of DMA Copy from Flash to Peripheral memory
 # Integrity Check
 # Blinky if crc matches, lights on constant else
