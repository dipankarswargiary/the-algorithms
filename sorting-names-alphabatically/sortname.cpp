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
 * 
 * (alignas(8) guarantees the memory address is
 * multiple of 8 - which makes the address's last
 * bits 000 - which makes pointer tagging possible)
 */// alignas(8) guarantees the memory address is multiple of 8 
class alignas(8) Node
{
    private:
        // Contains the parent's address and the colour
        Node* parent_and_colour;

    public:
        std::string name;   // Payload
        Node* left;
        Node* right;

        // Helper methods
        Node(const std::string& n);
        Node* getParent();
        void setParent(Node* new_parent);
        uintptr_t getColour();
        void setColour(uintptr_t new_colour);
        bool isGreaterThan(const Node& node) const;
};

// By default a node is created black
Node::Node(const std::string& n) : parent_and_colour(nullptr),
                                   left(nullptr),
                                   right(nullptr),
                                   name(n) {}

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

bool Node::isGreaterThan(const Node& node) const
{
    return (name > node.name);
}


// The tree class
class RedBlackTree
{
    public:
        Node* root;
        Node* NIL;

        RedBlackTree();
        void insert(const std::string& name);
        void insertFixup(Node* z);

    private:
        void leftRotate(Node* x);
        void rightRotate(Node* x);
};

RedBlackTree::RedBlackTree() : NIL(new Node(""))
{
    root = NIL;
}

void RedBlackTree::insert(const std::string& name)
{
    Node* x {root};
    Node* y {NIL};
    Node* z = new Node(name);
    
    while (x != NIL)
    {
        y = x;
        if (x->isGreaterThan(*z))
            x = x->left;
        else
            x = x->right;
    }
    
    z->setParent(y);
    if (y == NIL)
        root = z;
    else if (y->isGreaterThan(*z))
        y->left = z;
    else
        y->right = z;
    
    z->left = NIL;
    z->right = NIL;
    z->setColour(RED);
    insertFixup(z);
}

void RedBlackTree::insertFixup(Node* z)
{
    while (z->getParent()->getColour() == RED)
    {
        Node* parent = z->getParent();
        Node* grandParent = parent->getParent();

        if (parent == grandParent->left)
        {
            Node* uncle = grandParent->right;

            if (uncle->getColour() == RED)
            {
                parent->setColour(BLACK);
                uncle->setColour(BLACK);
                grandParent->setColour(RED);
                z = grandParent;
            }
            else
            {
                // Uncle BLACK and Triangle
                if (z == parent->right)
                {
                    z = parent;
                    leftRotate(z);
                }
                
                parent->setColour(BLACK);
                grandParent->setColour(RED);
                rightRotate(grandParent);
            }
        }
        else
        {
            Node* uncle = parent->left;
            
            if (uncle->getColour() == RED)
            {
                parent->setColour(BLACK);
                grandParent->setColour(RED);
                uncle->setColour(BLACK);
                z = grandParent;
            }
            else
            {
                // Uncle is BLACK and forms a triangle
                if (z == parent->left)
                {
                    z = parent;
                    rightRotate(z);
                }

                parent->setColour(BLACK);
                grandParent->setColour(RED);
                leftRotate(grandParent);
            }
        }
    }

    // Recolouring the root in case it become RED
    root->setColour(BLACK);
}

void RedBlackTree::leftRotate(Node* x)
{
    Node* y = x->right;

    x->right = y->left;
    if (y->left != NIL)
        y->left->setParent(x);
    
    if (x->getParent() == NIL)
    {
        root = y;
        y->setParent(NIL);
    }
    else if(x == x->getParent()->right)
        x->getParent()->right = y;
    else
        x->getParent()->left = y;
    
    y->setParent(x->getParent());
    y->left = x;
    x->setParent(y);
}

void RedBlackTree::rightRotate(Node* x)
{
    Node* y = x->left;

    x->left = y->right;
    if (y->right != NIL)
        y->right->setParent(x);
    
    if (x->getParent() == NIL)
    {
        root = y;
        y->setParent(NIL);
    }
    else if(x == x->getParent()->right)
        x->getParent()->right = y;
    else
        x->getParent()->left = y;
    
    y->setParent(x->getParent());
    y->right = x;
    x->setParent(y);
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
            if (writeIndex > 0)
                needSpace = true;
        }
        else
        {
            if(needSpace)
            {
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
    RedBlackTree* list[26] {nullptr};

    std::string name;

    while (getline(inputFileObj, name))
    {
        reduceName(name);

        if (!name.empty() && std::islower(name[0]))
        {
            if (list[name[0] - 97] == nullptr)
                list[name[0] - 97] = new RedBlackTree();
            
            RedBlackTree* tree = list[name[0] - 97];
            tree->insert(name);
        }
    }

    // TODO: write the sorted names into a file
    
    inputFileObj.close();
    return 0;
}