#ifndef __GRAPH__
#define __GRAPH__

#include <assert.h>
#include "gluethread/glthread.h"

#define NODE_NAME_SIZE 16
#define IF_NAME_SIZE 16
#define GRAPH_NAME_SIZE 16
#define MAX_INTERFACE_NO 10
#define NULL 0

typedef struct node_ node_t;
typedef struct link_ link_t;


typedef struct interface_{
    char* interface_name[IF_NAME_SIZE];
    node_t *node;
    link_t *link;
} interface_t;

struct node_{
    char *node_name[NODE_NAME_SIZE];
    interface_t *interfaces[MAX_INTERFACE_NO];
    glthread_t node_glue;
};

struct link_{
    interface_t ifa;
    interface_t ifb;
    unsigned int cost;
};

GLTHREAD_TO_STRUCT(graph_glue_to_node, node_t, node_glue);

typedef struct graph_{
    char *topology_name[GRAPH_NAME_SIZE];
    glthread_t node_list;
} graph_t;

static inline node_t* get_nbr_node(interface_t *interface){
    assert(interface->node);
    assert(interface->link);
    
    if (&interface->link->ifa==interface)
        return interface->link->ifb.node;
    else
        return interface->link->ifa.node;   
}

static inline int get_node_intf_available_slot(node_t *node){
    
    int i ;
    for( i = 0 ; i < MAX_INTERFACE_NO; i++){
        if(node->interfaces[i])
            continue;
        return i;
    }
    return -1;
}

graph_t *create_new_graph(char* topology_name);

node_t *create_graph_node(graph_t *graph, char *node_name);

void insert_link_between_two_nodes(node_t *node1,
                                    node_t *node2,
                                    char *from_if_name,
                                    char *to_if_name,
                                    unsigned int cost);
                                    


static inline interface_t *get_node_if_by_name(node_t *node, char *if_name){
    
    int i;

    for( i = 0 ; i < MAX_INTERFACE_NO; i++){
        if(0==strcmp(node->interfaces[i],if_name))
            return node->interfaces[i];
    }
    return 0;
}

static inline node_t *get_node_by_node_name(graph_t *topo, char *node_name){
    glthread_t *curr;
    node_t *node;
    
    ITERATE_GLTHREAD_BEGIN(&topo->node_list, curr){

        node = graph_glue_to_node(curr);
        
        if(0==strcmp(node->node_name,node_name))
            return node;

    } ITERATE_GLTHREAD_END(&graph->node_list, curr);
}

/*Display Routines*/


void dump_graph(graph_t *graph);
void dump_node(node_t *node);
void dump_interface(interface_t *interface);

#endif /* __NW_GRAPH_ */