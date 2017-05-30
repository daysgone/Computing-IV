/**@Program: 
 * @File:   xmlElemAttrib.h
 * @Author: Brian Day, < brian_day@student.uml.edu >
 * Program dependent files: 
 * Created on 2012/10/10
 */

#ifndef XMLELEMATTRIB_H
#define	XMLELEMATTRIB_H

#include <string>

class xmlElemAttrib
{
  public:
    /** copy constructor */
    xmlElemAttrib ( const xmlElemAttrib& orig ) ;
    /** Destructor */
    virtual ~xmlElemAttrib( ) ;
    /** default constructor */
    xmlElemAttrib( ) ;
    /** 1 param constructor 
     * set name and data properties of attribute
     * @param sAttrib     string containing entire attribute 
     */
    xmlElemAttrib ( std::string sAttrib ) ;
    
    /** 2 param constructor 
     * Take passed in strings and set name and data
     * @param sAttribName   string containing name of attribute
     * @param sAttribData   string of attribute description 
     */
    xmlElemAttrib ( std::string sAttribName, std::string sAttribData ) ;
    
    
    
    /** return attribute name
     * @return string containing name of attribute
     */
    std::string getAttribName( ) const ;
    
    /** Return the attribute data
     * @return string containing attribute
     */
    std::string getAttribData( ) const ;
    
    /** set attribute name
     * @param sAttribName string containing name of attribute
     */
    void setAttribName( std::string sAttribName ) ;
    
    /** set attribute Data
     * @param sAttribData string containing data of attribute
     */
    void setAttribData ( std::string sAttribData ) ;
    
    std::string toString() const ;
    
  private:
    std::string sAttribName ;     //string to hold attribute name
    std::string sAttribData ;     //string to hold string of attribute
    
} ;

#endif	/* XMLELEMATTRIB_H */

