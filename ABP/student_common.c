#include <string.h>
#include <stdlib.h>
#include "student_common.h"

#define RTT 10

static struct pkt pkt2snd;
static struct pkt pkt2rcv;

void make_pkt(struct pkt *packet, int seq, int ack, char *payload){
  // int length = strlen(payload);

  packet->seqnum = seq;
  packet->acknum = ack;
  packet->checksum = getChecksum(payload,seq,ack);

  for (int i = 0; i < MESSAGE_LENGTH; i++){
    packet->payload[i] = payload[i];
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
  int newChecksum = getChecksum(packet.payload, packet.seqnum, packet.acknum);
  if(newChecksum != packet.checksum){
    return FALSE;
  }
  else{
    return TRUE;
  }
}

int getChecksum(struct msg message, int seq, int ack){
  unsigned char *data = malloc(sizeof(char)*strlen(message.data) + sizeof(int) * 2);
  data[0] = (unsigned char)seq;
  data[1] = (unsigned char)ack;
  strcat(data, message.data);
  // char *data = message.data;
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
 * output() makes and sends a packet with the given message to
 */
void output(int AorB, struct msg message, int seq, int ack){
  make_pkt(&pkt2snd, (seq+1)%2, seq, message.data)
  tolayer3(AorB, pkt2snd);
  // udt_send(sndpkt);
  startTimer(AorB, RTT);
}

void input(int AorB, struct pkt packet,int currSeqNum){
  if(!corrupted(packet) && isACK(packet,currSeqNum)){
    stopTimer(AorB);
  }
}

void timerinterrupt(int AorB, struct pkt currPkt){
  if(getTimerStatus(AorB)){
    tolayer3(AorB, currPkt);
    startTimer(AorB, RTT);
  }

}

void init();
