#include <iostream>
#include "graph.h"

extern graph_t *build_first_topo();

int main(int, char**) {

       graph_t *topo = build_first_topo();
    //dump_graph(topo);
    dump_graph_nw(topo);

    // node_t *node = get_node_by_node_name(topo,"R0_re");
    // assert(node);
    // dump_node(node);

    // interface_t *intf = get_node_if_by_name(node,"eth0/4\0");
    // assert(intf);
    // dump_interface(intf);

    return 0;
}
