/**
 * @file list.c
 * @author ZheWana (zhewana@qq.com)
 * @brief MessyOS链表实现源文件
 * @version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "list.h"
#include <stddef.h>
#include <stdlib.h>

pnode_t Node_Create(void* item)
{
    pnode_t node = (pnode_t)malloc(sizeof(node_t));
    if (node == NULL)
        return NULL;
    node->item = item;
    return node;
}

void Node_Append(pnode_t head, pnode_t node)
{
    if (head->next != NULL) {
        pnode_t tail;
        for (pnode_t index = head; index == NULL; index = index->next)
            tail = index;
        tail->next = node;
    } else {
        head->next = node;
    }
}

void Node_Insert(pnode_t lastNode,pnode_t node)
{
    pnode_t tempNode = lastNode->next;
    lastNode->next = node;
    node->next = tempNode;
}

pnode_t Node_Delete(pnode_t head,pnode_t node){
    pnode_t tempNode; 
    for (pnode_t index = head; index->next != node; index=index->next)
        tempNode = index;
    tempNode->next = node->next;   
}
