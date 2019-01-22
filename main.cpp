#include "errors.h"
#include "helper.h"
#include "enigma.h"
#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char** argv){

  int error_code = 0;
  Enigma enigma(argc,argv);

  /* Checking there are enough configurations files for the enigma
     machine. */
  error_code = enigma.check_configuration_input();
  if(error_code)
    return error_code;
  
  /* Setting up the components for the enigma machine and if any
     issues, it will return with the corresponding error code. */
  error_code = enigma.set_enigma_components();
  if(error_code)
    return error_code;

  string input;

  /* Checking if the user is inputting a message into the terminal
     or via an input file. If it's through the terminal and the
     output is on the terminal, it will give a welcome message
     and ask for the message to encrypt. */
  if(isatty(STDIN_FILENO) && isatty(STDOUT_FILENO)){
    cout << "You have successfully configured the enigma machine." << endl;
    cout << "This machine can be used to encrypt a message for you." << endl;
    cout << "Please enter the message you want to encrypt in uppercase letters from A to Z. " << endl;
    getline(cin >> ws, input);
    error_code = enigma.encrypt(input);
    if(error_code)
      return error_code;
  }
  else{
    while(getline(cin >> ws, input)){
      error_code = enigma.encrypt(input);
      if(error_code)
        return error_code;
    }
  }

  /* This just adds an extra line if the message is printed on the terminal
     for presentation purposes. */
  if(isatty(STDOUT_FILENO)){
    cout << endl;
  }

  return NO_ERROR;
}
