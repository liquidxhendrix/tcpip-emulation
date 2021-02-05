#include "graph.h"
#include <memory.h>
#include <stdio.h>
#include "CommandParser/libcli.h"

extern graph_t *build_first_topo();
extern void nw_init_cli();

graph_t *topo = NULL;

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

    start_shell(); 

    return 0;
}
