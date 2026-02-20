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
                    return node;
                }
            
            }
            return node;
        }

        int helperHeight(Node* node){
            if (node == nullptr){
                return -1;
            }

            int leftHeight = helperHeight(node->left);
            int rightHeight = helperHeight(node->right);

            if (leftHeight > rightHeight){
                return 1 + leftHeight;
            }
            else{
                return 1 + rightHeight;
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
            helperRemove(root, key);
        }

        int height(){
            return helperHeight(root);
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