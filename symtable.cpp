/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
#include<iostream>
 SymbolTable::SymbolTable(){
     size=0;
     root=NULL;
 }
 void destroy(SymEntry*r){
     if(r!=NULL){
        destroy(r->left);
        destroy(r->right);
          r->~SymEntry();
     }
 }
 SymbolTable::~SymbolTable(){
    //  cout<<"Entered Symtable Destructor\n";
      destroy(root);
 }
 SymEntry* SymbolTable::get_root(){
    return root;
 }
 int SymbolTable::get_size(){
    return size;
 }
 void printtable(SymEntry*s){
     if(s==NULL){
      return;
     }
       printtable(s->left);
       cout<<s->key<<endl;
       printtable(s->right);
 }
 SymEntry* Searchforme(string k,SymEntry*root){
       if(root==NULL){
         return NULL;
       }
        if(root->key==k){
           return root;
        }
        if(root->key>k){
           return Searchforme(k,root->left);
        }
        if(root->key<k){
           return Searchforme(k,root->right);
        }
        return NULL;
 }
 void SymbolTable::remove(string k){
        Searchforme(k,root)->~SymEntry();
            size--;
 }
 void Insertit(string k,UnlimitedRational*v,SymEntry*root){
            // cout<<"hii\n";
          if(root==NULL){
             SymEntry*n=new SymEntry(k,v);
             root=n;
             return; 
          }
           if(root->key>k){
            if(root->left==NULL){
               SymEntry*e=new SymEntry(k,v);
               root->left=e;
               return;
            }
          Insertit(k,v,root->left);
          return;
        }
        if(root->key<k){
            if(root->right==NULL){
               SymEntry*e=new SymEntry(k,v);
               root->right=e;
               return;
            }
            Insertit(k,v,root->right);
            return;
        }
 }
 void SymbolTable::insert(string k,UnlimitedRational*v){
         Insertit(k,v,root);
         size++;
 }
  UnlimitedRational* SymbolTable:: search(string k){
       return Searchforme(k,root)->val;
  }
 /*int main(){
    string s1,s2,s3,s4;
    cin>>s1>>s2>>s3>>s4;
    UnlimitedInt*i=new UnlimitedInt(s1);
    UnlimitedInt*k=new UnlimitedInt(s2);
      UnlimitedInt*i1=new UnlimitedInt(s3);
    UnlimitedInt*k1=new UnlimitedInt(s4);
    UnlimitedRational*j1=new UnlimitedRational(i,k);
     UnlimitedRational*j2=new UnlimitedRational(i1,k1);
     cout<<j1->get_frac_str()<<" "<<j2->get_frac_str()<<endl;
     SymbolTable s;
     s.insert("Variable1",j1);
     s.insert("Variable2",j2);
      s.insert("Variable0",j1->add(j1,j2));
    // s.insert("variablew",j1);
      cout<<"hii\n";
     printtable(s.get_root());
     return 0;
 }*/