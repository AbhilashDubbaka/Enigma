#ifndef REFLECTOR_H
#define REFLECTOR_H

#include "helper.h"

/* Creates an instance of a Reflector object, which is a component of
   an Enigma machine. */
class Reflector{

 private:
  /* Contains the mapping from one letter to another. Each entry
     specifies the mapping of the letter represented by the position
     in the array to the letter, represented by the number provided
     in the array. */
  int mapping[alpha_size];

 public:
  /* Constructor maps the mapping array to the position numbers i.e.
     mapping[i] = i so all 26 letters map to themselves as default */
  Reflector();

  /* Set the reflector using the configuration file provided by the
     user. It takes in the name of the file that contains the
     mappings. It checks that the contents of that file are only
     numbers between 0 and 25, that any letter is not mapped to
     itself or to more than one other letter and that there are
     exactly 13 pairs of mappings. It returns an integer, which
     corresponds with an error code. If everything is configured
     successfully, it returns NO_ERROR (i.e. 0), otherwise it will
     provide an appropriate error message to the user. */
  int set_reflector(const char* reflector_config_file);

  /* Encrypts a letter using the mapping array.
     It takes in a number, which corresponds with a letter, and
     returns the number in that position in the array. */
  int encrypt(int letter);
};

#endif
