/* Error code if there is not enough memory on the heap -
   included here instead of the errors.h to avoid changing
   the skeleton file. */
#define NOT_ENOUGH_MEMORY                         12

#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <fstream>

const int alpha_size = 26;

/* Check if the file is able to open and read successfully. */
bool is_file_open_success(std::ifstream& in_stream, const char* filename);

/* Check if the input for the configuration files is a number.
   It takes in a string and it cycles through each character
   to check if it is a number or a non-numeric character. It
   prints out an error message if it is a non-numeric character.
   Returns false if there is a non-numeric character in the
   input. */
bool is_number(std::string input, const char* filename);

/* Check if the number is a valid number i.e. between 0 and 25.
   It takes in an integer and returns false if the number is
   outside this range. It prints out an error message if it is
   outside this range. */
bool is_number_valid(int number, const char* filename);

/* Check if there is a whitespace in the input from the user.
   It takes in a character to check if it is whitespace or not.
   Returns true if there is a white space as defined as a space,
   a horizontal tab, a carriage return, a new line, a vertical
   tab, and a form feed. */
bool is_space(unsigned char c);

#endif
