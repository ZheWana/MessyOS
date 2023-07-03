/**
 * @file mes_queue.c
 * @author ZheWana (zhewana@qq.com)
 * @brief 基于链表的队列实现
 * @version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "mes_queue.h"
#include "stdlib.h"

pQueue_t Queue_create(void)
{
    pQueue_t tempQueue = malloc(sizeof(queue_t));
    if (tempQueue == NULL)
        return NULL;

    tempQueue->entry = NULL;
    tempQueue->exit = NULL;
    return tempQueue;
}

int Queue_in(pQueue_t queue, void* item)
{
    pnode_t tempNode = Node_Create(item);
    
    // First element in queue
    if (queue->entry == NULL && queue->exit == NULL)
        queue->entry = queue->exit = tempNode;
    else { // Other elements in queue
        tempNode->next = queue->entry;
        queue->entry = tempNode;
    }
    
    return ++queue->len;
}

void* Queue_out(pQueue_t queue)
{
    pnode_t tempNode = queue->exit;
    void* ret = tempNode->item;

    // Last element in queue
    if (queue->entry == queue->exit)
        queue->entry = queue->exit = NULL;
    else { // Other elements in queue
        queue->exit = List_Delete(queue->entry, queue->exit);
    }

    return ret;
}
