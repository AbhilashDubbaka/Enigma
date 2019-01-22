#ifndef ROTOR_H
#define ROTOR_H

#include "helper.h"

/* Creates an instance of a Rotor object, which is a component of
   an Enigma machine. */
class Rotor{

 private:
  /* Contains the mapping from one letter to another. Each entry
     specifies the mapping of the letter represented by the position
     in the array to the letter, represented by the number provided
     in the array. This mapping is used for encrypting a letter,
     which is coming from the plugboard. */
  int mapping_forward[alpha_size];

  /* Contains the mapping from one letter to another. Each entry
     specifies the mapping of the letter represented by the position
     in the array to the letter, represented by the number provided
     in the array. This mapping is used for encrypting a letter,
     which is coming from the reflector. */
  int mapping_backward[alpha_size];

  /* Contains the notches for a rotor. Each entry specifies the
     letter represented by the position in the array and has a 1 if
     that is a letter is a notch i.e. triggers the rotor to its
     left to rotate once. */
  int notches[alpha_size];

  /* Used to keep account of the relative position to the position
     0. */
  int position;

 public:
  /* Constructor maps the forward and backward mapping arrays to
     the position numbers i.e. mapping[i] = i so all 26 letters
     map to themselves as default. It makes all the notches equal
     to 0 i.e. no notch at that letter as default. It puts the
     position equal to 0 and next_rotor point to null. */
  Rotor();

  /* Set the rotor using the configuration file provided by the
     user. It takes in the name of the file that contains the
     mappings. It checks that the contents of that file are only
     numbers between 0 and 25, that any letter is not mapped to
     itself or to more than one other letter and that there are
     exactly 26 mappings. Additionally, it checks that there are
     a maximum of 26 notches. It returns an integer, which
     corresponds with an error code. If everything is configured
     successfully, it returns NO_ERROR (i.e. 0), otherwise it will
     provide an appropriate error message to the user. */
  int set_rotor(const char* rotor_config_file);

  /* Set the initial position provided by the configuration files.
     It takes in a number, which specifies the current rotor's
     initial position. */
  void set_position(int number);

  /* Simulates a rotation on a rotor by increasing the position of
     that rotor by 1. Then, it checks if the rotation has triggered
     a notch and if it does, it increases the position of the next
     rotor by 1, assuming it is not the last rotor before the
     reflector. */
  void rotate();

  /* Encrypts a letter using the mapping array, which is going
     towards the reflector. It takes in a number, which corresponds
     with a letter, and returns the number in that position in the
     array, after accounting for the position change, caused by the
     rotations of the rotors. */
  int encrypt_forward (int letter);

  /* Encrypts a letter using the mapping array, which is going back
     towards the plugboard and then the user. It takes in a number,
     which corresponds with a letter, and returns the number in that
     position in the array, after accounting for the position change,
     caused by the rotations of the rotors. */
  int encrypt_backward (int letter);

  /* Pointer to the next rotor on the current rotor's left. */
  Rotor* next_rotor;
};

#endif
