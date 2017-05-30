/**@Program: Testing an XML File Hierarchy
 * @File:   utils.cpp
 * @Author: Brian Day, < brian_day@student.uml.edu >
 * Program dependent files:  utils.h , debug.h
 * Created 2012/10/12
 * Updated 2013/09/17
 * Updated 2013/10/1
 * Updated 2013/11/05
 */


//user defined includes
#include "utils.h"

bool debug_basic = false ;
bool debug_verbose = false ;
bool debug_parser = false ;
bool debug_state = false ;
bool debug_tree = false ;

std::string debug_spaces = "" ; // change to | to help show trimming of spaces

void writeFile ( std::string sFileName, std::ofstream& ofs) {
  if( debug_verbose  ) { std::cout << "in write file function " << std::endl ; }
  //from class notes
  char* pcharFileName = new char [sFileName.size() + 1];//string constructor with char* arg
  strcpy( pcharFileName,sFileName.c_str() );
  
  //open file
  ofs.open ( pcharFileName );
  
  //does file actually exist?
  const bool f_exists = checkFileExist( pcharFileName );
  if (!f_exists){ std::cerr << "File: " << sFileName << " does not exist" << std::endl ; }
  else { std::cout << "File Opened: " << sFileName << std::endl; }
}

void openFile ( std::string sFileName, std::fstream& ifs, bool b_dir ) {
  if( debug_verbose  ) { std::cout << "in file open function " << std::endl ; }
  //from class notes
  char* pcharFileName = new char [sFileName.size() + 1];//string constructor with char* arg
  strcpy( pcharFileName,sFileName.c_str() );
  
  if( b_dir ){ ifs.open ( pcharFileName, std::ifstream::in ); }
  else{ ifs.open ( pcharFileName, std::ifstream::out ); }

  
  
  //does file actually exist?
  const bool f_exists = checkFileExist( pcharFileName );
  if (!f_exists){ std::cerr << "File: " << sFileName << " does not exist" << std::endl ; }
  else { std::cout << "File Opened: " << sFileName << std::endl; }
}

bool checkFileExist ( const std::string& sFileName){
  std::ifstream fileTest( sFileName.c_str() );
  return fileTest.is_open();
}

std::string trimString( std::string& str) {
  if( debug_verbose ) { std::cout << " Trimming " << debug_spaces << str  << debug_spaces << std::endl ; }
  //check to see if tab or space at start of string
  while ( str[0] == ' ' || str[0] == '\t' ) { str.erase( str.begin() ) ; }  //must use an iterator, erase if space or tab char found
  
  //check to see if tab or space at end of string
  while ( str[str.length()-1] == ' ' || str[str.length()-1] == '\t' ) { str.erase( str.end()-1 ) ; } //must use an iterator, erase if space or tab char found
  
  return str ;
}

void displayVector( std::vector<xmlElement*>& vec) {
  //check if an empty vector
  if ( vec.empty()  ) { std::cout << sFormat(2) << "*** No elements were found ***" << std::endl ; }
  //non-empty vector
  else {
    std::cout << sFormat(1) << "Stack now contains: " ;
    //iterate through vector and display info
    std::vector<xmlElement*>::iterator iter = vec.begin() ;
    std::vector<xmlElement*>::iterator end = vec.end() ;
    for (; iter != end ; ++iter )
    {
      std::cout << (*iter)->getTag() << debug_spaces ;//dereference iterator
    }
   std::cout << std::endl ;
  }
}

std::string showState( ParserState ps ) {
  std::string sState = "" ;
  switch ( ps ) {
    case UNKNOWN : sState += "UNKNOWN" ; break ;
    case START_OF_DOCUMENT : sState += "STARTING_DOCUMENT" ; break ;
    case DIRECTIVE : sState += "DIRECTIVE" ; break ;
    case STARTING_COMMENT : sState += "STARTING_COMMENT" ; break ;
    case IN_COMMENT : sState += "IN_COMMENT" ; break ;
    case ENDING_COMMENT : sState += "ENDING_COMMENT" ; break ;
    case ONE_LINE_COMMENT : sState += "ONE_LINE_COMMENT" ; break ;
    case ELEMENT_OPENING_TAG : sState += "ELEMENT_OPENING_TAG" ; break ;
    case ELEMENT_CONTENT : sState += "ELEMENT_CONTENT" ; break ;
    case ELEMENT_CLOSING_TAG : sState += "ELEMENT_CLOSING_TAG" ; break ;
    case SELF_CLOSING_TAG : sState += "SELF_CLOSING_TAG" ; break ;
    case ERROR : sState += "ERROR" ; break ;
    case END_OF_DOCUMENT: sState += "END_OF_DOCUMENT" ; break ;
    default : sState += "DEFAULT" ; break ;
}
  return  sState ;
  }

ParserState stateReader( xmlElement* &root, xmlElement* &curElem, ParserState& curState, int nLineNum, int& nLevel, std::string& sAttrib, std::string& sTag, std::string& sCont, std::vector<xmlElement*>& vElem) {
  //print out depending on what state currently in
  switch ( curState ) {
    case DIRECTIVE :
      if(  debug_state ) { std::cout << sFormat(2) << "Found: " << showState( curState ) << " = " << sCont << std::endl ; }
      break;
    case STARTING_COMMENT :
    case IN_COMMENT :
    case ENDING_COMMENT :
    case ONE_LINE_COMMENT :
      if( debug_state ) { std::cout << sFormat(2) << "Found: " << showState( curState ) << std::endl ; }
      //if( debug_verbose) { std::cout << sFormat(1) << debug_spaces << sCont << debug_spaces << std::endl ; }
      break ;

    case ELEMENT_OPENING_TAG :
      if( debug_state && debug_verbose ) { std::cout << sFormat(2) << "Opening tag " << sTag << std::endl ; 
        std::cout << sFormat(3) << "+++ Adding " << debug_spaces << sTag << debug_spaces << " to stack +++" << std::endl ; 
      }
      if( debug_state ) {
        
        std::cout << sFormat(2) << "-Element Name: "<< debug_spaces << sTag << debug_spaces << std::endl ;
        if(sAttrib != ""){ std::cout << sFormat(2) << "-Element Attributes: " << debug_spaces << sAttrib << debug_spaces << std::endl ;}
      }

      curElem = addElement( root, curElem, vElem, nLineNum, nLevel, sAttrib, sTag, sCont ) ; 
      vElem.push_back( curElem  ) ;

      if( debug_parser && debug_verbose ) { std::cout << "vector contains:" << vElem.size() << " element(s). Last elem:" << (*vElem.at( vElem.size()-1 )).getTag() << std::endl ; }
      break ;

    case ELEMENT_CONTENT :
      if( debug_state ) { std::cout << sFormat(2) << "*** Complete Element found *** " << std::endl ; }
      if( debug_state ) { 
        std::cout << sFormat(2) << "-Element Name: " << debug_spaces << sTag << debug_spaces << std::endl ;
        if(sAttrib != ""){ std::cout << sFormat(2) << "-Element Attributes: "<< debug_spaces << sAttrib << debug_spaces << std::endl ;}
        if(sCont != ""){ std::cout << sFormat(2) <<"-Element Content: " << debug_spaces << sCont << debug_spaces << std::endl ;} 
      }
      addElement( root, curElem, vElem, nLineNum, nLevel, sAttrib, sTag, sCont ) ;
      break ;

    case ELEMENT_CLOSING_TAG : { 
      if( debug_state && debug_verbose ) { 
        std::cout << sFormat(2) << "*** Closing Tag found *** " << std::endl ; 
        std::cout << sFormat(3) << "--- Removing " << debug_spaces << sTag << debug_spaces << " from stack ---" << std::endl ; 
      }
      if( vElem.empty()  ) { std::cout << sFormat(2) << "Vector empty" << std::endl ; break ; }

      xmlElement* tempElem = vElem.back() ;

      //test to make sure current closing tag matches top most on the "stack"
      if( sTag.compare(tempElem->getTag()) == 0)  {
        if( debug_state && debug_verbose ) { std::cout <<sFormat(3)<< debug_spaces << sTag << debug_spaces << " matches " << tempElem->getTag() << std::endl ; }

        vElem.pop_back() ;//remove from stack

        curElem = vElem.back() ; //change pointer to last
        //if( debug_tree && !vElem.empty() ) { std::cout << curElem->getLevel() << std::endl ; }
      }
      else { 
        if( debug_state ) { std::cerr << "*** ERROR: Not well formed xml :ERROR ***" << std::endl ; }
        curState = ERROR ;
      }
      break ; 
    } 
    case SELF_CLOSING_TAG :
      if( debug_state && debug_verbose ){ std::cout << sFormat(1) << "-Self_Closing: " << debug_spaces << sCont << debug_spaces << std::endl ; }
      if( debug_state ) { 
        std::cout << sFormat(2) << "-Element Name: " << debug_spaces << sTag << debug_spaces << std::endl ;
        if(sAttrib != ""){ std::cout << sFormat(2) << "-Element Attributes: "<< debug_spaces << sAttrib << debug_spaces << std::endl ;}
        if(sCont != ""){ std::cout << sFormat(2) <<"-Element Content: " << debug_spaces << sCont << debug_spaces << std::endl ;} 
      }
      addElement( root, curElem, vElem, nLineNum, nLevel, sAttrib, sTag, sCont ) ;
      break;
    case END_OF_DOCUMENT :
      if( debug_state && debug_verbose ) { std::cout << "*** END OF DOCUMENT ***" << std::endl ; }
      break;
    case ERROR :
      if( debug_state && debug_verbose ) { std::cout << "*** ERROR *** " << sCont << std::endl ; }
      break ;
    case UNKNOWN:
      if( debug_state && debug_verbose ) { std::cout << "*** UNKNNOWN *** " << sCont << std::endl ; } 
      break ;
    default :
      if( debug_state && debug_verbose ) { std::cout << "*** SHOULD NEVER GET THIS *** " << sCont << std::endl ; }
      break ;
  }
  return curState ;
}
 
std::string sFormat( int level ){
  std::string temp = "" ;
  for( int i=0 ; i < level ; ++i ) {
    temp = temp + "  " ;
  }
  return temp;
}

xmlElement* addElement( xmlElement* &root, xmlElement* &curElem, std::vector<xmlElement*> &vElem, int nLineNum, int nLevel, std::string sAttrib, std::string sTag, std::string sCont ) {
  //std::cout << "in add element function" << std::endl ;
  xmlElement* xmlTemp ;
  if( curElem == NULL ) { 
    if( debug_state && debug_verbose ) { std::cout << sFormat(3) << "First element found :" << sTag  << std::endl; }
    root = new xmlElement( nLineNum, nLevel + 1, sTag, sAttrib, sCont ) ;
    return root ;
  }
  xmlTemp = new xmlElement( nLineNum, curElem->getLevel() + 1, sTag, sAttrib, sCont ) ;
  curElem->addChild( xmlTemp ); // add this as a child to current elem 
  return xmlTemp ; // make child element current elem
}

void displayXMLTree( xmlElement* xmlElem, int level ) {
  //indent appropriately
  
  for (int k = 0 ; k < level ; k++ ) {
    std::cout << "- " ;
  }
  // display data for the current element
  std::cout << xmlElem->toString() << std::endl ;
  
  // process the element's children
  for ( size_t k = 0 ; k < xmlElem->getChildren().size() ; k++ ) {
    displayXMLTree( xmlElem->getChildren().at( k ), level + 1 ) ;
  }
}

std::string displayJSON( xmlElement* xmlElem, int i_level ) {
  // display data for the current element
  std::stringstream s_temp ;
  //int tempLevel ;
  //s_temp += sFormat(level -1) + "},\n" ;
 
  s_temp << toJSON(xmlElem , i_level) ;
  //s_temp << sFormat( i_level ) << xmlElem->getTag() << ":" << i_level << "\r\n";
  //s_temp  << xmlElem->getChildren().size() <<": child(ren)\n" ;
  
  //if( xmlElem->getChildren().size() == 0 ) {s_temp += sFormat(level +1) + "},\n" ; }
  for ( size_t k = 0 ; k < xmlElem->getChildren().size() ; ++k ) {
    //xmlElement* tempElem = xmlElem->getChildren().at(k) ;
    //tempLevel = tempElem->getLevel() ;
    
    s_temp  << displayJSON( xmlElem->getChildren().at( k ), i_level + 1 ) ;
    if( k < xmlElem->getChildren().size()-1 ) { s_temp << ",\n" ; }
  }
  if( xmlElem->getChildren().size() >= 1 ) { s_temp << "\n" << sFormat( xmlElem->getLevel() - 1 ) << "}" ; } //<< (tempLevel-2) <<"\r\n"  ; }
  
  return s_temp.str() ;
}

//http://www.cplusplus.com/reference/clibrary/cstdio/sprintf/
std::string toJSON(xmlElement* curElem, int level ) {
  std::stringstream s_string ;
  std::string printLine = "" ;
  //s_string << "{|" << "third" << "|}" ;
  if( level == 0){ return sFormat( curElem->getLevel()-1 ) + "{\n" ; }
  int i_subNodeCount_inc = 0 ;
  
  //count how many sub nodes there are of the current node
  if(curElem->getChildren().size() >= 1 ) { i_subNodeCount_inc += curElem->getChildren().size() ; }
  if(curElem->getAttrib().size() >= 1 ) { i_subNodeCount_inc += curElem->getAttrib().size() ; }
  if(curElem->getContent() != "" ) {  i_subNodeCount_inc += 1 ; }
  int i_subNodeCount = i_subNodeCount_inc ; // store total number of sub nodes before decrementing
  
  //s_string << i_subNodeCount << " Nodes. " ;
  s_string << sFormat( curElem->getLevel() - 1 ) << "\"" << curElem->getTag() << "\"" << " : " ;
  // <editor-fold defaultstate="collapsed" desc="1 subnode">
if( i_subNodeCount_inc == 1) {  // content stays on same line as node if only 1 subnode
    if( curElem->getContent() != ""){ 
      s_string << "\"" << curElem->getContent() << "\"" ;
      i_subNodeCount_inc--; //content will go on same line as tag if its the only thing
      i_subNodeCount-- ; //decrement subnode so should go to 0
    }
//    else if(curElem->getAttrib().size() == 1 ){ //must create new line for attributes 
//      //s_string << curElem->getAttrib().front().toString() ;
//      //s_string << "\n" < sFormat( level +1 ) << curElem->getAttrib().at(1).getAttribName() <<  curElem->getAttrib().at(1).getAttribData() ;
//      i_subNodeCount--;
//    }
    else if( !curElem->getAttrib().empty()  ) { //no content and no children and only 1 attrib
      s_string << "{" ; //attributes always a new line
      if(curElem->getAttrib().size() > 1 ){ s_string << "ERROR" ; }
      s_string << "\n" << sFormat(curElem->getLevel() ) << "\"" << curElem->getAttrib().at(0)->getAttribName() << "\" : " << curElem->getAttrib().at(0)->getAttribData() ;
      i_subNodeCount_inc-- ;
      //not needed below if it gets to this point there should only be 1 attribute
//      for(unsigned int k = 0 ; k < curElem->getAttrib().size() ; ++k ) {
//          s_string << "\n" << sFormat(curElem->getLevel() ) << "\"" << curElem->getAttrib().at(k)->getAttribName() << "\" : " << curElem->getAttrib().at(k)->getAttribData() ;
//          if(i_subNodeCount_inc > 1 ){ s_string << ",test" ; }
//          i_subNodeCount_inc-- ;
//      }
    }
    else if ( curElem->getChildren().size() == 1 ) { //no content and no attributes and only 1 child
      s_string << "{\n" ; 
      i_subNodeCount_inc--;
    }
    
    //s_string << "\n"  ;
  }
  // </editor-fold>
  
  // <editor-fold defaultstate="collapsed" desc="more then 1 subnode">
  else if ( i_subNodeCount_inc > 1) {
    s_string << "{" ;
    if( curElem->getContent() != "") { 
      s_string << "\n" << sFormat( curElem->getLevel() ) << "\"" << curElem->getTag() << "\"" <<" : " << "\"" << curElem->getContent()<< "\"";
      if(i_subNodeCount_inc > 1 ){ s_string << "," ; } //not seemed to be used in my test xml so far
      //s_string << "+\n" ;
      i_subNodeCount_inc--;
      i_subNodeCount--;
    }
    if( curElem->getAttrib().size() >= 1 ) {
      //could not get this loop to work with an iterator calling a
//      for(std::vector<xmlElemAttrib*>::const_iterator iter = curElem->getAttrib().begin(); iter != curElem->getAttrib().end(); ++iter) {
//        s_string << (*iter)->getAttribName() << " : " << (*iter)->getAttribData() ;
//        if(i_subNodeCount > 1 ){ s_string << "," ; }
//        i_subNodeCount--;
//        s_string<< "\n" ;
//      }
      for(unsigned int k = 0 ; k < curElem->getAttrib().size() ; k++ ) {
        //std::cout << "\"" << curElem->getAttrib().at(k)->getAttribName() << "\" : " << curElem->getAttrib().at(k)->getAttribData() ;
        s_string << "\n" << sFormat(curElem->getLevel()  ) << "\"" << curElem->getAttrib().at(k)->getAttribName() << "\" : " << curElem->getAttrib().at(k)->getAttribData() ;
        if(i_subNodeCount_inc > 1 ){ s_string << "," ; }
        //s_string<< "\n" ;
        i_subNodeCount_inc--;
      }
    }
  }
  // </editor-fold>

  //else{ s_string << "\n" ; }
 
  if( curElem->getChildren().size() >= 1 && i_subNodeCount_inc >= 1  ) { s_string <<  "\n" ; } // " no children only attrib/content \r\n" ; }
  //add closing bracket after content/attributes if there are no children for this current node
  if( curElem->getChildren().size() == 0 && i_subNodeCount >= 1  ) { s_string <<"\n" << sFormat(curElem->getLevel()-1) << "}" ; } // " no children only attrib/content \r\n" ; }
  
  printLine = s_string.str() ;
  
  return printLine ;
}


