#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <Ethernet.h>
#include <EthernetClient.h>

#define PORT             9009
#define MQTT_SERVER      "172.21.101.21"
#define MQTT_SERVERPORT  1883
#define MQTT_USERNAME    "***"
#define MQTT_PWD         "***"
#define MQTT_TOPIC       "vacuum/se3/valve/6/position"
#define MAX_CMD_LENGTH   30 // maximum command length
#define CONV             100 // conversion count nm
#define DISCONN_DELAY    5000 // wait after disconnect
#define READ_DELAY       1000 // wait after read from Ethernet
#define PUB_COUNT        10 // publish all PUB_COUNT values

String cmd;
const byte S1 = 2;
const byte D1 = 3;
volatile long pos = 0;
volatile int pub_count = 0;

byte mac[] = {0x02, 0x78, 0x20, 0xa8, 0x7a, 0x18};
IPAddress ip(192, 168, 122, 24);
EthernetServer server(PORT);

EthernetClient mqtt_client;
Adafruit_MQTT_Client mqtt(&mqtt_client, MQTT_SERVER, MQTT_SERVERPORT, MQTT_USERNAME, MQTT_PWD);
Adafruit_MQTT_Publish pub_pos = Adafruit_MQTT_Publish(&mqtt, MQTT_TOPIC);

void setup() {
  Ethernet.begin(mac, ip);
  server.begin();
  pinMode(D1, INPUT);
  pinMode(S1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(S1), isr, RISING);
}

void mqtt_connect() {
  int8_t ret;
  if (mqtt.connected()) {
    return;
  }
  while ((ret = mqtt.connect()) != 0) {
    mqtt.disconnect();
    delay(DISCONN_DELAY); 
  }
}

void net_read(){
  EthernetClient tcp_client = server.available();  
  if (tcp_client) {
    int  i = 0;
    while (tcp_client.connected()) {
      if (tcp_client.available()) {
        char c = tcp_client.read();
        if (c == '\n' || c == '\r' || i > MAX_CMD_LENGTH) {
          tcp_client.println(net_exec(cmd));
          tcp_client.stop();
          cmd = "";
          break;
        }
	cmd += c;
      }
      i++;
    }
  }
}

String net_exec(String cmd) {
  String  res = "unknown cmd\n";
  int8_t mqtt_err;
  if( cmd == "get_pos") {
    res = String(pos);
  }
  if( cmd == "zero_pos") {
    pos = 0;
    res = "ok\n";
  }
  if( cmd == "mqtt_conn") {
  if (mqtt.connected()) {
      res = "ok\n";
      } else {
      res = mqtt.connectErrorString(mqtt_err);
  }}
  return res;
}

void isr() {
  pub_count++;
  
  if  (digitalRead(D1) == LOW) {
    pos++;
  } else {
    pos--;
  }

  if (pub_count == PUB_COUNT) {
    pub_count = 0;
    mqtt_connect();
    pub_pos.publish(pos*CONV);
     
    if(! mqtt.ping()) {
      mqtt.disconnect();
    }
  }
}

void loop() {
  net_read();
  delay(READ_DELAY);
}
