// 
// Some boring night.
// Require -
//  count the number of integer within some range [start, end] that contains no digit of '5' in it.
// Comment -
//  problem from codewar, and I just get bored and want to write some code.
//
#include <cmath>
#include <iostream>
#include <cassert>

using namespace std;
int check(int start , int end) ;
int dontGiveMeFive(int start, int end)
{
  assert();
  if(start < 0 ){return check(1,-start) + check(0,end); }
  else{return check(start, end); }
  return 0;
}
int check(int start , int end){
  if(!(start>=0 && end>=0)) return 0;
  int init = 1 + end - start  ;
  int hm = 1 , hn =1, ts = start ,te = end ;
  int weight = 1;

  while( ts / 10) {hm++; ts/=10; }
  while( te / 10) {hn++; te/=10; }
  weight = 1;

  for(; hn > 0; ){
    if(hm<hn){
        ts = 0 ;
    }
    if(1 == weight){ // only one possibility
      if(ts <= 5 && te >= 5 ){
        init -= int(pow(10,hn-1));
        weight = te -ts ;
      }
      else{
        weight = te - ts +1  ;
      }
    }
    else{ // more than one possibility
      // [ts, 9]
      int w0=0,w1 = 0,w2 =0 ;
      if(ts <= 5){
        init -= int(pow(10, hn-1));
        w0 = 9-ts;
      }
      else{
        w0 = 10-ts;
      }
      if(te >= 5){
        init -= int(pow(10, hn-1));
        w1 = te ;
      }
      else{
        w1 = te;
      }
      w2 =  ( weight -2 ) * 9 ;
      if( weight - 2 > 0 ){
        init -= (weight -2 )* int(pow(10, hn-1)) ;
      }
      weight = w0 + w1 + w2 ;
    }
    cout << ts << " " << te << endl ;
    cout << hm << " " << hn << endl ;
    cout << weight << endl;
    if(hn>hm){hn--; }
    else{
      hn--; hm--;
    }
    if(0 == hn ) break;
    ts= (start/int(pow(10,hm-1)))%10;
    te= (end/int(pow(10,hn-1)))%10;
  }

  cout << "Check(" << start << ", " << end << " ) = " << init << endl;
  return init ;
}
int main(){
  cout << dontGiveMeFive(4,5) << endl; ;
}
