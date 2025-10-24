#include<iostream>
#include<string>
#include<stdexcept> // Required for runtime_error and out_of_range
#include<utility> // Required for std::swap

using namespace std;

// Node class, typically used in tree structures (like Huffman coding, given the 'frequency')
class Node {
public:
    int frequency; // Key for the priority queue (min-heap)
    int data;      // Value stored in the node (e.g., ASCII code)
    Node *left, *right; // Pointers for tree structure

    // Parameterized Constructor
    Node(int x, int freq, Node* lefttree = nullptr, Node* righttree = nullptr) {
        data = x;
        frequency = freq;
        left = lefttree;
        right = righttree;
    }

    // Default Constructor
    Node() {
        data = 0;
        frequency = 1;
        left = nullptr;
        right = nullptr;
    }

    // Deep Copy Constructor: Essential for correct memory management (Rule of Three/Five)
    // It recursively creates new child nodes to prevent a "double free" crash.
    Node(const Node& other) {
        data = other.data;
        frequency = other.frequency;
        // Recursively create new nodes for children (deep copy)
        left = other.left ? new Node(*other.left) : nullptr;
        right = other.right ? new Node(*other.right) : nullptr;
    }

    // Copy Assignment Operator: Uses the copy-and-swap idiom for strong exception safety.
    Node& operator =(Node other) { 
        std::swap(data, other.data);
        std::swap(frequency, other.frequency);
        std::swap(left, other.left);
        std::swap(right, other.right);
        return *this;
    }

    // Destructor: Recursively deletes children to free allocated memory
    ~Node() {
        if (left != nullptr)
            delete left;
        if (right != nullptr)
            delete right;
    }

    // Overloaded comparison operators, based on frequency (for use in the min-heap)
    bool operator <(const Node& right) const {
        return frequency < right.frequency;
    }

    bool operator >(const Node& right) const {
        return frequency > right.frequency;
    }

    bool operator ==(const Node& right) const {
        return frequency == right.frequency;
    }

    bool operator != (const Node& right) const {
        return !(*this == right);
    }

    bool operator >=(const Node& right) const {
        return *this > right || *this == right;
    }

    bool operator <=(const Node& right) const {
        return *this < right || *this == right;
    }
};

// Custom dynamic array class (reimplementation of std::vector features)
template<typename T>
class vector {
    T *array;
    int size;   // Total capacity of the underlying array
    int count;  // Number of elements currently in the vector

    // Helper function to double the capacity when full
    void resize() {
        int new_size = size;
        if (size == 0)
            new_size = 1;
        else
            new_size = 2 * size;

        T* temp = new T[new_size];
        for (int i = 0; i < count; i++) { 
            temp[i] = array[i]; // Copy existing elements
        }

        size = new_size;
        if (array)
            delete[] array; // Must use delete[] for array deallocation
        array = temp;
    }

public:
    // Constructor with initial capacity
    vector(int chosen_size) {
        size = chosen_size;
        array = new T[size];
        count = size;
    }

    // Constructor with initial capacity and default value
    vector(int chosen_size, T value) {
        size = chosen_size;
        array = new T[size];
        for (int i = 0; i < size; i++) {
            array[i] = value;
        }
        count = size;
    }

    // Default Constructor
    vector() {
        size = 0;
        array = nullptr; // Initialize array pointer to null
        count = 0;
    }

    // Copy Constructor
    vector(const vector& other) : size(other.size), count(other.count) {
        array = new T[size];
        for (int i = 0; i < count; ++i) {
            array[i] = other.array[i];
        }
    }

    // Assignment Operator
    vector& operator=(vector other) {
        std::swap(size, other.size);
        std::swap(count, other.count);
        if(array)
            delete array;
        array = new T[size];
        for (int i = 0; i < count; ++i) {
            array[i] = other.array[i];
        }
        return *this;
    }


    // Destructor
    ~vector() {
        if (array)
            delete[] array; // Release the allocated array memory
    }

    // Overloaded subscript operator for element access
    T& operator [](int index) {
        if (index < 0 || index >= count) {
            throw out_of_range("Vector index out of bounds");
        }
        return array[index];
    }

    // Returns number of elements
    int getSize() const {
        return count;
    }

    // Checks if the vector is empty
    bool empty() const {
        return count == 0;
    }

    // Checks if the vector is at full capacity
    bool full() const {
        return count == size;
    }

    // Adds element to the end, resizing if needed
    void push_back(T value) {
        if (full()) {
            resize();
        }
        array[count++] = value;
    }

    // Removes and returns the last element
    T pop_back() {
        if (!empty()) {
            return array[--count];
        } else {
            throw runtime_error("the array is empty");
        }
    }

    // Public resize function to manually change capacity
    void resize(int new_size) {
        if (new_size < count) {
            count = new_size; // Truncate elements if new size is smaller
        }
        T* temp = array;
        array = new T[new_size];
        for (int i = 0; i < count; i++) {
            array[i] = temp[i];
        }
        size = new_size;
        if (temp)
            delete[] temp;
    }

    // Returns a reference to the last element
    T& back() {
        if (!empty())
            return array[count - 1];
        else
            throw runtime_error("The array is empty");
    }
};

// Custom Priority Queue (Min-Heap) implementation using the vector class
class PriorityQueue {
    vector<Node> array; // The underlying array to store the heap elements

    // Swaps two nodes
    void swap(Node& x, Node& y) {
        Node temp = x;
        x = y;
        y = temp;
    }

    // Restores heap property by moving a node up the tree
    void prelocateUp(int i) {
        int parent = findParent(i);
        if (parent != -1 && array[parent] > array[i]) {
            swap(array[parent], array[i]);
            prelocateUp(parent);
        }
    }

    // Restores heap property by moving a node down the tree
    void prelocateDown(int i) {
        int left_child = findChildrenOne(i);
        int right_child = findChildrenTwo(i);
        int smallest = i;

        // Find the smallest child
        if (left_child < array.getSize() && array[left_child] < array[smallest]) {
            smallest = left_child;
        }
        if (right_child < array.getSize() && array[right_child] < array[smallest]) {
            smallest = right_child;
        }

        // If a swap is needed, perform it and continue down
        if (smallest != i) {
            swap(array[i], array[smallest]);
            prelocateDown(smallest);
        }
    }

    // Calculates index of left child (0-indexed heap: 2i + 1)
    int findChildrenOne(int i) {
        return (i * 2 + 1);
    }

    // Calculates index of right child (0-indexed heap: 2i + 2)
    int findChildrenTwo(int i) {
        return i * 2 + 2;
    }

    // Calculates index of parent (0-indexed heap: (i - 1) / 2)
    int findParent(int i) {
        if (i > 0) { 
            return (i - 1) / 2;
        } else {
            return -1; // Root node has no parent
        }
    }

    // Converts an arbitrary array into a valid heap (O(N) complexity)
    void buildHeap() {
        int sz = array.getSize();
        // Start from the last non-leaf node
        for (int i = (sz / 2) - 1; i >= 0; i--) {
            prelocateDown(i);
        }
    }

public:
    // Constructor that initializes the heap from a given vector
    PriorityQueue(vector<Node>arr) {
        // Copy elements
        for (int i = 0; i < arr.getSize(); i++) {
            array.push_back(arr[i]);
        }
        buildHeap(); // Build the heap structure
    }

    // Default constructor (creates an empty heap)
    PriorityQueue() {

    }

    // Adds a new element to the heap
    void insert(Node num) {
        array.push_back(num);
        prelocateUp(array.getSize() - 1); // Restore heap property
    }

    // Removes the minimum element (the root)
    void removeMin() {
        if (array.empty()) {
            throw runtime_error("PriorityQueue is empty");
        }
        array[0] = array.back(); // Move last element to root
        array.pop_back();        // Remove the duplicated element
        if (array.getSize() > 0) {
            prelocateDown(0);    // Restore heap property from the root
        }
    }

    // Returns the minimum element (without removing it)
    Node getMin() {
        if (array.empty()) {
            throw runtime_error("PriorityQueue is empty");
        }
        return array[0];
    }
    
    // Checks if the queue contains any elements
    bool empty() const {
        return array.empty();
    }
};
//function returns the frequency array from some string
//String s is better to contain all characters of s
vector<int> frequency_array(string s){
    //There are 96 characters in ASCII code. The first element 
    //has ascii code 32, which is ' '
    vector<int>freq(96,0);
    for(auto character : s){
        freq[character-' ']++;
    }
    return freq;
}
int main() {
    // Test the PriorityQueue (Min-Heap)
    PriorityQueue pq;
    
    // Insert nodes (data, frequency)
    pq.insert(Node(3, 5)); // Freq 5
    pq.insert(Node(1, 1)); // Freq 1 (Min)
    pq.insert(Node(4, 2)); // Freq 2

    // Get minimum frequency node
    cout << pq.getMin().data << endl; // Output: 1
    pq.removeMin(); // Remove node with Freq 1

    // New minimum is Freq 2
    cout << pq.getMin().data << endl; // Output: 4
    pq.removeMin(); // Remove node with Freq 2

    // New minimum is Freq 5
    cout << pq.getMin().data << endl; // Output: 3
    pq.removeMin(); // Remove node with Freq 5
    return 0;
}