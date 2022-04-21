/* Given an integer array, find k'th smallest element in the array 
where k is a positive integer less than or equal to the length of array */

#include <cstring>
#include <algorithm>
#include <iostream>

template <size_t K, typename T, size_t N>
T findKthSmallestElement(const T (&input)[N]) {
    static_assert(K > 0, "K must be greater than 0");
    static_assert(K <= N, "K must be lesser than or equal input size");
    T heap[K];
    memcpy(heap, input, sizeof(T) * K);
    std::make_heap(heap, heap + K);
    for (auto i = K; i < N; ++i) {
        if (input[i] < heap[0])
        {
            std::pop_heap(heap, heap + K);
            heap[K - 1] = input[i];
            std::push_heap(heap, heap + K);
        }
    }
    return heap[0];
}

int main() {
    std::cout << findKthSmallestElement<4>({ 5, 2, 8, 3, 1, 9, 4, 6, 7 }) << std::endl;
    return 0;
}