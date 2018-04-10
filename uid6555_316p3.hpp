#ifndef UID6555_316P2_H_INCLUDED
#define UID6555_316P2_H_INCLUDED
#ifndef uid6555_316P2_H_INCLUDED
#define uid6555_316P2_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

//Hash class to run all the tests
class Hash{
private:
  const int tableSize = 10001; 
public:
  int* inputStream; //input stream is randomly generated in main
  int getTablesize(); //getter function
  int linearHash(int*, int, int); 
  int quadraticHash(int*, int, int);
  int failsQuadraticHash(int*, int, int);
  int doubleHash(int*, int, int);  
  int failsDoubleHash(int*, int, int); 
  void printResults();
};

#endif // DSP2_H_INCLUDED
#endif // UID6555_316P2_H_INCLUDED