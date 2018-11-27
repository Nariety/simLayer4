#include "project2.h"

/*
 * This file contains function prototypes of common functions in student2A and
 * student2B
 */

 /*
  * Common function prototypes for both sender and receiver
  */

void make_pkt(struct pkt *packet, int seq,int ack, char *payload);
int corrupted(struct pkt packet);
int isACK(struct pkt packet, int currSeqNum);
int checkChecksum(struct pkt packet);
int genChecksum(struct msg message, int seq, int ack);

void output(int AorB, struct msg message, int seq, int ack);
void input(int AorB, struct pkt packet, int currSeqNum);
void timerinterrupt(int AorB, struct pkt currPkt);
void init();
