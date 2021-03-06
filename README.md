# Heart-beating
## Introduction
To simulate a simple inter-process communication protocol using [CSIM](http://www.mesquite.com/).
 * There are five nodes in the network. Each node is fully connected to each others.
 * Each node generates a HELLO packet with the inter arrival time of exponential distribution (average 5 seconds).
 * A sending node transmits a HELLO packet to a randomly chosen receiving node. A receiving node replies a HELLO_ACK packet back after it receives packet. 
 If the sending node receives the HELLO_ACK, the transmission is successful.
 * The `transmission time` is `0.1`.
 * The `transmission delay` (e.g., local processing time) is `0.2`.
 * The `loss probabilities of packet` are `(0.1, 0.2, 0.3, 0.4, 0.5)`, due to the unreliable network quality.
 * The `timeout period` is `2 seconds`. If sending node does not receive the HELLO_ACK packet within timeout period, it retransmits a HELLO packet. 
 If sending node still does not receive the HELLO_ACK, then transmission is failed.
 
 ## Getting Started
 ### Prerequisites
  * install [Code::Blocks](http://www.codeblocks.org/) and [C Programming Language](https://www.geeksforgeeks.org/c-language-set-1-introduction/)
  * install [CSIM](http://www.mesquite.com/)
 ### Compilation & Run
 
 ```javascript
 csim64.gcc project.c -o project
 ./project
 ```
 * Specify a loss probability of packet.
 ```
 Enter a loss probability value:
 ```
 * Example of statistical results.
 ```python
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
  ### Simulation Results
  * **Sanpshot of events when packet loss probability is ***0.3*****
  ![image of simulation0](https://github.com/JaturongKongmanee/heart-beating/blob/master/images/loss_prob_0.3.png) 
  <br/><br/>
  * **The performance metrics against the loss probabilities (0.1, 0.2, 0.3, 0.4, 0.5)**
  ![image of successful vs failed transmission](https://github.com/JaturongKongmanee/heart-beating/blob/master/images/s_f_t.png)
  ![image of rtt](https://github.com/JaturongKongmanee/heart-beating/blob/master/images/rtt_1.png)


 ## Author
  * **Jaturong Kongmanee** - [jaturongkongmanee.github.io/jk/](https://jaturongkongmanee.github.io/jk/)
  
 ## Acknowledgment
  * **Assistant Professor [Sunho Lim](http://www.myweb.ttu.edu/slim/), Ph.D.**
  
 ## References
- [CSIM - Official Documents](http://www.mesquite.com/documentation)
- [CSIM - Michigan State University](http://www.cse.msu.edu/~cse808/CSIM_Notes03/cse808/)
- [CSIM - University of Pittsburgh](http://www.pitt.edu/~dtipper/2120/CSIM_tutorial.pdf)
- [CSIM - The Chinese University of Hong Kong](http://www.cse.cuhk.edu.hk/~cslui/CSIM19/index.html)
- [CSIM - U of T](http://www.cs.toronto.edu/~iq/csc354s/)
- [VIM Tutorial](http://www.cse.msu.edu/~cse420/Tutorials/VIM/vim.tutorial)
- [Computer Architecture](https://www.cse.msu.edu/~cse420/)
- [Arrays in C](https://www.cs.swarthmore.edu/~newhall/unixhelp/C_arrays.html)

