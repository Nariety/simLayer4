#include "student_common.h"

/* ***************************************************************************
 ALTERNATING BIT AND GO-BACK-N NETWORK EMULATOR: VERSION 1.1  J.F.Kurose

   This code should be used for Project 2, unidirectional or bidirectional
   data transfer protocols from A to B and B to A.
   Network properties:
   - one way network delay averages five time units (longer if there
     are other messages in the channel for GBN), but can be larger
   - packets can be corrupted (either the header or the data portion)
     or lost, according to user-defined probabilities
   - packets may be delivered out of order.

   Compile as gcc -g project2.c student2A.c student2B.c -o p2
**********************************************************************/

/********************* State Variables ***********************/
static int currSeqNum;
static int nextSeqNum;
static int currAckNum;
/***************** End of State Variables ********************/

/*
 * isACK() checks whether the received packet is an ACK that matches the
 * current packet number
 */
// int B_isACK(struct pkt packet){
//   return isACK(packet, currSeqNum);;
// }

/*
 * Note that with simplex transfer from A-to-B, there is no routine  B_output()
 */

 /*
  * Just like A_output, but residing on the B side.  USED only when the
  * implementation is bi-directional.
  */
 void B_output(struct msg message)  {
   output(BEntity, message, currSeqNum, currAckNum);
   currSeqNum = (currSeqNum + 1) % 2;
 }

/*
 * B_input(packet),where packet is a structure of type pkt. This routine
 * will be called whenever a packet sent from the A-side (i.e., as a result
 * of a tolayer3() being done by a A-side procedure) arrives at the B-side.
 * packet is the (possibly corrupted) packet sent from the A-side.
 */
void B_input(struct pkt packet) {
  if(input(BEntity, packet, currSeqNum)){
    currSeqNum = (currSeqNum + 1) % 2;
    currAckNum = (currAckNum + 1) % 2;
  }
}

/*
 * B_timerinterrupt()  This routine will be called when B's timer expires
 * (thus generating a timer interrupt). You'll probably want to use this
 * routine to control the retransmission of packets. See starttimer()
 * and stoptimer() in the writeup for how the timer is started and stopped.
 */
void  B_timerinterrupt() {
  timerinterrupt(BEntity);
  currSeqNum = (currSeqNum + 1) % 2;
}

/*
 * The following routine will be called once (only) before any other
 * entity B routines are called. You can use it to do any initialization
 */
void B_init() {
  currSeqNum = 0;
  currAckNum = 0;
  common_init();
}
