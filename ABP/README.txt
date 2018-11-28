CS3516 Computer Networks Project 2

Submitted by Hannan Liang (hliang2@wpi.edu)

****This is the instructions for ABP****

Note: This program is written for Linux/MacOS Machines. If you would like to run
it on Windows, please change the setting in project2.h.

How to run:
1. first type in terminal

    make

2. then run the following code

    ./ABP_hliang2

To clean the complied files, type in terminal

    make clean

*******************************************************************************
Please see ExampleOutputTraces_x_hliang2.pdf (where x is a number from 1 to 3)
for more examples.

Note: sometimes the program outputs warning "TOLAYER5:  PANIC!!  Data Received
in this packet are wrong". However, the message sent from layer5 on A-side is
identical to the message sent to layer 5 on B-side. The cause is unknown at this
moment but because the messages on both layer5's are the same, the ABP is still
functional.
