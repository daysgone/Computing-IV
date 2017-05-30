/* Program: Create xml document
 * File:   createDomDoc
 * Author: brian, < brian_day@student.uml.edu >
 * Program dependent files: 
 * Created on December 8, 2013, 7:56 PM
 */

#ifndef CREATEDOMDOC_HPP
#define	CREATEDOMDOC_HPP

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>

#include <xercesc/util/PlatformUtils.hpp>

#include <xercesc/dom/DOM.hpp>

#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>

#include "DOMTreeErrorReporter.hpp"
#include "DOMPrintFilter.hpp"
#include "DOMPrintErrorHandler.hpp"

#include <xercesc/dom/DOMTreeWalker.hpp>

#include <boost/regex.hpp>              // for regex_match
#include <boost/algorithm/string.hpp>   // for iequals (case-insensitive match)

#include <string.h>
#include <string>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <fstream>  //file stream
#include <cstring>  //needed to make program work in windows
#include <string>   //string operations
#include <sstream>

/**Prompt user for commands to work with a xml tree
 * @param doc - dom document object
 * @param bQuit - boolean value if loop should end
 */
void cmdLineParser(DOMDocument* doc, bool& bQuit) ; 

/**display help
 */
void displayHelp() ;

/**Print out current tree
 * @param doc document object
 */
void printDOM(DOMDocument* doc) ;


//unused function
void displayTree( DOMDocument* doc,  DOMElement* elemRoot ) ;


#endif	/* CREATEDOMDOC_HPP */

