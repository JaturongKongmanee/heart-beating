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
  * install C lanuage
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
## 


 ## Authors
  * **Jaturong Kongmanee** - [jaturong.me](http://jaturong.me/)
  
 ## Acknowledgments
  * **Assistant Professor [Sunho Lim](http://www.myweb.ttu.edu/slim/), Ph.D.**
