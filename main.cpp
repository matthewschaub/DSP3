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

int main(){

  Hash hashObj; //creates Hash object

  srand(time(NULL)); //seed rand
  int inputStream[hashObj.getTablesize() - 1]; //array to hold random numbers
  for(int i = 0; i < hashObj.getTablesize() - 1; i++)
  {
    inputStream[i] = rand(); //fill array 
  }
  hashObj.inputStream = inputStream; //pass to hash object
  hashObj.printResults(); //print the results of the tests

  return 0; 
}
//Getter function
int Hash::getTablesize(){
    return tableSize;
}
//double hashing function
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
    int key = input[i] % tableSize; //set key
    int r = 9973 - (input[i] % 9973); //set r value for double hash
    inserted = false; //control bool
    do //do while logic to execute insertion test until a open spot or failure
    {
      if(hashTable[key] == -1) //if empty
      {
        hashTable[key] = input[i]; //insert it
        inserted = true;
      }
      else
      {
        collisions++; 
        key = (key + r)%tableSize; //go to next location
        if(input[i] % tableSize == key)//if we get back to starting location
        {
          failures++;
          inserted = true; //fail and escape to prevent endless loop 
        }
      }
    }
    while(!inserted); 
  }
  return collisions;   
}
//failures function
//most likely a better way to do this as my code is redundant but gets the job done
//same logic as above see documentation there. Return value changes
int Hash::failsDoubleHash(int* input, int streamSize, int tableSize){
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
//nearly identical as double hashing will denote differences
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
        key = (input[i]%tableSize + (j*j))%tableSize; //logic for quadratic hash
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

int Hash::failsQuadraticHash(int* input, int streamSize, int tableSize){
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
        key = (input[i]%tableSize + (j*j))%tableSize;
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
        j = (j+1)%tableSize;  //logic for linear hash
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
    std::cout << std::right << std::setw(5) << failsQuadraticHash(inputStream, i*1000, getTablesize()) << std::setw(2) << std::right << '|'; 
  }  
  std::cout << "\nFailures Double" << std::setw(5) << std::right << '|';
  for(int i = 1; i < 11; i++)
  {
    std::cout << std::right << std::setw(5) << failsDoubleHash(inputStream, i*1000, getTablesize()) << std::setw(2) << std::right << '|'; 
  }  
  std::cout << std::endl << std::setw(91) << std::setfill('=') << '\n'<< std::setfill(' ');
} 