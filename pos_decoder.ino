#include <Ethernet.h>
#define PORT 9009
#define MAXTCPLENGTH 30
 
byte mac[] = {0x02, 0x78, 0x20, 0xa8, 0x7a, 0x14};
IPAddress ip(192, 168, 122, 20);
//byte mac[] = {0x00, 0x50, 0x56, 0x1E, 0x38, 0x36};
//IPAddress ip(192, 168, 98, 135);
EthernetServer server(PORT);

String cmd;
const byte S1 = 2;
const byte D1 = 3;
volatile int pos = 0;

void setup() {
  Ethernet.begin(mac, ip);
  server.begin();

  pinMode(D1, INPUT);
  pinMode(S1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(S1), isr, RISING);
}

void net_read(){
  EthernetClient client = server.available();  
  if (client) {
    int  i = 0;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n' || c == '\r' || i > MAXTCPLENGTH) {
          client.println(net_exec(cmd));
          client.stop();
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
  if( cmd == "get_pos") {
    res = String(pos);
  }
  if( cmd == "zero_pos") {
    pos = 0;
    res = "ok\n";
  }

  return res;
}

void isr() {
  if  (digitalRead(D1) == LOW) {
    pos++;
  } else {
    pos--;
  }
}

void loop() {
  net_read();
  delay(100);
}
