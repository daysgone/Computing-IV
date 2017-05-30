
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

#include <string.h>
#include <string>
#include <stdlib.h>
#include <time.h>

#if defined(XERCES_NEW_IOSTREAMS)
#include <iostream>
#include <fstream>  //file stream
#include <cstring>  //needed to make program work in windows
#include <string>   //string operations
#include <sstream>
#else
#include <iostream.h>
#endif

XERCES_CPP_NAMESPACE_USE

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

// options for DOMLSSerializer's features
static XMLCh* gOutputEncoding = 0 ;

static bool gSplitCdataSections = true ;
static bool gDiscardDefaultContent = true ;
static bool gUseFilter = false ;
static bool gFormatPrettyPrint = true ;
static bool gWriteBOM = false ;

/** Print out tree of xml document
 * 
 * @param doc pointer to DOMDocument
 */
void PrintDOM(DOMDocument* doc) {
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


// ---------------------------------------------------------------------------
//  main
// ---------------------------------------------------------------------------

int main(int argC , char*[])
{
  // Initialize the XML4C2 system.
  try
  {
    XMLPlatformUtils::Initialize() ;
  } catch (const XMLException& toCatch) {
    char *pMsg = XMLString::transcode(toCatch.getMessage()) ;
    XERCES_STD_QUALIFIER cerr << "Error during Xerces-c Initialization.\n"
            << "  Exception message:"
            << pMsg ;
    XMLString::release(&pMsg) ;
    return 1 ;
  }

  // Watch for special case help request
  int errorCode = 0 ;
  if (argC > 1) {
    XERCES_STD_QUALIFIER cout << "\nUsage:\n"
            "    CreateDOMDocument\n\n"
            "This program creates a new DOM document from scratch in memory.\n"
            "It then prints the count of elements in the tree.\n"
            << XERCES_STD_QUALIFIER endl ;
    errorCode = 1 ;
  }
  if (errorCode) {
    XMLPlatformUtils::Terminate() ;
    return errorCode ;
  }

  {
    //  Nest entire test in an inner block.
    //  The tree we create below is the same that the XercesDOMParser would
    //  have created, except that no whitespace text nodes would be created.

    DOMImplementation* impl = DOMImplementationRegistry::getDOMImplementation(X("Core")) ;

    if (impl != NULL){
      try{
        // current date and time
        // http://stackoverflow.com/questions/997946/c-get-current-time-and-date
        time_t now = time(0) ;
        struct tm tstruct ;
        char buf[80] ;
        tstruct = *localtime(&now) ;
        // http://www.cplusplus.com/reference/clibrary/ctime/strftime/
        strftime(buf , sizeof (buf) , "BRD  %F, at %I:%M %p " , &tstruct) ;

        char comment[500] = "" ;
        std::strcat(comment , "\
                 \n* Program: XML Create \
                 \n* Author:  brian day < brian_day@student.uml.edu > \
                 \n* Program dependent files: none \
                 \n* Created by BRD  2013-11-01 \
                 \n* Updated by ") ;

        std::strcat(comment , buf) ;
        //std::cout << comment << std::endl ;

        DOMDocument* doc = impl->createDocument(
                0 , // root element namespace URI.
                X("root") , // root element name
                0) ; // document type object (DTD).
        
        DOMElement* elemRoot = doc->getDocumentElement() ; //get root element
        DOMComment* comm = doc->createComment(X(comment)) ; //comment block at start of file
        elemRoot->appendChild(comm) ;
         
        DOMElement* elem = doc->createElement(X("root_child1")); //first tier of children
        elemRoot->appendChild(elem);
//        DOMText* text = doc->createTextNode(X("content_root_child1"));//add content to node
//        elem->appendChild(text);
        
        //root child 1
        DOMElement* elem2 = doc->createElement(X("child1_level_2"));
        elem->appendChild(elem2);
          elem2->setAttribute(X("att1"),X("attribute 1")) ;
          elem2->setAttribute(X("att2"),X("attribute 2")) ;
          elem2->setAttribute(X("att3"),X("attribute 3")) ;
        
          //subchild to root child 1
          DOMElement* elem3 = doc->createElement(X("child1_level_3")) ;
          elem2->appendChild(elem3);
          DOMText* text =  doc->createTextNode(X("content"));//add content to node
          elem3->appendChild(text) ;
        
            //subchild to root child 1
            elem2 = doc->createElement(X("child2_level_2"));
            elem->appendChild(elem2);
              elem2->setAttribute(X("att1"),X("attribute 1")) ;
              elem2->setAttribute(X("att2"),X("attribute 2")) ;
              elem2->setAttribute(X("att3"),X("attribute 3")) ;
        
          //subchild to root child 1
          elem2 = doc->createElement(X("child3_level_2"));
          elem->appendChild(elem2);
            elem2->setAttribute(X("att1"),X("attribute 1")) ;
            elem2->setAttribute(X("att2"),X("attribute 2")) ;
            elem2->setAttribute(X("att3"),X("attribute 3")) ;

        //root child 2
        elem = doc->createElement(X("root_child2")); //first tier of children
        elemRoot->appendChild(elem);
            //subchild to root child 2
            elem3 = doc->createElement(X("child1_level_3")) ;
            elem2->appendChild(elem3);
              elem3->setAttribute(X("att1"),X("attribute 1")) ;
              elem3->setAttribute(X("att2"),X("attribute 2")) ;
              elem3->setAttribute(X("att3"),X("attribute 3")) ;
            //subchild to root child 2
            elem3 = doc->createElement(X("child2_level_3")) ;
            elem2->appendChild(elem3);
              elem3->setAttribute(X("att1"),X("attribute 1")) ;
              elem3->setAttribute(X("att2"),X("attribute 2")) ;
              elem3->setAttribute(X("att3"),X("attribute 3")) ;
        
        //root child 3
        elem = doc->createElement(X("root_child3")); //first tier of children
        elemRoot->appendChild(elem);
            elemRoot->appendChild(elem);
            //subchild to root child 2
            elem2 = doc->createElement(X("child1_level_3")) ;
            elem->appendChild(elem2);
              elem2->setAttribute(X("att1"),X("attribute 1")) ;
              elem2->setAttribute(X("att2"),X("attribute 2")) ;
              elem2->setAttribute(X("att3"),X("attribute 3")) ;
            //subchild to root child 2
            elem3 = doc->createElement(X("child2_level_3")) ;
            elem2->appendChild(elem3);
              elem3->setAttribute(X("att1"),X("attribute 1")) ;
              elem3->setAttribute(X("att2"),X("attribute 2")) ;
              elem3->setAttribute(X("att3"),X("attribute 3")) ;
        
            elem3 = doc->createElement(X("child1_level_3")) ;
            elem2->appendChild(elem3);
            text =  doc->createTextNode(X("content "));//add content to node
            elem3->appendChild(text) ;
            
            elem3 = doc->createElement(X("child2_level_3")) ;
            elem2->appendChild(elem3);
            text =  doc->createTextNode(X("content "));//add content to node
            elem3->appendChild(text) ;
        
        elem = doc->createElement(X("root_child4")); //first tier of children
        elemRoot->appendChild(elem);
        text = doc->createTextNode(X("content_root_child4"));//add content to node
        elem->appendChild(text);
        
        elem = doc->createElement(X("root_child5")); //first tier of children
        elemRoot->appendChild(elem);
        text = doc->createTextNode(X("content_root_child5"));//add content to node
        elem->appendChild(text);
        
        elem = doc->createElement(X("root_child6")); //first tier of children
        elemRoot->appendChild(elem);
        text = doc->createTextNode(X("content_root_child6"));//add content to node
        elem->appendChild(text);
        
        elem = doc->createElement(X("root_child7")); //first tier of children
        elemRoot->appendChild(elem);
        text = doc->createTextNode(X("content_root_child7"));//add content to node
        elem->appendChild(text);
        
        elem = doc->createElement(X("root_child8")); //first tier of children
        elemRoot->appendChild(elem);
        text = doc->createTextNode(X("content_root_child8"));//add content to node
        elem->appendChild(text);
        
        elem = doc->createElement(X("root_child9")); //first tier of children
        elemRoot->appendChild(elem);
        text = doc->createTextNode(X("content_root_child9"));//add content to node
        elem->appendChild(text);
        
        elem = doc->createElement(X("root_child10")); //first tier of children
        elemRoot->appendChild(elem);
        text = doc->createTextNode(X("content_root_child10"));//add content to node
        elem->appendChild(text);
      
        //
        // Now count the number of elements in the above DOM tree.
        //

        const XMLSize_t elementCount = doc->getElementsByTagName(X("*"))->getLength() ;
        XERCES_STD_QUALIFIER cout << "The tree just created contains: " << elementCount
                << " elements.\n" << XERCES_STD_QUALIFIER endl ;

        PrintDOM(doc) ; // added by JMH
        std::cout << "\n------------------------------" << std::endl ;


        DOMTreeWalker* walker = doc->createTreeWalker(elemRoot , DOMNodeFilter::SHOW_ALL , NULL , true) ;
        for (DOMNode* current = walker->nextNode() ; current != 0 ; current = walker->nextNode()) {

          if (!XMLString::equals(XMLString::transcode(current->getNodeName()) , "#text")) {
            std::cout << "\nNode Name: " << XMLString::transcode(current->getNodeName()) << " | " ;
          }
          if (current->getNodeValue() != NULL) {
            std::cout << "Node Value: " << XMLString::transcode(current->getNodeValue()) << " | " ;
          }

          // see http://xerces.apache.org/xerces-c/apiDocs-3/classDOMNode.html
          DOMNamedNodeMap *map = current->getAttributes() ;
          // see http://xerces.apache.org/xerces-c/apiDocs-3/classDOMNamedNodeMap.html
          if (map == NULL || map->getLength() == 0) {
            //std::cout << std::endl << "no attributes" << std::endl ;
          } 
          else {
            // std::cout << map->getLength() << " attribute(s)" ;
            for (unsigned int k = 0 ; k < map->getLength() ; k++) {
              std::cout << "\n  Attribute " << k + 1 << ": " <<
                      XMLString::transcode(map->item(k)->getNodeName()) << " = " <<
                      XMLString::transcode(map->item(k)->getNodeValue()) << " | " ;
            }
          }
        }

        std::cout << std::endl ;

        doc->release() ;
      } 
      catch (const OutOfMemoryException&) {
        XERCES_STD_QUALIFIER cerr << "OutOfMemoryException" << XERCES_STD_QUALIFIER endl ;
        errorCode = 5 ;
      } 
      catch (const DOMException& e) {
        XERCES_STD_QUALIFIER cerr << "DOMException code is:  " << e.code << XERCES_STD_QUALIFIER endl ;
        errorCode = 2 ;
      } 
      catch (...) {
        XERCES_STD_QUALIFIER cerr << "An error occurred creating the document" << XERCES_STD_QUALIFIER endl ;
        errorCode = 3 ;
      }
    }// (inpl != NULL)
    else {
      XERCES_STD_QUALIFIER cerr << "Requested implementation is not supported" << XERCES_STD_QUALIFIER endl ;
      errorCode = 4 ;
    }
  }

  XMLPlatformUtils::Terminate() ;
  return errorCode ;
}