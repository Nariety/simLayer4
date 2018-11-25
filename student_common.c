#include "student_common.h"

#define RTT 10

//TODO
struct pkt make_pkt(int seq, struct msg message, int checksum){
  struct pkt packet;
  packet.seqnum = seq;
  packet.acknum = 0;
  packet.checksum = checksum;
  // maybe the TODO's below are not necessary
  //TODO prepend 0's to message if the message is shorter than message MESSAGE_LENGTH
  //TODO ? what char size in c? 8bytes?
  for (int i = 0; i < MESSAGE_LENGTH; i ++){
    packet.payload[i] = message.data[i];
  }
}

/*
 * corrupted() checks whether the data contained in the message is corrupted
 */
int corrupted(struct pkt pakcet){
  return TRUE; //TODO
}

/*
 * isACK() checks whether the received packet is an ACK that matches the
 * current packet number
 */
int isACK(struct pkt packet, int currSeqNum){
  return FALSE; //TODO
}

/*
 * getChecksum() returns true if checksum checks up in the given packet; false otherwise
 */
int checkChecksum(struct pkt packet){
  return 1; //TODO
}

int genChecksum(struct msg message, int seq, int ack){
  return 1; //TODO
}

/*
 * output() makes and sends a packet with the given message to
 */
struct pkt output(int AorB, struct msg message){
  int seq = 0; //TODO
  int ack = 0; //TODO
  int checksum = genChecksum(message,seq,ack);
  struct pkt sndpkt;
  sndpkt = make_pkt(seq,message,ack); // todo
  tolayer3(AorB, sndpkt);
  // udt_send(sndpkt);
  startTimer(AorB, RTT);
  return sndpkt;
}

void input(int AorB, struct pkt packet,int currSeqNum){
  if(!corrupted(packet) && isACK(packet,currSeqNum)){
    stopTimer(AorB);
  }
}

void timerinterrupt(int AorB, struct pkt currPkt){
  if(getTimerStatus(AorB)){
    stopTimer(AorB);
    tolayer3(AorB, currPkt);
    startTimer(AorB, RTT);
  }

}

void init();
