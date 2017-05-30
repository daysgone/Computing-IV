/* simple xml "parser"
 * File:   main.cpp
 * Author: Brian Day < brian_day@student.uml.edu >
 * Program dependent files: xmlElement.cpp, xmlElement.h, xmlReader.cpp, xmlReader.h, music.xml
 * Created 2013/09/05
 */

#include <iostream>
#include <fstream>
#include <string>

#include "xmlReader.h"

/**
 * C++ default function
 * @param argc	number of command line arguments
 * @param argv	array of pointers to command line arguments
 */
int main( int argc, char* argv[] ) {
  std::string sfileName =  "large.xml" ; //file to parse
  
  std::cout << "*** Program Start ***" << std::endl ;
  
  xmlReader( sfileName ) ; //process the file with given name as a string
  
  std::cout << std::endl << "***       Program Ended      ***" << std::endl ;
  
  return 0;
}

