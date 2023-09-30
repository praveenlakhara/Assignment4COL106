/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"
#include<iostream>
SymEntry::SymEntry(){
    key="";
    val=new UnlimitedRational();
     left=NULL;
    right=NULL;
}
SymEntry::SymEntry(string k,UnlimitedRational*v){
    //assure that you have unique urational pointers.
    key=k;
    val=v;
    left=NULL;
    right=NULL;
}
SymEntry::~SymEntry(){
  //  cout<<"entered here too\n";
    val->~UnlimitedRational();
    left=NULL;
    right=NULL;
}