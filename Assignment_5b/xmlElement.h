/* Program: simple xml "parser"
 * File:   xmlElement.h
 * Author:  brian day < brian_day@student.uml.edu >
 * Program dependent files: xmlElement.cpp
 * Created: 2012/09/08
 * Updated: 2013/09/12
 */

#ifndef XMLELEMENT_H
#define	XMLELEMENT_H

//system includes
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
//#include <map>

//user defined includes
#include "xmlElemAttrib.h"

class xmlElement 
{
  public:
    xmlElement();                             //default constructor
    
    // <editor-fold defaultstate="collapsed" desc="Function Description">
    /** 5 param constructor
     * @param line    line number of element as an int
     * @param level   tree hierarchy level
     * @param tag     element name
     * @param attrib  attributes
     * @param cont    content of xml tag
    */
    // </editor-fold>
    xmlElement( int line, int level, std::string tag, std::string attrib, std::string cont) ; 
    xmlElement( const xmlElement& obj ) ;    //copy constructor
    virtual ~xmlElement( ) ;                  //destructor
   
// <editor-fold defaultstate="collapsed" desc="Getters">
    // <editor-fold defaultstate="collapsed" desc="Function Description">
    /** 
     * @pre     line number set for current element
     * @return  line number
     **/
    // </editor-fold>
    int getLine( ) const ;
    
    // <editor-fold defaultstate="collapsed" desc="Function Description">
    /** 
     * @pre     level is set for current element
     * @return  current level in tree 
     **/
    // </editor-fold>
    int getLevel( ) const ; 
    
    // <editor-fold defaultstate="collapsed" desc="Function Description">
    /** 
     * @pre     tag is set for current element
     * @return  name of current element
     **/
    // </editor-fold>
    std::string getTag( ) const ;
    
    // <editor-fold defaultstate="collapsed" desc="Function Description">
    /** 
     * @pre     element may or may-not contain attributes
     * @return  key value pairs of attributes if they exist
     **/
    // </editor-fold>
    std::vector<xmlElemAttrib*> getAttrib ( ) const ;
    
    // <editor-fold defaultstate="collapsed" desc="Function Description">
    /** 
     * @pre     element may or may-not contain content
     * @return  content between tags
     **/
    // </editor-fold>
    std::string getContent (  ) const ;
    
    // <editor-fold defaultstate="collapsed" desc="Function Description">
    /** 
     * @pre     valid vector
     * @return  vector of pointers of children under current element
     **/
    // </editor-fold>
    std::vector<xmlElement*> getChildren( ) const ;        //vector of pointers to children of current object
    // </editor-fold>
    
// <editor-fold defaultstate="collapsed" desc="Setters">
    // <editor-fold defaultstate="collapsed" desc="Function Description">
    /**
     * @pre   valid int value
     * @param line  line number of element
     * @post  value set for current element
     */
    // </editor-fold>
    void setLine( int line) ;
    
    // <editor-fold defaultstate="collapsed" desc="Function Description">
    /**
     * @pre   valid int value
     * @param level  level of placement in tree
     * @post  value set for current element
     */
    // </editor-fold>
    void setLevel( int level ) ;  
    
    // <editor-fold defaultstate="collapsed" desc="Function Description">
    /**
     * @pre   valid string
     * @param tag  name of element
     * @post  value set for current element
     */
    // </editor-fold>
    void setTag( std::string tag ) ;  
    
    // <editor-fold defaultstate="collapsed" desc="Function Description">
    /**
     * @pre   valid string containing all of the attributes
     * @param attrib  attributes for element
     * @post  attributes added to vector of type xmlElemAttrib*
     */
    // </editor-fold>
    void setAttrib( std::string attrib ) ;

    // <editor-fold defaultstate="collapsed" desc="Function Description">
    /**
     * @pre   valid string
     * @param cont  content of element found between opening and closing tags
     * @post  value set for current element
     */
    // </editor-fold>    
    void setContent ( std::string cont ) ;
    
    // <editor-fold defaultstate="collapsed" desc="Function Description">
    /**
     * @pre valid vector of pointers
     * @param child   xmlElement pointer to be added to vector of children
     * @post xmlElement  pointer added as child to vector
     */
    // </editor-fold>
    void addChild( xmlElement* child ) ; 
    // </editor-fold>
    
    // <editor-fold defaultstate="collapsed" desc="Function Desciption">
    /**
     * @pre   object has been initialized
     * @return string containing detailed information about element
     * @post  valid string
     */
    // </editor-fold>
    std::string toString() ;
    
  private:
    int nLine ;                                 //line number
    int nLevel ;                                //current level in tree
    std::string sCont ;                         //content between tags
    std::string sTag ;                          //element tag
    std::vector<xmlElemAttrib*> vAttrib ;       //hold attribute objects
    std::vector<xmlElement*> vChildren ;        //element children
    //int *ptr;                                 //ptr for copy constructor
} ;

#endif	/* XMLELEMENT_H */

