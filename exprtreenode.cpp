/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"
#include<iostream>
ExprTreeNode::ExprTreeNode(){

}
ExprTreeNode::ExprTreeNode(string t,UnlimitedInt*v){
     left=NULL;
     right=NULL;
      int u=0;
       for(int i=0;i<t.length();i++){
          if(i==0){
               if(t[i]=='-'||(t[i]>=48&&t[i]<58)){
                     
               }else{
                    u=1;
                    break;
               }
          }else{
               if(!(t[i]-'0'>=0&&t[i]-'0'<9)){
                    u=1;
                    break;
               }
          }
     }
     if(u==0){
          type="VAL";
          UnlimitedInt*one=new UnlimitedInt("1");
          UnlimitedInt*num=new UnlimitedInt(t);
          val=new UnlimitedRational(num,one);
          delete one;
          delete num;
     }else{
          if(t=="+"){
               type="ADD";
          }else if(t=="-"){
               type="SUB";
          }else if(t=="*"){
               type="MUL";
          }else if(t=="/"){
               type="DIV";
          }else if(t=="%"){
               type="MOD";
          }else{
               type="VAR";
               id=t;
          }
           UnlimitedInt*one=new UnlimitedInt("1");
            val=new UnlimitedRational(v,one);
            delete one;
     }
}
ExprTreeNode::ExprTreeNode(string t,UnlimitedRational*v){
     left=NULL;
     right=NULL;
     int u=0;
     for(int i=0;i<t.length();i++){
          if(i==0){
               if(t[i]=='-'||(t[i]>=48&&t[i]<58)){
                     
               }else{
                    u=1;
                    break;
               }
          }else{
               if(!(t[i]-'0'>=0&&t[i]-'0'<9)){
                    u=1;
                    break;
               }
          }
     }
     if(u==0){
          type="VAL";
          UnlimitedInt*one=new UnlimitedInt("1");
          UnlimitedInt*num=new UnlimitedInt(t);
          val=new UnlimitedRational(num,one);
          delete one;
          delete num;
     }else{
          if(t=="+"){
               type="ADD";
          }else if(t=="-"){
               type="SUB";
          }else if(t=="*"){
               type="MUL";
          }else if(t=="/"){
               type="DIV";
          }else if(t=="%"){
               type="MOD";
          }else{
               type="VAR";
               id=t;
          }
          val=v;
     }
}
ExprTreeNode::~ExprTreeNode(){
     left=NULL;
     right=NULL;
     val->~UnlimitedRational();
   //  cout<<"!\n";
    // evaluated_value->~UnlimitedRational();
}
/*int main(){
     UnlimitedInt*e=new UnlimitedInt("9");
     ExprTreeNode s("rr",e);
     return 0;
}*/