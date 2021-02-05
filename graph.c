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

    // Assignment #4 init network properties
    init_node_nw_prop(&node->node_nw_prop);

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
    strncpy(link->ifa.interface_name,from_if_name,16);
    link->ifa.interface_name[16] = '\0';

    strncpy(link->ifb.interface_name,to_if_name,16);
    link->ifb.interface_name[16] = '\0';

    //Set values
    link->cost=cost;

    //Init interfaces A and B
    init_intf_nw_prop(&link->ifa.intf_nw_props);
    interface_assign_mac_address(&link->ifa);
    link->ifa.link=link;
    link->ifa.node=node1;
    
    init_intf_nw_prop(&link->ifb.intf_nw_props);
    interface_assign_mac_address(&link->ifb);
    link->ifb.node=node2;
    link->ifb.link=link;


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

void dump_nw_graph(graph_t *graph){

    assert(graph);

    glthread_t *curr;
    node_t *node;
    
    printf("Topology Name = %s\n", graph->topology_name);

    ITERATE_GLTHREAD_BEGIN(&graph->node_list, curr){

        node = graph_glue_to_node(curr);
        dump_node_nw(node);    
    } ITERATE_GLTHREAD_END(&graph->node_list, curr);
}


void dump_node_nw(node_t *node){

    assert(node);

    unsigned int i = 0;
    interface_t *intf;

    printf("Node Name = %s : \n", node->node_name);
    dump_node_nwprps(node);

    for( ; i < MAX_INTERFACE_NO ; i++){
        
        intf = node->interfaces[i];
        if(!intf) break;
        dump_interface(intf);
        dump_interface_nwprps(intf);
    }
}


void dump_node_nwprps(node_t *node){

      assert(node);

      printf("Node Network Properties = : \n");

      printf("Flags:%s \n", node->node_nw_prop.flags);
      printf("Has IP?:%d \n", node->node_nw_prop.is_lb_addr_config);
      if (true==node->node_nw_prop.is_lb_addr_config)
        printf("IP Address:%s \n", &node->node_nw_prop.lb_addr);
        
      printf("\n");

}

void dump_interface_nwprps(interface_t *interface){

      assert(interface);

      printf("Interface Properties = : \n");

      printf("MAC : %02x:%02x:%02x:%02x:%02x:%02x\n", 
                (unsigned char) IF_MAC(interface)[0], (unsigned char) IF_MAC(interface)[1],
                (unsigned char) IF_MAC(interface)[2], (unsigned char) IF_MAC(interface)[3],
                (unsigned char) IF_MAC(interface)[4], (unsigned char) IF_MAC(interface)[5]);
      printf("Has IP?:%d \n", interface->intf_nw_props.is_ipadd_config);
      if (true==interface->intf_nw_props.is_ipadd_config)
      {
        printf("IP Address:%s \n", &interface->intf_nw_props.ip_add.ip_addr);
        printf("Mask:%d \n", interface->intf_nw_props.mask);
      }
        
      printf("\n");
}
