#ifndef XMLTOOLS_H
#define XMLTOOLS_H

#include <memory>

namespace pugi
{
    class xml_node;
}

class XmlTools
{
public:
    static std::shared_ptr<pugi::xml_node> CopyXmlNode(const pugi::xml_node& srcNode);
    static void CopyXmlNode(const pugi::xml_node& srcNode, pugi::xml_node& dstNode);

private:
    XmlTools();
};

#endif // XMLTOOLS_H
