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
    qItem_t entry;
    qItem_t exit;
    int len;
} queue_t, *pQueue_t;

pQueue_t Queue_create(void);

int Queue_in(pQueue_t queue, qItem_t item);

qItem_t Queue_out(pQueue_t queue);

#endif // !_MOS_QUEUE_