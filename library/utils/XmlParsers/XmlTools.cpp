#include "pugixml.hpp"
#include "XmlTools.h"

///////////////////////////////////////////////////////////////////////////
void XmlTools::CopyXmlNode(const pugi::xml_node& srcNode, pugi::xml_node& dstNode)
{
    for (const pugi::xml_attribute& attr : srcNode.attributes())
    {
        auto attrCopy = dstNode.append_attribute(attr.name());
        attrCopy.set_value(attr.value());
    }
    for (const pugi::xml_node& node : srcNode.children())
    {
        auto nodeCopy = dstNode.append_child(node.name());
        CopyXmlNode(node, nodeCopy);
    }
    auto nodeText = srcNode.text();
    dstNode.text().set(nodeText.as_string());
}

///////////////////////////////////////////////////////////////////////////
std::shared_ptr<pugi::xml_node> XmlTools::CopyXmlNode(const pugi::xml_node& srcNode)
{
    auto ptr = std::make_shared< pugi::xml_node >();
    if (!ptr)
    {
        return ptr;
    }

    CopyXmlNode(srcNode, *ptr);
    return ptr;
}
