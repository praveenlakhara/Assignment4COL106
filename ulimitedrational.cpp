/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"
#include<iostream>
UnlimitedRational::UnlimitedRational(){
    UnlimitedInt*p1=new UnlimitedInt();
    UnlimitedInt*q1=new UnlimitedInt();
    p=p1;
    q=q1;
}
UnlimitedInt*GCD(UnlimitedInt* num, UnlimitedInt* den){
        if(num->get_sign()==-1||den->get_sign()==-1){
             string s1=num->to_string();
             string s2=den->to_string();
             if(s1[0]=='-'){
                s1.erase(0,1);
             }
             if(s2[0]=='-'){
                s2.erase(0,1);
             }
               UnlimitedInt*temp1=new UnlimitedInt(s1);
               UnlimitedInt*temp2=new UnlimitedInt(s2);
               UnlimitedInt*ans=GCD(temp1,temp2);
               temp1->~UnlimitedInt();
               temp2->~UnlimitedInt();
               return ans;
        }
    if(num->get_sign()==0){
        UnlimitedInt*ans=new UnlimitedInt(den->to_string());
        return ans;
    }
    if(den->get_sign()==0){
      UnlimitedInt*ans=new UnlimitedInt(num->to_string());
        return ans;
    }
    UnlimitedInt*diff=num->sub(num,den);
    if(diff->get_sign()==-1){
        diff->~UnlimitedInt();   
             UnlimitedInt*ans=GCD(den,num);           
             return ans;
    }
       diff->~UnlimitedInt(); 
       UnlimitedInt*modulo=num->mod(num,den);
    UnlimitedInt*ans=GCD(den,modulo);
      modulo->~UnlimitedInt();
    return ans;
}
UnlimitedInt*LCM(UnlimitedInt*den1,UnlimitedInt*den2){
    UnlimitedInt*mull=den1->mul(den1,den2);
    UnlimitedInt*g=GCD(den1,den2);
    UnlimitedInt*ans=den1->div(mull,g);
     mull->~UnlimitedInt();
     g->~UnlimitedInt();
    return ans;
}
UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den){
       if(num->to_string()=="0"&&den->to_string()=="0"){
              p=new UnlimitedInt("0");
                q=new UnlimitedInt("0");
       }else if(num->to_string()=="0"){
                 p=new UnlimitedInt("0");
                q=new UnlimitedInt("1");
      }else if(den->to_string()=="0"){
                  p=new UnlimitedInt("0");
                q=new UnlimitedInt("0");
       }else{
         UnlimitedInt*gcd=GCD(num,den);
           this->q=q->div(den,gcd);
           this->p=p->div(num,gcd);
         gcd->~UnlimitedInt();  
       }
}
UnlimitedRational::~UnlimitedRational(){
   //   cout<<"entered urational\n";
      p->~UnlimitedInt();
      q->~UnlimitedInt();
}
UnlimitedInt* UnlimitedRational::get_p(){
     return p;
}
UnlimitedInt* UnlimitedRational::get_q(){
     return q;
}
string UnlimitedRational::get_p_str(){
    return p->to_string();
}
string UnlimitedRational::get_q_str(){
    return q->to_string();
}
string UnlimitedRational::get_frac_str(){
    string ans=p->to_string()+"/"+q->to_string();
    return ans;
}
UnlimitedRational* UnlimitedRational::add(UnlimitedRational *i1,UnlimitedRational* i2){
         if(i1->get_frac_str()=="0/0"||i2->get_frac_str()=="0/0"){
       UnlimitedRational* ans=new UnlimitedRational(i1->p,i1->p);
            return ans;
         }
           UnlimitedInt* num1=i1->get_p()->mul(i1->get_p(),i2->get_q());
            UnlimitedInt* num2=i2->get_p()->mul(i2->get_p(),i1->get_q());
            UnlimitedInt*num=i1->get_p()->add(num1,num2);
            UnlimitedInt*den=i1->get_q()->mul(i1->get_q(),i2->get_q());
            UnlimitedRational*ans=new UnlimitedRational(num,den);
                  num->~UnlimitedInt();
                  den->~UnlimitedInt();
                   num1->~UnlimitedInt();
                   num2->~UnlimitedInt();
          return ans;
}
UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2){
     if(i1->get_frac_str()=="0/0"||i2->get_frac_str()=="0/0"){
       UnlimitedRational* ans=new UnlimitedRational(i1->p,i1->p);
            return ans;
         }
        UnlimitedInt*p=i2->get_p();
        if(p->get_sign()==0){
            return add(i1,i2);
        }
        string s=p->to_string();
        if(s[0]=='-'){
            s.erase(0,1);
        }else{
            s="-"+s;
        }
        UnlimitedInt*d=new UnlimitedInt(s);
        i2->p=d;
        UnlimitedRational*ans=add(i1,i2);
        i2->p=p;
        d->~UnlimitedInt();
        return ans;
}
UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2){
     if(i1->get_frac_str()=="0/0"||i2->get_frac_str()=="0/0"){
       UnlimitedRational* ans=new UnlimitedRational(i1->p,i1->p);
            return ans;
         }
    UnlimitedRational*ans;
    UnlimitedInt*i=i1->p->mul(i1->p,i2->p);
   UnlimitedInt*j=i1->p->mul(i1->q,i2->q);
   return new UnlimitedRational(i,j);
}
UnlimitedRational* UnlimitedRational::div(UnlimitedRational*i1,UnlimitedRational*i2){
     if(i1->get_frac_str()=="0/0"||i2->get_frac_str()=="0/0"){
       UnlimitedRational* ans=new UnlimitedRational(i1->p,i1->p);
            return ans;
         }
     UnlimitedInt*i=i->mul(i1->p,i2->q);
     UnlimitedInt*j=j->mul(i1->q,i2->p);
     return new UnlimitedRational(i,j);
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
      cout<<j1->div(j1,j2)->get_frac_str()<<endl;
        cout<<j1->get_frac_str()<<" "<<j2->get_frac_str()<<endl;
      return 0;
}*/