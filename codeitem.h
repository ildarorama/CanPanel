#ifndef CODEITEM_H
#define CODEITEM_H

#include <string>

class CodeItem
{
public:
    CodeItem(std::string name,std::string body);
    std::string body();
    std::string name();
private:
    std::string _name;
    std::string _body;
};

#endif // CODEITEM_H
