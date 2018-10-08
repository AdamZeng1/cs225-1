#include "abstractsyntaxtree.h"
#include <string>

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...
    return eval(root);
}

double AbstractSyntaxTree::eval(typename BinaryTree<std::string>::Node* root) const {
	if (root->elem == "+") return eval(root->left) + eval(root->right);
	else if (root->elem == "-") return eval(root->left) - eval(root->right);
	else if (root->elem == "*") return eval(root->left) * eval(root->right);
	else if (root->elem == "/") return eval(root->left) / eval(root->right);
	else {return std::stod(root->elem);}
}
