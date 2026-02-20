#ifndef NODE_H
#define NODE_H
class Node{
    public:
        int key;
        Node* left;
        Node* right;
        int height;

        Node(int nkey){
            key = nkey;
            left = nullptr;
            right = nullptr;
            height = 1;
        }

};

#endif