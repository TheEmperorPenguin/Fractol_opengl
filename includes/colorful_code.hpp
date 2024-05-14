/*******************************************************************************
* @author:    Gabriel Touzalin                          ▄███▀▄     ▄▀███▄      *
* @contact:   gabriel.touzalin@gmail.com                ██████▀▀ ▀▀██████      *
* @github:    https://github.com/TheEmperorPenguin     ████ █  ▄▄▄ █ ████      *
* @date:      1970-01-01 01:00:00                      ██▀█ █ █▄▀▄█ █ █▀██     *
*                                                     ▀▀█▄▄█▀ ▀███▀ ▀█▄▄█▀▀    *
* @lastModifiedBy:   Gabriel TOUZALIN                                          *
* @lastModifiedTime: 2024-03-02 13:36:28                                       *
*******************************************************************************/

#ifndef COLORFUL_CODE_HPP
# define COLORFUL_CODE_HPP

#include <iostream>
#include <iomanip>

#define COLOR_RESET "\e[0m"
#define BLUE        "\e[0;34m"
#define GREEN   	"\e[0;32m"
#define RED     	"\e[0;31m"
#define PURPLE      "\e[0;35m"
#define ORANGE      "\e[38;5;214m"

#define BLINKING    "\033[5m"
#define UNDERLINE   "\e[4m"

#define BOX_UP   "╓─────────────────────────────╼━━━━━━━━━━━━━━━━━━╾─────────────────────────────╖"
#define BOX_DOWN "╙─────────────────────────────╼━━━━━━━━━━━━━━━━━━╾─────────────────────────────╜"

#define NL          std::cout << std::endl

inline unsigned int TEST_COUNT;
inline unsigned int ERROR_COUNT;

std::string color_string(std::string str, std::string color);
std::string blinking_string(std::string str);
std::string center_string(std::string str);
std::string center_string_title(std::string str);

#define COLORED_OUTPUT(code_block, color)   \
    std::cout << color;                     \
    code_block                              \
    std::cout << COLOR_RESET;

#define COLORED_CSTRING(str, color)         \
    color str COLOR_RESET
 
#define TEST(description, code_block)                                       \
    std::cout << BOX_UP << std::endl;                         \
    std::cout << center_string_title("\e[4m\e[38;5;45mTEST") << " " << std::setw(2) << std::setfill('0') << TEST_COUNT << "\e[0m" << std::endl;  \
    std::cout << "\e[3m\e[38;5;215m" << center_string("-" description "-") << "\e[0m" << std::endl; \
    std::cout << BOX_DOWN << std::endl;                         \
    std::cout << std::endl << "\e[38;5;47m" << "--Start of test block--" << "\e[0m" << std::endl << std::endl;\
    TEST_COUNT++;\
    try\
    {\
        code_block\
    }\
    catch(const std::exception& e)\
    {\
        ERROR_COUNT++;\
        std::cout << __FILE__ << "::" << __FUNCTION__ << "::" << __LINE__ << "::" << e.what() << std::endl;\
    }\
    std::cout << std::endl << "\e[38;5;197m" << "--End of test block--" << "\e[0m" << std::endl << std::endl << std::endl;

#define TESTC(description, code_block)                                       \
    std::cout << BOX_UP << std::endl;                         \
    std::cout << center_string_title("\e[4m\e[38;5;45mTEST") << " " << std::setw(2) << std::setfill('0') << TEST_COUNT << "\e[0m" << std::endl;  \
    std::cout << "\e[3m\e[38;5;215m" << center_string("-" description "-") << "\e[0m" << std::endl; \
    std::cout << BOX_DOWN << std::endl;                         \
    std::cout << std::endl << "\e[38;5;47m" << "--Start of test block--" << "\e[0m" << std::endl << std::endl;\
    TEST_COUNT++;\
    try\
    {\
        code_block\
        ERROR_COUNT++;\
    }\
    catch(const std::exception& e)\
    {\
        std::cout << __FILE__ << "::" << __FUNCTION__ << "::" << __LINE__ << "::" << e.what() << std::endl;\
    }\
    std::cout << std::endl << "\e[38;5;197m" << "--End of test block--" << "\e[0m" << std::endl << std::endl << std::endl;

    std::string color_string(std::string str, std::string color)
    {
        return(color + str + COLOR_RESET);
    }

    std::string blinking_string(std::string str)
    {
        return(BLINKING + str + COLOR_RESET);
    }

    std::string underline_string(std::string str)
    {
        return(UNDERLINE + str + COLOR_RESET);
    }

    std::string   center_string(std::string str)
    {
        int left_space = (80 - str.length()) / 2;
        return (std::string(left_space, ' ') + str);
    }
    std::string   center_string_title(std::string str)
    {
        int left_space = (80 - (str.length() + 3 - 14)) / 2;
        return (std::string(left_space, ' ') + str);
    }

    class TestingError : public std::exception
		{
			public:
				virtual const char* what() const throw ();
		};
    const char* TestingError::what() const throw ()
    {
        return "TestingError::";
    }
#endif