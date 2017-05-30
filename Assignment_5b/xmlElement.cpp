/* Program XML Reader
 * File:   xmlElement.cpp
 * Author: Brian Day, brian_day@student.uml.edu
 * Program dependent files: main.cpp, xmlElement.h, xmlReader.cpp, xmlReader.h, music.xml
 * Created on 2012/10/08
 * Updated 2013/9/17
 */


//includes


#include "xmlElement.h"


//copy constructor
xmlElement::xmlElement(const xmlElement& obj) {
  //std::cout << "Copy constructor allocating ptr." << std::endl;
  //ptr = new int;
  //*ptr = *obj.ptr; // copy the value
}

//default constructor, not used
xmlElement::xmlElement() {}

xmlElement::xmlElement(int line, int level, std::string tag, std::string attrib, std::string cont){
  setLine( line ) ;
  setLevel( level ) ;
  setTag( tag ) ;
  setAttrib( attrib ) ;
  setContent( cont ) ;
}

xmlElement::~xmlElement() { }//destructor

// <editor-fold defaultstate="collapsed" desc="Getters">

int xmlElement::getLine( ) const { return this->nLine ; } //return line number of element
int xmlElement::getLevel( ) const { return this->nLevel ; } //return level in tree
std::string xmlElement::getTag ( ) const { return this->sTag ; } //return element tag
std::vector<xmlElemAttrib*> xmlElement::getAttrib ( ) const { return this->vAttrib  ; } //return attributes of element
std::string xmlElement::getContent ( ) const { return this->sCont ; }
std::vector<xmlElement*> xmlElement::getChildren( ) const { return this->vChildren ;}
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Setters">
void xmlElement::setLevel( int level ) { this->nLevel = level ; }//set line number of element
void xmlElement::setLine( int num ) { this->nLine = num ; }//set line number of element
void xmlElement::setTag( const std::string tag ) { this->sTag = tag ; }  //set element name(tag)

//take string of attributes and store in vector 
void xmlElement::setAttrib( std::string sAttrib ) {
  std::size_t subBegin = 0 ;
  std::size_t subSep = sAttrib.find( "=" ) ; // find first seperator in string
  if( subBegin != std::string::npos){
    std::size_t subEnd = sAttrib.find( " " ,subBegin ) ; //find first space after seperator
    while ( subSep != std::string::npos && subBegin != std::string::npos ){
      //std::cout << sAttrib.substr( subBegin, subSep-subBegin ) << "|=|" << sAttrib.substr( subSep+1, subEnd-subSep) << " , " ;
      //mAttrib.insert( std::pair<std::string,std::string>( sAttrib.substr( subBegin, subSep-subBegin ) , sAttrib.substr( subSep+1, subEnd-subSep) ) );
      this->vAttrib.push_back( new xmlElemAttrib( sAttrib.substr( subBegin, subSep-subBegin ),sAttrib.substr( subSep+1, subEnd-subSep) ) ); 
      subBegin = subEnd ;
      subSep = sAttrib.find( "=", subBegin ) ;
      subEnd = sAttrib.find( " ", subSep ) ;
    }// does not parse attributes 100% correct, grabs space before attributes if not the first one
  }
 
}
void xmlElement::setContent ( std::string cont ) { this->sCont = cont; }
void xmlElement::addChild( xmlElement* child ) { this->vChildren.push_back( child ) ; } //add child to vector of children
// </editor-fold>

//http://www.cplusplus.com/reference/clibrary/cstdio/sprintf/
std::string xmlElement::toString() {
  char cstrLineNo[8] ;
  std::string printLine ;
  sprintf( cstrLineNo, "%i", getLine() ) ;//write formated data to string %d signed int
  std::string strLineNo = cstrLineNo ;
  std::string strTemp ="";      //temporary string to hold built attribute string
  //std::map<std::string, std::string>::iterator iter; //iterator for map of attributes
  
  //need to adjust for vector instead of map
//  for( iter = mAttrib.begin(); iter != mAttrib.end(); iter++) {
//    strTemp.append(iter->first);
//    strTemp.append(" = ") ;
//    strTemp.append( iter->second );
//  }
  printLine = "Element " + getTag() + " was found at line " + strLineNo ;
  if( getContent() != ""){ printLine += " Content|" + getContent() + "|" ; }
  if( getContent() != "" && strTemp != "" ){ printLine += "," ; }
  if( strTemp != "" ){ printLine += " Attribute(s)|" + strTemp + "|" ; }
  
  return printLine ;
}


