#include "student_common.h"

#define RTT         10
#define BUFFER_SIZE 10

static struct pkt pkt2snd;
static struct pkt pkt2rcv;
static struct msg msg2snd;
static struct msg msg2rcv;
static char *ack = "ACK";

void make_pkt(struct pkt *packet, int seq, int ack, char *payload){
  // int length = strlen(payload);
  packet->seqnum = seq;
  packet->acknum = ack;
  // printf("geting checksum for new packet\n");
  packet->checksum = getChecksum(payload,seq,ack);

  for (int i = 0; i < MESSAGE_LENGTH; i++){
    packet->payload[i] = payload[i];
  }
}

void make_msg(struct msg *message, char *payload){
  for (int i = 0; i < MESSAGE_LENGTH; i++){
    message->data[i] = payload[i];
  }
}

/*
 * corrupted() checks whether the data contained in the message is corrupted
 */
int corruptedHuh(struct pkt *packet){
  // printf("checking the checksum\n");
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
// int isACK(struct pkt packet, int currSeqNum){
//   return FALSE; //TODO
// }

int getChecksum(char *payload, int seq, int ack){
  char data[MESSAGE_LENGTH+2];
  memcpy(data, payload, MESSAGE_LENGTH);
  data[MESSAGE_LENGTH] = ( char)seq;
  data[MESSAGE_LENGTH+1] = ( char)ack;

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
  // printf("original data: seq%d ack%d ",seq,ack);
  // for (i=0; i<MESSAGE_LENGTH; i++)
  //     printf("%c", payload[i] );
  // printf("\ndata stored in data: seq%d ack%d",data[20],data[21]);
  // for (i=2; i<MESSAGE_LENGTH+2; i++)
  //     printf("%c", data[i] );
  // printf("checksum: %d\n\n", ~crc);
  return ~crc;
}

/*
 * output() makes and sends a packet with the given message to
 */
void output(int AorB, struct msg message, int seq, int ack){
  // printf("******");
  make_pkt(&pkt2snd, (seq+1)%2, seq, message.data);
  tolayer3(AorB, pkt2snd);
  startTimer(AorB, RTT);
}

/*
 * input()
 */
void input(int AorB, struct pkt packet,int currSeqNum){
  // int i;
  if(!corruptedHuh(&packet) && packet.seqnum == currSeqNum){
    if(AorB == BEntity){
      make_msg(&msg2snd, packet.payload);
      tolayer5(BEntity,msg2snd);
      make_pkt(&pkt2snd, currSeqNum, currAckNum, "ACK");
      tolayer3(AEntity,pkt2snd);
    }
    else{

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

void common_init(){
  int i = 0;

  pkt2snd.seqnum = 0;
  pkt2snd.acknum = 0;
  pkt2snd.checksum = 0;
  for (i = 0; i < MESSAGE_LENGTH; i++){
    pkt2snd.payload[i] = 0;
  }

  pkt2rcv.seqnum = 0;
  pkt2rcv.acknum = 0;
  pkt2rcv.checksum = 0;
  for (i = 0; i < MESSAGE_LENGTH; i++){
    pkt2rcv.payload[i] = 0;
  }
}
