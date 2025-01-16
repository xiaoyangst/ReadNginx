
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_LIST_H_INCLUDED_
#define _NGX_LIST_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>


typedef struct ngx_list_part_s  ngx_list_part_t;

struct ngx_list_part_s {
    void             *elts;     // 节点内存的起始位置
    ngx_uint_t        nelts;    // 链表中已有节点数
    ngx_list_part_t  *next;     // 指向下一个节点
};  // 链表节点


typedef struct {
    ngx_list_part_t  *last;     // 尾节点
    ngx_list_part_t   part;     // 头节点
    size_t            size;     // 节点大小
    ngx_uint_t        nalloc;   // 节点个数
    ngx_pool_t       *pool;
} ngx_list_t;   // 链表

/*
 * 我们可以看到，链表 和 链表中节点的数据是分离的
 */

ngx_list_t *ngx_list_create(ngx_pool_t *pool, ngx_uint_t n, size_t size);

static ngx_inline ngx_int_t
ngx_list_init(ngx_list_t *list, ngx_pool_t *pool, ngx_uint_t n, size_t size)
{
    list->part.elts = ngx_palloc(pool, n * size);   // 指向 存储数据的实际内存的起始地址
    if (list->part.elts == NULL) {
        return NGX_ERROR;
    }

    list->part.nelts = 0;   // 目前 0 个实际节点
    list->part.next = NULL;
    list->last = &list->part;   // 当下，头节点和尾节点是同一个
    list->size = size;
    list->nalloc = n;   // 此链表能存储的元素个数，内存池的使用，让它无法随意指向一块内存地址
    list->pool = pool;

    return NGX_OK;
}


/*
 *
 *  the iteration through the list:
 *
 *  part = &list.part;
 *  data = part->elts;
 *
 *  for (i = 0 ;; i++) {
 *
 *      if (i >= part->nelts) {
 *          if (part->next == NULL) {
 *              break;
 *          }
 *
 *          part = part->next;
 *          data = part->elts;
 *          i = 0;
 *      }
 *
 *      ...  data[i] ...
 *
 *  }
 */


void *ngx_list_push(ngx_list_t *list);


#endif /* _NGX_LIST_H_INCLUDED_ */
