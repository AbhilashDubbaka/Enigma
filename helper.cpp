#include "helper.h"
#include <iostream>
using namespace std;

bool is_file_open_success(ifstream& in_stream, const char* filename){
  if(in_stream.fail()){
    cerr << "There is an error opening the file: " << filename << endl;
    return false;
  }
  return true;
}

bool is_number(string input, const char* filename){
  for(unsigned int i = 0; i < input.size(); i++){
    if(input[i] < '0' || input[i] > '9'){
      cerr << "There is a non-numeric character in the file: " << filename << endl;
      cerr << "Please remove this character or use a different file." << endl;
      return false;
    }
  }
  return true;
}

bool is_number_valid(int number, const char* filename){
  if(number < 0 || number > 25){
    cerr << "There is a number that is not between 0 and 25 in the file: " << filename << endl;
    cerr << "Please change this number or use a different file." << endl;
    return false;
  }
  return true;
}

bool is_space(unsigned char c){
  return (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f');
}
