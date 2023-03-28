/**
 * @file list.h
 * @author ZheWana (zhewana@qq.com)
 * @brief MessyOS中的单向链表实现头文件
 * @version 0.1
 * @date 2023-03-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _MOS_LIST_
#define _MOS_LIST_

#include "stdint.h"

typedef struct nodeTypedef{
    void *item;
    struct nodeTypedef* next;
}node_t,*pnode_t ;

pnode_t Node_Create(void*item);

void Node_Append(pnode_t head, pnode_t node);

void Node_Insert(pnode_t lastNode,pnode_t node);

pnode_t Node_Delete(pnode_t head,pnode_t node);

#endif // !_MOS_LIST_
