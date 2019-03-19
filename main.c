/* Project #2; Kongmanee, Jaturong */
#include "csim.h"
#include <stdio.h>


/* #define is used to define CONSTANT*/
#define SIMTIME 1000.0
#define NUM_NODES 5
#define TIME_OUT 2
#define PROCESS_TIME 0.2
#define TRANS_TIME 0.1
#define REQUEST 1 
#define REPLY 2
#define INTER_ARR_TIME 5.0

/* typedef is used to give a name to a type (it can be user-definded type)*/
typedef struct msg *msg_t;
struct msg {
    long type;
    long from;
    long to;
    TIME start_time;
    msg_t link;
};

msg_t msg_queue;

struct nde {
    FACILITY cpu;
    MBOX mbox;
};

struct nde node[NUM_NODES];
FACILITY network[NUM_NODES][NUM_NODES];
TABLE resp_tm;

void init();
void proc();
void send_msg();
void form_reply();
void return_msg();
void decode_msg();
msg_t new_msg();
void count_msg();


long avg_suc_trans, avg_failed_tran, rtt;
double loss_prob_threshold = 0.3;
long num_gen_mes_node1, num_gen_mes_node2, num_gen_mes_node3;
long num_gen_mes_node4, num_gen_mes_node0;

void sim(){
    

    printf( "Enter a loss probability threshold\n:");
    scanf("%lf", &loss_prob_threshold);
    printf( "You entered loss proability threshold: %lf\n", loss_prob_threshold);

    create("sim");
    init();
    hold(SIMTIME);


    printf("Average number of successful transmissions %ld\n", avg_suc_trans);
    printf("Average number of failed transmissions %ld\n", avg_failed_tran);
    printf("Average roundtrip time %ld\n", rtt);
    /*printf("Count %ld\n", count);*/
    printf("Node 0 gen %ld\n", num_gen_mes_node0);
    printf("Node 1 gen %ld\n", num_gen_mes_node1);
    printf("Node 2 gen %ld\n", num_gen_mes_node2);
    printf("Node 3 gen %ld\n", num_gen_mes_node3);
    printf("Node 4 gen %ld\n", num_gen_mes_node4);
}

void init(){
    long i, j;
    char str[24];

    max_facilities(NUM_NODES * NUM_NODES + NUM_NODES);
    max_servers(NUM_NODES * NUM_NODES + NUM_NODES);
    max_mailboxes(NUM_NODES);
    max_events(2 * NUM_NODES * NUM_NODES);
    resp_tm = table("msg rsp tm");
    msg_queue = NIL;

    for(i = 0; i < NUM_NODES; i++){
        sprintf(str, "cpu.%d", i);
        node[i].cpu = facility(str);
        sprintf(str, "input.%d", i);
        node[i].mbox = mailbox(str);
    }

    for(i = 0; i < NUM_NODES; i++){
        for(j = 0; j < NUM_NODES; j++){
            sprintf(str, "nt%d.%d", i, j);
            network[i][j] = facility(str);
        }
    }

    for(i = 0; i < NUM_NODES; i++){
        proc(i);
    }
        
}

void proc(long n){
    msg_t m;
    long s, t;
    

    create("proc");
    while(clock < SIMTIME){
        hold(exponential(INTER_ARR_TIME));
        /*use(node[n].cpu, exponential(INTER_ARR_TIME));*/
        m = new_msg(n);
        send_msg(m);
        printf("node.%ld sends a HELLO to node.%ld at %6.3f seconds\n", m->from, m->to, clock);
        count_msg("gen msg", m);
        

        s = timed_receive(node[n].mbox, (long *)&m, TIME_OUT);
        switch(s){
            case TIMED_OUT:
                avg_failed_tran += 1;
                rtt += 2;
                send_msg(m);
                printf("node.%ld re-sends a HELLO to node.%ld at %6.3f seconds\n", m->from, m->to, clock);
                break;
            case EVENT_OCCURRED:
                t = m->type;
                switch(t){
                case REQUEST:
                    form_reply(m);
                    double loss_prob = uniform(0.0, 1.0);
                    if(loss_prob > loss_prob_threshold ){
                        send_msg(m);
                    }
                    float clock1 = clock;
                    printf("node.%ld replies a HELLO_ACK to node.%ld at %6.3f seconds\n", m->from, m->to, clock1);           
                    break;
                case REPLY:
                    record(clock - m->start_time, resp_tm);
                    return_msg(m);
                    avg_suc_trans += 1;
                    rtt += 0.4;
                    printf("node.%ld receives a HELLO_ACK from node.%ld at %6.3f seconds\n", m->from, m->to, clock);
                    break;
                default:
                    printf("Unexpected type");
                    break;
                }
                break;
        } 
    }
}

void count_msg(char *str, msg_t m){
    long node_num = m->from;
    switch (node_num)
    {
        case 0:
            num_gen_mes_node0 += 1;
            break;
        case 1:
            num_gen_mes_node1 += 1;
            break;
        case 2:
            num_gen_mes_node2 += 1;
            break;
        case 3:
            num_gen_mes_node3 += 1;
            break;
        case 4:
            num_gen_mes_node4 += 1;
            break;
    
        default:
            break;
    }
}

/*void decode_msg(char *str, msg_t m, long n){
    if(m->type == REPLY){
        printf("node.%ld %str from node.&ld at %6.3f seconds\n", m->from, m->to, str, clock);
    }
    printf("node.%ld %str to node.&ld at %6.3f seconds\n", m->from, m->to, str, clock);
}*/

void send_msg(msg_t m){
    long from, to;
    from = m->from;
    to = m->to;

    reserve(network[from][to]);
    hold(TRANS_TIME);
    send(node[to].mbox, (long)m);
    release(network[from][to]);
}


msg_t new_msg(long from){
    msg_t m;
    long i;
    
    if(msg_queue == NIL){
        m = (msg_t)do_malloc(sizeof(struct msg));
    } else {
        m = msg_queue;
        msg_queue = msg_queue->link;
    }

    do {
        i = random(0L, NUM_NODES - 1);
    } while (i == from);

    m->to = i;
    m->from = from;
    m->type = REQUEST;
    m->start_time = clock;
    return m;
}


void return_msg(msg_t m){
    m->link = msg_queue;
    msg_queue = m;
}

void form_reply(msg_t m){
    long from, to;
    from = m->from;
    to = m->to;
    m->from = to;
    m->to = from;
    m->type = REPLY;
    use(node[to].cpu, PROCESS_TIME);
}


