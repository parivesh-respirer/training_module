#include "function.h"


Cleaner Sweeper;
void send_data_to_server(void){
      Sweeper.clear_stream_buff();
    sendDataToServer();
    Sweeper.clear_stream_buff();
}