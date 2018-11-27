#include "project2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 * This file contains function prototypes of common functions in student2A and
 * student2B
 */

 /*
  * Common function prototypes for both sender and receiver
  */

void make_pkt(struct pkt *packet, int seq,int ack, char *payload);
int corruptedHuh(struct pkt packet);
int isACK(struct pkt packet, int currSeqNum);
int getChecksum(struct msg message, int seq, int ack);

void output(int AorB, struct msg message, int seq, int ack);
void input(int AorB, struct pkt packet, int currSeqNum);
void timerinterrupt(int AorB);
void init();
