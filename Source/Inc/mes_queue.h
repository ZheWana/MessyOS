/**
 * @file mes_queue.h
 * @author ZheWana (zhewana@qq.com)
 * @brief 基于链表的队列实现
 * @version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _MOS_QUEUE_
#define _MOS_QUEUE_

#include "mes_list.h"

typedef pnode_t qItem_t;

typedef struct QueueTypeDef {
    qItem_t entry;  // head of queue(tail of list)
    qItem_t exit;   // tail of queue(head of list)
    int len;        // length of queue
} queue_t, *pQueue_t;

#define Queue_elementFree(qItem_t) Node_Free(qItem_t)

pQueue_t Queue_create(void);

int Queue_in(pQueue_t queue, void* item);

void* Queue_out(pQueue_t queue);

#endif // !_MOS_QUEUE_