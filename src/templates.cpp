#include "templates.h"

int gcd (int a, int b) {
  long r;
  while(b!=0){
    r = a % b;
    a = b;
    b = r;
  }
  return a;
}
