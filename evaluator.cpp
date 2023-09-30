/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"
#include <vector>
#include<iostream>
Evaluator::Evaluator() {
    symtable = new SymbolTable();
}
Evaluator::~Evaluator() {
   //  cout<<"1\n";
    delete symtable;

   
    for (ExprTreeNode* node : expr_trees) {
        delete node;
    }
    expr_trees.clear();
}
void Evaluator::parse(vector<string> code){
   UnlimitedInt*zero=new UnlimitedInt("0");
  vector<ExprTreeNode*> stack;

  for (string token : code) {
    if (token == "(") {
    } else if (token == ")") {
      // Pop two nodes from the stack and make them the children of the current node.
     ExprTreeNode* right = stack.back();
      stack.pop_back();
      ExprTreeNode* op = stack.back();
      stack.pop_back();
      ExprTreeNode* left = stack.back();
      stack.pop_back();
      op->left = left;
      op->right = right;
      stack.push_back(op);
    } else {
      // Create a new node for the operand.
      ExprTreeNode* node = new ExprTreeNode(token,zero);
      stack.push_back(node);
    }
  }
   ExprTreeNode* right = stack.back();
  stack.pop_back();
   ExprTreeNode*root=stack.back();
   stack.pop_back();
   ExprTreeNode*left=stack.back();
   stack.pop_back();
   root->left=left;
   root->right=right;
  expr_trees.push_back(root);
  // The root of the parse tree is the last node on the stack.
}
void printtable(ExprTreeNode*s){
     if(s==NULL){
      return;
     }
       if(s->left!=NULL){
        // cout<<"printing left\n";
       printtable(s->left);
       }
       //cout<<"printing val\n";
       cout<<s->val->get_frac_str()<<endl;
       if(s->right!=NULL){
       //  cout<<"printing right\n";
       printtable(s->right);
       }
 }
 UnlimitedRational*evaluatedval(ExprTreeNode*root,SymbolTable*sym){
      if(root->type=="VAL"){
         return root->val;
      }
      if(root->type=="ADD"){
        UnlimitedRational*left=evaluatedval(root->left,sym);
        UnlimitedRational*right=evaluatedval(root->right,sym);
        return left->add(left,right);
      }else if(root->type=="SUB"){
         UnlimitedRational*left=evaluatedval(root->left,sym);
        UnlimitedRational*right=evaluatedval(root->right,sym);
        return left->sub(left,right);
      }else if(root->type=="MUL"){
         UnlimitedRational*left=evaluatedval(root->left,sym);
        UnlimitedRational*right=evaluatedval(root->right,sym);
        return left->mul(left,right);
      }else if(root->type=="DIV"){
         UnlimitedRational*left=evaluatedval(root->left,sym);
        UnlimitedRational*right=evaluatedval(root->right,sym);
        return left->div(left,right);
      }else if(root->type=="MOD"){
         UnlimitedRational*left=evaluatedval(root->left,sym);
        UnlimitedRational*right=evaluatedval(root->right,sym);
         UnlimitedInt*n=left->get_p();
         UnlimitedInt*m=right->get_p();
         UnlimitedInt*one=right->get_q();
         UnlimitedInt*ans=n->mod(n,m);
         return new UnlimitedRational(ans,one);
      }else if(root->type=="VAR"){
         string k=root->id;
           return sym->search(k);
      }
        UnlimitedInt*one=new UnlimitedInt("0");
           UnlimitedInt*on=new UnlimitedInt("1");
           UnlimitedRational* val=new UnlimitedRational(one,on);
            return val;
 }
void Evaluator:: eval(){
     ExprTreeNode*traveller=expr_trees.back();
     traveller->evaluated_value=evaluatedval(traveller->right,symtable);
     // cout<<evaluatedval(traveller->right)->get_frac_str()<<endl;
     symtable->insert(traveller->left->id,traveller->evaluated_value);
}
/*int main(){
   Evaluator p;
  vector<string> code;
code.push_back("v");
code.push_back(":=");
code.push_back("(");
code.push_back("13");
code.push_back("+");
code.push_back("2");
code.push_back(")");
// for(string i:code){
  //  cout<<i<<endl;
 //}
      p.parse(code);
      p.eval();
     // cout<<p.symtable->search("v")->get_frac_str()<<endl;
    //  printtable(p.expr_trees.back());
    return 0;
}*/