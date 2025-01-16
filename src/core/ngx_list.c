
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#include <ngx_config.h>
#include <ngx_core.h>


ngx_list_t *
ngx_list_create(ngx_pool_t *pool, ngx_uint_t n, size_t size)
{
    ngx_list_t  *list;

    list = ngx_palloc(pool, sizeof(ngx_list_t));    // 创建链表
    if (list == NULL) {
        return NULL;
    }

    if (ngx_list_init(list, pool, n, size) != NGX_OK) { // 初始化链表成员
        return NULL;
    }

    return list;
}


void *
ngx_list_push(ngx_list_t *l)
{
    void             *elt;
    ngx_list_part_t  *last;

    last = l->last; // 尾节点

    if (last->nelts == l->nalloc) { // 扩容

        last = ngx_palloc(l->pool, sizeof(ngx_list_part_t));    // 创建一个节点
        if (last == NULL) {
            return NULL;
        }

        // 分配同等大小的内存
        last->elts = ngx_palloc(l->pool, l->nalloc * l->size);
        if (last->elts == NULL) {
            return NULL;
        }

        last->nelts = 0;
        last->next = NULL;

        l->last->next = last;   // 当前节点指向 新节点
        l->last = last;         // 更新当前节点的尾节点
    }

    // nginx 的 list 不是创建一个一个节点来存储元素
    // nginx 的节点和数据是分离的，并不绑定到一块
    // 而是从当前节点的 elts 指针指向的内存取出一块给用户存储数据
    elt = (char *) last->elts + l->size * last->nelts;
    last->nelts++;

    return elt;
}
