/**
 * @file huffman_tree.cpp
 * Implementation of a Huffman Tree class.
 *
 * @author Chase Geigle
 * @date Summer 2012
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>

#include "huffman_tree.h"

using namespace std;

HuffmanTree::HuffmanTree(vector<Frequency> frequencies)
{
    std::stable_sort(frequencies.begin(), frequencies.end());
    buildTree(frequencies);
    vector<bool> path;
    buildMap(root_, path);
}

HuffmanTree::HuffmanTree(const HuffmanTree& other)
{
    copy(other);
}

HuffmanTree::HuffmanTree(BinaryFileReader& bfile)
{
    root_ = readTree(bfile);
    vector<bool> path;
    buildMap(root_, path);
}

HuffmanTree::~HuffmanTree()
{
    clear(root_);
}

const HuffmanTree& HuffmanTree::operator=(const HuffmanTree& rhs)
{
    if (this != &rhs) {
        clear(root_);
        copy(rhs);
    }
    return *this;
}

void HuffmanTree::clear(TreeNode* current)
{
    if (current == NULL)
        return;
    clear(current->left);
    clear(current->right);
    delete current;
}

void HuffmanTree::copy(const HuffmanTree& rhs)
{
    root_ = copy(rhs.root_);
}

HuffmanTree::TreeNode* HuffmanTree::copy(const TreeNode* current)
{
    if (current == NULL)
        return NULL;
    TreeNode* node = new TreeNode(current->freq);
    node->left = copy(current->left);
    node->right = copy(current->right);
    return node;
}

HuffmanTree::TreeNode*
HuffmanTree::removeSmallest(queue<TreeNode*>& singleQueue,
                            queue<TreeNode*>& mergeQueue)
{
     TreeNode * current;
     if (mergeQueue.empty() == true && singleQueue.empty() == false) {
       current = singleQueue.front();
       singleQueue.pop();
     }
     if (mergeQueue.empty() == false && singleQueue.empty() == true) {
       current = mergeQueue.front();
       mergeQueue.pop();
     }
     if (singleQueue.empty() == false) {
       if (mergeQueue.empty() == false) {
         if(mergeQueue.front() -> freq.getFrequency() <= singleQueue.front() -> freq.getFrequency()) {
           current = mergeQueue.front();
           mergeQueue.pop();
         }
         else {
           current = singleQueue.front();
           singleQueue.pop();
         }
       }
     }
     bool a = true;
     bool b = false;
     if (a) {
       if (!b) {
         return current;
       }
     }
     return NULL;
}

void HuffmanTree::buildTree(const vector<Frequency>& frequencies)
{
    queue<TreeNode*> singleQueue;
    queue<TreeNode*> mergeQueue;
     TreeNode * a;
     unsigned count = 0;
     while(count < frequencies.size()) {
       a = new TreeNode(frequencies[count]);
       singleQueue.push(a);
       count++;
	   }
     TreeNode * b;
     TreeNode * c;
     while (singleQueue.size() + mergeQueue.size() > 1) {
       b = removeSmallest(singleQueue, mergeQueue);
       if (singleQueue.size() + mergeQueue.size() > 0) {
    c = removeSmallest(singleQueue, mergeQueue);
       }
       a = new TreeNode(b -> freq.getFrequency() + c -> freq.getFrequency());
       if (a && b && c) {
         a -> left = b;
         a -> right = c;
         mergeQueue.push(a);
       }
     }
     if (mergeQueue.front() != NULL) {
       root_ = mergeQueue.front();
       mergeQueue.pop();
     }
}

string HuffmanTree::decodeFile(BinaryFileReader& bfile)
{
    stringstream ss;
    decode(ss, bfile);
    return ss.str();
}

void HuffmanTree::decode(stringstream& ss, BinaryFileReader& bfile)
{
    TreeNode * checkAgainst = root_;
    while (!(!(bfile.hasBits()))) {
         if (bfile.getNextBit()) {
           checkAgainst = checkAgainst -> right;
         }
         else {
           checkAgainst = checkAgainst -> left;
         }
         if (!(checkAgainst -> left)) {
           if (!(checkAgainst -> right != NULL)) {
             ss << checkAgainst -> freq.getCharacter();
             checkAgainst = root_;
           }
         }
    }
}

void HuffmanTree::writeTree(BinaryFileWriter& bfile)
{
    writeTree(root_, bfile);
}

void HuffmanTree::writeTree(TreeNode* current, BinaryFileWriter& bfile)
{
       if (!(current -> left)) {
         if (!(current -> right)) {
           bfile.writeBit(1);
           bfile.writeByte(current -> freq.getCharacter());
         }
       }
       else {
         bfile.writeBit(0);
         if (current -> left) {
           writeTree(current -> left, bfile);
         }
         if (current -> right) {
           writeTree(current -> right, bfile);
         }
       }
}

HuffmanTree::TreeNode* HuffmanTree::readTree(BinaryFileReader& bfile)
{
     if (bfile.getNextBit()) {
       TreeNode * a = new TreeNode(Frequency(bfile.getNextByte(), 0));
       return a;
     }
     else {
       TreeNode * a = new TreeNode(0);
       a -> left = readTree(bfile);
       a -> right = readTree(bfile);
       return a;
     }
     return NULL;
}

void HuffmanTree::buildMap(TreeNode* current, vector<bool>& path)
{
    // Base case: leaf node.
    if (current->left == NULL && current->right == NULL) {
        bitsMap_[current->freq.getCharacter()] = path;
        return;
    }

    // Move left
    path.push_back(false);
    buildMap(current->left, path);
    path.pop_back();

    // Move right
    path.push_back(true);
    buildMap(current->right, path);
    path.pop_back();
}

void HuffmanTree::printInOrder() const
{
    printInOrder(root_);
    cout << endl;
}

void HuffmanTree::printInOrder(const TreeNode* current) const
{
    if (current == NULL)
        return;
    printInOrder(current->left);
    cout << current->freq.getCharacter() << ":" << current->freq.getFrequency()
         << " ";
    printInOrder(current->right);
}

void HuffmanTree::writeToFile(const string& data, BinaryFileWriter& bfile)
{
    for (auto it = data.begin(); it != data.end(); ++it)
        writeToFile(*it, bfile);
}

void HuffmanTree::writeToFile(char c, BinaryFileWriter& bfile)
{
    vector<bool> bits = getBitsForChar(c);
    for (auto it = bits.begin(); it != bits.end(); ++it)
        bfile.writeBit(*it);
}

vector<bool> HuffmanTree::getBitsForChar(char c)
{
    return bitsMap_[c];
}

// class for generic printing

template <typename TreeNode>
class HuffmanTreeNodeDescriptor
    : public GenericNodeDescriptor<HuffmanTreeNodeDescriptor<TreeNode>>
{
  public:
    HuffmanTreeNodeDescriptor(const TreeNode* root) : subRoot_(root)
    { /* nothing */
    }

    string key() const
    {
        std::stringstream ss;
        char ch = subRoot_->freq.getCharacter();
        int freq = subRoot_->freq.getFrequency();

        // print the sum of the two child frequencies
        if (ch == '\0')
            ss << freq;
        // print the leaf containing a character and its count
        else {
            if (ch == '\n')
                ss << "\\n";
            else
                ss << ch;
            ss << ":" << freq;
        }
        return ss.str();
    }

    bool isNull() const
    {
        return subRoot_ == NULL;
    }
    HuffmanTreeNodeDescriptor left() const
    {
        return HuffmanTreeNodeDescriptor(subRoot_->left);
    }
    HuffmanTreeNodeDescriptor right() const
    {
        return HuffmanTreeNodeDescriptor(subRoot_->right);
    }

  private:
    const TreeNode* subRoot_;
};

int HuffmanTree::height(const TreeNode* subRoot) const
{
    if (subRoot == NULL)
        return -1;
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

void HuffmanTree::print(std::ostream& out) const
{
    int h = height(root_);
    if (h > _max_print_height) {
        out << "Tree is too big to print. Try with a small file (e.g. "
               "data/small.txt)"
            << endl;
        return;
    }

    printTree(HuffmanTreeNodeDescriptor<TreeNode>(root_), out);
}

Frequency
HuffmanTree::testRemoveSmallest(vector<Frequency> single,
                                vector<Frequency> merge)
{
    queue<TreeNode*> singleQueue;
    queue<TreeNode*> mergeQueue;
    for (auto it = single.begin(); it != single.end(); ++it) {
         singleQueue.push(new TreeNode(*it));
    }
    for (auto it = merge.begin(); it != merge.end(); ++it) {
         mergeQueue.push(new TreeNode(*it));
    }

    TreeNode* testNode = removeSmallest(singleQueue, mergeQueue);
    Frequency testFreq = testNode->freq;

    delete testNode;
    while (!singleQueue.empty()) {
        delete singleQueue.front();
        singleQueue.pop();
    }
    while (!mergeQueue.empty()) {
        delete mergeQueue.front();
        mergeQueue.pop();
    }

    return testFreq;
}
