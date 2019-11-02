#ifndef CUSTOMEXCEPTION_H
#define CUSTOMEXCEPTION_H

#include <stdexcept>

class CustomException : public std::runtime_error
{
public:
    explicit CustomException(const std::string& msg);
};

#endif // CUSTOMEXCEPTION_H
