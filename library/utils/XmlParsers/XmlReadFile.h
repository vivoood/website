#ifndef XMLREADFILE_H
#define XMLREADFILE_H

#include <string>
#include <memory>
#include <vector>

// forwards
namespace pugi
{
  class xml_document;
  class xml_node;
}


class XmlReadFile
{
  
  
public:
    XmlReadFile();
    ~XmlReadFile();
    
        /**
    * Init configuration
    * @param pszFilespec - fill or relative path to xml file
    * @return true on success
    */
    virtual bool Init ( const char* pszFilespec );

    std::shared_ptr<const pugi::xml_document> GetXmlDoc() { return m_spxmlDoc; };

protected:    


    /**
    * Get integer value
    * @param pszSection - name of section
    * @param pszEntry - name of entry
    * @param [out] nValue - value of entry
    * @return true on success
    */
    virtual bool GetInteger ( const char* pszSection, const char* pszEntry, int& nValue ) const;

    /**
    * Get string value
    * @param pszSection - name of section
    * @param pszEntry - name of entry
    * @param [out] strValue - value of entry
    * @return true on success
    */
    virtual bool GetString ( const char* pszSection, const char* pszEntry, std::string& strValue ) const;

    /**
    * Get float value
    * @param pszSection - name of section
    * @param pszEntry - name of entry
    * @param [out] nValue - value of entry
    * @return true on success
    */
    virtual bool GetFloat(const char* pszSection, const char* pszEntry, float& nValue) const;

    /**
    * Get bool value
    * @param pszSection - name of section
    * @param pszEntry - name of entry
    * @param [out] nValue - value of entry
    * @return true on success
    */
    virtual bool GetBool(const char* pszSection, const char* pszEntry, bool& nValue) const;
    
    /** xml document */
    std::shared_ptr<pugi::xml_document> m_spxmlDoc;
    
};

#endif // XMLREADFILE_H
