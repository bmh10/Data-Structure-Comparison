#ifndef RBST_H_
#define RBST_H_

#include <iostream>
#include <assert.h>
#include <vector>
#include <math.h>
#include "Key.hpp"
#include "DataStructure.hpp"

using namespace std;

class RBSTNode;
class RBSTNode: public Key
{
public:
        RBSTNode(const Key& key):Key(key), m_left(NULL), m_right(NULL)
        {
                m_size = 1;
        }
        virtual ~RBSTNode(){}

        string setKey(const Key& key){return Key(key);}

        RBSTNode* left(){return m_left; }
        RBSTNode* right(){return m_right;}

        RBSTNode* setLeft(RBSTNode* left) { m_left = left; return this; }
        RBSTNode* setRight(RBSTNode* right) { m_right =right; return this; }

        unsigned int size() { return m_size; }

        void setSize(unsigned int val)
        {
                if (val > 0)
                        m_size = val;
        }

        void incSize() { m_size++; }

        void decSize()
        {
                if (m_size > 0)
                        m_size--;
        }


private:
        RBSTNode(){}
        RBSTNode* m_left;
        RBSTNode* m_right;
        unsigned int m_size;
};

class RBST : public DataStructure
{
public:
        RBST():m_head(NULL)
        {
                m_size = 0;
        };

        virtual ~RBST() {};

        bool add(const Key& key, bool v=false);
        bool addString(const string& key);
        bool del(const Key& key, bool v=false);
        bool find(const Key& key, bool v = false);
        unsigned int count() { return m_size; }


        int dump(char sep = ' ');
        int dump(RBSTNode* target, char sep);
        unsigned int size(RBSTNode* x);


private:
        RBSTNode* randomAdd(RBSTNode* target, const Key& key);
        RBSTNode* addRoot(RBSTNode* target, const Key& key);
        RBSTNode* rightRotate(RBSTNode* target);
        RBSTNode* leftRotate(RBSTNode* target);

        RBSTNode* del(RBSTNode* target, const Key& key);
        RBSTNode* join(RBSTNode* left, RBSTNode* right);

        RBSTNode* find(RBSTNode* target, const Key& key);

        RBSTNode* m_head;
        unsigned int m_size;
};

#endif /*RBST_H_*/
