#include <iostream>
#include <cstdint>
#include <fstream>

/*
 * Node for the red-black tree:
 * 
 * Colour of the node will be tagged with
 * the parent pointer (last bit of the address)
*/
class Node
{
    public:
        Node* parent;
        Node* left;
        Node* right;

        Node(Node* p) : left(nullptr), right(nullptr)
        {
            // Adding the colour red to the parent pointer
            uintptr_t parent_bits = reinterpret_cast<uintptr_t>(p) | 1;
            parent = reinterpret_cast<Node*> (parent_bits);
        }

        Node* getParent()
        {

        }

        void setParent()
        {
            
        }

        bool isRed()
        {

        }

        void changeColour()
        {

        }
};

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