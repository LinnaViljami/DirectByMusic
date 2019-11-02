#include "customexception.h"



CustomException::CustomException(const std::string &msg) : std::runtime_error (msg)
{

}
