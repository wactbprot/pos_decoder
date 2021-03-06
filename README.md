```

 ____  ____  ____  _  _____  _  ____  _        ____  _____ ____  ____  ____  _____ ____ 
/  __\/  _ \/ ___\/ \/__ __\/ \/  _ \/ \  /|  /  _ \/  __//   _\/  _ \/  _ \/  __//  __\
|  \/|| / \||    \| |  / \  | || / \|| |\ ||  | | \||  \  |  /  | / \|| | \||  \  |  \/|
|  __/| \_/|\___ || |  | |  | || \_/|| | \||  | |_/||  /_ |  \_ | \_/|| |_/||  /_ |    /
\_/   \____/\____/\_/  \_/  \_/\____/\_/  \|  \____/\____\\____/\____/\____/\____\\_/\_\
                                                                                        
```

Counts the steps (+/-) provided by the inlet/outlet valves [M1-M6](https://gitlab1.ptb.de/vaclab/valve_schemes/-/blob/master/SE3.png) rail guides. Positions are accessible via TCP.

**Next up**: publish position via [mqtt lib](https://github.com/adafruit/Adafruit_MQTT_Library/blob/master/examples/mqtt_ethernet/mqtt_ethernet.ino)



```

                             ┌──────────────────────┐  ┌────────┐
                             │                      │  │        │
                             │ MINISCALE            │  │ POWER  │
                             │                      │  │        │
                             │ 1  2  3    6  7  8   │  │        │
                             │ A- 0V B-   A+ 5V B+  │  │  0V 5V │
                             └─┬──┬──┬────┬──┬──┬───┘  └───┬──┬─┘
 ┌────────────────────────┐    │  │  │    │  │  │          │  │
 │ RS422-Shield           │    │  └──┼────┼──┼──┼──────────┤  │
 │                   GND  │    │     │    │  │  │          │  │
 │                        │    │     │    │  └──┼──────────┼──┤
 │                     Y  │    │     │    │     │          │  │
 │                        │    │     │    │     │          │  │
 │                     Z  │    │     │    │     │          │  │
 │                        │    │     │    │     │          │  │
 │                     A  ├────┼─────┼────┼─────┘          │  │
 │  J3: Port-RX           │    │     │    │                │  │
 │                     B  ├────┼─────┘    │                │  │
 │                        │    │          │                │  │
 ├────────────────────────┤    │          │                │  │
 ├────────────────────────┤    │          │                │  │
 │  RS422-Shield          │    │          │                │  │
 │                   GND  │    │          │                │  │
 │                        │    │          │                │  │
 │                     Y  │    │          │                │  │
 │                        │    │          │                │  │
 │                     Z  │    │          │                │  │
 │                        │    │          │                │  │
 │                     A  ├────┼──────────┘                │  │
 │  J2: Port-RX           │    │                           │  │
 │                     B  ├────┘                           │  │
 │                        │                                │  │
 ├────────────────────────┤                                │  │
 ├────────────────────────┤                                │  │
 │ Arduino UNO       GND  ├────────────────────────────────┘  │
 │                        │                                   │
 │                    5V  ├───────────────────────────────────┘
 └────────────────────────┘
```

## RS422 Shield

See docs folder for manual.

Switch settings:

S1: 
1:on
2:off
3:off
4:off

S2: 
1:off
2:off
3:on
4:on

S3: 
1:on
2:off
3:off
4:off


<img src="decoder.jpg" alt="decoder" width="690">

## MAC/IP

|       Name          |     MAC-Adresse          |     IP-Ardesse             | 
|---------------------|--------------------------|----------------------------|
|        e75410m      |      027820a87a13        |       192.168.122.19       |
|        e75411m      |      027820a87a14        |       192.168.122.20       |
|        e75412m      |      027820a87a15        |       192.168.122.21       |
|        e75413m      |      027820a87a16        |       192.168.122.22       |
|        e75414m      |      027820a87a17        |       192.168.122.23       |
|        e75415m      |      027820a87a18        |       192.168.122.24       |

