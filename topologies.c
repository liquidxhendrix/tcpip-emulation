#include "graph.h"

extern void
network_start_pkt_receiver_thread(graph_t *topo);

graph_t *
build_first_topo(){

#if 0

                          +----------+
                      0/4 |          |0/0
         +----------------+   R0_re  +---------------------------+
         |                |          |                           |
         |                +----------+                           |
         |                                                       |
         |                                                       |
         |                                                       |
         |                                                       |
         |0/5                                                    |0/1
     +---+---+                                              +----+-----+
     |       |0/3                                        0/2|          |
     | R2_re +----------------------------------------------+    R1_re |
     |       |                                              |          |
     +-------+                                              +----------+

#endif


    graph_t *topo = create_new_graph("Hello World Generic Graph\0");
    node_t *R0_re = create_graph_node(topo, "R0_re\0");
    node_t *R1_re = create_graph_node(topo, "R1_re\0");
    node_t *R2_re = create_graph_node(topo, "R2_re\0");

    node_set_loopback_address(R0_re, "127.0.0.10");
    node_set_loopback_address(R1_re, "127.0.0.11");
    node_set_loopback_address(R2_re, "127.0.0.12");

    insert_link_between_two_nodes(R0_re, R1_re, "eth0/0\0", "eth0/1\0", 1);
    insert_link_between_two_nodes(R1_re, R2_re, "eth0/2\0", "eth0/3\0", 1);
    insert_link_between_two_nodes(R0_re, R2_re, "eth0/4\0", "eth0/5\0", 1);

    interface_t *intfa; 
    
    intfa = get_node_if_by_name(R0_re,"eth0/0");
    interface_assign_mac_address(intfa);
    node_set_intf_ip_address(R0_re,"eth0/0","10.0.48.10",24);

    intfa = get_node_if_by_name(R1_re,"eth0/1");
    interface_assign_mac_address(intfa);
    node_set_intf_ip_address(R1_re,"eth0/1","10.0.47.11",24);

    network_start_pkt_receiver_thread(topo);

    return topo;
}
