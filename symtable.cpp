/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
#include <iostream>
using namespace std;
bool bg(string s1, string s2)
{
    if (s1.length() > s2.length())
    {
        return true;
    }
    else if (s1.length() < s2.length())
    {
        return false;
    }
    else
    {
        for (int i = 0; i < s1.length(); i++)
        {
            if (s2[i] > s1[i])
            {
                return false;
            }
            else if (s2[i] < s1[i])
            {
                return true;
            }
        }
    }
    return false;
}
SymEntry *findmin(SymEntry *root)
{
    while (root->left)
    {
        root = root->left;
    }
    return root;
}
SymbolTable::SymbolTable()
{
    size = 0;
    UnlimitedRational *v = new UnlimitedRational();
    root = new SymEntry("0", v);
}
SymbolTable::~SymbolTable()
{
    delete root;
}
SymEntry *SymbolTable::get_root()
{
    return root;
}
int SymbolTable::get_size()
{
    return size;
}
void SymbolTable::insert(string k, UnlimitedRational *v)
{

    SymEntry *temp = new SymEntry(k, v);

    // problem here

    if (size == 0)
    {

        root = temp;
        size++;
    }
    else
    {
        SymEntry *temp1 = root;
        SymEntry *parent;
        while (temp1)
        {
            parent = temp1;
            if (bg(temp1->key, k))
            {

                temp1 = temp1->left;
            }
            else
            {

                temp1 = temp1->right;
            }
        }
        if (bg(parent->key, k))
        {

            parent->left = temp;
            size++;
        }
        else
        {

            parent->right = temp;
            size++;
        }
    }
}
void SymbolTable::remove(string k)
{
    size--;
    SymEntry *parent = NULL;
    SymEntry *current = this->get_root();
    while (current)
    {
        if (bg(current->key, k))
        {
            parent = current;
            current = current->left;
        }
        else if (bg(k, current->key))
        {
            parent = current;
            current = current->right;
        }
        else
        {
            if (!current->left && !current->right)
            {
                if (parent)
                {
                    if (parent->left == current)
                    {
                        parent->left = NULL;
                    }
                    else
                    {
                        parent->right = NULL;
                    }
                }
                else
                {
                    root = NULL;
                }
                delete current;
            }
            else if (current->left && current->right)
            {
                SymEntry *successor = findmin(current->right);
                current->key = successor->key;
                current->val = successor->val;
                k = successor->key;
                parent = current;
                current = current->right;
            }
            else
            {
                SymEntry *temp;
                if (current->left)
                {
                    temp = current->left;
                }
                else
                {
                    temp = current->right;
                }
                if (parent->left == current)
                {
                    parent->left = temp;
                }
                else
                {
                    parent->right = temp;
                }
                delete current;
            }
        }
    }
}
UnlimitedRational *SymbolTable::search(string k)
{
    SymEntry *cur = this->get_root();
    while (cur)
    {
        if (k == cur->key)
        {
            return cur->val;
        }
        else if (bg(cur->key, k))
        {
            cur = cur->left;
        }
        else
        {
            cur = cur->right;
        }
    }
}
