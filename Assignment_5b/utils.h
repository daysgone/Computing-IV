/**@Program: Parse XML File
 * @File:   utils.h
 * @Author:  Brian Day < brian_day@student.uml.edu >
 * Program dependent files: xmlElement.h
 * Created: 2012/10/12
 * Updated 2013/09/17
 * Updated 2013/11/05
 */

#ifndef UTILS_H
#define	UTILS_H

//system includes
#include <fstream>  //file stream
#include <cstring>  //needed to make program work in windows
#include <string>   //string operations
#include <sstream>
#include <vector>   //vector operations

//user defined includes
#include "xmlElement.h"

//current parser state
enum ParserState { START_OF_DOCUMENT, DIRECTIVE,
STARTING_COMMENT,IN_COMMENT,ENDING_COMMENT,ONE_LINE_COMMENT,
ELEMENT_OPENING_TAG, ELEMENT_CONTENT, ELEMENT_CLOSING_TAG, 
SELF_CLOSING_TAG,END_OF_DOCUMENT, UNKNOWN, ERROR } ;


// <editor-fold defaultstate="collapsed" desc="Function Description">
  /** Check if file actually exists
   * @pre   string containing sFileName to open, and stream passed by reference
   * @param sFileName   filename
   * @param ifs          file stream 
   * @post  file opened if it exists
   **/
// </editor-fold>
void openFile( std::string sFileName, std::fstream& ifs, bool b_dir ) ;


// <editor-fold defaultstate="collapsed" desc="Function Description">
  /**
   * @pre  : string containing sFileName to open
   * @param sFileName   filename
   * @return bool       true if file exists
   * @post : if file actually exists, true is returned
   **/
// </editor-fold>
bool checkFileExist ( const std::string& sFileName) ; 

// <editor-fold defaultstate="collapsed" desc="Function Description">
  /** 
   * @pre valid string
   * @param str   input string
   * @return str  no white-space at the beginning or end 
   * @post string returned with white space removed before and after string
   **/
// </editor-fold>
std::string trimString( std::string& str ) ; 

// <editor-fold defaultstate="collapsed" desc="Function Description">
  /** output elements of vector 
   * @pre vector of type xmlElement pointer passed by reference
   * @param vElem vector to display
   * @post prints to screen a vectors toString function 
   **/
// </editor-fold>
void displayVector( std::vector<xmlElement*>& vec ) ;

// <editor-fold defaultstate="collapsed" desc="Function Description">
/**
 * @param ps parser-state which is an enum
 * @return string of current parser-state
 **/
// </editor-fold>
std::string showState( ParserState ps ) ;

// <editor-fold defaultstate="collapsed" desc="Function Description">
  /** display and store information based on current parser-state
   * @pre vector of type xmlElement pointer passed by reference
   * @param root      pointer to root element passed by reference
   * @param curElem   pointer to current element passed by reference
   * @param curState  parser-state
   * @param nLineNum  integer of current line number
   * @param sAttrib   string of all attributes
   * @param sTag      string of tag name
   * @param sCont     string of content
   * @param vElem     vector to display
   * @return current  parser-state
   **/
// </editor-fold>
ParserState stateReader( xmlElement* &root,xmlElement* &curElem , ParserState& curState, int nLineNum, int& level, std::string& sAttrib, std::string& sTag, std::string& sCont,  std::vector<xmlElement*>& vElem);

//<editor-fold defaultstate="collapsed" desc="Function Description">
  /** indent string by certain # of tabs that is passed in
   * @pre int value of how many indents to create
   * @param level   int value of indentation level
   * @post string of tabs for correct indentation
   **/
// </editor-fold>
std::string sFormat( int level );

// <editor-fold defaultstate="collapsed" desc="Function Description">
  /** from class notes
   * @pre valid tree to traverse
   * @param level     int value of indentation level
   * @param xmlElem   element that is the root of the tree to display
   * @post display each element of tree in a structured format
   **/
// </editor-fold>
void displayXMLTree( xmlElement* xmlElem, int level ) ;

// <editor-fold defaultstate="collapsed" desc="Function Description">
  /** from class notes
   * @pre valid tree to traverse
   * @param xmlElem   element that is the root of the tree to display
   * @param level     int value of indentation level
   * @post display each element and sub-members of tree in a structured format (JSON)
   **/
// </editor-fold>
std::string displayJSON( xmlElement* xmlElem, int i_level ) ;

// <editor-fold defaultstate="collapsed" desc="Function Description">
  /**
   * @pre valid vector to traverse
   * @param root root element of tree
   * @param curElem current place in xml tree
   * @param vElem vector of elements
   * @param nLineNum current line number
   * @param nLevel level in tree
   * @param sAttrib attributes of current element
   * @param sTag tag of current elem
   * @param sCont content of current elem
   * @post display each element of tree in a structured format
   * @return current element
   **/
// </editor-fold>
xmlElement* addElement( xmlElement* &root, xmlElement* &curElem, std::vector<xmlElement*> &vElem, int nLineNum, int nLevel, std::string sAttrib, std::string sTag, std::string sCont ) ;

// <editor-fold defaultstate="collapsed" desc="Function Description">
/** process xml tree into json format
 * @pre   valid xml root (xmlElem*)
 * @return string containing json formated text
 * @post  valid string
 */
// </editor-fold>
std::string toJSON( xmlElement* elem, int level ) ;                  //simple string representation of class

#endif	/* UTILS_H */

