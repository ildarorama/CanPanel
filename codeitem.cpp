#include "codeitem.h"

CodeItem::CodeItem(std::string name, std::string body) :
    _name(name),
    _body(body)
{
}

std::string CodeItem::name() {
    return _name;
}


std::string CodeItem::body() {
    return _body;
}
