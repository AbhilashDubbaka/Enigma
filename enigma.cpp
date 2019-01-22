#include "errors.h"
#include "enigma.h"
#include <iostream>
#include <algorithm>
using namespace std;

Enigma::Enigma(int argc, char** argv)
  : number_of_arguments(argc), values_of_arguments(argv), error_code(0), success_config(0),
    number_of_rotors(0), plugboard(nullptr), reflector(nullptr), rotor(nullptr){}

int Enigma::check_configuration_input(){

  if(number_of_arguments < 3 || number_of_arguments == 4){
    cerr << "There are not enough command line parameters provided. ";
    cerr << "Please provide the file parameters in the following order: ";
    cerr << "enigma plugboard-file reflector-file rotor-file(s) rotor-positions-file ";
    cerr << "(the rotor and rotor position files are optional).";
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }
  
  return NO_ERROR;
}


int Enigma::set_enigma_components(){

  /* Creating space on the HEAP for the plugboard, reflector, and rotors (if any). */
  number_of_rotors = number_of_arguments - 4;
  char* plugboard_config_file = values_of_arguments[1];
  char* reflector_config_file = values_of_arguments[2];

  plugboard = new (nothrow) Plugboard();
  reflector = new (nothrow) Reflector();

  if(plugboard == nullptr || reflector == nullptr){
    cerr << "Sorry, ran out of memory";
    return NOT_ENOUGH_MEMORY;
  }

  if(number_of_rotors >= 1){
    rotor = new (nothrow) Rotor*[number_of_rotors];
    if(rotor == nullptr){
      cerr << "Sorry, ran out of memory";
      return NOT_ENOUGH_MEMORY;
    }
  }

  /* Setting up the plugboard. */
  error_code = plugboard->set_plugboard(plugboard_config_file);
  if(error_code)
    return error_code;

  /* Setting up the reflector. */
  error_code = reflector->set_reflector(reflector_config_file);
  if(error_code)
    return error_code;

  /* Creating the individual rotor objects. */
  if(number_of_rotors >= 1){
    for(int i = 0; i < number_of_rotors; i++){
      rotor[i] = new (nothrow) Rotor();
      if(rotor[i] == nullptr){
        cerr << "Sorry, ran out of memory";
        for(int j = i; j >= 0; j--){
          delete rotor[j];
        }
        return NOT_ENOUGH_MEMORY;
      }

      /* Setting the rotor configuration using the file given in the command line. */
      error_code = rotor[i]->set_rotor(values_of_arguments[i+3]);
      if(error_code){
        for(int j = i; j >= 0; j--){
          delete rotor[j];
        }
        return error_code;
      }
    }

    /* Setting the initial starting rotor positions. */
    error_code = set_rotor_positions(values_of_arguments[number_of_arguments - 1]);
    if(error_code){
      for(int i = 0; i < number_of_rotors; i++){
        delete rotor[i];
      }
      return error_code;
    }

    /* Connecting the current rotor to the next rotor. */
    for(int i = number_of_rotors - 1; i > 0; i--){
      rotor[i]->next_rotor = rotor[i-1];
    }
  }

  success_config = 1;
  return NO_ERROR;
}

int Enigma::set_rotor_positions(const char* rotor_pos_config_file){

  string input;
  int number = 0;
  int count_rotor_pos = 0;

  ifstream in_stream;
  in_stream.open(rotor_pos_config_file);

  if(!is_file_open_success(in_stream, rotor_pos_config_file)){
    in_stream.close();
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  in_stream >> input;

  while(!in_stream.eof() && count_rotor_pos < number_of_rotors){

    if(!is_number(input, rotor_pos_config_file)){
      in_stream.close();
      return NON_NUMERIC_CHARACTER;
    }

    /* Converts the string into an integer. */
    number = stoi(input);

    if(!is_number_valid(number, rotor_pos_config_file)){
      in_stream.close();
      return INVALID_INDEX;
    }

    rotor[count_rotor_pos]->set_position(number);
    count_rotor_pos++;
    in_stream >> input;
  }

  if(!in_stream.eof()){
    cerr << "WARNING: The rotor positions file " << rotor_pos_config_file;
    cerr << " has more positions than number of rotors supplied. " << endl;
    cerr << "The additional positions have been ignored." << endl;
  }

  if(count_rotor_pos != number_of_rotors){
    cerr << "No starting position for rotor " << count_rotor_pos;
    cerr << " in rotor position file: " << rotor_pos_config_file << endl;
    cerr << "Please change this or use a different file." << endl;
    in_stream.close();
    return NO_ROTOR_STARTING_POSITION;
  }

  in_stream.close();
  return NO_ERROR;
}

int Enigma::encrypt(string input){
  /* Removes white space in the input from the user. */
  input.erase(remove_if(input.begin(), input.end(), is_space), input.end());

  for(unsigned int i = 0; i < input.size(); i++){
    if(input[i] < 'A' || input[i] > 'Z'){
      cerr << endl;
      cerr << input[i] << " is not a valid input character (input characters must be upper case letters A-Z)!" << endl;
      return INVALID_INPUT_CHARACTER;
    }

    int letter_index = static_cast<int>(input[i] - 'A');

    if(number_of_rotors > 0)
      rotor[number_of_rotors - 1]->rotate();

    letter_index = plugboard->encrypt(letter_index);

    for(int i = number_of_rotors - 1; i >= 0; i--){
      letter_index = rotor[i]->encrypt_forward(letter_index);
    }

    letter_index = reflector->encrypt(letter_index);

    for(int i = 0; i < number_of_rotors; i++){
      letter_index = rotor[i]->encrypt_backward(letter_index);
    }

    letter_index = plugboard->encrypt(letter_index);

    input[i] = static_cast<char>(letter_index + 'A');
    cout << input[i];
  }

  return NO_ERROR;
}

Enigma::~Enigma(){
  delete plugboard;
  delete reflector;
  if(number_of_rotors >= 1){
    if(success_config){
      for(int i = 0; i < number_of_rotors; i++){
        delete rotor[i];
      }
    }
    delete[] rotor;
  }
}
