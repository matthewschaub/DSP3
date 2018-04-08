#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

class Hash{
private:
  const int tableSize = 10001; 
public:
  int* inputStream;
  int getTablesize();
  int linearHash(int*, int, int);  
  void printResults();
};

int main(){

  Hash hashObj; 
  //const int tableSize = 10001;
  srand(time(NULL));
  
  //Create and initialize a random sequence to be used as the input stream
  //Note, these are not independent sequeneces but build on the previous
  //i.e the stream for 1000 is random, stream for 2000 is the first 1000 + 1000 new random
  int inputStream[hashObj.getTablesize() - 1];
  for(int i = 0; i < hashObj.getTablesize() - 1; i++)
  {
    inputStream[i] = rand(); 
  }
  hashObj.inputStream = inputStream; 
  //Creates an array to be mapped to
  //int hashTable[tableSize]; 
  //for(int i = 0; i < tableSize; ++i)
  //{
  // hashTable[i] = -1;
  //}


  hashObj.printResults();

  return 0; 
}

int Hash::getTablesize(){
    return tableSize;
}

int Hash::linearHash(int* input, int streamSize, int tableSize){
  int collisions = 0; 
  int hashTable[tableSize]; 
  for(int i = 0; i < tableSize; ++i)
  {
    hashTable[i] = -1;
  }
  //
  for(int i = 0; i < streamSize; i++)
  {
    int j = input[i]%streamSize; 
    if(hashTable[j] != -1)
    {
      collisions++;
      j++;  
    }
    else
      hashTable[j] = input[i];

  }
  return collisions; 
}

void Hash::printResults() //prints the menu
{
  std::cout << std::setw(91) << std::setfill('=') << '\n'<< std::setfill(' ');
  std::cout << std::left << std::setw(42) << ' ' <<  "Results" << std::setw(18) << std::right << "\n";
  std::cout << std::setw(91) << std::setfill('=') << '\n'<< std::setfill(' ');
  std::cout << "Size" << std::setw(16) << std::right << '|';
  for(int i = 1; i < 11; i++)
  {
    std::cout << std::right << std::setw(5) << i*1000 << std::setw(2) << std::right << '|'; 
  }    
  std::cout << "\nLinear" << std::setw(14) << std::right << '|';
  for(int i = 1; i < 11; i++)
  {
    std::cout << std::right << std::setw(5) << "xxxx" << std::setw(2) << std::right << '|'; 
  }    
  std::cout << "\nQuadratic" << std::setw(11) << std::right << '|';
  for(int i = 1; i < 11; i++)
  {
    std::cout << std::right << std::setw(5) << "xxxx" << std::setw(2) << std::right << '|'; 
  }    
  std::cout << "\nFailures Quadratic" << std::setw(2) << std::right << '|';
  for(int i = 1; i < 11; i++)
  {
    std::cout << std::right << std::setw(5) << "xxxx" << std::setw(2) << std::right << '|'; 
  }  
  std::cout << "\nFailures Double" << std::setw(5) << std::right << '|';
  for(int i = 1; i < 11; i++)
  {
    std::cout << std::right << std::setw(5) << "xxxx" << std::setw(2) << std::right << '|'; 
  }  
  std::cout << std::endl << std::setw(91) << std::setfill('=') << '\n'<< std::setfill(' ');
} 