### Compiler-for-Simple-Language-of-Expressions
## For problem statement: [COL106_Assignment_4_v2.pdf](https://github.com/user-attachments/files/16754204/COL106_Assignment_4_v2.pdf)
## To run code:
  # Go to ***evaluator.cpp*** file --> Type your Expression as tokens in *main()*
## Example:

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

  
