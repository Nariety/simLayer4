#include <stdio.h>
#include <stdlib.h>
#include "project2.h"
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



/********* STUDENTS WRITE THE NEXT SEVEN ROUTINES *********/
/*
 * The routines you will write are detailed below. As noted above,
 * such procedures in real-life would be part of the operating system,
 * and would be called by other procedures in the operating system.
 * All these routines are in layer 4.
 */

/********************* State Variables ***********************/
struct pkt currPkt;
/***************** End of State Variables ********************/

//TODO
struct pkt make_pkt(int seq, struct msg message, int checksum){
  struct pkt packet;
  packet.seqnum = seq;
  packet.acknum = 0;
  packet.checksum = checksum;
  for (int i = 0; i < MESSAGE_LENGTH; i ++){
    packet.payload[i] = message.data[i];
  }
  currPkt = packet;
}

/*
 * corrupted() checks whether the data contained in the message is corrupted
 */
boolean corrupted(struct msg message){
  return true;
}

/*
 * A_output(message), where message is a structure of type msg, containing
 * data to be sent to the B-side. This routine will be called whenever the
 * upper layer at the sending side (A) has a message to send. It is the job
 * of your protocol to insure that the data in such a message is delivered
 * in-order, and correctly, to the receiving side upper layer.
 */
void A_output(struct msg message) {
  sndpkt = make_pkt(); // todo
  tolayer3(AENTITY, sndpkt);
  // udt_send(sndpkt);
  startTimer();
}


/*
 * A_input(packet), where packet is a structure of type pkt. This routine
 * will be called whenever a packet sent from the B-side (i.e., as a result
 * of a tolayer3() being done by a B-side procedure) arrives at the A-side.
 * packet is the (possibly corrupted) packet sent from the B-side.
 */
void A_input(struct pkt packet) {

}

/*
 * A_timerinterrupt()  This routine will be called when A's timer expires
 * (thus generating a timer interrupt). You'll probably want to use this
 * routine to control the retransmission of packets. See starttimer()
 * and stoptimer() in the writeup for how the timer is started and stopped.
 */
void A_timerinterrupt() {
  tolayer3(AENTITY, currPkt);
}

/* The following routine will be called once (only) before any other    */
/* entity A routines are called. You can use it to do any initialization */
void A_init() {
}
