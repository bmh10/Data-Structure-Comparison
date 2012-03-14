#include "RBST.hpp"
#include <stdlib.h>

bool RBST::add(const Key& key, bool v){
        unsigned int oldSize = m_size;
        m_head = randomAdd(m_head, key);
        if (m_size > oldSize){
                if(v) cout<<"Node "<<key<< " is added into the tree."<<endl;
                return true;
        }else {
                if(v) cout<<"Node "<<key<< " is already in the tree."<<endl;
                return false;
        }
        if(v) cout<<endl;
};

bool RBST::addString(const string& key) {
        return add(Key(key), false);
}

bool RBST::del(const Key& key, bool v){
        unsigned oldSize= m_size;
        m_head = del(m_head, key);
        if (m_size < oldSize) {
                if(v) cout<<"Node "<<key<< " is deleted from the tree."<<endl;
                return true;
        }
        else {
                if(v) cout<< "Node "<<key<< " is not in the tree."<<endl;
                return false;
        }
};

bool RBST::find(const Key& key, bool v){
        RBSTNode* ret = find(m_head, key);
        if (ret == NULL){
                if(v) cout<< "Node "<<key<< " is not in the tree."<<endl;
                return false;
        }else {
                if(v) cout<<"Node "<<key<< " is in the tree."<<endl;
                return true;
        }
};


int RBST::dump(char sep){
        int ret = dump(m_head, sep);
        cout<<"SIZE: " <<ret<<endl;
        return ret;
};

int RBST::dump(RBSTNode* target, char sep){
        if (target == NULL) return 0;
        int ret = dump(target->left(), sep);
        cout<< *target<<sep;
        ret ++;
        ret += dump(target->right(), sep);
        return ret;
};



RBSTNode* RBST::rightRotate(RBSTNode* target)
{
        if (target == NULL || target->left() == NULL) 
                return NULL;

        RBSTNode* l = target->left();
        int tmp = l->size();

        // Update subtree sizes
        l->setSize( l->size() + (target->right() == NULL ? 0 : target->right()->size()) + 1);
        target->setSize( target->size() -tmp + (l->right() == NULL ? 0 : l->right()->size()) );

        target->setLeft(l->right());
        l->setRight(target);
        return l;
};


RBSTNode* RBST::leftRotate(RBSTNode* target)
{
        if (target == NULL || target->right() == NULL)
                return NULL;

        RBSTNode* r = target->right();
        int tmp = r->size();

        // Update subtree sizes
        r->setSize(r->size() + (target->left() == NULL ? 0 : target->left()->size()) + 1);
        target->setSize(target->size() -tmp + (r->left() == NULL ? 0 : r->left()->size()));

        target->setRight(r->left());
        r->setLeft(target);
        return r;
};


RBSTNode* RBST::addRoot(RBSTNode* target, const Key& key)
{
        countAdd++;

        if (target == NULL) 
                return new RBSTNode(key);

        if (*target < key)
        {
                target->setRight( addRoot(target->right(), key) );
                target->incSize();
                return leftRotate(target);;
        }

        target->setLeft( addRoot(target->left(), key) );
        target->incSize();
        return rightRotate(target);
};


RBSTNode* RBST::randomAdd(RBSTNode* target, const Key& key)
{
        countAdd++;

        if (target == NULL)
        {
                m_size++;
                return new RBSTNode(key);
        }

        int r = (rand() % target->size()) + 1;

        if (r == 1)
        {
                m_size++;
                return addRoot(target, key);
        }

        if (*target <= key)
        {
                target->setRight( randomAdd(target->right(), key) );
                target->incSize();
        }
        else
        {
                target->setLeft( randomAdd(target->left(), key) );
                target->incSize();
        }

        m_size++;
        return target;
};


/////////////////////////////////////////////////////////////
/////////////////////  FIND FUNCTIONS ///////////////////////
/////////////////////////////////////////////////////////////


RBSTNode* RBST::find(RBSTNode* target, const Key& key)
{
        countFind++;
        if (target == NULL)
                return NULL;

        if (*target == key)
                return target;

        if (*target < key)
                return find(target->right(), key);

        return find(target->left(), key);
};

/////////////////////////////////////////////////////////////
/////////////////////  DEL FUNCTIONS ////////////////////////
/////////////////////////////////////////////////////////////


RBSTNode* RBST::del(RBSTNode* target, const Key& key)
{
        countDelete++;

        if (target == NULL)
                return NULL;

        if (*target == key)
        {
                RBSTNode* ret = join(target->left(), target->right());
                m_size--;
                delete target;
                return ret;
        }

        // Store a tmp size before recursive deletion.
        unsigned int size = m_size;

        if (*target < key)
              target->setRight( del(target->right(), key) );
        else
              target->setLeft( del(target->left(), key) );

        if (m_size < size)
                target->decSize();

        return target;
};

/*
 * Joins two subtrees by choosing randomly which to
 * make the root, weighted on size of sub-tree.
 */
RBSTNode* RBST::join(RBSTNode* left, RBSTNode* right)
{
        if (left == NULL) return right;
        if (right == NULL) return left;

        // Probability = |l| / (|l| + |r|)
        bool useLeftAsRoot = ((rand()%1000) < (signed)((float)left->size()/
                (float)(left->size() + right->size()) * 1000.0));

        RBSTNode* subtree = NULL;

        if (useLeftAsRoot)
        {
                subtree = join(left->right(), right);

				// Update subtree size
                left->setRight(subtree)
                        ->setSize((left->left() == NULL ? 0 : left->left()->size())
                                                + subtree->size() + 1 );

                return left;
        }

        subtree = join(right->left(), left);

		// Update subtree size
        right->setLeft(subtree)
                 ->setSize((right->right() == NULL ? 0 : right->right()->size())
                                        + subtree->size() + 1);

        return right;
};

