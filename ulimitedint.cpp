/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
#include <iostream>

UnlimitedInt::UnlimitedInt(string s){
     capacity=1000000;
     if(s=="0/0"){
        unlimited_int=new int[1];
        unlimited_int[0]=11;
        size=1;
        sign=2;
        capacity=1;
     }
     if(s[0]=='0' && s.length()==1){
        sign=0;
        size=1;
        unlimited_int=new int[1];
        unlimited_int[0]=0;
     }else{
  if(s[0]=='-'){
        sign=-1;
          size=s.size()-1;
       capacity=size-1;
       unlimited_int=new int[s.size()-1];
       for(int i=0;i<s.size()-1;i++){
        unlimited_int[i]=s[i+1]-'0';
       }
       }else{
        sign=1;
         size=s.size();
       capacity=size;
       unlimited_int=new int[s.size()];
       for(int i=0;i<s.length();i++){
        unlimited_int[i]=s[i]-'0';
       }
       }
     }
}
UnlimitedInt:: UnlimitedInt(int i){
    capacity=0;
   if(i>0){
    int k=i;
    while(i>0){
        i=i/10;
        capacity++;
    }
    sign=1;
    size=capacity;
    unlimited_int=new int[size];
    i=0;
    while(k>0){
      unlimited_int[size-i-1]=k%10;
      k=k/10;
      i++;
    }
   }else if(i<0){
    sign=-1;
    i=-i;
      int k=i;
    while(i>0){
        i=i/10;
        capacity++;
    }
    size=capacity;
    unlimited_int=new int[size];
    i=0;
    while(k>0){
      unlimited_int[size-i-1]=k%10;
      k=k/10;
      i++;
    }
   }else{
    unlimited_int=new int[1];
    sign=0;
    size=1;
    capacity=1;
    unlimited_int[0]=0;
   }
}
 UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz){
    unlimited_int=ulimited_int;
    capacity=cap;
    sign=sgn;
    size=sz;
  }
UnlimitedInt::UnlimitedInt(){
}

UnlimitedInt::~UnlimitedInt(){
  // cout<<"entered uint\n";
    delete[] unlimited_int;
}
int UnlimitedInt::get_size(){
    return size;
}
int* UnlimitedInt::get_array(){
    return unlimited_int;
}
int UnlimitedInt::get_sign(){
    return sign;
}
string UnlimitedInt::to_string(){
    string unlimitedint;
    int i=0;
    if(unlimited_int[0]==11){
      return "0/0";
    }
    if(sign==-1){
       unlimitedint='-';
    }
    while(i<size){
        unlimitedint+=char(unlimited_int[i]+48);
       i++;
    }
    return unlimitedint;
}
UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2){
          if(i1->sign==0){
              string sol=i2->to_string();
         UnlimitedInt* solution=new UnlimitedInt(sol);
        return solution;
          } 
         if(i2->sign==0){
               string sol=i1->to_string();
         UnlimitedInt* solution=new UnlimitedInt(sol);
        return solution;
         }
         int*arr1=i1->unlimited_int;
         string s1=i1->to_string();
    string s2=i2->to_string();
         string sol="";
     int*arr2=i2->unlimited_int;
       if(i1->sign==i2->sign){
          int idx1=0,idx2=0;
          int carry=0;
          int curr;
          while(idx1<i1->size&&idx2<i2->size){
              curr=arr1[i1->size-idx1-1]+arr2[i2->size-idx2-1]+carry;
              idx1++;idx2++;
              carry=curr/10;
              curr=curr%10;
             sol=char(curr+48)+sol;
          }
          while(idx1<i1->size){
              curr=arr1[i1->size-idx1-1]+carry;
              idx1++;
              carry=curr/10;
              curr=curr%10;
             sol=char(curr+48)+sol;
          }
          while(idx2<i2->size){
              curr=arr2[i2->size-idx2-1]+carry;
              idx2++;
              carry=curr/10;
              curr=curr%10;
             sol=char(curr+48)+sol;
          }
          if(carry>0){
            sol=char(carry+48)+sol;
          }
          if(i1->sign==-1){
            sol="-"+sol;
          }
       }else{
          int u=0;
          int idx1=0,idx2=0;
          if(i1->size==i2->size){
            while(idx1<i1->size&&idx2<i2->size){
               if(arr1[idx1]>arr2[idx2]){
                  u=0;
                  break;
               }
               if(arr1[idx1]<arr2[idx2]){
                  u=1;
                  break;
               }
               idx1++;
               idx2++;
            }
          }
          if(i1->size<i2->size||u==1){
              UnlimitedInt* p=add(i2,i1);
              p->sign=-1;
              return p;
          }
             idx1=0,idx2=0;
          int carry=0;
          int curr;
          while(idx1<i1->size&&idx2<i2->size){
              curr=arr1[i1->size-idx1-1]-arr2[i2->size-idx2-1]+carry;
                if(curr<0){
                  curr=curr+10;
                  carry=-1;
                }else{
                  carry=0;
                }
              idx1++;idx2++;
             sol=char(curr+48)+sol;
          }
          while(idx1<i1->size){
              curr=arr1[i1->size-idx1-1]+carry;
                if(curr<0){
                    curr=curr+10;
                  carry=-1;
                }else{
                  carry=0;
                }
              idx1++;
             sol=char(curr+48)+sol;
          }
          int ik=0;
          while(sol[ik]=='0'){
            ik++;
          }
          sol.erase(0,ik);
          if(sol==""){
            sol="0";
          }
         
       }
          UnlimitedInt*ans=new UnlimitedInt(sol);
          return ans;
}
UnlimitedInt* UnlimitedInt::sub(UnlimitedInt*i1,UnlimitedInt*i2){
     i2->sign*=-1;
     UnlimitedInt* p=add(i1,i2);
     i2->sign*=-1;
     return p;
}
UnlimitedInt* UnlimitedInt::mul(UnlimitedInt*i1,UnlimitedInt*i2){
    if(i1->sign==0||i2->sign==0){
      return new UnlimitedInt(0);
    }
     int sign1=i1->sign;
     int sign2=i2->sign;
      i1->sign=1;
      i2->sign=1;
    string s1=i1->to_string();
    string s2=i2->to_string();
    string ans="0";
    int*arr1=i1->unlimited_int;
    int*arr2=i2->unlimited_int;
     int carry=0;
     int curr;
   for(int i=0;i<s1.length();i++){
       string s3="";
    for(int j=0;j<s2.length();j++){
          curr=arr1[s1.length()-i-1]*arr2[s2.length()-j-1]+carry;
          carry=curr/10;
          curr=curr%10;
         s3=char(curr+48)+s3;
    }
    if(carry>0){
      s3=char(carry+48)+s3;
      carry=0;
    }
    for(int k=0;k<i;k++){
       s3=s3+"0";
    }
    UnlimitedInt* num1=new UnlimitedInt(s3);
     UnlimitedInt* num2=new UnlimitedInt(ans);
      UnlimitedInt* num3=add(num1,num2);
      ans=num3->to_string();
      delete num1;
       delete num2;
        delete num3;
   }
    i1->sign=sign1;
      i2->sign=sign2;
   UnlimitedInt*sol = new UnlimitedInt(ans);
   sol->sign=sign1*sign2;
   return sol;
}
string divideby2(string number){
       string anss;
        int divisor=2;
    int idxx = 0;
    int tempp = number[idxx] - '0';
    while (tempp < divisor)
        tempp = tempp * 10 + (number[++idxx] - '0');
  
    while (number.length() > idxx) {
      
        anss += (tempp / divisor) + '0';
  
       
        tempp = (tempp % divisor) * 10 + number[++idxx] - '0';
    }
  
   
    if (anss.length() == 0){
      anss="0";
    }
    return anss;
}
string addstr(string s1,string s2){
    string sol="";
   int idx1=0,idx2=0;
          int carry=0;
          int curr;
          while(idx1<s1.length()&&idx2<s2.length()){
              curr=(s1[s1.length()-idx1-1]-'0')+(s2[s2.length()-idx2-1]-'0')+carry;
              idx1++;idx2++;
              carry=curr/10;
              curr=curr%10;
             sol=char(curr+48)+sol;
          }
          while(idx1<s1.length()){
              curr=(s1[s1.length()-idx1-1]-'0')+carry;
              idx1++;
              carry=curr/10;
              curr=curr%10;
             sol=char(curr+48)+sol;
          }
          while(idx2<s2.length()){
              curr=(s2[s2.length()-idx2-1]+'0')+carry;
              idx2++;
              carry=curr/10;
              curr=curr%10;
             sol=char(curr+48)+sol;
          }
          if(carry>0){
            sol=char(carry+48)+sol;
          }
          return sol;
}
UnlimitedInt* UnlimitedInt:: div(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* ans=new UnlimitedInt("0");
     UnlimitedInt* one=new UnlimitedInt("1");
      if(i1->sign==0&&i2->sign==0){
           delete ans;
           delete one;
             return new UnlimitedInt("0/0");
      }
      if(i1->sign==0){
        delete one;
        return ans;
      }
         int sign1=i1->sign;
         int sign2=i2->sign;
         i1->sign=1;
         i2->sign=1;
         string s1=i1->to_string();
         string s2=i2->to_string();
         if(s2=="1"){
           i1->sign=sign1;
      i2->sign=sign2;
          return new UnlimitedInt(i1->to_string());
         }
       UnlimitedInt* dif1=sub(i1,i2);
         if(dif1->sign==0){
            delete ans;
            delete dif1;
             i1->sign=sign1;
      i2->sign=sign2;
          return one;
         }else if(dif1->sign==-1){
           delete dif1;
            i1->sign=sign1;
      i2->sign=sign2;
           if(sign1==sign2){
                 delete one;
               return ans;
           }else{
            one->sign=-1;
            delete ans;
            return one;
           }
         }else{
         string number=s1;
        string zero="0";
        string mid;
           UnlimitedInt temp1(number);
           UnlimitedInt zeroui(zero);
           UnlimitedInt*checker=sub(&temp1,&zeroui);
          while(checker->sign==1){   
               mid=divideby2(addstr(number,zero));
               UnlimitedInt*midd=new UnlimitedInt(mid);
               UnlimitedInt*chknum=mul(midd,i2);
               UnlimitedInt* difff=sub(chknum,i1);
                if(mid==number||mid==zero){
                  delete chknum;
                  delete midd;
                  delete difff;
                  break;
                }
               if(difff->sign==-1){
                zero=mid;            
               }else if(difff->sign==1){
                number=mid;
               }else{
                 midd->~UnlimitedInt();
              chknum->~UnlimitedInt();
              difff->~UnlimitedInt();
                break;
               }
              midd->~UnlimitedInt();
              chknum->~UnlimitedInt();
              difff->~UnlimitedInt();
               UnlimitedInt temp1(number);
           UnlimitedInt zeroui(zero);
                 checker->~UnlimitedInt();
             checker=sub(&temp1,&zeroui);
          }
            UnlimitedInt*temp=ans;
            delete temp;
            delete dif1;
          ans=new UnlimitedInt(mid);
         }
      i1->sign=sign1;
      i2->sign=sign2;
      ans->sign=sign1*sign2;
      if(sign1!=sign2){
         UnlimitedInt*chkit=mul(ans,i2);
         UnlimitedInt*difff=sub(i1,chkit);
         if(difff->sign==1){
             UnlimitedInt*another=sub(ans,one);
             delete one;
             delete ans;
             delete difff;
             delete chkit;
              return another;
         }
      }
       delete one;
    return ans;
}
UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2){
      if(i1->to_string()=="0"){
        return new UnlimitedInt("0");
      }
     int sign1=i1->sign;
     int sign2=i2->sign;
     i1->sign=1;
     i2->sign=1;
    string s1=i1->to_string();
     string s2=i2->to_string();
     UnlimitedInt*i3=div(i1,i2);
     UnlimitedInt*mull=mul(i3,i2);
     UnlimitedInt*ans=sub(i1,mull);
     delete mull;
     delete i3;
     i1->sign=sign1;
     i2->sign=sign2;
     return ans;
}
/*int main(){
  string s1,s2;
  cin>>s1>>s2;
  UnlimitedInt*p=new UnlimitedInt(s1);
  UnlimitedInt*q=new UnlimitedInt(s2);
    cout<<p->to_string()<<"/"<<q->to_string()<<endl;
    cout<<p->div(p,q)->to_string()<<endl;
      cout<<p->to_string()<<"/"<<q->to_string()<<endl;
}*/
