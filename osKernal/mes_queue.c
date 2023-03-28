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

int Queue_in(pQueue_t queue, qItem_t item)
{
    // First element in queue
    if (queue->entry == NULL && queue->exit == NULL)
        queue->entry = queue->exit = item;
    else { // Other elements in queue
        Node_Append(queue->entry, item);
        queue->entry = item;
    }
    
    return ++queue->len;
}

int Queue_out(pQueue_t queue)
{
    // Last element in queue
    if (queue->entry == queue.exit)
        queue->entry = queue->exit = NULL;
    else { // Other elements in queue
        queue->exit = Node_Delete(queue->exit, queue->exit);
    }

    return ++queue->len;
}
