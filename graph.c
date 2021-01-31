#include "graph.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

graph_t *create_new_graph(char* topology_name){

    graph_t *g = malloc(sizeof(graph_t));

    strcpy(g->topology_name,topology_name);

    init_glthread(&g->node_list);

    return g;
}

node_t *create_graph_node(graph_t *graph, char *node_name){

    node_t *node = malloc(sizeof(node_t));

    strcpy(node->node_name,node_name);

    init_glthread(&node->node_glue);

    glthread_add_next(&graph->node_list, &node->node_glue);

    return node;
}

void insert_link_between_two_nodes(node_t *node1,
                                    node_t *node2,
                                    char *from_if_name,
                                    char *to_if_name,
                                    unsigned int cost){


    int slot1;
    slot1 =get_node_intf_available_slot(node1);
    assert(slot1!=-1);

    int slot2;
    slot2 =get_node_intf_available_slot(node2);
    assert(slot2!=-1);
    
    //Allocate memory for the link
    link_t *link = malloc(sizeof(link_t));
    
    //Copy the names
    strcpy(link->ifa.interface_name,from_if_name);
    strcpy(link->ifb.interface_name,to_if_name);

    //Set values
    link->cost=cost;

    //Set backpointers
    link->ifa.link=link;
    link->ifb.link=link;
    link->ifa.node=node1;
    link->ifb.node=node2;

    //assign the interfaces belonging to the link to the available slots 
        node1->interfaces[slot1] = &link->ifa;
        node2->interfaces[slot2] = &link->ifb;

}

void dump_graph(graph_t *graph){

    glthread_t *curr;
    node_t *node;
    
    printf("Topology Name = %s\n", graph->topology_name);

    ITERATE_GLTHREAD_BEGIN(&graph->node_list, curr){

        node = graph_glue_to_node(curr);
        dump_node(node);    
    } ITERATE_GLTHREAD_END(&graph->node_list, curr);
}

void dump_node(node_t *node){

    unsigned int i = 0;
    interface_t *intf;

    printf("Node Name = %s : \n", node->node_name);
    for( ; i < MAX_INTERFACE_NO ; i++){
        
        intf = node->interfaces[i];
        if(!intf) break;
        dump_interface(intf);
    }
}

void dump_interface(interface_t *interface){

   link_t *link = interface->link;
   node_t *nbr_node = get_nbr_node(interface);

   printf(" Local Node : %s, Interface Name = %s, Nbr Node %s, cost = %u\n", 
            interface->node->node_name, 
            interface->interface_name, nbr_node->node_name, link->cost); 
}
