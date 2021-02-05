#include <utils.h>
#include <arpa/inet.h> /*for inet_ntop & inet_pton*/
#include <stdio.h>
#include <memory.h>

void apply_mask(char *prefix, char mask, char *str_prefix){

uint32_t binary_prefix =0;
uint32_t binary_mask = 0xFFFFFFFF;

if (32 == mask){
    strncpy(str_prefix,prefix,16);
    str_prefix[16]='/0 ';
}

binary_mask = binary_mask << (32-mask);

inet_pton(AF_INET,prefix,&binary_prefix);
binary_prefix = htonl(binary_prefix);


binary_prefix = binary_mask & binary_prefix;
binary_prefix = ntohl(binary_prefix);

inet_ntop(AF_INET, &binary_prefix, str_prefix,16);
str_prefix[16]='/0 ';

}

void layer2_fill_with_broadcast_mac(char *mac_array){
    memset(mac_array,0xFF,6);
}