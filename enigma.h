#ifndef ENIGMA_H
#define ENIGMA_H

#include "plugboard.h"
#include "reflector.h"
#include "rotor.h"
#include <string>

/* Creates an instance of an Enigma machine object. */
class Enigma{

 private:
  /* The number of arguments given in the command line. */
  int number_of_arguments;

  /* The values of arguments given in the command line. These
     are filenames to configure the plugboard, reflector and
     rotors. */
  char** values_of_arguments;

  /* Used to return the corresponding error code, when the
     program fails. */
  int error_code;

  /* Set to 1 if all the components given in the command line
     have been successfully configured, i.e. the content has
     been checked and they can be correctly used for
     encryption. */
  int success_config;

  /* Keeps account of the number of rotors provided. */
  int number_of_rotors;

  /* Pointer to a plugboard object. */
  Plugboard* plugboard;

  /* Pointer to a reflector object. */
  Reflector* reflector;

  /* Pointer to an array of rotor objects. */
  Rotor** rotor;

 public:
  /* Constructor takes in an int and a pointer to an array
     for char, which are stored in the number of arguments
     and values of arguments data members. These are the
     number of arguments and filenames provided in the
     command line. All the data members are initialised to
     0 or nullptr if they are pointers. */
  Enigma(int argc, char** argv);

  /* Checks if the number of arguments provided on the 
     command line is at least 3 or more than 4, as otherwise, 
     there isn't enough information to create an enigma machine. 
     It returns an error code if it fails and otherwise, it 
     returns NO_ERROR i.e. 0. */
  int check_configuration_input();

  /* Creates the components for the enigma machine using 
     the command line input. These are the plugboard, 
     reflector and rotors (if any). */
  int set_enigma_components();

  /* Set the initial positions provided by the configuration
     files for all the rotors. It takes in the name of the
     rotor position file and returns an integer, which
     corresponds to an error code. If it is 0, then there
     are no errors. It checks that the configuration file
     has no invalid entries, i.e. that it only has numbers
     between 0 and 25. */
  int set_rotor_positions(const char* rotor_pos_config_file);

  /* Encrypts the user's message, one character at a time.
     It takes in the string inputted by the user. First, it
     removes any white spaces in the text and then encrypts
     each character and outputs it to the user. It returns
     an integer, which represents an error code. If there
     is no error, it returns NO_ERROR, i.e. 0. */
  int encrypt(std::string input);

  /* Destructor that deletes the memory on the HEAP allocated
     for the plugboard, reflector and rotors. This is only
     executed if the components were successfully created. */
  ~Enigma();
};

#endif
