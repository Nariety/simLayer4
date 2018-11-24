#include <string.h>


struct msg {
    char  data[MESSAGE_LENGTH];
};

struct   pkt {
    int  seqnum;
    int  acknum;
    int  checksum;
    char payload[MESSAGE_LENGTH];
};

struct pkt make_pkt(int seq, struct msg message, int checksum){
  struct pkt packet;
  packet.seqnum = seq;
  packet.acknum = 0;
  packet.checksum = checksum;
  //TODO prepend 0's to message if the message is shorter than message MESSAGE_LENGTH
  //TODO ? what char size in c? 8bytes?
  for (int i = 0; i < MESSAGE_LENGTH; i ++){
    packet.payload[i] = message.data[i];
  }
}

/*
 * getChecksum() returns checksum for the given packet
 */
int getChecksum(struct pkt packet){
  return 1;
}

// generates a checksum for payload, sequance, and acknowledge fields
int getChecksum(struct msg message, int seq, int ack){

}

void main(int argc, char *argv[]){
  struct msg message;
  message.data = "this is a test";
  struct pkt packet = make_pkt(0,message,getChecksum())
  printf(getChecksum())
}
