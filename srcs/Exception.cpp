#include "Exception.hpp"

Exception::Exception() {}

Exception::~Exception() {}

// __RuntimeException_______________
const char* Exception::NullOperand::what() const throw() {
    return ("Null Operand Constructeur");
}
