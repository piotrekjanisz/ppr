#ifndef MY_TEST_H
#define MY_TEST_H

#include <iostream>
#include <string>

#define TEST_SUITE \
	void suite() { \
		int passed_tests = 0; \
		int failed_tests = 0;

#define TEST_SUITE_END \
		int total_tests = passed_tests + failed_tests; \
		std::cout << "-------------------------------------------------------" << std::endl; \
		std::cout << "number of tests: " << total_tests << std::endl; \
		std::cout << "PASSED: " << passed_tests << std::endl; \
		std::cout << "FAILED: " << failed_tests << std::endl; \
	}

#define TEST(name) \
	std::cout << "TEST: " #name ": "; \
	try { \
		name(); \
		std::cout << "PASSED" << std::endl; \
		passed_tests++; \
	} catch (AssertionException& ex) { \
		std::cout << "FAILED" << std::endl << "\t" << ex.getMessage() << std::endl; \
		failed_tests++; \
		std::cout << "--------------------" << std::endl; \
	} catch (...) { \
		std::cout << "FAILED" << std::endl << "\t" << "unexpected exception thrown at: " << std::endl; \
		failed_tests++; \
		std::cout << "--------------------" << std::endl; \
	} 

#define ASSERT_TRUE(expression) \
	if (!(expression)) { \
		throw AssertionException("expression: '" #expression "', expected to be TRUE"); \
	}

#define ASSERT_FALSE(expression) \
	if (expression) { \
		throw AssertionException("expression: '" #expression "', expected to be FALSE"); \
	}

#define ASSERT_LESS_THAN(expression, value) \
	if ((expression) < (value)) { \
		throw AssertionException("expression: '" #expression ", expected to be less than '" #value) \
	}

#define ASSERT_LESS_THAN_OR_EQUAL(expression, value) \
	if ((expression) <= (value)) { \
		throw AssertionException("expression: '" #expression ", expected to be less than or equal'" #value) \
	}

#define ASSERT_NO_THROW(statement) \
	try { \
		statement; \
	} catch (...) { \
		throw AssertionException("statement: '" #statement "', expected not to throw any exception"); \
	}

class AssertionException 
{
	std::string _msg;
public:
	AssertionException(const std::string& msg)
		:_msg(msg) {}

	std::string getMessage() const { return _msg; }
};
#endif
