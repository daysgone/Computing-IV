/* Program: Build a tree in memory from inputs of user
 * File:   BuildTree.cpp
 * Author: brian, < brian_day@student.uml.edu >
 * Program dependent files: 
 * Created by JMH
 * Updated on 2013/12/1
 */

#include <iostream>
#include <fstream>
#include <string>

#include <boost/regex.hpp>              // for regex_match
#include <boost/algorithm/string.hpp>   // for iequals (case-insensitive match)

#include "BuildTree.hpp"

//testing variables
bool debug = true ;
bool tester = false ;


void cmdLineParser() {

  boost::cmatch what;
  // what[0] contains the entire matched string
  // what[1] contains the first matched group
  // what[2] contains the second matched group
  // what[3] etc.
  
  //add { element | attribute } parent-node-name new-node-name { new-node-content | new-node-value }
  boost::regex reBasicCmd( "^\\s*(add|print|help|quit).*", boost::regex::icase ) ;
  boost::regex reAddCmd( "^\\s*add\\s*(element|attribute)\\s(\\w+)\\s(\\w+)\\s*(\\w*)$" , boost::regex::icase ) ;
  //boost::regex reAddElementCmd( "^\\s*(a|add)\\s*(e|element)\\s(.+)\\s(.+)\\s*(.*)$", boost::regex::icase ) ;
  //boost::regex reAddAttributeCmd( "^\\s*(a|add)\\s*(a|attribute)\\s(.+)\\s(.+)\\s*(.*)$", boost::regex::icase ) ; 
  //boost::regex rePrintCmd( "^\\s*(p|print)\\s*$", boost::regex::icase ) ;
  //boost::regex reHelpCmd( "^\\s*(h|help)\\s*$", boost::regex::icase ) ;
  //boost::regex reQuitCmd( "^\\s*(q|quit|exit|bye)\\s*$", boost::regex::icase ) ;
  
  
  
  // <editor-fold defaultstate="collapsed" desc="Tester code">
  // loop through all hard-coded command strings for testing purposes
  if(tester){
  // <editor-fold defaultstate="collapsed" desc="Tester input">
    std::string strCmd[10] ; //string array does not have a size/length function
    strCmd[0] = "add element root first one" ;
    strCmd[1] = "  add element root second" ;
    strCmd[2] = "add  attribute first attr1 attr1value" ;
    strCmd[3] = "  add  attribute second attr2" ;//if no attribute value stated should put in ""
    strCmd[4] = "print" ;
    strCmd[5] = "quit" ;
    strCmd[6] = "another command" ;
    int nCmds = 7 ;
  // </editor-fold>
    for ( int n = 0 ; n < nCmds ; n++ ) {
      // user entry point
      std::cout << "\nYour command: " ;
      // cin >> strCmd ;
      std::cout << strCmd[n] << std::endl ;

      // string version of a matched group 
      // for building a bridge between the cmatch type and an STL sting so that we can
      // process matches with STL string functions
      std::string strWhat ;

      // test for a match of a basic command
      if ( boost::regex_match( strCmd[n].c_str(), what, reBasicCmd ) ) {
        // <editor-fold defaultstate="collapsed" desc="Debug code">
        std::cout << "  what.size() = " << what.size() << std::endl ;
        for ( int k = 0 ; k < what.size() ; k++ ) {
          strWhat = what[k] ;
          std::cout << "    what[" << k << "] = " << what[k] << " (" << strWhat.size()  << " chars)" << std::endl ;
        }
        // </editor-fold>

        // handle an ADD command
        if ( boost::iequals( strWhat, "add" ) ) {
          std::cout << "  Command is ADD" << std::endl ;

          // test for a match on the second word in the command
          if ( boost::regex_match( strCmd[n].c_str(), what, reAddCmd ) ) {
            // <editor-fold defaultstate="collapsed" desc="Debug code">

              for ( int k = 0 ; k < what.size() ; k++ ) {
                strWhat = what[k] ;
                std::cout << "    what[" << k << "] = " << what[k] << " (" << strWhat.size()  << " chars)" << std::endl ;
              }

            // </editor-fold>
            strWhat = what[1] ;

            // handle an ADD ELEMENT command
            if ( boost::iequals( strWhat, "element" ) ) {
              std::cout << "  Command is ADD ELEMENT" << std::endl ;
              std::cout << "  Continue with adding an element here." << std::endl ;
            } 
            // handle an ADD ATTRIBUTE command
            else if ( boost::iequals( strWhat, "attribute" ) ) {
              std::cout << "  Command is ADD ATTRIBUTE" << std::endl ;
              std::cout << "  Continue with adding an attribute here." << std::endl ;
            } 
            // parsing error: ADD is followed by an invalid keyword
            else {
              std::cout << "    Invalid ADD command: 2nd word must be 'element' or 'attribute'." << std::endl ;
            }
          } 
          // parsing error: ADD command syntax does not match the regular expression
          else {
            std::cout << "    Invalid ADD command syntax." << std::endl ;
          }
        } 

        // handle a PRINT command
        else if ( boost::iequals( strWhat, "print" ) ) {
          std::cout << "  Command is PRINT" << std::endl ;
          std::cout << "  Call your print function here." << std::endl ;
        } 

        // handle a QUIT command
        else if ( boost::iequals( strWhat, "quit" ) ) {
          std::cout << "  Command is QUIT" << std::endl ;
          std::cout << "  Goodbye." << std::endl ;
          return ;
        } 

        // parsing error: the first keyword is not ADD, PRINT, or QUIT
        else {
          std::cout << "  Invalid command: 1st word must be 'add', 'print', or 'quit'." << std::endl ;
        }
      }  
    }
  }
  // </editor-fold>
  std::string strCmdInput ;
  bool bQuit = 0 ;
  do {
    //user entry point
    std::cout << "\nYour command: " ;
    getline(std::cin , strCmdInput ); //getline used instead of cin since it breaks on spaces
    
  // string version of a matched group 
  // for building a bridge between the cmatch type and an STL sting so that we can
  // process matches with STL string functions
  std::string strWhat ;

  // test for a match of a basic command
  if ( boost::regex_match( strCmdInput.c_str(), what, reBasicCmd ) ) {
    std::cout << "basic command found" << std::endl ;
    std::cout << "  what.size() = " << what.size() << std::endl ;
    for ( int k = 0 ; k < what.size() ; k++ ) {
      strWhat = what[k] ;
      std::cout << "    what[" << k << "] = " << what[k] << " (" << strWhat.size()  << " chars)" << std::endl ;
    }
 
    // handle an ADD command
    if ( boost::iequals( strWhat, "add" ) ) {
      std::cout << "  Command is ADD" << std::endl ;

      // test for a match on the second word in the command
      if ( boost::regex_match( strCmdInput.c_str(), what, reAddCmd ) ) {
          for ( int k = 0 ; k < what.size() ; k++ ) {
            strWhat = what[k] ;
            std::cout << "    what[" << k << "] = " << what[k] << " (" << strWhat.size()  << " chars)" << std::endl ;
          }
        strWhat = what[1] ; // set string of word that 

        // handle an ADD ELEMENT command
        if ( boost::iequals( strWhat, "element" ) ) {
          std::cout << "  Command is ADD ELEMENT" << std::endl ;
          std::cout << "element:" << what[2] << " content " << what[3] ;
        } 
        // handle an ADD ATTRIBUTE command
        else if ( boost::iequals( strWhat, "attribute" ) ) {
          std::cout << "  Command is ADD ATTRIBUTE" << std::endl ;
          std::cout << "  Continue with adding an attribute here." << std::endl ;
        } 
        // parsing error: ADD is followed by an invalid keyword
        else {
          std::cout << "    Invalid ADD command: 2nd word must be 'element' or 'attribute'." << std::endl ;
        }
      } 
      // parsing error: ADD command syntax does not match the regular expression
      else {
        std::cout << "    Invalid ADD command syntax." << std::endl ;
      }
    } 

    // handle a PRINT command
    else if ( boost::iequals( strWhat, "print" ) ) {
      std::cout << "  Command is PRINT" << std::endl ;
      //std::cout << "  Call your print function here." << std::endl ;
    } 
    else if ( boost::iequals( strWhat, "help" ) ) {
      std::cout << "  Command is HELP" << std::endl ;
      //std::cout << "  Call your help function here." << std::endl ;
    } 

    // handle a QUIT command
    else if ( boost::iequals( strWhat, "quit" ) ) {
      std::cout << "  Command is QUIT" << std::endl ;
      bQuit = 1 ; //exit loop
      return ;
    } 

    // parsing error: the first keyword is not ADD, PRINT, or QUIT
    else { 
      std::cout << "  Invalid command: 1st word must be 'add', 'print', 'help' or 'quit|exit|bye'." << std::endl ;
    }
  } 
  else { 
      std::cout << "  Invalid command: Please use help for more info or quit" << std::endl ;
    }
  }while( bQuit == 0 ) ;
  
}

//add Node to specified parent
void addNode( boost::cmatch what ) {
  // what[0] whole string
  // what[1] attribute | element
  // what[2] contains parent of node to add
  // what[3] contains name of node to add
  // what[4] new-node-content | new-node-value??
  if(debug){ std::cout << "Adding " << what[3] << " as an " << what[1] << " with a parent of " << what[2] << std::endl ; }
}



// standard C++ main function
int main( int argc, char* argv[] ) {
  
  cmdLineParser();
  return 0 ;
}


