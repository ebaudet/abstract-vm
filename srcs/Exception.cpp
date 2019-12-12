#include "Exception.hpp"

Exception::Exception() {}

Exception::~Exception() {}
// __ConceptionException____________
const char* Exception::Factory::what() const throw() {
	return ( "Unexpected event" );
}
const char* Exception::Operand::what() const throw() {
	return ( "Unexpected event" );
}

// __RuntimeException_______________
const char* Exception::Overflow::what() const throw() {
	return ( "Overflow on a value" );
}
const char* Exception::Underflow::what() const throw() {
	return ( "Underflow on a value" );
}
