#include "Exception.hpp"

Exception::Exception() {}

Exception::~Exception() {}

// __RuntimeException_______________
const char* Exception::Overflow::what() const throw() {
	return ( "Overflow on a value" );
}
const char* Exception::Underflow::what() const throw() {
	return ( "Underflow on a value" );
}
