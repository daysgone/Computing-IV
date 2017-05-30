/** Program: simple xml "parser"
 * File:    xmlReader.cpp
 * @Author:  brian day < brian_day@student.uml.edu >
 * Program dependent files: xmlReader.h
 * Created: 2012/09/23
 * Updated: 2013/09/05
 * Updated: 2013/09/12
 * Updated: 2013/10/02
 **/

#ifndef XMLREADER_H
#define	XMLREADER_H

//system includes
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//user defined includes
#include "utils.h"

// <editor-fold defaultstate="collapsed" desc="Function Description">
/**
 * @pre string passed in that is the name of a valid file
 * @param fileName file to be opened in current directory
 * @post file open, parsed and then filestream closed
 * @return none
 */
// </editor-fold>
void xmlReader(  std::string sfileName ) ;                             

// <editor-fold defaultstate="collapsed" desc="Function Description">
/* 
 * @pre : valid file-stream 
 * @param ifs -> file-stream that needs to be parsed
 * @post: file-stream parsed and all elements found and stored in a vector
 * @return none
 */
// </editor-fold>
void parseXMLFile ( std::fstream& ifs) ;

// <editor-fold defaultstate="collapsed" desc="Function Description">
/* 
 * pre : valid string and vectors
 * @param curState  parser-state 
 * @param nLineNum  int with current line num
 * @param sLine     string from stream using getline()
 * @param sAttrib   string to contain all attributes
 * @param sTag      string to contain tag name
 * @param sCont     string for xml element content, contains whole line if no tag found
 * @param vElem     vector(stack) to contain parser states to test well formed-ness
 * @post: vectors contain xmlElements
 * @return current parser state
 */
// </editor-fold>
ParserState xmlElementParser ( ParserState curState, std::string sLine, std::string& sAttrib, std::string& sTag, std::string& sCont) ;
#endif	/* XMLREADER_H */

