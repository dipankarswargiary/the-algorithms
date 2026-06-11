#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>
#include <cctype>

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
        Node(const std::string& n);
        Node* getParent();
        void setParent(Node* new_parent);
        uintptr_t getColour();
        void setColour(uintptr_t new_colour);
        bool isGreaterThan(Node& node);
};

Node::Node(const std::string& n) : parent_and_colour(nullptr), left(nullptr), right(nullptr), name(n)
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

bool Node::isGreaterThan(Node& node)
{
    return (name > node.name);
}

// This function will remove extra whitespaces and convert
// the names into lower case for ease string comparison
void reduceName(std::string& name)
{
    int writeIndex = 0;
    bool needSpace = false;

    for (int readIndex = 0; readIndex < name.size(); ++readIndex)
    {
        if (std::isspace(static_cast<unsigned char> (name[readIndex])))
        {
            if (writeIndex > 0) {
                needSpace = true;
            }
        }
        else
        {
            if(needSpace) {
                name[writeIndex] = ' ';
                ++writeIndex; 
                needSpace = false;
            }
            name[writeIndex] = std::tolower(static_cast<unsigned char> (name[readIndex]));
            ++writeIndex;
        }
    }

    name.erase(writeIndex);
}

// TODO: Yet to implement the insert function
void insert(const std::string& name, Node*& root)
{
    Node* node = new Node(name);
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

    std::string name;

    while (getline(inputFileObj, name))
    {
        reduceName(name);

        if (!name.empty() && (name[0] - 97) < 0)
        {
            Node* root = list[name[0] - 97];
            insert(name, root);
        }
    }

    // TODO: write the sorted names into a file
    
    inputFileObj.close();
    return 0;
}