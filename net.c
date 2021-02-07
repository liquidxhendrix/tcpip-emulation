#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include "net.h"
#include <arpa/inet.h> /*for inet_ntop & inet_pton*/
#include <math.h>

/*Just some Random number generator*/
static unsigned int
hash_code(void *ptr, unsigned int size){
    unsigned int value=0, i =0;
    char *str = (char*)ptr;
    while(i < size)
    {
        value += *str;
        value*=97;
        str++;
        i++;
    }
    return value;
}


/*Heuristics, Assign a unique mac address to interface*/
void
interface_assign_mac_address(interface_t *interface){

    node_t *node = interface->node;
    
    if(!node)
        return;

    unsigned int hash_code_val = 0;
    hash_code_val = hash_code(node->node_name, NODE_NAME_SIZE);
    hash_code_val *= hash_code(interface->interface_name, IF_NAME_SIZE);
    memset(IF_MAC(interface), 0, sizeof(IF_MAC(interface)));
    memcpy(IF_MAC(interface), (char *)&hash_code_val, sizeof(unsigned int));
   
  /*  IF_MAC(interface)[0]=0xAF;
   IF_MAC(interface)[1]=0xBF;
   IF_MAC(interface)[2]=0xCF;
   IF_MAC(interface)[3]=0xDF;
   IF_MAC(interface)[4]=0xEF;
   IF_MAC(interface)[5]=0xFF; */
}

bool_t node_set_loopback_address(node_t *node, char *ip_addr){
    assert(ip_addr);
    assert(node);

    strncpy(NODE_LB_ADDR(node),ip_addr,16);
    NODE_LB_ADDR(node)[15]='/0';
    node->node_nw_prop.is_lb_addr_config=true;
}

bool_t node_set_intf_ip_address(node_t *node, char *local_if, char *ip_addr, char mask){
    assert(node);
    assert(local_if);
    assert(ip_addr);
    
    interface_t *intfp = get_node_if_by_name(node,local_if);
    assert(intfp);
    
    strncpy(IF_IP(intfp),ip_addr,16);
    IF_IP(intfp)[15]='/0';
    intfp->intf_nw_props.is_ipadd_config=true;
    intfp->intf_nw_props.mask=mask;
    return true;
}

bool_t node_unset_intf_ip_address(node_t *node, char *local_if){
    assert(node);
    assert(local_if);
    
    interface_t *intfp = get_node_if_by_name(node,local_if);
    assert(intfp);

    memset(IF_IP(intfp),0,16);
    intfp->intf_nw_props.mask=0;
    return TRUE;
}

interface_t* node_get_matching_subnet_interface(node_t *node, char *ip_addr){

    char *base_ip = (char *) calloc(1,16);
    char *src_ip = (char *) calloc(1,16);

    int i=0;
    int mask=0;

    for (i=0;i<MAX_INTERFACE_NO;i++){
        if (NULL != node->interfaces[i]){
              if (true == node->interfaces[i]->intf_nw_props.is_ipadd_config){
                  //Found active interface
                mask = node->interfaces[i]->intf_nw_props.mask;
                apply_mask(ip_addr,mask,base_ip);
                apply_mask(&node->interfaces[i]->intf_nw_props.ip_add,mask,src_ip);

                if (0==strcasecmp(base_ip,src_ip)){
                    //found
                    free(base_ip);
                    free(src_ip);
                    return node->interfaces[i];                    
                }
              }
              
        }
    }
}

unsigned int convert_ip_from_str_to_int(char *ipadd){    
   
    // char src_ip[4];

    // inet_pton(AF_INET,ipadd,src_ip);

    // unsigned int octA,octB,octC,octD;

    // octA = (unsigned int) src_ip[0];
    // octB = (unsigned int) src_ip[1];
    // octC = (unsigned int) src_ip[2];
    // octD = (unsigned int) src_ip[3];

    // return (octA * pow(256,3) 
    // + octB * pow(256,2) 
    // + octC * pow(256,1) 
    // + octD * pow(256,0));

    unsigned int src_ip;

    inet_pton(AF_INET,ipadd,&src_ip);

    return htonl(src_ip);
}

unsigned int convert_ip_from_int_to_str(unsigned int ip_addr, char *output_buffer){
    inet_ntop(AF_INET, &ip_addr, output_buffer, 16);
    output_buffer[15] = '/0';
}