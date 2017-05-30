/* Program: simple xml "parser"
 * File:    xmlReader.cpp
 * Author:  brian day < brian_day@student.uml.edu >
 * Program dependent files: xmlReader.h
 * Created: 2012/09/23
 * Updated: 2013/09/05
 * Updated: 2013/09/12
 * Updated: 2013/10/02
 */

//system includes
#include <iostream> //stream operations
#include <fstream> //file stream operations
#include <sstream>
#include <string> //string operations
#include <vector>

//user defined includes
#include "xmlReader.h"

//global debug variables change in util.cpp
extern bool debug_basic ;
extern bool debug_verbose  ;
extern bool debug_parser  ;
extern bool debug_tree ;
extern bool debug_state ;
extern std::string debug_spaces ;

void xmlReader( std::string fileName ) {  
  std::fstream ifs ; //filestream to pass file into
  openFile( fileName, ifs, true ) ; //generic open file function
  parseXMLFile( ifs ) ; //read XML file
  ifs.close( ); //done with stream, close up shop
}

void parseXMLFile ( std::fstream& ifs ) {
  std::string sLine ;               //full line of text from getline function
  std::string sTag ;                //name of tag
  std::string sAttrib ;             //if tag has a space in it, hold rest of substring between space and closing carat
  std::string sCont ;               //data between opening tag and closing tag on same line, or whole line if comment
  int nLineNum ;                    //current line number
  int nLevel ;                      //current tree level
  std::vector<xmlElement*> vElem ;  //vector (stack) to keep track of current place in xml structure
  
  //initialize variables
  nLineNum = 0 ;
  nLevel = 0 ;
  xmlElement* root = NULL ;         //create pointer to NULL for root element 
  xmlElement* curElem = root ;      //root element pointer
  ParserState curState = START_OF_DOCUMENT ; 
  
  //<editor-fold defaultstate="collapsed" desc="Read line debug code">
  /*
   * Tester code to make sure it reads line by line and prints out correct info with white space trimmed
   
   */
  if( false )
  {
    std::cout << "\t------------------Debug line reader start-----------------" << std::endl ;
    int debug_line = 0;
    while( ifs.good() ) //print line by line xml file with line number
    {
      getline( ifs, sLine ) ; //read current line from stream till /n character found
      debug_line++ ;
      trimString( sLine ) ; //remove all whitespace before and after string
      std::cout << sFormat(1) << "Line Number: " << debug_line << " contains: " << sLine << std::endl ;
      
    }
    //reset filestream so rest of code will work if debug used
    ifs.seekg(0, ifs.beg );
    ifs.clear();
    
    std::cout << "\t-------------------Debug line reader end-----------------" << std::endl << std::endl << std::endl;
    //std::cout.setf(std::ios::boolalpha);
    //if( debug_verbose ) { std::cout << "File is good? " << ifs.good()<< std::endl ; }
  }
  //</editor-fold>
  
  //while file still has info
  while( ifs.good() ) {
    getline( ifs, sLine ) ; //read line from file-stream and store in string sLine 
    nLineNum++ ; //increment line number 
    
    if( debug_tree && curElem != NULL ){ std::cout << sFormat(2) << "Current Element: " << curElem->getTag() << " @ level: " << curElem->getLevel() << std::endl << std::endl ; }
    if( debug_parser ) { 
      std::cout << nLineNum  << ":" << trimString( sLine ) << std::endl ;
      std::cout << sFormat(1) << "Current Parser State: " << showState(curState) << std::endl ; 
    }
    
    curState = xmlElementParser( curState, sLine, sAttrib, sTag, sCont ) ; //function to pull info out of current line and put into correct strings
    
    curState = stateReader( root, curElem, curState, nLineNum, nLevel, sAttrib, sTag, sCont, vElem ) ;
    if( debug_parser ) { std::cout << sFormat(1) << "New Parser State: " << showState(curState) << std::endl << std::endl; }
  
  }
  
  curState = END_OF_DOCUMENT ;
  //if( debug_parser ) { std::cout << showState(curState) << std::endl << std::endl  ;}
  
//  std::cout << std::endl << "***** XML TREE *****" << std::endl ;
//  displayXMLTree( root, 0 ) ;
//  std::cout << std::endl << "***** end XML TREE *****" << std::endl ;
  
  std::cout << std::endl << "***** JSON file output *****" << std::endl ;
  int i_level  = 0 ;
  std::fstream outputFile ;
  openFile( "test.json", outputFile, false ) ;
  outputFile << displayJSON( root , i_level ) ;
  outputFile.close() ;
  std::cout << sFormat( 1 ) << "File closed" << std::endl ;
  std::cout << "***** end JSON file output *****" << std::endl ;
  
  std::cout << std::endl << "***** JSON TREE *****" << std::endl ;
  std::cout << displayJSON( root , i_level );
  std::cout << std::endl << "***** END JSON TREE *****" << std::endl ;
  
}

ParserState xmlElementParser ( ParserState curState,  std::string sLine, std::string& sAttrib, std::string& sTag, std::string& sCont ) {
  //local variables
  std::size_t tagStart, tagEnd ;      //iterators
  std::size_t found ;                 //stand in variable to check for certain things in string
  
  //initialize variables
  tagStart = sLine.find_first_of("<") ; //first instance of opening element tag start
  tagEnd = sLine.find_first_of(">") ;   //first instance of opening element tag end
  sAttrib = ""; //clear attributes from last element
  sTag = "";   //clear tag from last element
  sCont = sLine; //default whole line as content ??

  std::string sElem  = sLine.substr( tagStart + 1 , ( tagEnd - tagStart ) - 1) ; //index of substring starts after opening < and ends before trailing >
  found = sElem.find( " ", 0 ); //returns std::string::npos if space not found 
  
 
  // <editor-fold defaultstate="collapsed" desc="end token found">
 if( tagStart == std::string::npos && tagEnd != std::string::npos ) {
    if( debug_verbose) { std::cout << sFormat(2) << "Ending token found only: " << debug_spaces << sLine << debug_spaces << std::endl ; }

   // stay in comment states if currently in comment states
    if( (curState == IN_COMMENT || curState == STARTING_COMMENT)) {
      if( sLine.substr( tagEnd - 2 , 2 ).compare ( "--" ) == 0 ) { 
        sCont = sLine.substr( 0 , tagEnd - 3 ) ;
        return ENDING_COMMENT ; 
      }
      sCont = sLine ;
      return IN_COMMENT ;
    }
    return ERROR ;
  }
  // </editor-fold>
  
  // <editor-fold defaultstate="collapsed" desc="start token found, no closing">
  else if(tagStart != std::string::npos && tagEnd == std::string::npos) {
    if( debug_verbose) { std::cout << sFormat(2) << "Starting token found only: " << debug_spaces << sLine << debug_spaces << std::endl ; }
    
    //check next few trailing characters to see if it matches starting_comment token
    if( sLine.substr( tagStart + 1 , 3 ).compare ( "!--" ) == 0 ) { 
      sCont = sLine.substr( tagStart + 4 , std::string::npos ) ;
      return STARTING_COMMENT ; 
    }
    //allows for angle brackets in comment block
    else if( (curState == IN_COMMENT || curState == STARTING_COMMENT)) { return IN_COMMENT ; }
    
    //could be multi-lined tag
    return UNKNOWN ;
  }
  // </editor-fold>
  
  // <editor-fold defaultstate="collapsed" desc="starting token found , ending token found">
  else if( tagStart != std::string::npos && tagEnd != std::string::npos ) {
    //break out if still in comment block
    if( (curState == IN_COMMENT || curState == STARTING_COMMENT)) { return IN_COMMENT ; } 
    
    // <editor-fold defaultstate="collapsed" desc="Special cases: checking first character(s) after starting token">
    if ( sLine[ tagStart + 1 ] == '?' || sLine[ tagStart + 1 ] == '!' || sLine[ tagStart + 1 ] == '/' ) {
      if( debug_verbose ) { std::cout << sFormat(1) << "Special: " << debug_spaces << sLine << debug_spaces << std::endl ; }
        
        //directive token
        if ( sLine[ tagStart + 1 ] == '?' ) { 
          sCont = sElem.substr( 1, sElem.size()-2 ) ;
          return DIRECTIVE ; 
        }
      
        //closing token
        else if ( sLine[ tagStart + 1 ] == '/' ) { 
          //if( debug_verbose ) { std::cout << sFormat(1) << sLine.substr( tagStart + 2, ( tagEnd - tagStart ) - 2) << std::endl ; } 
          sTag = sElem.substr( 1, sElem.size()-1 ) ;
          sCont = debug_spaces;
          return ELEMENT_CLOSING_TAG ;
        }
      
        //single line token, closing tag found on same line so we know its not a starting comment token
        else if (sLine.substr( tagStart + 1 , 3 ).compare ( "!--" ) == 0  ) {
          //set line between opening and closing tokens as content
          found = sLine.find_last_of(">") ; //make sure we have the whole comment line
          
          sCont = sLine.substr( (tagStart + 4), ( found - 2) - (tagStart + 4) ) ; //start after <!-- and end before -->
          return ONE_LINE_COMMENT ; 
        }
        return ERROR ; 
    }
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="Special case: check character before end token">
    //self closing tag
    
    else if( sLine[ tagEnd - 1 ] == '/' ) { 
      if( debug_verbose ) { std::cout << sFormat(1) << "\tSelf-closing tag found. " << sLine << std::endl ; }
        
        //trim after space for attribute
      if (found != std::string::npos ) {
          sAttrib = sElem.substr( found + 1 , sElem.size() - found - 2 ) ;
          sTag = sElem.substr(0, found ) ; 
        }
        else{ sTag = sElem ; } 
        sCont = debug_spaces ;//no content
        return SELF_CLOSING_TAG ; //nothing added to stack
      }
      
    // </editor-fold>
    
    // <editor-fold defaultstate="collapsed" desc="Valid tag found">
    else {
      if( debug_verbose ) { std::cout << sFormat(1) << "tag: " << debug_spaces << sTag << debug_spaces << " with attributes: " << debug_spaces << sAttrib << debug_spaces << std::endl ; }
      //create a new xmlElement and add this element to the vector
      //.push_back( new xmlElement( nLineNum, sTag ) ) ;
      
      //find out if there is a closing tag on the same line
      std::size_t nextTag = sLine.find( "</", tagEnd ) ;
      
      //tag and closing tag found on same line
      if( nextTag != std::string::npos ){
        //look for space in tag to split out attributes
        if (found != std::string::npos ) {
          sAttrib = sElem.substr( found + 1 , std::string::npos ) ; //still grabbing ending slash.....
          sTag = sElem.substr(0, found ) ; 
        }
        else{ sTag = sElem ; } 
        sCont = sLine.substr( tagEnd + 1, nextTag - tagEnd - 1 );
        return ELEMENT_CONTENT ; 
      }
      else {
        //look for space in tag to split out attributes
        if (found != std::string::npos ) {
          sAttrib = sElem.substr( found + 1 , std::string::npos ) ;
          sTag = sElem.substr(0, found ) ; 
        }
        else{ sTag = sElem ; } 
        sCont = debug_spaces;
        return ELEMENT_OPENING_TAG ;
      }
    }
    // </editor-fold>
  }
  // </editor-fold>
  
  // <editor-fold defaultstate="collapsed" desc="no tokens found">
  else if( tagStart == std::string::npos && tagEnd == std::string::npos ) {
    if( debug_verbose) { std::cout << sFormat(2) <<"NO tokens: " << debug_spaces << sLine << debug_spaces << std::endl ; } 
    
    //if current state is a comment
    if ( (curState == IN_COMMENT || curState == STARTING_COMMENT) ) { 
      sAttrib = "";
      sTag = "";
      sCont = sLine;
      return IN_COMMENT ; 
    }
    sAttrib = "";
    sTag = "";
    sCont = sLine;
    return UNKNOWN ;
  }
  // </editor-fold>
  return ERROR ;
  }








