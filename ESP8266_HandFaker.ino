#include <ESP8266WiFi.h>
#include "AuthMessages.h"

// Include user_interface.h and add the headers needed
extern "C" {
  #include "user_interface.h"
  typedef void (*freedom_outside_cb_t)(uint8 status);
  int wifi_register_send_pkt_freedom_cb(freedom_outside_cb_t cb);
  void wifi_unregister_send_pkt_freedom_cb(void);
  int wifi_send_pkt_freedom(uint8 *buf, int len, bool sys_seq);
}
const int channels[14] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
const uint8_t bssid[6] = {0xab, 0xcd, 0xef, 0x12, 0x34, 0x56};
//const uint8_t bssid[6] = {0x11, 0x11, 0x11, 0x11, 0x11, 0x11}; // for testing

void frameFilter(uint8_t *buf, uint16_t len) {
  // No serial communications beyond this point? May cause issues with timings?
  //^ https://arduino.stackexchange.com/questions/71205/nodemcu-v3-serial-input-results-in-fatal-exception-9-loadstorealignmentcause related?
  unsigned char fc = buf[12]; // Thank you SpaceHuhn
  if (fc == 0xC0 || fc == 0xA0) {
    Serial.println("deauthentication/disassociation");
    broadcastHandshakes();
  }
}

void broadcastHandshakes() {
  
  //3.3.47. os_get_random - non-os sdk function to generate random numbers
  //for (int i = 0; i < 3; i++) {
    // if an 802.11 ACK is not received, the ESP8266 will retransmit the packet 10 times and continue.
    // https://github.com/espressif/esp-idf/issues/677
    int i = 0;
    i += wifi_send_pkt_freedom(key1Temp, sizeof(key1Temp), 0); // Try disabling the sequence counter
    Serial.println("1");
    delay(100);
    i += wifi_send_pkt_freedom(key2Temp, sizeof(key2Temp), 0);
    Serial.println("2");
    delay(100);
    i += wifi_send_pkt_freedom(key3Temp, sizeof(key3Temp), 0);
    Serial.println("3");
    delay(100);
    i += wifi_send_pkt_freedom(key4Temp, sizeof(key4Temp), 0);
    Serial.println("4");
    delay(1000);
  //}
  Serial.println(i);
}

void HandFakerSetup() {
  // Setup wifi configuration
  WiFi.mode(WIFI_OFF);
  wifi_set_opmode(STATION_MODE);
  wifi_set_promiscuous_rx_cb(frameFilter); // Supply packetScan callback
  wifi_set_channel(1); // Start on channel 1
  wifi_promiscuous_enable(1); // Enable promiscuous mode to gather packets
  //wifi_promiscuous_set_mac(bssid); // 3.11.2 of non-os sdk docs:
  // char ap_mac[6] = {0x16,  0x34, 0x56, 0x78, 0x90, 0xab};
  // wifi_promiscuous_set_mac(ap_mac);
  
  /* ^ Line 310 of user_interface.h
  void wifi_promiscuous_enable(uint8 promiscuous);
  typedef void (* wifi_promiscuous_cb_t)(uint8 *buf, uint16 len);
  void wifi_set_promiscuous_rx_cb(wifi_promiscuous_cb_t cb);
  void wifi_promiscuous_set_mac(const uint8_t *address);
  */
}

void setup() {
  Serial.begin(115200);
  Serial.println("test");
  HandFakerSetup();
}

void loop() {
  //broadcastHandshakes(); // for testing
}
