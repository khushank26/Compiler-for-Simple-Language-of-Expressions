/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"
// have assumed that there is no need of mod
ExprTreeNode::ExprTreeNode()
{
    type = "VAR";
    id = "hehe";
    evaluated_value = new UnlimitedRational();
    val = evaluated_value;
    left = NULL;
    right = NULL;
}
ExprTreeNode::ExprTreeNode(string t, UnlimitedInt *v)
{

    type = "VAL";
    id = "hehe";
    left = NULL;
    right = NULL;
    UnlimitedInt *i2 = new UnlimitedInt("1");
    evaluated_value = new UnlimitedRational(v, i2);
    val = evaluated_value;
    delete i2;
}
ExprTreeNode::~ExprTreeNode()
{

    delete evaluated_value;

    if (this->left != NULL)
    {
        delete left;
        delete right;
    }
}