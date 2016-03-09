#include <stdlib.h>
#include <stdio.h>
#include "lru.h"

queue_t create_queue(){
	queue_t out = malloc(sizeof(struct evict));
	out->queue_size = 0;
	out->head = NULL;
	out->tail = NULL;
	return out;
}

void queue_add(queue_t queue,int index){
	if (queue->queue_size == 0){
		if(queue->head ==NULL)queue->head = malloc(sizeof(struct node));
		// if(queue->tail ==NULL)queue->tail = malloc(sizeof(struct node));
		queue->head->index = index;
		// queue->tail->index = index;
		// queue->head->next = queue->tail;
		queue->head->next = NULL;
		queue->head->prev = NULL;
		// queue->tail->next = NULL;
		// queue->tail->prev = queue->head;
		++queue->queue_size;
	}
	else if (queue->queue_size==1){
		queue->tail = queue->head;
		node_t n;
		n = malloc(sizeof(struct node));
		n->index = index;
		n->prev = NULL;
		n->next = queue->tail;
		queue->head = n;
		queue->tail->prev=queue->head;
		++queue->queue_size;
	}
	else{
		node_t n;
		n = malloc(sizeof(struct node));
		n->index = index;
		n->prev = NULL;
		n->next = queue->head;
		queue->head->prev = n;
		queue->head = n;
		++queue->queue_size;
	}
}

void queue_update(queue_t queue,node_t node){
	if (queue->head == node) return;
	else if (queue->tail == node){
		queue->tail = node->prev;
		queue->tail->next = NULL;
		node->prev = NULL;
		node->next = queue->head;
		queue->head->prev = node;
		queue->head = node;
		return;

	}
	else{
		node->prev->next = node->next;
		node->next->prev = node->prev;
		node->prev = NULL;
		queue->head->prev = node;
		node->next = queue->head;
		queue->head = node;
	}
};

void queue_delete(queue_t queue,node_t node){
	if (queue->queue_size == 0){
		printf("Error: Attempting to delete from an empty queue!\n");
	}
	else if (queue->queue_size == 1){
		queue->head->next = NULL;
		// queue->tail->prev = NULL;
		free(queue->head);
		// free(queue->tail);
		queue->head=NULL;
		// queue->tail=NULL;
		--queue->queue_size;
	}
	// else if (queue->queue_size == 2){
	// 	if(queue->head->index == index){
	// 		queue->head->index = queue->tail->index;
	// 		--queue->queue_size;
	// 	}
	// 	else{
	// 		queue->tail->index = queue->head->index;
	// 			--queue->queue_size;
	// 	}
	// }
	else if (queue->queue_size == 2){
		if(queue->head->index == index){
			queue->head = queue->tail;
			queue->head->prev = NULL;
			free(queue->tail);
			queue->tail = NULL;
			--queue->queue_size;
		}
		else{
			queue->head->next = NULL;
			free(queue->tail);
			queue->tail = NULL;
			--queue->queue_size;
		}
	}

	else if (queue->head==node){
		queue->head = queue->head->next;
		free(queue->head->prev);
		queue->head->prev = NULL;
		--queue->queue_size;
	}
	else if (queue->tail==node){
		queue->tail = queue->tail->prev;
		free(queue->tail->next);
		queue->tail->next = NULL;
		--queue->queue_size;		
	}
	else{
		node->prev->next = node->next;
		node->next->prev = node->prev;
		--queue->queue_size;
		free(node);
		node = NULL;
	}
}

void destroy_queue(queue_t queue){
	while (queue->queue_size!=0) queue_delete(queue,queue->head);
	if (queue->head!=NULL) printf("Head not null\n");
	if (queue->tail!=NULL) printf("Tail not null\n");
	free(queue);
	queue = NULL;
}
