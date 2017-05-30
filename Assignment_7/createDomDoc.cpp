/* Program: Create xml document
 * File:   createDomDoc.cpp
 * Author: brian, < brian_day@student.uml.edu >
 * Program dependent files: 
 * Created by JMH 
 * Updated by BRD December 8, 2013, 7:56 PM
 */

#include "createDomDoc.hpp"

XERCES_CPP_NAMESPACE_USE

bool debug = false ;
// ---------------------------------------------------------------------------
//  This is a simple class that lets us do easy (though not terribly efficient)
//  transcoding of char* data to XMLCh data.
// ---------------------------------------------------------------------------
class XStr {
public:
  // -----------------------------------------------------------------------
  //  Constructors and Destructor
  // -----------------------------------------------------------------------

  XStr(const char* const toTranscode)
  {
    // Call the private transcoding method
    fUnicodeForm = XMLString::transcode(toTranscode) ;
  }

  ~XStr()
  {
    XMLString::release(&fUnicodeForm) ;
  }


  // -----------------------------------------------------------------------
  //  Getter methods
  // -----------------------------------------------------------------------

  const XMLCh* unicodeForm() const
  {
    return fUnicodeForm ;
  }

private:
  // -----------------------------------------------------------------------
  //  Private data members
  //
  //  fUnicodeForm
  //      This is the Unicode XMLCh format of the string.
  // -----------------------------------------------------------------------
  XMLCh* fUnicodeForm ;
} ;

#define X(str) XStr(str).unicodeForm()

// <editor-fold defaultstate="collapsed" desc="Local Data">
/*
  Local data
  
  gXmlFile
      The path to the file to parser. Set via command line.
  
  gDoNamespaces
      Indicates whether namespace processing should be done.
  
  gDoSchema
      Indicates whether schema processing should be done.
  
  gSchemaFullChecking
      Indicates whether full schema constraint checking should be done.
  
  gDoCreate
      Indicates whether entity reference nodes needs to be created or not
      Defaults to false
  
  gOutputEncoding
      The encoding we are to output in. If not set on the command line,
      then it is defaults to the encoding of the input XML file.
  
  gSplitCdataSections
      Indicates whether split-cdata-sections is to be enabled or not.
  
  gDiscardDefaultContent
      Indicates whether default content is discarded or not.
  
  gUseFilter
      Indicates if user wants to plug in the DOMPrintFilter.
  
  gValScheme
      Indicates what validation scheme to use. It defaults to 'auto', but
      can be set via the -v= command.
  
 ---------------------------------------------------------------------------
 not used, as reported by -Wall   static char* gXmlFile            = 0;
 not used, as reported by -Wall   static bool  gDoNamespaces       = false;
 not used, as reported by -Wall   static bool  gDoSchema           = false;
 not used, as reported by -Wall   static bool  gSchemaFullChecking = false;
 not used, as reported by -Wall   static bool  gDoCreate           = false;
 */
// </editor-fold>

static char* goutputfile = 0 ;
static char* gXPathExpression = 0 ;

// options for DOMLSSerializer's features from xerces sample code
static XMLCh* gOutputEncoding = 0 ;
static bool gSplitCdataSections = true ;
static bool gDiscardDefaultContent = true ;
static bool gUseFilter = false ;
static bool gFormatPrettyPrint = true ;
static bool gWriteBOM = false ;


void cmdLineParser(DOMDocument* doc, bool& bQuit) {
  if(debug){ std::cout << "CmdLineParser Fuction" << std::endl ; }
  
  DOMElement* elemRoot = doc->getDocumentElement() ; //get root element
  std::string strCmdInput ; //hold user input
  boost::cmatch what;
  // what[0] contains the entire matched string
  // what[1] contains the first matched group
  // what[2] contains the second matched group
  // what[3] etc.
  
  boost::regex reBasicCmd( "^\\s*(add|print|help|quit).*", boost::regex::icase ) ;
  //add { element | attribute } parent-node-name new-node-name { new-node-content | new-node-value }
  boost::regex reAddCmd( "^\\s*add\\s*(element|attribute)\\s(\\w+)\\s(\\w+)\\s*(\\w*)$" , boost::regex::icase ) ;
  
  // <editor-fold defaultstate="collapsed" desc="unused regex">
  //boost::regex reAddElementCmd( "^\\s*(a|add)\\s*(e|element)\\s(.+)\\s(.+)\\s*(.*)$", boost::regex::icase ) ;
  //boost::regex reAddAttributeCmd( "^\\s*(a|add)\\s*(a|attribute)\\s(.+)\\s(.+)\\s*(.*)$", boost::regex::icase ) ; 
  //boost::regex rePrintCmd( "^\\s*(p|print)\\s*$", boost::regex::icase ) ;
  //boost::regex reHelpCmd( "^\\s*(h|help)\\s*$", boost::regex::icase ) ;
  //boost::regex reQuitCmd( "^\\s*(q|quit|exit|bye)\\s*$", boost::regex::icase ) ;
  // </editor-fold>

  //user entry point
  std::cout << "\nYour command: " ;
  getline(std::cin , strCmdInput ); //getline used instead of cin since it breaks on spaces
    
  // string version of a matched group 
  // for building a bridge between the cmatch type and an STL sting so that we can
  // process matches with STL string functions from JMH
  std::string strWhat ;
  
  // test for a match of a basic command
  if ( boost::regex_match( strCmdInput.c_str(), what, reBasicCmd ) ) {
    // what[0] contains the entire matched string
    // what[1] contains command
    // what[2] contains parent
    // what[3] contains element name or attribute key
    // what[4] may contain element content or attribute value
    if(debug){
      std::cout << "basic command found" << std::endl ;
      std::cout << "  what.size() = " << what.size() << std::endl ;
      for ( int k = 0 ; k < what.size() ; k++ ) {
        strWhat = what[k] ;
        std::cout << "    what[" << k << "] = " << what[k] << " (" << strWhat.size()  << " chars)" << std::endl ;
      }
    }
    
    strWhat = what[1];//first matched group should be a command
    
    // handle an ADD command
    if ( boost::iequals( strWhat, "add" ) ) {
      if(debug){ std::cout << "  Command is ADD" << std::endl ; }

      // test for a match on the second word in the command
      if ( boost::regex_match( strCmdInput.c_str(), what, reAddCmd ) ) {
        for ( int k = 0 ; k < what.size() ; k++ ) {
          strWhat = what[k] ;
          if(debug){ std::cout << "    what[" << k << "] = " << what[k] << " (" << strWhat.size()  << " chars)" << std::endl ; }
        }
          
        strWhat = what[1] ; //first matched group should be element or attribute 

        // handle an ADD ELEMENT command
        if ( boost::iequals( strWhat, "element" ) ) {
          std::cout << "  Command is ADD ELEMENT" << std::endl ;
          if(debug){ std::cout << "parent:" << what[2] << "| element:" << what[3] << "| content " << what[4] ; }
          
          std::string strTemp = what[2] ;
          std::string strName = what[3] ; //convert char* to string
          std::string strCont = what[4] ;
          
          if(debug){ std::cout << what[2] << std::endl ; }
          
          if( strTemp == "root") {
            //std::cout << "root is parent of this new node:" << strName << ":"<< strCont << std::endl ;
            
            DOMElement* elem = doc->createElement(X( strName.c_str() )); //X needs to use c-strings
            elemRoot->appendChild(elem);
            DOMText* text =  doc->createTextNode(X( strCont.c_str() ));//add content to node
            elem->appendChild(text) ;
          }
          else{
            
            //std::cout << "not root: " << what[2]<< "=" << strTemp << std::endl ;
            DOMTreeWalker* walker = doc->createTreeWalker( elemRoot , DOMNodeFilter::SHOW_ELEMENT , NULL , true) ;
            int count = 0;
             
            for ( DOMNode* current = walker->nextNode() ; current != 0 ; current = walker->nextNode()) {
              // std::cout << count++ ;
              //std::cout << "\nNode Name: |" << XMLString::transcode(current->getNodeName()) << "|" << strTemp.c_str()<< "|" ;
              //std::cout << XMLString::equals(XMLString::transcode(current->getNodeName()) , strTemp.c_str() ) ;
              
              if ( XMLString::equals(XMLString::transcode(current->getNodeName()) , strTemp.c_str() )) {
                //std::cout << "\nNode Matches: " << XMLString::transcode(current->getNodeName()) << " | " ;
                DOMElement* elem2 = doc->createElement(X( strName.c_str() )); //X needs to use c-strings
                current->appendChild(elem2);
                DOMText* text =  doc->createTextNode(X( strCont.c_str() ));//add content to node
                elem2->appendChild(text) ;
                count++ ;
                //break;
              }
            }
            if( count == 0){//no node match
                std::cout << "    Invalid ADD command: 3rd word must be an element that already exists." << std::endl ;
            }
            
            //should throw error if parent node does not exist
          }
          
        } 
        // handle an ADD ATTRIBUTE command
        else if ( boost::iequals( strWhat, "attribute" ) ) {
          //std::cout << "  Command is ADD ATTRIBUTE" << std::endl ;
          if(debug){ std::cout << "parent:" << what[2] << "| attribute key:" << what[3] << "| value " << what[4] ; }
          
          //convert values to string so we can later convert to c_string
          std::string strTemp = what[2] ;
          std::string strKey = what[3] ; //convert char* to string
          std::string strValue = what[4] ;
          //std::cout << what[2] << std::endl ;
          
          if( strTemp == "root") {
            //std::cout << "root is parent of this new attribute:" << strKey << ":"<< strValue << std::endl ;
            elemRoot->setAttribute(X( strKey.c_str() ),X( strValue.c_str() )) ;
          }
          else{
            //std::cout << "not root: " << what[2]<< "=" << strTemp << std::endl ;
            DOMTreeWalker* walker = doc->createTreeWalker( elemRoot , DOMNodeFilter::SHOW_ELEMENT , NULL , true) ;
            //int count = 0;
             
            for ( DOMNode* current = walker->nextNode() ; current != 0 ; current = walker->nextNode()) {
             // std::cout << count++ ;
//              std::cout << "\nNode Name: |" << XMLString::transcode(current->getNodeName()) << "|" << strTemp.c_str()<< "|" ;
//              std::cout << XMLString::equals(XMLString::transcode(current->getNodeName()) , strTemp.c_str() ) ;
//              std::cout << current->getNodeType() ;
              if ( XMLString::equals(XMLString::transcode(current->getNodeName()) , strTemp.c_str() )) {
                //std::cout << "\nNode Matches: " << XMLString::transcode(current->getNodeName()) << " | " ;
                if (current->getNodeType() == 1){
                  DOMElement* test = dynamic_cast<DOMElement*>(current) ;
                  test->setAttribute(X( strKey.c_str() ),X( strValue.c_str() )) ;
                }
              }
            }
          }
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
      //std::cout << "  Command is PRINT" << std::endl ;
      printDOM( doc ); //print out current tree
    } 
    else if ( boost::iequals( strWhat, "help" ) ) {
      //std::cout << "  Command is HELP" << std::endl ;
      displayHelp();
    } 

    // handle a QUIT command
    else if ( boost::iequals( strWhat, "quit" ) ) {
      //std::cout << "  Command is QUIT" << std::endl ;
      bQuit = false ; //exit loop
    } 

    // parsing error: the first keyword is not ADD, PRINT, or QUIT
    else { 
      std::cout << "  Invalid command: 1st word must be 'add', 'print', 'help' or 'quit'." << std::endl ;
    }
  } 
  else { 
      std::cout << "  Invalid command: Please use |help| for more info or |quit|" << std::endl ;
    }
}
void displayHelp() {
  std::cout << "*********************\
                \nValid Command List: \
                \n\t\tadd { element | attribute } parent-node-name new-node-name { new-node-content | new-node-value }\
                \n\t\tprint - print out tree \
                \n\t\thelp - displays this message \
                \n\t\tquit - exit this program \
                \n*********************" << std::endl ;
}
void printDOM(DOMDocument* doc) {
  int retval = 0 ; // function return value
  DOMPrintFilter *myFilter = 0 ;

  try {
    // get a serializer, an instance of DOMLSSerializer
    XMLCh tempStr[3] = {chLatin_L , chLatin_S , chNull} ;
    DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(tempStr) ;
    DOMLSSerializer *theSerializer = ((DOMImplementationLS*) impl)->createLSSerializer() ;
    DOMLSOutput *theOutputDesc = ((DOMImplementationLS*) impl)->createLSOutput() ;

    // set user specified output encoding
    theOutputDesc->setEncoding(gOutputEncoding) ;
    
    // plug in user's own filter
    if (gUseFilter) {
      // even we say to show attribute, but the DOMLSSerializer
      // will not show attribute nodes to the filter as
      // the specs explicitly says that DOMLSSerializer shall
      // NOT show attributes to DOMLSSerializerFilter.
      //
      // so DOMNodeFilter::SHOW_ATTRIBUTE has no effect.
      // same DOMNodeFilter::SHOW_DOCUMENT_TYPE, no effect.
      //
      myFilter = new DOMPrintFilter(DOMNodeFilter::SHOW_ELEMENT |
              DOMNodeFilter::SHOW_ATTRIBUTE |
              DOMNodeFilter::SHOW_DOCUMENT_TYPE) ;
      theSerializer->setFilter(myFilter) ;
    }

    // The end-of-line sequence of characters to be used in the XML being written out. 
    theSerializer->setNewLine(XMLString::transcode("\n"));
    
    // plug in user's own error handler
    DOMErrorHandler *myErrorHandler = new DOMPrintErrorHandler() ;
    DOMConfiguration* serializerConfig = theSerializer->getDomConfig() ;
    serializerConfig->setParameter(XMLUni::fgDOMErrorHandler , myErrorHandler) ;



    // set feature if the serializer supports the feature/mode
    if (serializerConfig->canSetParameter(XMLUni::fgDOMWRTSplitCdataSections , gSplitCdataSections))
      serializerConfig->setParameter(XMLUni::fgDOMWRTSplitCdataSections , gSplitCdataSections) ;

    if (serializerConfig->canSetParameter(XMLUni::fgDOMWRTDiscardDefaultContent , gDiscardDefaultContent))
      serializerConfig->setParameter(XMLUni::fgDOMWRTDiscardDefaultContent , gDiscardDefaultContent) ;

    if (serializerConfig->canSetParameter(XMLUni::fgDOMWRTFormatPrettyPrint , gFormatPrettyPrint))
      serializerConfig->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint , gFormatPrettyPrint) ;

    if (serializerConfig->canSetParameter(XMLUni::fgDOMWRTBOM , gWriteBOM))
      serializerConfig->setParameter(XMLUni::fgDOMWRTBOM , gWriteBOM) ;

   
    //
    // Plug in a format target to receive the resultant
    // XML stream from the serializer.
    //
    // StdOutFormatTarget prints the resultant XML stream
    // to stdout once it receives any thing from the serializer.
    //
    XMLFormatTarget *myFormTarget ;
    if (goutputfile)
      myFormTarget = new LocalFileFormatTarget(goutputfile) ;
    else
      myFormTarget = new StdOutFormatTarget() ;
    theOutputDesc->setByteStream(myFormTarget) ;

    // do the serialization through DOMLSSerializer::write();
    if (gXPathExpression != NULL) {
      XMLCh* xpathStr = XMLString::transcode(gXPathExpression) ;
      DOMElement* root = doc->getDocumentElement() ;
      try {
        DOMXPathNSResolver* resolver = doc->createNSResolver(root) ;
        DOMXPathResult* result = doc->evaluate(
                xpathStr ,
                root ,
                resolver ,
                DOMXPathResult::ORDERED_NODE_SNAPSHOT_TYPE ,
                NULL) ;

        XMLSize_t nLength = result->getSnapshotLength() ;
        for (XMLSize_t i = 0 ; i < nLength ; i++) {
          result->snapshotItem(i) ;
          theSerializer->write(result->getNodeValue() , theOutputDesc) ;
        }

        result->release() ;
        resolver->release() ;
      } 
      catch (const DOMXPathException& e) {
        XERCES_STD_QUALIFIER cerr << "An error occurred during processing of the XPath expression. Msg is:"
                << XERCES_STD_QUALIFIER endl
                << StrX(e.getMessage()) << XERCES_STD_QUALIFIER endl ;
        retval = 4 ;
      } 
      catch (const DOMException& e) {
        XERCES_STD_QUALIFIER cerr << "An error occurred during processing of the XPath expression. Msg is:"
                << XERCES_STD_QUALIFIER endl
                << StrX(e.getMessage()) << XERCES_STD_QUALIFIER endl ;
        retval = 4 ;
      }
      XMLString::release(&xpathStr) ;
    } 
    else { theSerializer->write(doc , theOutputDesc) ; }

    theOutputDesc->release() ;
    theSerializer->release() ;

    //
    // Filter, formatTarget and error handler
    // are NOT owned by the serializer.
    //
    delete myFormTarget ;
    delete myErrorHandler ;

    if (gUseFilter)
      delete myFilter ;

  } catch (const OutOfMemoryException&)
  {
    XERCES_STD_QUALIFIER cerr << "OutOfMemoryException" << XERCES_STD_QUALIFIER endl ;
    retval = 5 ;
  } catch (XMLException& e)
  {
    XERCES_STD_QUALIFIER cerr << "An error occurred during creation of output transcoder. Msg is:"
            << XERCES_STD_QUALIFIER endl
            << StrX(e.getMessage()) << XERCES_STD_QUALIFIER endl ;
    retval = 4 ;
  }

}
void displayTree( DOMDocument* doc,  DOMElement* elemRoot ){
  //
  // Now count the number of elements in the above DOM tree.
  //
    const XMLSize_t elementCount = doc->getElementsByTagName(X("*"))->getLength() ;
    XERCES_STD_QUALIFIER cout << "The tree just created contains: " << elementCount
            << " elements.\n" << XERCES_STD_QUALIFIER endl ;

    printDOM(doc) ; // added by JMH
    std::cout << "\n------------------------------" << std::endl ;


//    DOMTreeWalker* walker = doc->createTreeWalker(elemRoot , DOMNodeFilter::SHOW_ALL , NULL , true) ;
//    for (DOMNode* current = walker->nextNode() ; current != 0 ; current = walker->nextNode()) {
//
//      if (!XMLString::equals(XMLString::transcode(current->getNodeName()) , "#text")) {
//        std::cout << "\nNode Name: " << XMLString::transcode(current->getNodeName()) << " | " ;
//      }
//      if (current->getNodeValue() != NULL) {
//        std::cout << "Node Value: " << XMLString::transcode(current->getNodeValue()) << " | " ;
//      }
//
//      // see http://xerces.apache.org/xerces-c/apiDocs-3/classDOMNode.html
//      DOMNamedNodeMap *map = current->getAttributes() ;
//      // see http://xerces.apache.org/xerces-c/apiDocs-3/classDOMNamedNodeMap.html
//      if (map == NULL || map->getLength() == 0) {
//        //std::cout << std::endl << "no attributes" << std::endl ;
//      } 
//      else {
//        // std::cout << map->getLength() << " attribute(s)" ;
//        for (unsigned int k = 0 ; k < map->getLength() ; k++) {
//          std::cout << "\n  Attribute " << k + 1 << ": " <<
//                  XMLString::transcode(map->item(k)->getNodeName()) << " = " <<
//                  XMLString::transcode(map->item(k)->getNodeValue()) << " | " ;
//        }
//      }
//
//
//    }
//
//    std::cout << std::endl ;


}
int main(int argC , char*[]) {
  int errorCode = 0;
  // Initialize the XML4C2 system.
  try { XMLPlatformUtils::Initialize() ; } 
  catch (const XMLException& toCatch) {
    char *pMsg = XMLString::transcode(toCatch.getMessage()) ;
    XERCES_STD_QUALIFIER cerr << "Error during Xerces-c Initialization.\n"
            << "  Exception message:"
            << pMsg ;
    XMLString::release(&pMsg) ;
    return 1 ;
  }
  DOMImplementation* impl = DOMImplementationRegistry::getDOMImplementation(X("Core")) ;
  if (impl != NULL){
    try{
      DOMDocument* doc = impl->createDocument(
              0 , // root element namespace URI.
              X("root") , // root element name
              0) ; // document type object (DTD).
      
       bool bQuit = true ;
      do{
        cmdLineParser( doc, bQuit ) ;
      }while (bQuit);
      //createDomDoc( doc ) ;
      
      doc->release() ; //close document

    } catch (const OutOfMemoryException&) {
      XERCES_STD_QUALIFIER cerr << "OutOfMemoryException" << XERCES_STD_QUALIFIER endl ;
      errorCode = 5 ;
    } catch (const DOMException& e) {
      XERCES_STD_QUALIFIER cerr << "DOMException code is:  " << e.code << XERCES_STD_QUALIFIER endl ;
      errorCode = 2 ;
    } catch (...) {
      XERCES_STD_QUALIFIER cerr << "An error occurred creating the document" << XERCES_STD_QUALIFIER endl ;
      errorCode = 3 ;
    }
    
  }// (inpl != NULL)
  else {
    XERCES_STD_QUALIFIER cerr << "Requested implementation is not supported" << XERCES_STD_QUALIFIER endl ;
    errorCode = 4 ;
  }
  
  XMLPlatformUtils::Terminate() ; //close out xerces
  return errorCode ;
}