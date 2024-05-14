/*******************************************************************************
* @author:    Gabriel Touzalin                          ▄███▀▄     ▄▀███▄      *
* @contact:   gabriel.touzalin@gmail.com                ██████▀▀ ▀▀██████      *
* @github:    https://github.com/TheEmperorPenguin     ████ █  ▄▄▄ █ ████      *
* @date:      1970-01-01 01:00:00                      ██▀█ █ █▄▀▄█ █ █▀██     *
*                                                     ▀▀█▄▄█▀ ▀███▀ ▀█▄▄█▀▀    *
* @lastModifiedBy:   Gabriel TOUZALIN                                          *
* @lastModifiedTime: 2024-03-02 15:09:37                                       *
*******************************************************************************/

#include "../includes/Matrix.hpp"

int main(void)
{
    TESTC("Empty Matrix",
        Matrix<float> test00(0);
    )

    TEST("Smallest Matrix",
        Matrix<float> test01(1);
        std::cout << test01 << std::endl;
    )

    TEST("Simple Matrix",
        Matrix<float> test02(10);
        std::cout << test02 << std::endl;
    )

    TESTC("Empty Matrix",
        Matrix<float> test03(0,0);
    )

    TEST("Simple Matrix",
        Matrix<float> test04(1,1);
        std::cout << test04 << std::endl;
    )
    TEST("Simple Matrix",
        Matrix<float> test05(10,1);
        std::cout << test05 << std::endl;
    )
    TEST("Simple Matrix",
        Matrix<float> test06(1,10);
        std::cout << test06 << std::endl;
    )
    TEST("Simple Matrix",
        Matrix<float> test07(100,2);
        std::cout << test07 << std::endl;
    )

    std::vector<float> vec08 = {1.0f, 10.0f, 5.0f, 21.4f,1.0f, 10.0f, 5.0f, 21.4f,1.0f, 10.0f, 5.0f, 21.4f,1.0f, 10.0f, 5.0f, 21.4f};
    TEST("Matrix Values",
        Matrix<float> test08(vec08, 4, 4);
        std::cout << test08 << std::endl;
        if( test08.getValue(0,0) != 1.0f )
            throw(TestingError());
    )

    std::vector<float> vec09 = {};
    TEST("Simple Matrix",
        Matrix<float> test09(vec09, 4, 4);
        std::cout << test09 << std::endl;
    )

    std::vector<float> vec10 = {1.0f, 5.0f, 21.4f,1.0f, 10.0f, 5.0f, 21.4f};
    TEST("Simple Matrix",
        Matrix<float> test10(vec10, 2, 2);
        std::cout << test10  << std::endl;
    )




    // Matrix<float> hello1(1,5);
    // std::cout << hello1 << std::endl;
    // Matrix<float> hello2(2,9);
    // std::cout << hello2 << std::endl;
    // Matrix<float> hello3(2,1);
    // std::cout << hello3 << std::endl;
    // std::vector<float> input = {10.0f, 20.0f, 1.0f};
    // Matrix<float> hello4( input, 10 , 5 );
    // hello4.setValue(1000.50123f, 9, 4);
    // std::cout << hello4.getValue(9,4) << std::endl;
    // std::cout << hello4 << std::endl;
    // hello3 = hello4;
    // std::cout << hello3 << std::endl;
    // std::vector<float> input5 = {1.0f, 10.0f, 5.0f, 21.4f,1.0f, 10.0f, 5.0f, 21.4f,1.0f, 10.0f, 5.0f, 21.4f,1.0f, 10.0f, 5.0f, 21.4f};
    // Matrix<float> hello5(input5, 1, 16);
    // std::cout << hello5 << std::endl;
    // std::vector<float> input6 = {10.0f, 10.0f, 50.0f, 2100.4f,10.0f, 10.0f, 50.0f, 2100.4f,10.0f, 10.0f, 50.0f, 2100.4f,10.0f, 10.0f, 50.0f, 2100.4f};
    // Matrix<float> hello6(input6, 16, 1);
    // std::cout << hello6 << std::endl;
    // hello5 = hello5 * hello6;
    // std::cout << hello5 << std::endl;
    // hello5 *= 10.f;
    // std::cout << hello5 << std::endl;
    std::cout << ERROR_COUNT << std::endl;
    return ERROR_COUNT;
}