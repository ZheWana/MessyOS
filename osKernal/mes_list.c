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

#include "mes_list.h"
#include <stddef.h>
#include <stdlib.h>

/**
 * @brief 创建节点数据结构
 * 
 * @param item 链表载荷指针（void）
 * @return pnode_t 创建成功返回结点指针，创建失败返回NULL
 */
pnode_t Node_Create(void* item)
{
    pnode_t node = (pnode_t)malloc(sizeof(node_t));
    if (node == NULL)
        return NULL;
    node->item = item;
    return node;
}

/**
 * @brief 释放节点空间
 * 
 * @param node 
 */
void Node_Free(pnode_t node){
    if(node != NULL){
        free(node);
    }
}

/**
 * @brief 附加链表节点到链表尾
 * 
 * @param head 链表头指针
 * @param node 链表节点指针
 */
void List_Append(pnode_t head, pnode_t node)
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

/**
 * @brief 插入节点到链表
 * 
 * @param lastNode 插入位置的上一个节点
 * @param node 链表结点指针
 */
void List_Insert(pnode_t lastNode,pnode_t node)
{
    pnode_t tempNode = lastNode->next;
    lastNode->next = node;
    node->next = tempNode;
}

/**
 * @brief 从链表中删除节点
 * 
 * @param head 链表头指针
 * @param node 链表节点指针
 * @return pnode_t 返回删除的链表指针
 */
pnode_t List_Delete(pnode_t head,pnode_t node){
    pnode_t tempNode; 
    
    for (pnode_t index = head; index->next != node; index=index->next)
        tempNode = index;
    tempNode->next = node->next;   

    return node;
}
