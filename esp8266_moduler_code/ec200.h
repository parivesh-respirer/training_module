#ifndef EC200_H
#define EC200_H

void wait_for_at_response(void);
void setup_ec(void);
void init_ec(void);
extern char saveBuf[200];
void sendDataToServer();
class Cleaner {
public:
  void serUSB();
  void clear_stream_buff();
};
#endif