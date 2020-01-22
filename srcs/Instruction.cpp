/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Instruction.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:50:19 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/21 17:12:01 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Instruction.hpp"
#include <iostream>
#include "Color.hpp"
#include "Lexer.hpp"

// -- Public members -----------------------------------------------------------

std::map<std::string, Instruction::InstructionArg>	Instruction::instrArgs = {
	{"push", {1, &Instruction::push}},
	{"pop", {0, &Instruction::pop}},
	{"dump", {0, &Instruction::dump}},
	{"assert", {1, &Instruction::assert_val}},
	{"add", {0, &Instruction::add}},
	{"sub", {0, &Instruction::sub}},
	{"mul", {0, &Instruction::mul}},
	{"div", {0, &Instruction::div}},
	{"mod", {0, &Instruction::mod}},
	{"print", {0, &Instruction::print}},
	{"exit", {0, &Instruction::exit}},
	// bonus
	{"ls", {0, &Instruction::dump}},
	{"abs", {0, &Instruction::abs}},
	{"min", {0, &Instruction::min}},
	{"max", {0, &Instruction::max}},
	{"pow", {0, &Instruction::pow}},
	{"debug", {0, &Instruction::debug}},
	{"clear", {0, &Instruction::clear}},
	{"sep", {0, &Instruction::sep}},
	{"help", {0, &Instruction::help}},
};

// -- Constructors -------------------------------------------------------------

Instruction::Instruction() {
	deque = new std::deque<const IOperand *>();
	instruction_exited = false;
	verbose = false;
	continue_error = false;
	interactive = false;
}

Instruction::Instruction( Instruction const &src ) {
	*this = src;
}

Instruction::~Instruction() {
	while (deque->size() > 0)
		pop();
	delete deque;
}

// -- Operators ----------------------------------------------------------------

Instruction &Instruction::operator=( Instruction const &rhs ) {
	if ( this != &rhs ) {
		deque = new std::deque<const IOperand *>(*rhs.deque);
		instruction_exited = rhs.instruction_exited;
		verbose = rhs.verbose;
		continue_error = rhs.continue_error;
		interactive = rhs.interactive;
	}
	return *this;
}

// -- Exceptions errors --------------------------------------------------------

Instruction::StackException::StackException()
: std::runtime_error( "Stack exception" ) {}

Instruction::StackException::StackException(const char* what_arg)
: std::runtime_error( what_arg ) {}

Instruction::AssertException::AssertException()
: std::runtime_error( "Assert exception" ) {}

Instruction::ExitException::ExitException()
: std::runtime_error( "Exit instruction is missing." ) {}

// -- Instructions -------------------------------------------------------------

/**
 *  -- Push --
 * Pushes the value v at the top of the stack. The value v must have one of
 * the following form:
 * ◦ int8(n) : Creates an 8-bit integer with value n.
 * ◦ int16(n) : Creates a 16-bit integer with value n.
 * ◦ int32(n) : Creates a 32-bit integer with value n.
 * ◦ float(z) : Creates a float with value z.
 * ◦ double(z) : Creates a double with value z.
 **/
int		Instruction::push(const IOperand *value) {
	if (verbose)
		std::cout << BLUE "<push>" EOC << std::endl;
	deque->push_front(value);

	return EXIT_SUCCESS;
}

/**
 *  -- Pop --
 * Unstacks the value from the top of the stack. If the stack is empty, the
 * program execution must stop with an error.
 **/
int		Instruction::pop(const IOperand *value) {
	(void)value;
	if (verbose)
		std::cout << BLUE "<pop>" EOC << std::endl;
	if (deque->size() == 0)
		throw Instruction::StackException( "pop: Stack is empty." );
	const IOperand *front_deque = deque->front();
	deque->pop_front();
	delete front_deque;

	return EXIT_SUCCESS;
}

/**
 *  -- Dump --
 * Displays each value of the stack, from the most recent one to the oldest
 * one WITHOUT CHANGING the stack. Each value is separated from the next one
 * by a newline.
 **/
int		Instruction::dump(const IOperand *value) {
	(void)value;
	std::deque<const IOperand *>::iterator it;
	if (verbose)
		std::cout << BLUE "<dump>" EOC << std::endl;
	for (it = deque->begin(); it != deque->end(); ++it) {
		std::cout << (*it)->toString() << std::endl;
	}

	return EXIT_SUCCESS;
}

/**
 *  -- Assert --
 * Asserts that the value at the top of the stack is equal to the one passed
 * as parameter for this instruction. If it is not the case, the program
 * execution must stop with an error. The value v has the same form that those
 * passed as parameters to the instruction push.
 **/
int		Instruction::assert_val(const IOperand *value) {
	if (verbose)
		std::cout << BLUE "<assert>" EOC << std::endl;
	if (deque->size() == 0)
		throw Instruction::StackException( "assert: Empty stack." );
	const IOperand *test = deque->front();
	if (*value != *test) {
		delete value;
		throw Instruction::AssertException();
	}
	delete value;

	return EXIT_SUCCESS;
}

/**
 *  -- Add --
 * Unstacks the first two values on the stack, adds them together and stacks the
 * result. If the number of values on the stack is strictly inferior to 2, the
 * program execution must stop with an error.
 **/
int		Instruction::add(const IOperand *value) {
	(void)value;
	if (verbose)
		std::cout << BLUE "<add>" EOC << std::endl;
	if (deque->size() < 2)
		throw Instruction::StackException( "add: Stack is lower 2." );
	const IOperand *A = deque->front();
	deque->pop_front();
	const IOperand *B = deque->front();
	deque->pop_front();
	const IOperand *C;
	C = *A + *B;
	push(C);
	delete A;
	delete B;

	return EXIT_SUCCESS;
}

/**
 *  -- Sub --
 * Unstacks the first two values on the stack, subtracts them, then stacks the
 * result. If the number of values on the stack is strictly inferior to 2, the
 * program execution must stop with an error.
 **/
int		Instruction::sub(const IOperand *value) {
	(void)value;
	if (verbose)
		std::cout << BLUE "<sub>" EOC << std::endl;
	if (deque->size() < 2)
		throw Instruction::StackException( "sub: Stack is lower 2." );
	const IOperand *A = deque->front();
	deque->pop_front();
	const IOperand *B = deque->front();
	deque->pop_front();
	const IOperand *C = *A - *B;
	push(C);
	delete A;
	delete B;

	return EXIT_SUCCESS;
}

/**
 *  -- Mul --
 * Unstacks the first two values on the stack, multiplies them, then stacks the
 * result. If the number of values on the stack is strictly inferior to 2, the
 * program execution must stop with an error.
 **/
int		Instruction::mul(const IOperand *value) {
	(void)value;
	if (verbose)
		std::cout << BLUE "<mul>" EOC << std::endl;
	if (deque->size() < 2)
		throw Instruction::StackException( "mul: Stack is lower 2." );
	const IOperand *A = deque->front();
	deque->pop_front();
	const IOperand *B = deque->front();
	deque->pop_front();
	const IOperand *C;
	C = *A * *B;
	push(C);
	delete A;
	delete B;

	return EXIT_SUCCESS;
}

/**
 *  -- Div --
 * Unstacks the first two values on the stack, divides them, then stacks the
 * result. If the number of values on the stack is strictly inferior to 2, the
 * program execution must stop with an error. Moreover, if the divisor is equal
 * to 0, the program execution must stop with an error too. Chatting about
 * floating point values is relevant a this point. If you don’t understand why,
 * some will understand. The linked question is an open one, there’s no
 * definitive answer.
 **/
int		Instruction::div(const IOperand *value) {
	(void)value;
	if (verbose)
		std::cout << BLUE "<div>" EOC << std::endl;
	if (deque->size() < 2)
		throw Instruction::StackException( "div: Stack is lower 2." );
	const IOperand *A = deque->front();
	deque->pop_front();
	const IOperand *B = deque->front();
	deque->pop_front();
	const IOperand *C;
	C = *A / *B;
	push(C);
	delete A;
	delete B;

	return EXIT_SUCCESS;
}

/**
 *  -- Mod --
 * Unstacks the first two values on the stack, calculates the modulus, then
 * stacks the result. If the number of values on the stack is strictly inferior
 * to 2, the program execution must stop with an error. Moreover, if the divisor
 * is equal to 0, the program execution must stop with an error too. Same note
 * as above about fp values.
 **/
int		Instruction::mod(const IOperand *value) {
	(void)value;
	if (verbose)
		std::cout << BLUE "<mod>" EOC << std::endl;
	if (deque->size() < 2)
		throw Instruction::StackException( "mod: Stack is lower 2." );
	const IOperand *A = deque->front();
	deque->pop_front();
	const IOperand *B = deque->front();
	deque->pop_front();
	const IOperand *C;
	C = *A % *B;
	push(C);
	delete A;
	delete B;

	return EXIT_SUCCESS;
}

/**
 *  -- Print --
 * Asserts that the value at the top of the stack is an 8-bit integer. (If not,
 * see the instruction assert), then interprets it as an ASCII value and
 * displays the corresponding character on the standard output.
 **/
int		Instruction::print(const IOperand *value) {
	(void)value;
	if (verbose)
		std::cout << BLUE "<print>" EOC << std::endl;
	if (deque->size() == 0)
		throw Instruction::StackException( "print: Empty stack." );
	const IOperand *to_print = deque->front();
	if (to_print->getType() != eOperandType::Int8)
		throw Instruction::AssertException();
	std::cout << static_cast<char>( std::stod( to_print->toString() ) )
	<< std::endl;

	return EXIT_SUCCESS;
}

/**
 *  -- Exit --
 * Terminate the execution of the current program. If this instruction does not
 * appears while all others instruction has been processed, the execution must
 * stop with an error.
 **/
int		Instruction::exit(const IOperand *value) {
	(void)value;
	if (verbose)
		std::cout << BLUE "<exit>" EOC << std::endl;
	while (deque->size() > 0)
		pop();
	instruction_exited = true;

	return EXIT_INSTR;
}

// -- Bonus Instructions -------------------------------------------------------

/**
 *  -- Abs --
 * Unstacks the first value on the stack, found it absolute value, then stack
 * the result. If the number of values on the stack is empty, the program
 * execution must stop with an error.
 **/
int		Instruction::abs( const IOperand *value ) {
	(void)value;
	if (verbose)
		std::cout << BLUE "<abs>" EOC << std::endl;
	if (deque->size() == 0)
		throw Instruction::StackException( "abs: Empty stack." );

	Factory factory = Factory();

	const IOperand *val = deque->front();
	if ( val->toString().at(0) == '-' ) {
		const IOperand *absVal = factory.createOperand(val->getType()
		, val->toString().substr( 1 ));
		pop();
		push (absVal);
	}

	return EXIT_SUCCESS;
}

/**
 *  -- Min --
 * Add to the stack the min value of the 2 top value of the stack.
 * If the number of values on the stack is strictly inferior to 2,
 * the program execution must stop with an error.
 **/
int		Instruction::min( const IOperand *value ) {
	(void)value;
	if (verbose)
		std::cout << BLUE "<min>" EOC << std::endl;

	Factory factory;
	if (deque->size() < 2)
		throw Instruction::StackException( "min: Stack is lower 2." );
	const IOperand *A = deque->front();
	deque->pop_front();
	const IOperand *B = deque->front();
	push (A);
	const IOperand *C;
	if (*A < *B)
		C = factory.createOperand(A->getType(), A->toString());
	else
		C = factory.createOperand(B->getType(), B->toString());
	push( C );

	return EXIT_SUCCESS;
}

/**
 *  -- Max --
 * Add to the stack the max value of the 2 top value of the stack.
 * If the number of values on the stack is strictly inferior to 2,
 * the program execution must stop with an error.
 **/
int		Instruction::max( const IOperand *value ) {
	(void)value;
	if (verbose)
		std::cout << BLUE "<max>" EOC << std::endl;
	if (deque->size() < 2)
		throw Instruction::StackException( "max: Stack is lower 2." );
	Factory factory;
	const IOperand *A = deque->front();
	deque->pop_front();
	const IOperand *B = deque->front();
	push (A);
	const IOperand *C;
	if (*A > *B)
		C = factory.createOperand(A->getType(), A->toString());
	else
		C = factory.createOperand(B->getType(), B->toString());
	push( C );

	return EXIT_SUCCESS;
}

/**
 *  -- Pow --
 * Unstacks the first two values on the stack, pow them, then stacks the
 * result. If the number of values on the stack is strictly inferior to 2, the
 * program execution must stop with an error.
 **/
int		Instruction::pow( const IOperand *value ) {
	(void)value;

	if (verbose)
		std::cout << BLUE "<pow>" EOC << std::endl;

	if (deque->size() < 2)
		throw Instruction::StackException( "pow: Stack is lower 2." );
	const IOperand *A = deque->front();
	deque->pop_front();
	const IOperand *B = deque->front();
	deque->pop_front();
	const IOperand *C;
	C = A->pow(*B);
	push(C);
	delete A;
	delete B;

	return EXIT_SUCCESS;
}

/**
 * Debug print all the stack.
 **/
int		Instruction::debug(const IOperand *value) {
	(void)value;
	std::deque<const IOperand *>::iterator it;

	if (verbose)
		std::cout << BLUE "<debug>" EOC << std::endl;

	for (it = deque->begin(); it != deque->end(); ++it) {
		std::cout << dval(*it) << std::endl;
	}

	return EXIT_SUCCESS;
}

/**
 *  -- Clear --
 * Clear all the values from the stack.
 **/
int		Instruction::clear(const IOperand *value) {
	(void)value;
	if (verbose)
		std::cout << BLUE "<clear>" EOC << std::endl;
	while (deque->size() > 0)
		pop();
	return EXIT_SUCCESS;
}

/**
 *  -- Sep --
 * Print a separator on the output.
 **/
int		Instruction::sep(const IOperand *value) {
	(void)value;
	std::cout << "=====================================" << std::endl;
	return EXIT_SUCCESS;
}

/**
 *  -- Help --
 * Print all instruction usable.
 **/
int		Instruction::help(const IOperand *value) {
	(void)value;
	std::cout << "========= list instructions =========\n"
				 " push VALUE   : push value on stack\n"
				 " pop          : unstacks the value from the top of the stack\n"
				 " dump         : print all the stack values\n"
				 " assert VALUE : assert top stack value to VALUE\n"
				 " add          : unstack the 2 top stack's value and add them\n"
				 " sub          : unstack the 2 top stack's value and substract them\n"
				 " mul          : unstack the 2 top stack's value and multiply them\n"
				 " div          : unstack the 2 top stack's value and divide them\n"
				 " mod          : unstack the 2 top stack's value and mod them\n"
				 " print        : print the top value as a char if int8 type\n"
				 " exit         : exit the program\n"
				 BLUE ULINE "Bonus :\n" EOC
				 " ls           : alias to dump\n"
				 " abs          : absolute of the top of the stack value\n"
				 " min          : add to the stack the min value of the 2 top value of the stack\n"
				 " max          : add to the stack the max value of the 2 top value of the stack\n"
				 " pow          : unstack the 2 top stack's value and pow them\n"
				 " debug        : like dump, but also print the type and the precision\n"
				 " clear        : clear the all stack\n"
				 " sep          : print a separator\n"
				 " help         : print this help message\n"
				 "=====================================" << std::endl;
	return EXIT_SUCCESS;
}

// -- Public methods -----------------------------------------------------------

void Instruction::test_exit() {
	if (!instruction_exited)
		throw Instruction::ExitException();
}

std::string Instruction::dval(const IOperand *value) {
	std::string result;
	std::string type = "unknown";

	for (auto &&i : Lexer::typeArg) {
		if (i.second.operandType == value->getType()) {
			type = i.first;
		}
	}

	result = "{" + value->toString() + ", " + type + ", "
	+ std::to_string(value->getPrecision())  + "}";
	return result;
}
