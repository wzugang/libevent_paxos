/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/15/2014 03:53:15 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Milannic (), milannic.cheng.liu@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"

typedef uint64_t hk_t;
typedef uint64_t sec_t;
typedef uint16_t nid_t;
typedef uint16_t nc_t;

typedef struct hash_obj_t{
    hk_t id;
    // socket client
    int s_c;
    // socket server
    int s_s;
    UT_hash_handle hh;
}hash_obj;

hk_t getKey(nid_t node_id,nc_t node_count,sec_t time){
    hk_t key = time;
    key |= ((hk_t)node_id<<52);
    key |= ((hk_t)node_count<<36);
    return key;
}

int main ( int argc, char *argv[] )
{
    hash_obj* hash_map = NULL;
    nid_t node_id = 10;
    nc_t  count = 0;
    for(int i=0;i<100;i++){
        struct timeval temp;
        gettimeofday(&temp,NULL);
        sec_t time = temp.tv_sec;
        hk_t key = getKey(node_id,count,time);
        hash_obj* cur = (hash_obj*)malloc(sizeof(hash_obj));
        cur->s_s = -1;
        cur->s_c = -1;
        cur->id = key;
        HASH_ADD(hh,hash_map,id,sizeof(hk_t),cur);
        count++;
    }
    unsigned num_count = HASH_COUNT(hash_map);
    printf("there is %u elements in the hash table.\n",num_count);
    hash_obj* iter;
    for(iter=hash_map;iter!=NULL;iter=iter->hh.next){
        printf("the key is %ld.\n",iter->id);
    }
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

