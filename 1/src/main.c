#include "../include/arr.h"
#include "../include/single_linked_list.h"
#include "../include/hash_map.h"
#include "../include/stack.h"
#include "../include/queue.h"

int main(void) {
    queue q;
    init_queue(&q);

    push_queue(&q, "Hello");
    push_queue(&q, "World");
    push_queue(&q, "Queue in C");

    char* item;

    item = pop_queue(&q);
    free(item);  // Освобождаем строку после использования

    item = pop_queue(&q);
    free(item);  // Освобождаем строку после использования

    if (isEmpty(&q)) {
        printf("Очередь пуста.\n");
    } else {
        printf("В очереди есть элементы.\n");
    }
}