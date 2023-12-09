#include <iostream>
#include <armadillo>

using namespace arma;

int main(){
    mat A = randu<mat>(5, 5)*10;
    A.print("A = \n");
    cout<<"A的第（2，3）个元素为："<<A(1,2)<<endl;
}
