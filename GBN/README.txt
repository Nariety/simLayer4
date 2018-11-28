CS3516 Computer Networks Project 2

Submitted by Hannan Liang (hliang2@wpi.edu)

****This is the instructions for GBN****

Note: This program is written for Linux/MacOS Machines. If you would like to run
it on Windows, please change the setting in project2.h.

How to run:
1. first type in terminal

    make

2. then run the following code

    ./GBN_hliang2

To clean the complied files, type in terminal

    make clean

*******************************************************************************
Please see ExampleOutputTraces_x_hliang2.pdf (where x is a number from 1 to 3)
for more examples.

Note: it happens really rarely, but the program sometimes freeze in the first
few traces print statements in the beginning. I suspect it is either caused by
the timer value preset in the program or the CRC checksum algorithm used in the
program. In the rare case that it does happen, please wait for 2 seconds and
rerun the program. Because it rarely happens it is quite hard to debug. Thus I'm
submitting the project as it is.
