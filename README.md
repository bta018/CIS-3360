# Checksum Calculator 
This C program reads a text file, then calculates a checksum from its contents based on a specified bit size (8, 16, or 32 bits), and outputs the checksum. It supports padding the data when needed to ensure it's a multiple of 16 or 32 bits.

## Features

- Reads the content of a text file.
- Pads the content if required to meet a specific bit size.
- Calculates the checksum using one of three methods:
  - **8-bit checksum**
  - **16-bit checksum**
  - **32-bit checksum**
- Displays the contents of the file and the computed checksum.