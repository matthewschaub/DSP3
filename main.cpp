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
  int quadraticHash(int*, int, int);
  int quadraticHash(int*, int, int, char);
  int doubleHash(int*, int, int);  
  int doubleHash(int*, int, int, char); 
  void printResults();

};

int main(){

  Hash hashObj; 

  srand(time(NULL));
  int inputStream[hashObj.getTablesize() - 1];
  for(int i = 0; i < hashObj.getTablesize() - 1; i++)
  {
    inputStream[i] = rand(); 
  }
  hashObj.inputStream = inputStream; 
  hashObj.printResults();

  return 0; 
}

int Hash::getTablesize(){
    return tableSize;
}
int Hash::doubleHash(int* input, int streamSize, int tableSize){
  int collisions = 0;
  int failures = 0; 
  bool inserted; 
  int hashTable[tableSize]; 
  for(int i = 0; i < tableSize; ++i)
  {
    hashTable[i] = -1;
  }

  for(int i = 0; i < streamSize; i++)
  {
    int key = input[i] % tableSize;
    int r = 9973 - (input[i] % 9973); 
    inserted = false; 
    do
    {
      if(hashTable[key] == -1)
      {
        hashTable[key] = input[i];
        inserted = true;
      }
      else
      {
        collisions++;
        //key = (key + 1)%tableSize;
        key = (key + r)%tableSize; 
        if(input[i] % tableSize == key)
        {
          failures++;
          inserted = true;
        }
      }
    }
    while(!inserted); 
  }
  return collisions;   
}
int Hash::doubleHash(int* input, int streamSize, int tableSize, char f){
  int collisions = 0;
  int failures = 0; 
  bool inserted; 
  int hashTable[tableSize]; 
  for(int i = 0; i < tableSize; ++i)
  {
    hashTable[i] = -1;
  }

  for(int i = 0; i < streamSize; i++)
  {
    int key = input[i] % tableSize;
    int r = 9973 - (input[i] % 9973); 
    inserted = false; 
    do
    {
      if(hashTable[key] == -1)
      {
        hashTable[key] = input[i];
        inserted = true;
      }
      else
      {
        collisions++;
        //key = (key + 1)%tableSize;
        key = (key + r)%tableSize; 
        if(input[i] % tableSize == key)
        {
          failures++;
          inserted = true;
        }
      }
    }
    while(!inserted); 
  }
  return failures;   
}
int Hash::quadraticHash(int* input, int streamSize, int tableSize){
  int collisions = 0;
  int failures = 0; 
  bool inserted; 
  int hashTable[tableSize]; 
  for(int i = 0; i < tableSize; ++i)
  {
    hashTable[i] = -1;
  }

  for(int i = 0; i < streamSize; i++)
  {
    int j = 0; 
    int key = input[i]%tableSize;
    inserted = false; 
    do
    {
      if(hashTable[key] == -1)
      {
        hashTable[key] = input[i];
        inserted = true; 
      }
      else
      {
        collisions++;
        j++;
        key = (key + (j*j))%tableSize;
        if(input[i] % tableSize == key)
        {
          failures++;
          inserted = true;  
        }
      }
    }
    while(!inserted);
  }
  return collisions;   
}
int Hash::quadraticHash(int* input, int streamSize, int tableSize, char f){
  int collisions = 0;
  int failures = 0; 
  bool inserted; 
  int hashTable[tableSize]; 
  for(int i = 0; i < tableSize; ++i)
  {
    hashTable[i] = -1;
  }

  for(int i = 0; i < streamSize; i++)
  {
    int j = 0; 
    int key = input[i]%tableSize;
    inserted = false; 
    do
    {
      if(hashTable[key] == -1)
      {
        hashTable[key] = input[i];
        inserted = true; 
      }
      else
      {
        collisions++;
        j++;
        key = (key + (j*j))%tableSize;
        if(input[i] % tableSize == key)
        {
          failures++;
          inserted = true;  
        }
      }
    }
    while(!inserted);
  }
  return failures;   
}
int Hash::linearHash(int* input, int streamSize, int tableSize){
  int collisions = 0; 
  int hashTable[tableSize]; 
  bool inserted; 
  for(int i = 0; i < tableSize; ++i)
  {
    hashTable[i] = -1;
  }
  //
  for(int i = 0; i < streamSize; i++)
  {
    int j = input[i]%tableSize;
    inserted = false;  
    do
    { 
      if(hashTable[j] != -1)
      {
        collisions++;
        j = (j+1)%tableSize;  
      }
      else
      {
        hashTable[j] = input[i];
        inserted = true; 
      }
    }
    while(!inserted);
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
    std::cout << std::right << std::setw(5) << linearHash(inputStream, i*1000, getTablesize()) << std::setw(2) << std::right << '|'; 
  }    
  std::cout << "\nQuadratic" << std::setw(11) << std::right << '|';
  for(int i = 1; i < 11; i++)
  {
    std::cout << std::right << std::setw(5) << quadraticHash(inputStream, i*1000, getTablesize()) << std::setw(2) << std::right << '|'; 
  }
  std::cout << "\nDouble" << std::setw(14) << std::right << '|';
  for(int i = 1; i < 11; i++)
  {
    std::cout << std::right << std::setw(5) << doubleHash(inputStream, i*1000, getTablesize()) << std::setw(2) << std::right << '|'; 
  }  
  std::cout << "\nFailures Quadratic" << std::setw(2) << std::right << '|';
  for(int i = 1; i < 11; i++)
  {
    std::cout << std::right << std::setw(5) << quadraticHash(inputStream, i*1000, getTablesize(), 'f') << std::setw(2) << std::right << '|'; 
  }  
  std::cout << "\nFailures Double" << std::setw(5) << std::right << '|';
  for(int i = 1; i < 11; i++)
  {
    std::cout << std::right << std::setw(5) << doubleHash(inputStream, i*1000, getTablesize(), 'f') << std::setw(2) << std::right << '|'; 
  }  
  std::cout << std::endl << std::setw(91) << std::setfill('=') << '\n'<< std::setfill(' ');
} 