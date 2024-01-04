/**
 * Copyright (C) 2024 sma.  All rights reserved.
 *
 * This header was taken from the sma
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public
 *  License v2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc.
 */

#ifndef __CQUEUE_H__
#define __CQUEUE_H__
#include <stdio.h>
#include <stdlib.h>


// Define the maximum size of the queue
#define MAX_QUEUE_SIZE 100

// Define the queue structure
#define DEFINE_QUEUE(type)                    \
    struct Queue_##type {                      \
        type* data[MAX_QUEUE_SIZE];             \
        int front, rear;                       \
    };                                        \
                                              \
    void initQueue_##type(struct Queue_##type* q) { \
        q->front = -1;                        \
        q->rear = -1;                         \
    }                                         \
                                              \
    int isEmpty_##type(struct Queue_##type* q) { \
        return (q->front == -1);              \
    }                                         \
                                              \
    int isFull_##type(struct Queue_##type* q) { \
        return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front); \
    }                                         \
                                              \
    void enqueue_##type(struct Queue_##type* q, type* item) { \
        if (isFull_##type(q)) {               \
            printf("Queue is full\n");        \
            return;                           \
        }                                     \
        if (isEmpty_##type(q)) {              \
            q->front = 0;                     \
        }                                     \
        q->rear = (q->rear + 1) % MAX_QUEUE_SIZE; \
        q->data[q->rear] = item;              \
    }                                         \
                                              \
    type* dequeue_##type(struct Queue_##type* q) { \
        type* item;                            \
        if (isEmpty_##type(q)) {              \
            printf("Queue is empty\n");       \
            exit(EXIT_FAILURE);               \
        }                                     \
        item = q->data[q->front];             \
        if (q->front == q->rear) {            \
            q->front = q->rear = -1;          \
        } else {                              \
            q->front = (q->front + 1) % MAX_QUEUE_SIZE; \
        }                                     \
        return item;                          \
    }


#endif