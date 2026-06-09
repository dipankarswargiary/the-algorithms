#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>

#define RED 1ull
#define BLACK 0ull

/*
 * Node for the red-black tree:
 * 
 * Colour of the node will be tagged with
 * the parent pointer (last bit of the address)
*/
class alignas(8) Node
{
    public:
        std::string name;   // Payload
        Node* left;
        Node* right;

        // Contains the parent's address and the colour
        Node* parent_and_colour;

        // Helper methods
        Node(std::string n);
        Node* getParent();
        void setParent(Node* new_parent);
        uintptr_t getColour();
        void setColour(uintptr_t new_colour);
};

Node::Node(std::string n) : parent_and_colour(nullptr), left(nullptr), right(nullptr), name(n)
{
    // Colouring the node RED
    parent_and_colour = reinterpret_cast<Node*> (RED);
}

Node* Node::getParent()
{
    uintptr_t clean_parent = reinterpret_cast<uintptr_t> (parent_and_colour) & ~(1ull);
    return reinterpret_cast<Node*> (clean_parent);
}

void Node::setParent(Node* new_parent)
{
    uintptr_t tagged_parent = reinterpret_cast<uintptr_t> (new_parent) | getColour();
    parent_and_colour = reinterpret_cast<Node*> (tagged_parent);
}

uintptr_t Node::getColour()
{
    return reinterpret_cast<uintptr_t> (parent_and_colour) & 1ull;
}

void Node::setColour(uintptr_t new_colour)
{
    uintptr_t parent = reinterpret_cast<uintptr_t> (getParent());
    parent_and_colour = reinterpret_cast<Node*> (parent | new_colour);
}

int main(int argc, char* argv[])
{
    // Command validation
    if (argc != 2)
    {
        std::cerr << "Error: No file is provided." << std::endl;
        return 1;
    }

    std::string inputFileName = argv[1];

    std::ifstream inputFileObj(inputFileName);

    if (!inputFileObj.is_open())
    {
        std::cerr << "Error: Failed to open file - " << inputFileName << std::endl;
        return 1;
    }

    // 26 pointers for 26 alphabet letters
    Node* list[26] {nullptr};


}