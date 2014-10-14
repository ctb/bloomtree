#ifndef HEAP_H
#define HEAP_H
#include <cmath>
#include <vector>
#include <cassert>
#include <iostream>



template<typename T> 
class Heap {
public:
    // the nodes of the heap
    struct heap_reference {
        int pos;
        T* item;
        int key;

        heap_reference() : pos(-1), item(0), key(0) {}

        heap_reference(int p, T* i, int k) :
            pos(p), item(i), key(k) {}

        /* bool is_valid() { return pos >= 0; }
        void invalidate() { pos = -1; } */
    };

    Heap() : heap() {};

    ~Heap() {};

    int size() { return heap.size(); }

    // remove and return the item with the min key
    T* pop() {
        heap_reference* top = heap[0];
        auto last = heap.back();
        heap.pop_back();

        // if heap not now empty, we move the last to the top
        // and sift down.
        if (heap.size() > 0) {
            heap[0] = last;
            heap[0]->pos = 0;
            siftdown(0);
        }
        // return the previous top item and delete the heap record
        // we removed.
        T* item = top->item;
        std::cerr << "Removing heap item with key " << top->key << std::endl;
        delete top;
        return item;
    }

    // insert a new item with the given key
    heap_reference* insert(T* n, int key) {
        heap.push_back(new heap_reference(heap.size()-1, n, key));
        return siftup(heap.size()-1);
    }

    heap_reference* increase_key(heap_reference* n, int new_key) {
        assert(heap[n->pos] == n);
        heap[n->pos]->key = new_key;
        return siftup(n->pos);
    }

private:
    std::vector<heap_reference*> heap;

    heap_reference* siftup(int hole) {
        auto moving = heap[hole];

        auto p = heap_parent(hole);
        while (p != 0 && heap[hole]->key > moving->key) {
            // put p into hole
            heap[hole] = heap[p];
            heap[hole]->pos = hole;
            
            // move the pointers up
            hole = p;
            p = heap_parent(hole);
        }
        heap[hole] = moving;
        heap[hole]->pos = hole;
        return heap[hole];
    }

    heap_reference* siftdown(int hole) {
        auto moving = heap[hole];
        auto c = minchild(hole);
        while (c > 0 && heap[c]->key < moving->key) {
            heap[hole] = heap[c];
            heap[hole]->pos = hole;
            hole = c;
            c = minchild(c);
        }
        heap[hole] = moving;
        heap[hole]->pos = hole;
        return heap[hole];
    }

    int heap_parent(int pos) {
        if (pos == 0) return -1;
        return (pos - 1) / 2;
    }

    int minchild(int pos) {
        size_t left = 2*pos + 1;
        size_t right = 2*pos + 2;
        // both children exist
        if (right < heap.size()) {
            // return the smallest
            return (heap[right]->key < heap[left]->key) ? right : left;

        // left child is the only child, so it's the smallest
        } else if (left < heap.size()) {
            return left;

        // no children
        } else return -1;
    }

};
#endif

