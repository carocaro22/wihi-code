/******************************************************************************
 * Test of class CMatrix                                                      *
 * MatrixLib.cpp                                                              *
 *                                                                            *
 * Module: "Embedded Systems II" - Uebung 3-03                                *
 *                                                                            *
 * Hochschule Mittweida, INW                                                  *
 * Prof. J. Thomanek                                                          *
 *                                                                            *
 ******************************************************************************/
#include <MatrixLib/CMatrix.h>
#include <MatrixLib/MatrixLib.h>
#include "ASCLIN_Shell_UART.h"

// Help function to display 3 x 3 matrix
void PrintMatrix(CMatrix &m)
{
    printDouble(m.GetElement(0, 0)); printMessage(" "); printDouble(m.GetElement(0, 1)); printMessage(" "); printDouble(m.GetElement(0, 2));
    printDouble(m.GetElement(1, 0)); printMessage(" "); printDouble(m.GetElement(1, 1)); printMessage(" "); printDouble(m.GetElement(1, 2));
    printDouble(m.GetElement(2, 0)); printMessage(" "); printDouble(m.GetElement(2, 1)); printMessage(" "); printDouble(m.GetElement(2, 2));
    printLine("");
/*
    std::cout << m.GetElement(0, 0) << " " << m.GetElement(0, 1) << " "
              << m.GetElement(0, 2) << "\n";
    std::cout << m.GetElement(1, 0) << " " << m.GetElement(1, 1) << " "
              << m.GetElement(1, 2) << "\n";
    std::cout << m.GetElement(2, 0) << " " << m.GetElement(2, 1) << " "
              << m.GetElement(2, 2) << "\n\n";
*/
}

void TestCMatrix(void) {
    // Create some matrices
    // ------------------------------------------------
    CMatrix m1(5.0); // Initialization by a scalar
    CMatrix m2(4.0); // Initialization by a scalar
    CMatrix m3;      // Initialization by zero
    CMatrix m4;      // Initialization by zero

    // Check add and multiply with a scalar
    // ------------------------------------------------
    // m1 = 2.0 + m1
    m1.AddScalar(2.0);
    PrintMatrix(m1);

    // m2 = 3.0 * m2
    m2.MulScalar(3);
    PrintMatrix(m2);

    // Check addition of two matrices
    // ------------------------------------------------
    // m2 = m2 + m1
    m2.Plus(m1);
    PrintMatrix(m2);

    // m3 = m1 + m2
    m3 = m1.Add(m2);
    PrintMatrix(m3);

    // Check multiplication of two matrices
    // ------------------------------------------------
    // m4 = m1 * m2
    m4 = m1.Mul(m2);
    PrintMatrix(m4);

    // Check transpose
    // ------------------------------------------------
    double b[3*3] = { 1.9, 2.8, 3.7,
                      4.6, 5.5, 6.4,
                      7.3, 8.2, 9.1 };
    CMatrix B(b); // Initialization by an array
    PrintMatrix(B);

    // Transpose
    B.Transpose();
    PrintMatrix(B);
}
