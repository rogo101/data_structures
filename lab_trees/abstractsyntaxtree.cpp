#include "abstractsyntaxtree.h"

using namespace std;
/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...
  return evalHelper(getRoot());
}
double AbstractSyntaxTree::evalHelper(Node * subRoot) const {
  if (subRoot == NULL) {
    return 0.0;
  }
  //cout << std::stod(subRoot -> elem) << endl;
  if ((subRoot -> elem) != "+" && (subRoot -> elem) != "-" && (subRoot -> elem) != "*" && (subRoot -> elem) != "/") {
    return std::stod(subRoot -> elem);
  }
  else {
    if (subRoot -> elem == "+")
      return (evalHelper(subRoot -> left) + evalHelper(subRoot -> right));
    else if (subRoot -> elem == "-")
      return (evalHelper(subRoot -> left) - evalHelper(subRoot -> right));
    else if (subRoot -> elem == "*")
      return (evalHelper(subRoot -> left) * evalHelper(subRoot -> right));
    else
      return (evalHelper(subRoot -> left) / evalHelper(subRoot -> right));
  }
}
