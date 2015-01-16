/*
 * =====================================================================================
 *
 *       Filename:  view_controller.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/06/2014 03:06:57 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Milannic (), milannic.cheng.liu@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef VIEW_CONTROLLER_H
#define VIEW_CONTROLLER_H
#include "../util/common-structure.h"

// acceptor is the only role whose information should be stored in the 
// database 
// proposer and learner can be treated as an in-memory structure.
//

typedef uint32_t pnum_t;
typedef enum leader_election_msg_type_t{
    LELE_PREPARE = 0,
    LELE_PREPARE_ACK = 1,
    LELE_ACCEPT = 2,
    LELE_ACCEPT_ACK = 3,
    LELE_ANNOUNCE = 4,
    LELE_HIGHER_NODE = 5, // optimization,if we've found a node with lower node id has sent the leader election, then other node could immediately stop that.
    LELE_LAGGED = 6, // once we've found some nodes is lagged behind, we should tell them in case the new leader is down and we cannot get enough nodes to form a majority.
}lele_msg_type;

typedef struct proposer_record_t{
    pnum_t p_pnum;
    pnum_t a_pnum;
    node_id_t content;
}proposer_record;
#define PROPOSER_REC_SIZE (sizeof(proposer_record))

typedef struct accepted_record_t{
    pnum_t pnum; // this is the propose number, and we use node id to separate 
    node_id_t content; // since the node id is the only thing we need to get consensus
    req_id_t last_req; // in propose ack, this value has another meaning,act as the corresponding propose number from the proposer
}accepted_record;
#define ACCEPTED_REC_SIZE (sizeof(accepted_record))

typedef struct acceptor_record_t{ // this should be placed into database
    pnum_t highest_seen_pnum;
    pnum_t accepted_pnum;
    node_id_t content;
}acceptor_record;
#define ACCEPTOR_REC_SIZE (sizeof(acceptor_record))

typedef union reqorpnum_t{
    req_id_t last_req;
    pnum_t p_pnum;
}reqorpnum;

typedef struct lele_msg_t{
    lele_msg_type type;
    node_id_t node_id;
    view_id_t next_view;
    pnum_t pnum;
    node_id_t content;
    reqorpnum tail_data;
}lele_msg;
#define LELE_MSG_SIZE (sizeof(lele_msg))

typedef struct leader_election_module_t{
    //int is_proposer;
    view_id_t next_view; 
    pnum_t next_pnum; 
    acceptor_record acceptor;
    accepted_record* learner_arr;
    proposer_record* proposer_arr;
    struct event* slient_period; //
}lele_mod;
#define LELE_MOD_SIZE (sizeof(lele_mod))


// we have 3 kinds of msg
#endif
