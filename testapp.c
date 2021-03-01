#include "graph.h"
#include <memory.h>
#include <stdio.h>
#include "comm.h"
#include "CommandParser/libcli.h"

extern graph_t *build_first_topo();
extern void nw_init_cli();
//For test
extern char * 
pkt_buffer_shift_right(char *pkt,unsigned int pkt_size,unsigned int max_buffer_size);

graph_t *topo = NULL;

int 
main(int argc, char **argv){

    nw_init_cli();
    
    topo = build_first_topo();

    start_shell(); 
    return 0;
}

/*
int 
main(int argc, char **argv){

    // graph_t *topo = build_first_topo();
    //dump_graph(topo);
    // dump_graph_nw(topo);

    // // node_t *node = get_node_by_node_name(topo,"R0_re");
    // // assert(node);
    // // dump_node(node);

    // // interface_t *intf = get_node_if_by_name(node,"eth0/4\0");
    // // assert(intf);
    // // dump_interface(intf);
    // interface_t *intfa; 

    // printf("test apply_mask\n");
    
    // char ip[16];
    // apply_mask("10.0.47.111",24,ip);
    // printf("%s\n",&ip);

    // printf("test node_get_matching_subnet_interface\n");

    // node_t *node;
    // node = get_node_by_node_name(topo, "R0_re");
    // intfa = node_get_matching_subnet_interface(node,"10.0.48.1");
    // dump_interface_nwprps(intfa);

    // printf("test convert IP to int \n");
    // printf("%u \n",convert_ip_from_str_to_int("10.0.48.178"));

    nw_init_cli();
    
    topo = build_first_topo();

    // --> Test Messaging
    
    // sleep(1);

    // node_t *node = get_node_by_node_name(topo,"R0_re");
    // interface_t *intf = get_node_if_by_name(node,"eth0/7");

    // char msg[] = "Hello! From Zhikai";

    // //send_pkt_out(msg,sizeof(msg),intf);
    // send_pkt_flood(node,intf,msg,sizeof(msg));
    
    // <-- Test Messaging End

    // --> Test Packet Management

    char pkt[MAX_PACKET_BUFFER_SIZE];

    memset(pkt, 0, MAX_PACKET_BUFFER_SIZE);

    char *pkt_with_aux_data = pkt;

    memset(pkt_with_aux_data, 0xAA, IF_NAME_SIZE);

    pkt_with_aux_data[IF_NAME_SIZE] = '\0';

    memset(pkt_with_aux_data + IF_NAME_SIZE, 0xFF, 10);

    int i=0;

    printf("\nBefore Shift: \n");
    
    for(i=0;i<MAX_PACKET_BUFFER_SIZE;i++)
    {
        printf("%02x",(unsigned char)*(pkt_with_aux_data+i));
    }

    printf("\nAfter Shift: \n");

    char *new_pkt = pkt_buffer_shift_right(pkt_with_aux_data + IF_NAME_SIZE, 10, MAX_PACKET_BUFFER_SIZE-IF_NAME_SIZE);

    
    for(i=0;i<MAX_PACKET_BUFFER_SIZE;i++)
    {
        printf("%02x",(unsigned char)*(pkt_with_aux_data+i));
    }


    printf("\nPayload: \n");

     
    for(i=0;i<10;i++)
    {
        printf("%02x",(unsigned char)*(new_pkt+i));
    }
    // Test Shift


    // <-- Test Packet Management End


    start_shell(); 

    return 0;
}
*/
