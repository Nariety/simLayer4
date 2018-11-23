#include "student_common.h"

#define TIMER_INCREMENT 15

//TODO
struct pkt make_pkt(int seq, struct msg message, int checksum){
  struct pkt packet;
  packet.seqnum = seq;
  packet.acknum = 0;
  packet.checksum = checksum;
  for (int i = 0; i < MESSAGE_LENGTH; i ++){
    packet.payload[i] = message.data[i];
  }
}

/*
 * corrupted() checks whether the data contained in the message is corrupted
 */
int corrupted(struct pkt pakcet){
  return TRUE;
}

/*
 * isACK() checks whether the received packet is an ACK that matches the
 * current packet number
 */
int isACK(struct pkt packet, int currPktNum){
  return FALSE;
}

/*
 * getChecksum() returns checksum for the given packet
 */
int getChecksum(struct pkt packet){
  return 1;
}

/*
 * output() makes and sends a packet with the given message to
 */
struct pkt output(int AorB, struct msg message){
  struct pkt sndpkt = make_pkt(0,message,0); // todo
  tolayer3(AorB, sndpkt);
  currPktNum = !currPktNum; //todo check bit flip
  // udt_send(sndpkt);
  startTimer(AorB, TIMER_INCREMENT);
  return sndpkt;
}
void input(int AorB, struct pkt packet){
  if(!corrupted(packet) && isACK(packet)){
    stopTimer(AorB);
  }
}
void timerinterrupt(int AorB){
  tolayer3(AorB, currPkt);
  startTimer(AorB,TIMER_INCREMENT);
}
void init();
