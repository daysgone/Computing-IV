/**@Program: XML Tree tester 
 * @File:   xmlElemAttrib.cpp
 * @Author: Brian Day, < brian_day@student.uml.edu >
 * Program dependent files: xmlElemAttrib.h, utils.h, debug.h 
 * Created: 2012/10/12
 */

#include <iostream> //stream operations
#include <string>   //string operations
#include <cstring>  
#include <cstdlib>

#include "xmlElemAttrib.h"
#include "utils.h"
extern int wtf_level ;

/** set name and data properties of attribute
 * @param sAttrib     string containing entire attribute 
 */
xmlElemAttrib::xmlElemAttrib ( std::string sAttrib ) 
{
  //need better variable names for these
  size_t found, foundEnd = 0 ;//initialize start of string pos
  std::string subStr ;
  
  //trim string to get rid of pre/post whitespace
  sAttrib = trimString( sAttrib );
  
  //find first split
  found = sAttrib.find_first_of( "=" ) ;
  
  //make sure not at end of string
  while( found != std::string::npos ) 
  {
    //set attribute name
    setAttribName( sAttrib.substr( foundEnd, found - foundEnd ) ) ;
    std::cout << "Attrib name: " << sAttrib.substr( foundEnd, found - foundEnd ) << std::endl ;
    //find opening "
    found = sAttrib.find( "\"", found ) ; 
    if( found != std::string::npos ) 
    {
      //find closing " adjust for space after
      foundEnd = sAttrib.find( "\"", found + 1 ) +2 ;
      
      //adjust start of substring to get rid of "
      found++ ;
      subStr = sAttrib.substr( found , foundEnd - found ) ;
      setAttribData( subStr ) ; 
    }
    else
    {
      std::cout << "<ERROR>" ;
      break;
    }
    found = sAttrib.find( "=", foundEnd ) ;
    
    //debug code
    
      //std::cout << "\tAttribute:" << attCount << std::endl ;
      //std::cout << "\t\tAttrib Name:" << getAttribName() << std::endl ;
      //std::cout << "\t\tAttrib Data:" << getAttribData() << std::endl ;
     
  }
}

/** 2 param constructor 
 * Take passed in strings and set name and data
 * @param sAttribName   string containing name of attribute
 * @param sAttribData   string of attribute description 
 */
xmlElemAttrib::xmlElemAttrib ( std::string sAttribName, std::string sAttribData ) 
{ 
  setAttribName( sAttribName ) ;
  setAttribData( sAttribData ) ;
}

/** copy constructor */
xmlElemAttrib::xmlElemAttrib ( const xmlElemAttrib& orig ) { }

/** Destructor */
xmlElemAttrib::~xmlElemAttrib( ) { }

std::string xmlElemAttrib::getAttribName( ) const { return sAttribName ; }

std::string xmlElemAttrib::getAttribData( ) const { return sAttribData ; }

void xmlElemAttrib::setAttribName( std::string sAttribName ) { this->sAttribName = sAttribName ; }

void xmlElemAttrib::setAttribData ( std::string sAttribData ){ this->sAttribData = sAttribData ; }

std::string xmlElemAttrib::toString() const { return "Attribute Object: " + getAttribName() + " : Contains: " + getAttribData() ; }

