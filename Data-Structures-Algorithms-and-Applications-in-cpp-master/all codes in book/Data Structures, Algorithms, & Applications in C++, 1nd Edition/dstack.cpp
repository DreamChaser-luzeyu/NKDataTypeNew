// derived formula based stack

#include <iostream.h>
#include "dstack.h"

void main(void)
{
   int x;
   Stack<int> S(3);
   try {S.Add(1).Add(2).Add(3).Add(4);}
   catch (...) {
      cout << "Could not complete additions" << endl;
      }
   cout << "Stack should be 123" << endl;
   cout << "Stack top is " << S.Top() << endl;
   try {
      S.Delete(x);
      cout << "Deleted " << x << endl;
      S.Delete(x);
      cout << "Deleted " << x << endl;
      S.Delete(x);
      cout << "Deleted " << x << endl;
      S.Delete(x);
      cout << "Deleted " << x << endl;
      }
   catch (OutOfBounds) {
      cout << "Last delete failed " << endl;
      }
}
