#include "Instruction.hpp"
#include "Operand.hpp"
#include "IOperand.hpp"
#include <iostream>

#define TEST(x) try { x } catch (std::exception &e) { print_error(e.what()); \
if (!instruction.continue_error) return (EXIT_FAILURE); }

void	print_error(std::string error);

int		test(Instruction &instruction) {
	test_factory();

	// instruction.clear();

	if (!test1(instruction)) {
		try {
			instruction.test_exit();
		} catch (std::exception &e) {
			print_error(e.what());
		}
	}
	instruction.clear();

	if (!test2(instruction)) {
		try {
			instruction.test_exit();
		} catch (std::exception &e) {
			print_error(e.what());
		}
	}

	instruction.clear();

	if (!test3(instruction)) {
		try {
			instruction.test_exit();
		} catch (std::exception &e) {
			print_error(e.what());
		}
	}
	instruction.clear();

	return (0);
}

int		test_factory()
{
	Factory factory = Factory();

	const IOperand *A = factory.createOperand(eOperandType::Int8, "15");
	const IOperand *B = factory.createOperand(eOperandType::Float, "0");

	const IOperand *C;

	std::cout << "A: " << A->toString() << ", " << A->getType() << ", "
	<< A->getPrecision() << std::endl;
	std::cout << "B: " << B->toString() << ", " << B->getType() << ", "
	<< B->getPrecision() << std::endl;

	try {
		C = *A + *B;
		std::cout << "C: A + B = "  << A->toString() << " + " << B->toString() << " = " << C->toString() << ", " << C->getType() << ", " << C->getPrecision() << std::endl;
		delete C;
	} catch (std::exception &e) {
		print_error("C: A + B = " + A->toString() + " + " + B->toString() + " = " + e.what());
	}
	try {
		C = *A - *B;
		std::cout << "C: A - B = "  << A->toString() << " - " << B->toString() << " = " << C->toString() << ", " << C->getType() << ", " << C->getPrecision() << std::endl;
		delete C;
	} catch (std::exception &e) {
		print_error("C: A - B = " + A->toString() + " - " + B->toString() + " = " + e.what());
	}
	try {
		C = *A / *B;
		std::cout << "C: A / B = " << A->toString() << " / " << B->toString() << " = " << C->toString() << ", " << C->getType() << ", " << C->getPrecision() << std::endl;
		delete C;
	} catch(std::exception &e) {
		print_error("C: A / B = " + A->toString() + " / " + B->toString() + " = " + e.what());
	}
	try {
		C = *A % *B;
		std::cout << "C: A % B = " << A->toString() << " % " << B->toString() << " = " << C->toString() << ", " << C->getType() << ", " << C->getPrecision() << std::endl;
		delete C;
	} catch (std::exception &e) {
		print_error("C: A % B = " + A->toString() + " % " + B->toString() + " = " + e.what());
	}
	try {
		C = *A * *B;
		std::cout << "C: A x B = " << A->toString() << " x " << B->toString() << " = " << C->toString() << ", " << C->getType() << ", " << C->getPrecision() << std::endl;
		delete C;
	} catch (std::exception &e) {
		print_error("C: A x B = " + A->toString() + " x " + B->toString() + " = " + e.what());
	}

	delete A;
	delete B;

	return (EXIT_SUCCESS);
}

int		test1(Instruction &instruction) {
	Factory factory = Factory();

	/**
	 * Test 1
	 */
	std::cout << ">>>>> TEST 1" << std::endl;
	try {
		// push int32(2)
		instruction.push(factory.createOperand(eOperandType::Int32, "2"));
		// push int32(3)
		instruction.push(factory.createOperand(eOperandType::Int32, "3"));
		// add
		instruction.add();
		// assert int32(5)
		instruction.assert_val(factory.createOperand(eOperandType::Int32, "5"));
		// dump
		instruction.dump();

	} catch (std::exception &e) {
		print_error(e.what());
	}
	// exit
	instruction.exit();
	return (EXIT_SUCCESS);
}

int		test2(Instruction &instruction) {
	/**
	 * Test 2
	 */
	std::cout << ">>>>> TEST 2" << std::endl;
	// pop
	try {
		instruction.pop();
	} catch (std::exception &e) {
		print_error(e.what());
	}

	instruction.exit();
	return (EXIT_SUCCESS);
}

int		test3(Instruction &instruction) {
	Factory factory = Factory();

	/**
	 * Test 3
	 */
	std::cout << ">>>>> TEST 3" << std::endl;
	// push int32(2)
	instruction.push(factory.createOperand(eOperandType::Int32, "42"));

	// add
	TEST(instruction.add();)

	// push int32(33)
	instruction.push(factory.createOperand(eOperandType::Int32, "33"));

	// add
	TEST(instruction.add();)

	// push float(44.55)
	TEST(instruction.push(factory.createOperand(eOperandType::Float, "44.55"));)

	// mul
	TEST(instruction.mul();)

	// push double(42.42)
	TEST(instruction.push(factory.createOperand(eOperandType::Double, "42.42"));)

	// push int32(42)
	TEST(instruction.push(factory.createOperand(eOperandType::Int32, "42"));)

	// dump
	TEST(instruction.dump();)

	// pop
	TEST(instruction.pop();)

	// assert double(42.42)
	TEST(instruction.assert_val(factory.createOperand(eOperandType::Double, "42.42"));)

	// push int8(42)
	TEST(instruction.push(factory.createOperand(eOperandType::Int8, "42"));)

	instruction.print();

	// exit
	instruction.exit();
	TEST(instruction.test_exit();)

	return (EXIT_SUCCESS);
}
