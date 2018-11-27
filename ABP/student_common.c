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
int corruptedHuh(struct pkt *pakcet){
  int newChecksum = getChecksum(packet->payload, packet->seqnum, packet->acknum);
  if(newChecksum != packet->checksum){
    return TRUE;
  }
  else{
    return FALSE;
  }
}

/*
 * isACK() checks whether the received packet is an ACK that matches the
 * current packet number
 */
int isACK(struct pkt packet, int currSeqNum){
  return FALSE; //TODO
}

int getChecksum(char *payload, int seq, int ack){
  unsigned char *data = malloc(sizeof(char)*strlen(payload) + sizeof(int) * 2);
  data[0] = (unsigned char)seq;
  data[1] = (unsigned char)ack;
  strcat(data, payload);
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
  printf("original data: seq%d ack%d ",seq,ack);
  for (i=0; i<MESSAGE_LENGTH; i++)
      printf("%c", message.data[i] );
  printf("checksum: %d\n", ~crc);

  return ~crc;
}

/*
 * output() makes and sends a packet with the given message to
 */
void output(int AorB, struct msg message, int seq, int ack){
  make_pkt(&pkt2snd, (seq+1)%2, seq, message.data);
  tolayer3(AorB, pkt2snd);
  // udt_send(sndpkt);
  startTimer(AorB, RTT);
}

void input(int AorB, struct pkt packet,int currSeqNum){
  int i;
  char payload2snd[MESSAGE_LENGTH];
  if(!corruptedHuh(&packet)){
    if(packet.acknum == currSeqNum){

    }
  }

  // if(!corruptedHuh(&packet) && isACK(packet,currSeqNum)){
  //   stopTimer(AorB);
  // }
}

void timerinterrupt(int AorB){
  if(getTimerStatus(AorB)){
    tolayer3(AorB, pkt2snd);
    startTimer(AorB, RTT);
  }
}

void init();
