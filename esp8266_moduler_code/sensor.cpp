#include "sensor.h"
#include <stdio.h> 
#include <Arduino.h>
#include "o3_sensor.h"
#include "wifi_config.h"

String payload;

void formSensorData()
{  
  // make_pms_array_zero();
  // readPMS();
  int16_t pm1 = read_pm1_sensor_value();
   int16_t pm25 = read_pm25_sensor_value();
    int16_t pm10 = read_pm10_sensor_value();
  // int pm25 = 40, pm10 = 38;
  // float op1 = 34.55;
  float op1 = read_o3_op1();
  float op2 = read_o3_op2();

sprintf(stream_buffer_arr + strlen(stream_buffer_arr),
        "&pm1cnc=%d&pm2.5cnc=%d&pm10cnc=%d&o3op1=%0.3f&o3op2=%0.3f",
        pm1, pm25, pm10, op1, op2);


  payload = String("[{\"imei\":\"") + getMacAddress()
                  //  + "\",\"timestr2\":\"" + getFormattedTime1()
                   + "\",\"pm1cnc\":\"" + String(pm1)
                   + "\",\"pm2.5cnc\":\"" + String(pm25)
                   + "\",\"pm10cnc\":\"" + String(pm10)
                  //  + "\",\"pm2.5cnc_cf1\":\"" + String(pm25cf1)
                  //  + "\",\"pm1cnc_cf1\":\"" + String(pm1cf1)
                  //  + "\",\"pm10cnc_cf1\":\"" + String(pm10cf1)
                  //  + "\",\"pm1cnc_alt\":\"" + String(pm1_alt, 2)
                  //  + "\",\"pm2.5cnc_alt\":\"" + String(pm25_alt, 2)
                  //  + "\",\"pm10cnc_alt\":\"" + String(pm10_alt, 2)                   
                  //  + "\",\"tvocconc\":\"" + String(num)
                  //  + "\",\"pm1cnt\":\"" + String(cnt1)
                  //  + "\",\"pm0.3cnt\":\"" + String(cnt03)             
                  //  + "\",\"pm0.5cnt\":\"" + String(cnt05)     
                  //  + "\",\"pm2.5cnt\":\"" + String(cnt25)             
                  //  + "\",\"pm5cnt\":\"" + String(cnt5)         
                  //  + "\",\"pm10cnt\":\"" + String(cnt10)     
                   + "\",\"o3op1\":\"" + String(op1,3)
                   + "\",\"o3op2\":\"" + String(op2,3)                                            
                   + "\"}]";
  // Serial.print("Payload: ");
  // Serial.println(payload);
//     sprintf(stream_buffer_arr + strlen(stream_buffer_arr), "&kafka_topic=airview");
//     sprintf(stream_buffer_arr + strlen(stream_buffer_arr), "&temp=%0.1f&humidity=%0.1f&pres=%d&altd=%d", temp_avg, humd_avg, pres_avg / 100, altd_avg);
    // sprintf(stream_buffer_arr + strlen(stream_buffer_arr), "&pm1cnc=%d&pm2.5cnc=%d&pm10cnc=%d&pm0.3cnt=%d&pm0.5cnt=%d&pm1cnt=%d&pm2.5cnt=%d&pm5cnt=%d&pm10cnt=%d", pm1cnc_avg, pm25cnc_avg, pm10cnc_avg, pm03cnt_avg, pm05cnt_avg, pm1cnt_avg, pm25cnt_avg, pm5cnt_avg, pm10cnt_avg);
//     sprintf(stream_buffer_arr + strlen(stream_buffer_arr), "&pm25conc=%d&pm25raw=%d", pm25cnc_avg, pm25cnc_avg);	
//     sprintf(stream_buffer_arr + strlen(stream_buffer_arr), "&hchoconc=%s&vocconc=%s&tvocconc=%s&co2conc=%s",hchoconcCh, vocconcCh,tvocconcCh,co2concCh);
// //	 if(pwr_flag_send_freq>=3600)
// //  {
// 	  sprintf(stream_buffer_arr + strlen(stream_buffer_arr), "&power_avl=%d&rssi_4G=%d&solvolt=%d", EXT_5_AVL,rssi,solvolt);
// //   pwr_flag_send_freq = 0;
// //  }
   
  
//     sprintf(stream_buffer_arr + strlen(stream_buffer_arr), "&coop1=%s", co_mv_WE);
//     sprintf(stream_buffer_arr + strlen(stream_buffer_arr), "&coop2=%s", co_mv_AUX);
 
//   	sprintf(stream_buffer_arr + strlen(stream_buffer_arr), "&no2op1=%s", no2_mv_WE);
//     sprintf(stream_buffer_arr + strlen(stream_buffer_arr), "&no2op2=%s", no2_mv_AUX);
  
//     sprintf(stream_buffer_arr + strlen(stream_buffer_arr), "&so2op1=%s", so2_mv_WE);
//     sprintf(stream_buffer_arr + strlen(stream_buffer_arr), "&so2op2=%s", so2_mv_AUX);
  
//     sprintf(stream_buffer_arr + strlen(stream_buffer_arr), "&o3op1=%s", o3_mv_WE);
//     sprintf(stream_buffer_arr + strlen(stream_buffer_arr), "&o3op2=%s", o3_mv_AUX);

 

//     sprintf(stream_buffer_arr + strlen(stream_buffer_arr), "&battery=%s", batteryCh);





//   sprintf(stream_buffer_arr + strlen(stream_buffer_arr), "&BB0_opcr2=%d", SDCount);
//   sprintf(stream_buffer_arr + strlen(stream_buffer_arr), "&BB1_opcr2=%d", SDFlag);
//   sprintf(stream_buffer_arr + strlen(stream_buffer_arr), "&BB2_opcr2=%d", readFlag);
//   sprintf(stream_buffer_arr + strlen(stream_buffer_arr), "&BB3_opcr2=%d", saveFlag);
      

//     sprintf(stream_buffer_arr + strlen(stream_buffer_arr), "&devicetime=%0.3f", ((float)millis())/1000.0/60.0/60.0);
//      hourly_data_flag = 0;
  
//     String reset_reason = ESP.getResetReason();
//     reset_reason.replace(" ","");
//     sprintf(stream_buffer_arr + strlen(stream_buffer_arr), "&BB4_opcr2=%s", FirmwareVer.c_str());
//     sprintf(stream_buffer_arr + strlen(stream_buffer_arr), "&BB5_opcr2=%s", reset_reason.c_str());

 
}