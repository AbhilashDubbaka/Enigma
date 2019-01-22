#include "errors.h"
#include "helper.h"
#include "rotor.h"
#include <iostream>
using namespace std;

Rotor::Rotor() : position(0), next_rotor(nullptr){
  for(int i = 0; i < alpha_size; i++){
    mapping_forward[i] = i;
    mapping_backward[i] = i;
    notches[i] = 0;
  }
}

int Rotor::set_rotor(const char* rotor_config_file){

  string input;
  int number = 0;
  int count_rotor_input = 0;

  ifstream in_stream;
  in_stream.open(rotor_config_file);

  if(!is_file_open_success(in_stream, rotor_config_file)){
    in_stream.close();
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  in_stream >> input;

  while(!in_stream.eof() && count_rotor_input < (alpha_size * 2)){

    if(!is_number(input, rotor_config_file)){
      in_stream.close();
      return NON_NUMERIC_CHARACTER;
    }

    /* Converts the string into an integer. */
    number = stoi(input);

    if(!is_number_valid(number, rotor_config_file)){
      in_stream.close();
      return INVALID_INDEX;
    }

    if(count_rotor_input < alpha_size){
      for(int i = 0; i < count_rotor_input; i++){
        if(mapping_forward[i] == number){
          cerr << "Invalid mapping of input " << count_rotor_input << " to output " << endl;
          cerr << number << " (output " <<  number << " is already mapped to from input " << endl;
          cerr << i << ") in rotor file: " << rotor_config_file << endl;
          cerr << "Please change this or use a different file." << endl;
          in_stream.close();
          return INVALID_ROTOR_MAPPING;
        }
      }
      mapping_forward[count_rotor_input] = number;
    }

    if(count_rotor_input >= alpha_size && count_rotor_input < (alpha_size * 2)){
      if(notches[number] == 0){
        notches[number] = 1;
      }
      else{
        cerr << "This position has already been specified a notch in rotor file: " << rotor_config_file << endl;
        cerr << "Please change this or use a different file." << endl;
        in_stream.close();
        return INVALID_ROTOR_MAPPING;
      }
    }

    count_rotor_input++;
    in_stream >> input;
  }

  if((!in_stream.eof() && count_rotor_input == (alpha_size * 2)) || count_rotor_input < alpha_size){
    cerr << "There are an incorrect number of parameters in the file: " << rotor_config_file << endl;
    cerr << "Please change this or use a different file." << endl;
    in_stream.close();
    return INVALID_ROTOR_MAPPING;
  }

  /* Creating the backwards mapping array to use when a letter is coming back from the reflector. */
  for(int i = 0; i < alpha_size; i++){
    for(int j = 0; j < alpha_size; j++){
      if(i == mapping_forward[j])
        mapping_backward[i] = j;
    }
  }

  in_stream.close();
  return NO_ERROR;
}

void Rotor::set_position(int number){
  position = number;
}

void Rotor::rotate(){
  position = (position + 1) % alpha_size;
  if(notches[position] && next_rotor != nullptr){
    next_rotor->rotate();
  }
}

int Rotor::encrypt_forward(int letter){
  return ((mapping_forward[(letter + position) % alpha_size] - position + alpha_size) % alpha_size);
}

int Rotor::encrypt_backward(int letter){
  return ((mapping_backward[(letter + position) % alpha_size] - position + alpha_size) % alpha_size);
}
