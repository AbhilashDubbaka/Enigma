# Enigma
An Enigma Machine implementation in C++

The Enigma machine can encrypt and decrypt messages that are written in the letters A-Z (all 26 uppercase alphabet). The message to be encoded can be written directly in the terminal or can be written in input.txt file. This project was the second C++ coursework as part of MSc Computing Science at Imperial College London.

To run it with the original message in input.txt, you need to provide the parameters in the following order:
```
enigma plugboard-file reflector-file rotor-file(s) rotor-positions-file (the rotor and rotor position files are optional).
```
For example, you can do the following:
```
./enigma plugboards/I.pb reflectors/I.rf rotors/I.rot rotors/II.rot rotors/III.rot rotors/I.pos < input.txt
```
or if you want to type the message in yourself, run it in the same way without < input.txt
