#pragma once
#include "Path.h"

void Path::ReversePath()
{
    // Initialize current, previous and
        // next pointers
    node_ptr current = first;
    last = first;
    node_ptr prev = NULL;
    node_ptr next = NULL;

    while (current != NULL) {
        // Store next
        next = current->next;

        // Reverse current node's pointer
        current->next = prev;

        // Move pointers one position ahead.
        prev = current;
        current = next;
    }
    first = prev;
}

int Path::length()
{
    return first->length(0);
}


