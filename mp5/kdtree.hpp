/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

/* The following required function determines if the first points
has a smalled value than the second in whatever dimension inputed.*/

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */

     bool a = first[curDim] == second[curDim];
     bool b = first[curDim] >= second[curDim];
     if (a) {
       return !(first >= second);
     }
     else {
       return !b;
     }
}

/* The following required function determines if a point has a
better euclidean distance to target than the current best.*/

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currenta,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */

     int a , b, one, two, count;
     a = 0;
     b = 0;
     for (count = 0; count < Dim; count++) {
       one = target[count] - currenta[count];
       two = target[count] - potential[count];
       a = a + one * one;
       b = b + two * two;
     }
     bool check1 = a == b;
     if (check1) {
       return !(potential >= currenta);
     }
     return !(b >= a);
}

/* The following required constructor constructs a KD tree with a pointer
to root.*/

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     size = 0;
     size = newPoints.size();
     points = newPoints;
     root = NULL;
     treeConstructor(0, size - 1, 0);
     root = createRootPointer(0, size - 1);
}

/* The following required constructor copies a KD tree with a pointer
to root.*/

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   size = 0;
   size = other.size;
   points = other.Points;
   root = NULL;
   treeConstructor(0, size - 1, 0);
   root = createRootPointer(0, size - 1);

}

/* The following helper fucntion recursively constructs a tree.*/

template <int Dim>
void KDTree<Dim>::treeConstructor(int s, int e, int d) {
  while (s <= e) {
    Select(s, e, d, (s + e) * .5);
    if (e > (s + e) * .5 + 1) {
      treeConstructor(((s + e) * .5 + 1), e, (d + 1) % Dim);
    }
    if (s < (s + e) * .5 - 1) {
      treeConstructor( s, ((s + e) * .5 - 1), (d + 1) % Dim);
    }
    break;
  }
}

/* The following required operator defines setting one tree/object placeholder equal to another.*/

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
   
   _destroy(root);
   this = new KDTree(rhs);
   return *this;

}

/* The following required destructor frees up memory allocated by the tree.*/

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   _destroy(root);
}

/* The following helper fucntion recursively deletes a tree.*/

template <int Dim>
void KDTree<Dim>::_destroy(KDTreeNode* value){
  KDTreeNode* hasToBeDeleted = value;
  if(hasToBeDeleted==NULL){
    return;
  }
  else {
    if(hasToBeDeleted->left != NULL){
      _destroy(hasToBeDeleted->left);
    }
    if(hasToBeDeleted->right != NULL){
      _destroy(hasToBeDeleted->right);
    }
  }
  delete hasToBeDeleted;
}

/* The following helper fucntion is employed by findNearestNeighbor to recursively
locate the nearest neighbor.*/

template <int Dim>
Point<Dim> KDTree<Dim>::recursiveLocator(int s, int e, int d, const Point<Dim> & a, const Point<Dim> & b) const {
    int median = (s + e) / 2, temp = 0, i;
    bool check = true;
    Point<Dim> value = a;
    if (s == e && shouldReplace(b, a, points[s]) == true) {
        value = points[s];
        return value;
    }
    else if (s == e) {
      return a;
    }
    if (smallerDimVal(points[median], b, d) == true && e > median) {
      value = recursiveLocator((median + 1), e, ((d + 1) % Dim), a, b);
      check = false;
    }
    if (smallerDimVal(b, points[median], d) == true && s < median) {
      value = recursiveLocator(s, (median - 1), ((d + 1) % Dim), a, b);
      check = true;
    }
    if (shouldReplace (b, value, points[median]) == true) {
      value = points[median];
    }

    for (i = 0; i < Dim; i++) {
      int one = b[i] - value[i];
      temp = temp + one * one;
    }
    int two = points[median][d] - b[d];
    if(!(two * two > temp)) {
      if (check == true) {
        if (e > median) {
          value = recursiveLocator ((median + 1), e, ((d + 1) % Dim), value, b);
        }
      }
      else {
        if (s < median) {
            value = recursiveLocator (s, (median - 1), ((d + 1) % Dim), value, b);
        }
      }
    }
    return value;
}

/* The following required fucntion takes a point and determines the point in the
tree that is coleses to it.*/

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return recursiveLocator(0, size - 1, 0, points[(size - 1) *.5], query);
}

/*The following helper function quickselects the median of a value with respect to constraints upon it*/

template <int Dim>
void KDTree<Dim>::Select(int s, int e, int d, int pointerCheckValue) {

    int a = s;
    if (s < e) {
      int i = 0;
      Point<Dim> placeHolderOne = points[(s + e) * .5];
      Point<Dim> placeHolderTwo = points[(s + e) * .5];
      points[(s + e) * .5] = points[e];
      points[e] = placeHolderOne;

      for (i = s; i <= e; i++) {
        if (smallerDimVal(points[i], placeHolderTwo, d) == true) {
          Point<Dim> placeHolderThree = points[a];
          points[a] = points[i];
          points[i] = placeHolderThree;
          a++;
        }
        else {
          continue;
        }
      }
      if (s != e) {
        Point<Dim> placeHolderFour = points[e];
        points[e] = points[a];
        points[a] = placeHolderFour;
      }
    }
    else {
      return;
    }
    if (pointerCheckValue == a) {
      return;
    }
    else {
      if (pointerCheckValue < a) {
        Select(s, (a - 1), d, pointerCheckValue);
      }
      else {
        Select((a + 1), e, d, pointerCheckValue);
      }
    }
}

/* The following helper function returns a pointer to the root of the tree*/

template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::createRootPointer(int s, int e) {
  if (e >= s) {
    int location = (s + e) * .5, comparator = (int) points.size();
    if (location < comparator) {
      if (location >= 0) {
        KDTree<Dim>::KDTreeNode * newNode = new KDTree<Dim>::KDTreeNode(points[location]);
        newNode -> left = createRootPointer(s, (location - 1));
        newNode -> right = createRootPointer((location + 1), e);
        return newNode;
      }
    }
  }
  return NULL;

}
