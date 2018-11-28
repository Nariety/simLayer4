#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project2.h"

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

   Compile as gcc -g project2.c student2.c -o p2
**********************************************************************/
#define RTT         20
#define BUFFER_SIZE 50

#define RECEIVING   17
#define WAITING     18
/********************* State Variables ***********************/
static int pktcount = 0;
static int aStatus;
static int aSeq;
static int bSeq;
static struct pkt pktAsnd;
static struct msg msgAsndBuffer[BUFFER_SIZE];
static int bufferHead;
static int bufferBase;
static struct pkt pktBsnd;
static struct msg msg2snd;
static char *ackMsg = "ACK";

/***************** End of State Variables ********************/

/********* STUDENTS WRITE THE NEXT SEVEN ROUTINES *********/
/*
 * The routines you will write are detailed below. As noted above,
 * such procedures in real-life would be part of the operating system,
 * and would be called by other procedures in the operating system.
 * All these routines are in layer 4.
 */

/*
 *  Returns void.
 */
int flip(int a){return (a+1)%2;}

/*
 * getChecksum() uses CRC32 algorithm to calculate checksum for sequance number,
 * acknowledge number, and the payload itself. Returns an int.
 */
int getChecksum(char *payload, int seq, int ack){
  // add all information into one data string
  char data[MESSAGE_LENGTH+2];
  strncpy(data, payload,MESSAGE_LENGTH);
  data[MESSAGE_LENGTH] = (char)seq;
  data[MESSAGE_LENGTH+1] = (char)ack;

  // CRC32 implementation
  int i, j;
  unsigned int byte, crc, mask;
  i = 0;
  crc = 0xFFFFFFFF;
  while (data[i] != 0){
    byte = data[i];
    crc = crc ^ byte;
    for (j = 7; j > 0; j--){
      mask = -(crc & 1);
      crc = (crc >> 1) ^ (0xEDB88320 & mask);
    }
    i++;
  }
  return ~crc;
}

/*
 * make_pkt() fills the fields of the given packet with the given seqnum, acknum,
 * and payload, along with the calculated checksum. Returns void.
 */
void make_pkt(struct pkt *packet, int seq, int ack, char *payload){
  packet->seqnum = seq;
  packet->acknum = ack;
  for (int i = 0; i < MESSAGE_LENGTH; i++){
    packet->payload[i] = payload[i];
  }
  packet->checksum = 0;
  packet->checksum = getChecksum(packet->payload,seq,ack);
}

/*
 * make_msg() fills the data field of the given message with the given payload.
 * Returns void.
 */
void make_msg(struct msg *message, char *payload){
  for (int i = 0; i < MESSAGE_LENGTH; i++){
    message->data[i] = payload[i];
  }
}

 /*
  * corrupted() checks whether the data contained in the message is corrupted
  */
 int corruptedHuh(struct pkt *packet){
   int newChecksum = getChecksum(packet->payload, packet->seqnum, packet->acknum);
   if(newChecksum != packet->checksum){ // packet is corrupted!
     return TRUE;
   }
   else{
     return FALSE;
   }
 }

 /*
  * A_output(message), where message is a structure of type msg, containing
  * data to be sent to the B-side. This routine will be called whenever the
  * upper layer at the sending side (A) has a message to send. It is the job
  * of your protocol to insure that the data in such a message is delivered
  * in-order, and correctly, to the receiving side upper layer.
  */
 void A_output(struct msg message) {
   if(aStatus == WAITING){  // if there is a packet being sent
     msgAsndBuffer[bufferHead%BUFFER_SIZE] = message;
   }
   else{
     make_pkt(&pktAsnd, aSeq, aSeq, message.data);
     tolayer3(AEntity, pktAsnd);
     aStatus = WAITING;
     startTimer(AEntity, RTT);
   }
 }

 /*
  * Just like A_output, but residing on the B side.  USED only when the
  * implementation is bi-directional.
  */
 void B_output(struct msg message)  {

 }

 /*
  * A_input(packet), where packet is a structure of type pkt. This routine
  * will be called whenever a packet sent from the B-side (i.e., as a result
  * of a tolayer3() being done by a B-side procedure) arrives at the A-side.
  * packet is the (possibly corrupted) packet sent from the B-side.
  */
 void A_input(struct pkt packet) {
   if(!corruptedHuh(&packet) && packet.seqnum == aSeq && !strcmp(ackMsg,packet.payload)){
     stopTimer(AEntity);
     aStatus = RECEIVING;
     aSeq = flip(aSeq);
     if(bufferBase != bufferHead){
       bufferBase++;
       A_output(msgAsndBuffer[bufferBase%BUFFER_SIZE]);
     }
   }
 }

 /*
  * A_timerinterrupt()  This routine will be called when A's timer expires
  * (thus generating a timer interrupt). You'll probably want to use this
  * routine to control the retransmission of packets. See starttimer()
  * and stoptimer() in the writeup for how the timer is started and stopped.
  */
 void A_timerinterrupt() {
   stopTimer(AEntity);
   tolayer3(AEntity, pktAsnd);
   startTimer(AEntity, RTT);
 }

 /* The following routine will be called once (only) before any other    */
 /* entity A routines are called. You can use it to do any initialization */
 void A_init() {
   aStatus = RECEIVING;
   aSeq = 0;
   bufferHead = 0;
   bufferBase = 0;
 }


 /*
  * Note that with simplex transfer from A-to-B, there is no routine  B_output()
  */

 /*
  * B_input(packet),where packet is a structure of type pkt. This routine
  * will be called whenever a packet sent from the A-side (i.e., as a result
  * of a tolayer3() being done by a A-side procedure) arrives at the B-side.
  * packet is the (possibly corrupted) packet sent from the A-side.
  */
 void B_input(struct pkt packet){
   printf("\n");
   if(!corruptedHuh(&packet) && packet.seqnum == bSeq){ // correct package is received
     make_msg(&msg2snd, packet.payload);
     tolayer5(BEntity,msg2snd);
     make_pkt(&pktBsnd, bSeq, bSeq, ackMsg);
     tolayer3(BEntity,pktBsnd);
     bSeq = flip(bSeq);
   }
   else if(!corruptedHuh(&packet) && packet.seqnum != bSeq){ // duplicate message received
     tolayer3(BEntity,pktBsnd);
   }
 }

 /*
  * B_timerinterrupt()  This routine will be called when B's timer expires
  * (thus generating a timer interrupt). You'll probably want to use this
  * routine to control the retransmission of packets. See starttimer()
  * and stoptimer() in the writeup for how the timer is started and stopped.
  */
 void  B_timerinterrupt() {
 }

 /*
  * The following routine will be called once (only) before any other
  * entity B routines are called. You can use it to do any initialization
  */
 void B_init() {
   bSeq = 0;
 }
