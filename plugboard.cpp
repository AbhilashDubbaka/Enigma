#include "errors.h"
#include "helper.h"
#include "plugboard.h"
#include <iostream>
using namespace std;

Plugboard::Plugboard(){
  for(int i = 0; i < alpha_size; i++){
    mapping[i] = i;
  }
}

int Plugboard::set_plugboard(const char* plugboard_config_file){

  string input;
  int number_1 = 0;
  int number_2 = 0;
  int count_plugboard_pair = 0;

  ifstream in_stream;
  in_stream.open(plugboard_config_file);

  if(!is_file_open_success(in_stream, plugboard_config_file)){
    in_stream.close();
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  in_stream >> input;

  while(!in_stream.eof()){

    if(!is_number(input, plugboard_config_file)){
      in_stream.close();
      return NON_NUMERIC_CHARACTER;
    }

    /* Converts the string into an integer. */
    number_1 = stoi(input);

    if(!is_number_valid(number_1, plugboard_config_file)){
      in_stream.close();
      return INVALID_INDEX;
    }

    /* Every number in the mapping array was made to equal its position in the constructor.
       If the number does not match its position in the array, then it must have been mapped
       already. */
    if(mapping[number_1] != number_1){
      cerr << "Contact " << number_1 << " has already been connected with another contact or " << endl;
      cerr << "is attempting to connect with itself in this file: " << plugboard_config_file << endl;
      cerr << "Please change this or use a different file." << endl;
      in_stream.close();
      return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
    }

    in_stream >> input;

    /*If the file has reached the EOF flag at this point, then it has a mapping from above
      but has no corresponding pair, therefore, there are an odd number of parameters. */
    if(in_stream.eof()){
      cerr << "There are an odd number of parameters in this file: " << plugboard_config_file << endl;
      cerr << "Please change this or use a different file." << endl;
      in_stream.close();
      return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    }

    if(!is_number(input, plugboard_config_file)){
      in_stream.close();
      return NON_NUMERIC_CHARACTER;
    }

    number_2 = stoi(input);

    if(!is_number_valid(number_2, plugboard_config_file)){
      in_stream.close();
      return INVALID_INDEX;
    }

    if(mapping[number_2] != number_2 || number_1 == number_2){
      cerr << "Contact " << number_2 << " has already been connected with another contact or " << endl;
      cerr << "is attempting to connect with itself in this file: " << plugboard_config_file << endl;
      cerr << "Please change this or use a different file." << endl;
      in_stream.close();
      return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
    }

    mapping[number_1] = number_2;
    mapping[number_2] = number_1;

    count_plugboard_pair++;
    in_stream >> input;

    if(count_plugboard_pair == (alpha_size / 2) && !in_stream.eof()){
      cerr << "There are too many mappings in the file: " << plugboard_config_file << endl;
      cerr << "Please change this or use a different file." << endl;
      in_stream.close();
      return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    }
  }

  in_stream.close();
  return NO_ERROR;
}

int Plugboard::encrypt(int letter){
  return mapping[letter];
}
