/*
 * This file contains function prototypes of common functions in student2A and
 * student2B
 */

 /*
  * Common function prototypes for both sender and receiver
  */

struct pkt make_pkt(int seq, struct msg message, int checksum);
int corrupted(struct pkt packet);
int isACK(struct pkt packet, int currSeqNum);
int checkChecksum(struct pkt packet);
int genChecksum(char *data, int seq, int ack);

struct pkt output(int AorB, struct msg message);
void input(int AorB, struct pkt packet, int currSeqNum);
void timerinterrupt(int AorB, struct pkt currPkt);
void init();
