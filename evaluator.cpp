/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"
#include <iostream>
using namespace std;
bool isOperator(string token)
{
    if (token == "+" || token == "-" || token == "*" || token == "/")
    {
        return true;
    }
    return false;
}
bool isnumber(string token)
{
    for (int i = 0; i < token.length(); i++)
    {
        if (!isdigit(token[i]))
        {
            return false;
        }
    }
    return true;
}
class Stack
{
private:
    vector<string> elements;

public:
    void push(string value)
    {
        elements.push_back(value);
    }

    void pop()
    {

        elements.pop_back();
    }

    string top()
    {

        return elements.back();
    }

    bool isEmpty()
    {
        return elements.empty();
    }

    int size()
    {
        return elements.size();
    }
    void print()
    {
        cout << "printing starts for opstack" << endl;
        for (string x : elements)
        {
            cout << x << " ";
        }
        cout << endl;
    }
};
class Stacknode
{
private:
    vector<ExprTreeNode *> elements;

public:
    void push(ExprTreeNode *value)
    {
        elements.push_back(value);
    }

    void pop()
    {

        elements.pop_back();
    }

    ExprTreeNode *top()
    {

        return elements.back();
    }

    bool isEmpty()
    {
        return elements.empty();
    }

    int size()
    {
        return elements.size();
    }
    void print()
    {
        cout << "printing starts for main stack" << endl;
        for (ExprTreeNode *x : elements)
        {
            cout << x->evaluated_value->get_frac_str() << " ";
        }
        cout << endl;
    }
};
Evaluator::Evaluator()
{

    symtable = new SymbolTable();
}
Evaluator::~Evaluator()
{
    delete symtable;
    for (int i = 0; i < int(expr_trees.size()); i++)
    {
        delete expr_trees[i];
    }
}
void Evaluator::parse(vector<string> code)
{
    // cout << "i";
    Stack opstack;
    Stacknode mainstack;
    // cout << "i" << endl;
    for (int i = 2; i < code.size(); i++)
    {
        // cout << "for " << i << endl;

        if (code[i] == "(")
        {

            opstack.push(code[i]);
        }
        else if (code[i] == ")")
        {
            while (!opstack.isEmpty() && opstack.top() != "(")
            {
                // cout << "closed bracks" << endl;
                string op = opstack.top();
                opstack.pop();
                ExprTreeNode *right1 = mainstack.top();
                mainstack.pop();
                ExprTreeNode *left1 = mainstack.top();
                mainstack.pop();
                ExprTreeNode *b1 = new ExprTreeNode();
                b1->right = right1;
                b1->left = left1;
                b1->id = "heh";
                if (op == "/")
                {
                    // cout << "division" << endl;
                    // cout << "left and right" << left1->evaluated_value->get_frac_str() << "   " << right1->evaluated_value->get_frac_str() << endl;
                    b1->evaluated_value = UnlimitedRational::div(left1->evaluated_value, right1->evaluated_value);
                    b1->type = "DIV";
                    // cout << "l";
                }
                else if (op == "+")
                {
                    b1->evaluated_value = UnlimitedRational::add(left1->evaluated_value, right1->evaluated_value);
                    b1->type = "ADD";
                }
                else if (op == "-")
                {
                    b1->evaluated_value = UnlimitedRational::sub(left1->evaluated_value, right1->evaluated_value);
                    b1->type = "SUB";
                }
                else
                {

                    b1->evaluated_value = UnlimitedRational::mul(left1->evaluated_value, right1->evaluated_value);
                    b1->type = "MUL";
                }
                mainstack.push(b1);
            }
            opstack.pop();
        }
        else if (isOperator(code[i]))
        {
            opstack.push(code[i]);
        }
        else
        {
            if (isnumber(code[i]))
            {
                UnlimitedInt *i1 = new UnlimitedInt(code[i]);
                ExprTreeNode *b1 = new ExprTreeNode("hehe", i1);
                mainstack.push(b1);
                // cout << "number entered" << endl;
            }
            else
            {
                ExprTreeNode *b1 = new ExprTreeNode();
                b1->type = "VAR";
                b1->id = code[i];
                b1->evaluated_value = symtable->search(code[i]);
                b1->val = b1->evaluated_value;
                mainstack.push(b1);
            }
        }
        // opstack.print();
        // mainstack.print();
    }

    ExprTreeNode *b1 = new ExprTreeNode();
    ExprTreeNode *b2 = new ExprTreeNode();

    b1->type = "VAR";

    b1->id = code[0];

    b1->evaluated_value = mainstack.top()->evaluated_value;

    // cout << b1->id << "    " << b1->evaluated_value->get_frac_str();
    // cout << "l";
    symtable->insert(b1->id, b1->evaluated_value);
    // cout << "l";

    b1->val = b1->evaluated_value;
    b2->left = b1;
    b2->right = mainstack.top();
    b2->id = "ROOT";
    b2->evaluated_value = mainstack.top()->evaluated_value;
    b2->type = "VARi";

    expr_trees.push_back(b2);
    // cout << "eneded";
}
void Evaluator::eval()
{
}
int main()
{

    vector<string> code = {"v", ":=", "(", "13", "+", "(", "2", "/", "51", ")", ")"};
    vector<string> code2 = {"g", ":=", "(", "2", "*", "v", ")"};
    vector<string> code3 = {"x", ":=", "(", "g", "+", "6", ")"};
    vector<string> code4 = {"y", ":=", "x"};

    Evaluator *e1 = new Evaluator();

    e1->parse(code);
    e1->parse(code2);

    e1->parse(code3);
    e1->parse(code4);

    vector<ExprTreeNode *> e2 = e1->expr_trees;

    cout << e2[0]->evaluated_value->get_frac_str() << endl;
    cout << e2[1]->evaluated_value->get_frac_str() << endl;
    cout << e2[2]->evaluated_value->get_frac_str() << endl;

    cout << e2[3]->evaluated_value->get_frac_str() << endl;
}