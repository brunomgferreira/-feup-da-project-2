#ifndef FEUP_DA_PROJECT_2_MUTABLE_PRIORITY_QUEUE
#define FEUP_DA_PROJECT_2_MUTABLE_PRIORITY_QUEUE

#include <vector>

/**
 * @brief A mutable priority queue data structure.
 *
 * @complexity Insertion: O(log n); Extraction of Minimum: O(log n); Decrease Key: O(log n);
 */

template <class T>
class MutablePriorityQueue {
        std::vector<T *> H;
        void heapifyUp(unsigned i);
        void heapifyDown(unsigned i);
        inline void set(unsigned i, T * x);
        public:
        MutablePriorityQueue();
        void insert(T * x);
        T * extractMin();
        void decreaseKey(T * x);
        bool empty();
};

// Index calculations
#define parent(i) ((i) / 2)
#define leftChild(i) ((i) * 2)

/**
 * @brief Constructs a new MutablePriorityQueue object.
 */
template <class T>
MutablePriorityQueue<T>::MutablePriorityQueue() {
    H.push_back(nullptr);
    // indices will be used starting in 1
    // to facilitate parent/child calculations
}

/**
 * @brief Checks if the priority queue is empty.
 *
 * @return True if the priority queue is empty, otherwise false.
 */
template <class T>
bool MutablePriorityQueue<T>::empty() {
    return H.size() == 1;
}

/**
 * @brief Extracts the minimum element from the priority queue.
 *
 * @return A pointer to the minimum element extracted from the priority queue.
 */
template <class T>
T* MutablePriorityQueue<T>::extractMin() {
    auto x = H[1];
    H[1] = H.back();
    H.pop_back();
    if(H.size() > 1) heapifyDown(1);
    x->queueIndex = 0;
    return x;
}

/**
 * @brief Inserts a new element into the priority queue.
 *
 * @param x A pointer to the element to be inserted into the priority queue.
 */
template <class T>
void MutablePriorityQueue<T>::insert(T *x) {
    H.push_back(x);
    heapifyUp(H.size()-1);
}

/**
 * @brief Decreases the key of an element in the priority queue.
 *
 * @param x A pointer to the element whose key needs to be decreased.
 */
template <class T>
void MutablePriorityQueue<T>::decreaseKey(T *x) {
    heapifyUp(x->queueIndex);
}

/**
 * @brief Performs the heapify-up operation to maintain the heap property.
 *
 * @param i The index of the element to heapify-up.
 */
template <class T>
void MutablePriorityQueue<T>::heapifyUp(unsigned i) {
    auto x = H[i];
    while (i > 1 && *x < *H[parent(i)]) {
        set(i, H[parent(i)]);
        i = parent(i);
    }
    set(i, x);
}

/**
 * @brief Performs the heapify-down operation to maintain the heap property.
 *
 * @param i The index of the element to heapify-down.
 */
template <class T>
void MutablePriorityQueue<T>::heapifyDown(unsigned i) {
    auto x = H[i];
    while (true) {
        unsigned k = leftChild(i);
        if (k >= H.size())
            break;
        if (k+1 < H.size() && *H[k+1] < *H[k])
            ++k; // right child of i
        if ( ! (*H[k] < *x) )
            break;
        set(i, H[k]);
        i = k;
    }
    set(i, x);
}

/**
 * @brief Sets the element at a specified index in the priority queue.
 *
 * @param i The index where the element should be set.
 * @param x The element to be set at the specified index.
 */
template <class T>
void MutablePriorityQueue<T>::set(unsigned i, T * x) {
    H[i] = x;
    x->queueIndex = i;
}

#endif /* FEUP_DA_PROJECT_2_MUTABLE_PRIORITY_QUEUE */
