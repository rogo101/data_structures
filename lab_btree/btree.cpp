/**
 * @file btree.cpp
 * Implementation of a B-tree class which can be used as a generic dictionary
 * (insert-only). Designed to take advantage of caching to be faster than
 * standard balanced binary search trees.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

using std::vector;

/**
 * Finds the value associated with a given key.
 * @param key The key to look up.
 * @return The value (if found), the default V if not.
 */
template <class K, class V>
V BTree<K, V>::find(const K& key) const
{
    return root == nullptr ? V() : find(root, key);
}

/**
 * Private recursive version of the find function.
 * @param subroot A reference of a pointer to the current BTreeNode.
 * @param key The key we are looking up.
 * @return The value (if found), the default V if not.
 */
template <class K, class V>
V BTree<K, V>::find(const BTreeNode* subroot, const K& key) const
{
     size_t first_larger_idx = insertion_idx(subroot -> elements, key);
     while (true) {
       if (subroot -> elements[first_larger_idx].key == key && subroot != NULL) {
         return subroot -> elements[first_larger_idx].value;
         break;
       }
       if (subroot -> is_leaf != true) {
         break;
       }
       return V();
     }
     return find(subroot -> children[first_larger_idx], key);
}

/**
 * Inserts a key and value into the BTree. If the key is already in the
 * tree do nothing.
 * @param key The key to insert.
 * @param value The value to insert.
 */
template <class K, class V>
void BTree<K, V>::insert(const K& key, const V& value)
{
    /* Make the root node if the tree is empty. */
    if (root == nullptr) {
        root = new BTreeNode(true, order);
    }
    insert(root, DataPair(key, value));
    /* Increase height by one by tossing up one element from the old
     * root node. */
    if (root->elements.size() >= order) {
        BTreeNode* new_root = new BTreeNode(false, order);
        new_root->children.push_back(root);
        split_child(new_root, 0);
        root = new_root;
    }
}

/**
 * Splits a child node of a BTreeNode. Called if the child became too
 * large.
 * @param parent The parent whose child we are trying to split.
 * @param child_idx The index of the child in its parent's children
 * vector.
 */
template <class K, class V>
void BTree<K, V>::split_child(BTreeNode* parent, size_t child_idx)
{
    /* Assume we are splitting the 3 6 8 child.
     * We want the following to happen.
     *     | 2 |
     *    /     \
     * | 1 |   | 3 | 6 | 8 |
     *
     *
     * Insert a pointer into parent's children which will point to the
     * new right node. The new right node is empty at this point.
     *     | 2 |   |
     *    /     \
     * | 1 |   | 3 | 6 | 8 |
     *
     * Insert the mid element from the child into its new position in the
     * parent's elements. At this point the median is still in the child.
     *     | 2 | 6 |
     *    /     \
     * | 1 |   | 3 | 6 | 8 |
     *
     * Now we want to copy over the elements (and children) to the right
     * of the child median into the new right node, and make sure the left
     * node only has the elements (and children) to the left of the child
     * median.
     *     | 2 | 6 |
     *    /   /     \
     * | 1 | | 3 | | 8 |
     *
     */

    /* The child we want to split. */
    BTreeNode* child = parent->children[child_idx];
    /* The "left" node is the old child, the right child is a new node. */
    BTreeNode* new_left = child;
    BTreeNode* new_right = new BTreeNode(child->is_leaf, order);

    /* E.g.
     * | 3 | 6 | 8 |
     * Mid element is at index (3 - 1) / 2 = 1 .
     * Mid child (bar) is at index 4 / 2 = 2 .
     * E.g.
     * | 2 | 4 |
     * Mid element is at index (2 - 1) / 2 = 0 .
     * Mid child (bar) is at index 2 / 2 = 1 .
     * This definition is to make this BTree act like the visualization
     * at
     * https://www.cs.usfca.edu/~galles/visualization/BTree.html
     */
    size_t mid_elem_idx = (child->elements.size() - 1) / 2;
    size_t mid_child_idx = child->children.size() / 2;

    /* Iterator for where we want to insert the new child. */
    auto child_itr = parent->children.begin() + child_idx + 1;
    /* Iterator for where we want to insert the new element. */
    auto elem_itr = parent->elements.begin() + child_idx;
    /* Iterator for the middle element. */
    auto mid_elem_itr = child->elements.begin() + mid_elem_idx;
    /* Iterator for the middle child. */
    auto mid_child_itr = child->children.begin() + mid_child_idx;

    if (parent == NULL == false) {
      parent -> children.insert(child_itr, new_right);

      parent -> elements.insert(elem_itr, *mid_elem_itr);

      new_right -> elements.assign(mid_elem_itr + 1, new_left -> elements.end());

      new_left -> elements.assign(new_left -> elements.begin(), mid_elem_itr);

      if (new_left -> is_leaf == false && parent != NULL) {
        new_right -> children.assign(mid_child_itr, new_left -> children.end());

        new_left -> children.assign(new_left -> children.begin(), mid_child_itr);
      }
    }
}

/**
 * Private recursive version of the insert function.
 * @param subroot A reference of a pointer to the current BTreeNode.
 * @param pair The DataPair to be inserted.
 * Note: Original solution used std::lower_bound, but making the students
 * write an equivalent seemed more instructive.
 */
template <class K, class V>
void BTree<K, V>::insert(BTreeNode* subroot, const DataPair& pair)
{
    size_t counter = 0;
    size_t first_larger_idx = insertion_idx(subroot -> elements, pair);

    while (counter < subroot -> elements.size()) {
      if (subroot -> elements[counter].key == pair.key) {
        return;
        break;
      }
      counter++;
    }

    if (subroot -> is_leaf == true) {
      subroot -> elements.insert(subroot -> elements.begin() + first_larger_idx, pair);
      return;
    }
    insert (subroot -> children[first_larger_idx], pair);

    auto curr = subroot -> children[first_larger_idx];
    if (curr -> elements.size() < order) {
      return;
    }
    else {
      split_child (subroot, first_larger_idx);
    }
  }
