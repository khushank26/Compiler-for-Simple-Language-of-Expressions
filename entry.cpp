/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"
SymEntry::SymEntry()
{

    key = "00";
    val = NULL;
    left = NULL;
    right = NULL;
}
SymEntry::SymEntry(string k, UnlimitedRational *v)
{
    key = k;
    val = v;
    left = NULL;
    right = NULL;
}
SymEntry::~SymEntry()
{
    if (this->left != NULL)
    {
        delete this->left;
    }
    if (this->right != NULL)
    {
        delete this->right;
    }
}