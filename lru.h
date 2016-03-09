struct node{
	struct node * prev;
	struct node * next;
	int index;
};
typedef struct node * node_t;

struct evict{
	int queue_size;
	node_t head;
	node_t tail;
};
typedef struct evict * queue_t;

//Create a queue
queue_t create_queue();

// Adds a key to a queue
void queue_add(queue_t queue,int index);

// Moves a node that already exists in the queue to the front
// and properly readjusts the pointers in the rest of the queue
void queue_update(queue_t queue, node_t node);

// Deletes a node from the queue
void queue_delete(queue_t queue,node_t node);

// Destroys all resources connected to a queue
void destroy_queue(queue_t queue);