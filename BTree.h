#include <iostream>
#ifndef BTREE_H
#define BTREE_H

#include "Node.h"

class BTree{
    private:
        Node* root;
        int size;
        Node* helperInsert(Node* node, int key){
            if(node == nullptr){
                size++;
                return new Node(key);
            }

            if (key < node->key){
                node->left = helperInsert(node->left, key);
            }

            else if (key > node->key){
                node->right = helperInsert(node->right, key);
            }
            updateHeight(node);
            int balance = getBalance(node);
            if(balance > 1){
                if(getBalance(node->left) >= 0){
                    return rightRotate(node);
                }else if(getBalance(node->left) < 0){
                    node->left = leftRotate(node->left);
                    return rightRotate(node);
                }
            }
            else if(balance < -1){
                if(getBalance(node->right) <= 0){
                    return leftRotate(node);
                }
                else if(getBalance(node->right) > 0){
                    node->right = rightRotate(node->right);
                    return leftRotate(node);
                }
            }
            return node;

        }

        void helperInOrder (Node* node){
            if (node == nullptr){
                return;
            }

            helperInOrder(node->left);
            std::cout << node->key << std::endl;
            helperInOrder(node->right);
        }

        Node* helperFind(Node* node, int key){
            if (node == nullptr){
                return nullptr;
            }
            if (key == node->key){
                return node;
            }
            if(key < node->key){
                return helperFind(node->left, key);
            }
            return helperFind(node->right, key);
        }

        Node* helperRemove(Node* node, int key){
            if (node == nullptr){
                return nullptr;
            }
            else if (key < node->key){
                node->left = helperRemove(node->left, key);
            }
            else if (key > node->key){
                node->right = helperRemove(node->right, key);
            }
            else{
                if(!node->left && !node->right){
                    size--;
                    delete node;
                    return nullptr;
                }
                else if(node->left && !node->right){
                    size--;
                    Node* tempNode = node->left;
                    delete node;
                    return tempNode;
                }
                else if(!node->left && node->right){
                    size--;
                    Node* tempNode = node->right;
                    delete node;
                    return tempNode;
                }
                else{
                    Node* successorNode = node->right;
                    while(successorNode->left != nullptr){
                        successorNode = successorNode->left;
                    }

                    node->key = successorNode->key;
                    node->right = helperRemove(node->right, successorNode->key);
                }
            
            }

            updateHeight(node);
            int balance = getBalance(node);
            if(balance > 1){
                if(getBalance(node->left) >= 0){
                    return rightRotate(node);
                }else if(getBalance(node->left) < 0){
                    node->left = leftRotate(node->left);
                    return rightRotate(node);
                }
            }
            else if(balance < -1){
                if(getBalance(node->right) <= 0){
                    return leftRotate(node);
                }
                else if(getBalance(node->right) > 0){
                    node->right = rightRotate(node->right);
                    return leftRotate(node);
                }
            }
            return node;
        }

        int getHeight(Node* node){
            if(node == nullptr){
                return -1;
            }

            return node->height;
        }

        void updateHeight(Node* node){
            int leftHeight = getHeight(node->left);
            int rightHeight = getHeight(node->right);

            if(leftHeight > rightHeight){
                node->height = leftHeight + 1;
            }
            else{
                node->height = rightHeight + 1;
            }
        }

        int helperMax(Node* node){
            while(node->right){
                node = node->right;
            }
            return node->key;
        }

        int helperMin(Node* node){
            while(node->left){
                node = node->left;
            }
            return node->key;
        }

        int getBalance(Node* node){
            return getHeight(node->left) - getHeight(node->right);
        }

        Node* rightRotate(Node* node){
            Node* x = node->left;
            Node* T2 = x->right;

            x->right = node;

            node->left = T2;

            updateHeight(node);
            updateHeight(x);

            return x;
        }

        Node* leftRotate(Node* node){
            Node* x = node->right;
            Node* T2 = x->left;

            x->left = node;
            node->right = T2;

            updateHeight(node);
            updateHeight(x);

            return x;
        }

        void helperPrint(Node* node, int space) {
            if (node == nullptr)
                return;

            const int indent = 6;

            space += indent;
            
            helperPrint(node->right, space);

            std::cout << std::endl;
            for (int i = indent; i < space; i++)
                std::cout << " ";
            std::cout << node->key << "(" << node->height << ")" << std::endl;

            helperPrint(node->left, space);
        }

        void helperClear(Node* node){
            if(node == nullptr){
                return;
            }

            helperClear(node->left);
            helperClear(node->right);

            delete node;
        }

    public:
        BTree(){
            root = nullptr;
            size = 0;
        }

        void insert(int key){
            root = helperInsert(root, key);
        }

        void inOrderTraversal(){
            helperInOrder(root);
        }

        Node* find(int key){
            return helperFind(root, key);
        }

        void remove(int key){
            root = helperRemove(root, key);
        }

        int height(){
            return getHeight(root);
        }

        int getMax(){
            if(root == nullptr){
                throw std::runtime_error("Tree is empty");
            }
            return helperMax(root);
        }

        int getMin(){
            if(root == nullptr){
                throw std::runtime_error("Tree is empty");
            }
            return helperMin(root);
        }

        void printTree() {
            helperPrint(root, 0);
        }

        void clear(){
            helperClear(root);
            root = nullptr;
        }

        int getSize(){
            return size;
        }

        ~BTree(){
            clear();
        }

};

#endif