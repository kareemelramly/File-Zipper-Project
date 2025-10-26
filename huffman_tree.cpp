#include<iostream>
#include<string>
#include<stdexcept> // Required for runtime_error and out_of_range
#include<utility> // Required for std::swap
#include<fstream>  //Required for file operations
#include<sstream>  // Required for string stream

//Special character for Huffman coding
#define INTERNAL_NODE_CHARACTER char(128)
#define PSEUDO_EOF char(129)
#define CHARACTER_CODE_SEPERATOR char(130)
#define HEADER_ENTRY_SEPERATOR char(131)
#define HEADER_TEXT_SEPERATOR char(132)
#define FIRST_ASCI_CHARACTER char(0)

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
    vector& operator=(const vector& other) {
        size = other.size;
        count=other.count;
        if(array)
            delete [] array;
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
    //There are 127 characters in printable ASCII code. The first element 
    //has ascii code 32, which is FIRST_ASCI_CHARACHTER
    vector<int>freq(127,0);
    for(auto character : s){
        freq[character-FIRST_ASCI_CHARACTER]++;
    }
    return freq;
}


// Huffman Coding class
class Huffman {

private:
    vector<string> codeMap;   //Maps character to their huffman codes
    //makes_sure the value of the casting is a correct value
    int convertToASCII(int value){
        if(value<0) return value+256;
        else return value;
    }

public:

    //Compress input file
    void CompressToFile(string inputFile, string outputFile)
    {

        // Error in case file can't be opened
        ifstream inputStream(inputFile);
        if (!inputStream) {
            throw runtime_error("Cannot open input file: " + inputFile);
        }
        string fileContent;
        char character;
        while (inputStream.get(character)) {
            fileContent += character;
        }
        inputStream.close();

        // Build frequency array and Huffman tree
        vector<int> freq = frequency_array(fileContent);
        Node* huffmanTree = BuildHuffmanTree(freq);

        // Initialize codeMap and generate codes
        codeMap = vector<string>(convertToASCII(PSEUDO_EOF - FIRST_ASCI_CHARACTER + 1), "");
        EncodeCharacters(huffmanTree, "");

        // Write compressed file
        ofstream outputStream(outputFile, ios::binary);
        WriteHeader(outputStream);

        //Encode text
        string encodedText;
        for (char c : fileContent) {
            int index = convertToASCII(c - FIRST_ASCI_CHARACTER);
            if (index >= 0 && index < codeMap.getSize()) {
                encodedText += codeMap[index];
            }
        }

        // Add PSEUDO_EOF
        encodedText += codeMap[convertToASCII(PSEUDO_EOF - FIRST_ASCI_CHARACTER)];

        // Pad with zeros to make complete bytes
        int remainder = encodedText.length() % 8;
        if (remainder != 0) {
            encodedText += string(8 - remainder, '0');
        }

        // Convert binary string to bytes and write
        for (size_t i = 0; i < encodedText.length(); i += 8) {
            string byteStr = encodedText.substr(i, 8);
            char byte = static_cast<char>(stoi(byteStr, nullptr, 2));
            outputStream.put(byte);
        }

        outputStream.close();
        delete huffmanTree;
    }

    private:

    //Generate haffman codes for characters by traversing the tree
    void EncodeCharacters(Node* rootnode, string code)
    {
        if (!rootnode)
            return;

        // If the node is a leaf node, it stores its code
        if (rootnode->data != INTERNAL_NODE_CHARACTER) {
            int index= convertToASCII(rootnode->data - FIRST_ASCI_CHARACTER);
            if (index >= 0 && index < codeMap.getSize()) {
                codeMap[index] = code;
            }

            return;
        }
        //Recursion call to traverse the tree
        EncodeCharacters(rootnode->left, code + "0");
        EncodeCharacters(rootnode->right, code + "1");

    }


    //Building Huffman tree based on codeMap
    Node* BuildHuffmanTree( vector<int>& freq) {
        PriorityQueue pq1;

        // Create leaf node for all characters that have frequency value
        for (int i=0; i< freq.getSize(); i++) {
            if (freq[i] > 0) {
                char character = static_cast<char>(convertToASCII(i + FIRST_ASCI_CHARACTER));
                pq1.insert(Node(character, freq[i]));
            }
        }

        //PSEUDO_EOF marker- end of the file
        pq1.insert(Node(PSEUDO_EOF, 1));

        //Build Huufman tree by combining nodes
        while (!pq1.empty()) {
            Node left= pq1.getMin();
            pq1.removeMin();

            if (pq1.empty()) {
                return new Node(left);
            }
            Node right= pq1.getMin();
            pq1.removeMin();

            //Create Internal node by summing frequency
            Node* internalNode= new Node(INTERNAL_NODE_CHARACTER, left.frequency + right.frequency, new Node(left),new Node(right));
            pq1.insert(*internalNode);

        }
        return nullptr;
    }





    //Write a header line with the characters and their huffman codes
    void WriteHeader(ofstream& outputStream)
    {
        for (int i=0; i< codeMap.getSize(); i++) {
            if (!codeMap[i].empty()) {
                char character= static_cast<char>(i + FIRST_ASCI_CHARACTER);
                outputStream.put(character);
                outputStream.put(CHARACTER_CODE_SEPERATOR);
                outputStream << codeMap[i];
                outputStream.put(HEADER_ENTRY_SEPERATOR);
            }
        }
        outputStream.put(HEADER_TEXT_SEPERATOR);
    }

    // Decompress binary string to file
    void DecompressToFile(string codeString, Node* rootNode, string decompressedFileName) {
        ofstream outputStream(decompressedFileName);
        if (!outputStream) {
            throw runtime_error("Cannot open output file: " + decompressedFileName);
        }

        Node* currentNode = rootNode;
        for (size_t i = 0; i < codeString.length(); i++) {
            if (codeString[i] == '0') {
                if(currentNode->left)
                currentNode = currentNode->left;
                else break;
            } else {
                if(currentNode->right)
                currentNode = currentNode->right;
                else break;
            }

            if (!currentNode->left && !currentNode->right) {
                if (currentNode->data == PSEUDO_EOF) {
                    break;
                }
                outputStream.put(currentNode->data);
                currentNode = rootNode;
            }
        }

        outputStream.close();
    }

    public:
    //Function to decompress files
    void DecompressFile(string compressedfile, string decompressedfile)
    {
        //Check if the compressed file can be opened
        ifstream inputStream(compressedfile, ios::binary);
        if (!inputStream) {
            throw runtime_error("Cannot open compressed file: " + compressedfile);
        }

        ReadHeader(inputStream);
        string codeString;

        //Convert bytes to binary string
        char byte;
        while (inputStream.get(byte)) {
            for (int i=7; i>=0; i--) {
                codeString += (byte & (1 << i)) ? '1' : '0';
            }
        }
        inputStream.close();

        Node* rootNode= BuildDecodingTree();
        DecompressToFile(codeString, rootNode, decompressedfile);
        delete rootNode;

    }
    private:
    // Read header and reconstruct codeMap
    void ReadHeader(ifstream& inputStream) {
        vector<string>freq(127, " ");
        codeMap = freq;
        char character;
        inputStream.get(character);
        char key = character;

        while (character != HEADER_TEXT_SEPERATOR) {
            if (character == CHARACTER_CODE_SEPERATOR) {
                string code;
                inputStream.get(character);
                while (character != HEADER_ENTRY_SEPERATOR) {
                    code += character;
                    inputStream.get(character);
                }
                int index = convertToASCII(key - FIRST_ASCI_CHARACTER);
                if (index >= 0 && index < codeMap.getSize()) {
                    codeMap[index] = code;
                }
            } else {
                key = character;
            }
            inputStream.get(character);
        }
    }

    // Build decoding tree from codeMap
    Node* BuildDecodingTree() {
        Node* rootNode = new Node(INTERNAL_NODE_CHARACTER, 0);

        for (int i = 0; i < codeMap.getSize(); i++) {
            if (!codeMap[i].empty()) {
                char character = static_cast<char>(i + FIRST_ASCI_CHARACTER);
                Node* currentNode = rootNode;
                string code = codeMap[i];

                for (size_t j = 0; j < code.length(); j++) {
                    if (code[j] == '0') {
                        if (!currentNode->left) {
                            currentNode->left = new Node(INTERNAL_NODE_CHARACTER, 0);
                        }
                        currentNode = currentNode->left;
                    } else {
                        if (!currentNode->right) {
                            currentNode->right = new Node(INTERNAL_NODE_CHARACTER, 0);
                        }
                        currentNode = currentNode->right;
                    }
                }
                // Set the character at the leaf node
                currentNode->data = character;
            }
        }
        return rootNode;
    }




};
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

    //Test Huffman
    try{
    Huffman Test;
    Test.CompressToFile("test.txt","output.txt");
    Test.DecompressFile("output.txt","final_result.txt");
    }catch(...){
        cout<<"lol\n";
    }
    return 0;
}