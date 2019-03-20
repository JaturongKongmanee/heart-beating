# Heart-beating
## Introduction
To simulate a simple inter-process communication protocol using [CSIM](http://www.mesquite.com/).
 * There are five nodes in the network. Each node is fully connected to each others.
 * Each node generates a HELLO packet with the inter arrival time of exponential distribution (average 5 seconds).
 * A sending node transmits a HELLO packet to a randomly chosen receiving node. A receiving node replies a HELLO_ACK packet back after it receives packet. 
 If the sending node receives the HELLO_ACK, the transmission is successful.
 * The transmission time is 0.1.
 * The transmission delay (e.g., local processing time) is 0.2.
 * The loss probabilities of packet are (0.1, 0.2, 0.3, 0.4, 0.5), due to the unreliable network quality.
 * The timeout period is 2 seconds. If sending node does not receive the HELLO_ACK packet within timeout period, it retransmits a HELLO packet. 
 If sending node still does not receive the HELLO_ACK, then transmission is failed.
 
 ## Getting Started
 ### Prerequisites
  * install [Code::Blocks](http://www.codeblocks.org/) and [C Programming Language](https://www.geeksforgeeks.org/c-language-set-1-introduction/)
  * install [CSIM](http://www.mesquite.com/)
 ### Compilation & Run
 ```
 csim64.gcc project.c -o project
 ./project
 ```
 * Specify a loss probability of packet.
 ```
 Enter a loss probability value:
 ```
 * Example of statistical results.
 ```
 Statistics of loss probability: 0.300000
 Average number of successful transmissions 0.59
 Average number of failed transmissions 0.41
 Average roundtrip time 0.50
 Node 0 generates 108 packets
 Node 1 generates 120 packets
 Node 2 generates 90 packets
 Node 3 generates 110 packets
 Node 4 generates 116 packets
```
  ### Results
  * Sanpshot of events when packet loss probability is **0.3**
  ![image of simulation0](https://github.com/JaturongKongmanee/heart-beating/blob/master/images/ex_print.png) 
  ![image of simulation1](https://github.com/JaturongKongmanee/heart-beating/blob/master/images/ex_print1.png)
  * The performance metrics against the loss probabilities (0.1, 0.2, 0.3, 0.4, 0.5).
  ![image of successful vs failed transmission](https://github.com/JaturongKongmanee/heart-beating/blob/master/images/s_f_t.png)
  ![image of rtt](https://github.com/JaturongKongmanee/heart-beating/blob/master/images/rtt_1.png)


 ## Authors
  * **Jaturong Kongmanee** - [jaturong.me](http://jaturong.me/)
  
 ## Acknowledgments
  * **Assistant Professor [Sunho Lim](http://www.myweb.ttu.edu/slim/), Ph.D.**
