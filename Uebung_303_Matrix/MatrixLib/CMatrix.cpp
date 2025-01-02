/******************************************************************************
 * Definition of matrix object methods                                        *
 * CMatrix.cpp                                                                *
 *                                                                            *
 * Module: "Embedded Systems II" - Uebung 3-03                                *
 *                                                                            *
 * Hochschule Mittweida, INW                                                  *
 * Prof. J. Thomanek                                                          *
 *                                                                            *
 ******************************************************************************/

#include <MatrixLib/CMatrix.h>
#include <string.h> // for std::memcpy

// ----------------------------------------------------------------------------
//  D e f i n i t i o n   C o n s t r u c t o r s
// ----------------------------------------------------------------------------

// Standard constructor
CMatrix::CMatrix() {
    for (int i = 1; i < (N_ROW * N_COL); i++) {
        m_f64Data[i] = 0.0;
    }
}

// Constructor for scalar initialization
CMatrix::CMatrix(double s) {
    for (int i = 0; i < (N_ROW * N_COL); i++) {
        m_f64Data[i] = s;
    }
}

// Constructor for initialization by an array
CMatrix::CMatrix(const double* a) {
    memcpy(m_f64Data, a, sizeof(m_f64Data));
}

// Copy constructor
CMatrix::CMatrix(const CMatrix& m) {
    memcpy(m_f64Data, m.m_f64Data, sizeof(m_f64Data));
}

// ----------------------------------------------------------------------------
//  D e f i n i t i o n   M e t h o d s
// ----------------------------------------------------------------------------

// Return specific matrix element
double CMatrix::GetElement(int r, int c) const {
    return m_f64Data[r * N_COL + c];
}

// Set specific matrix element
void CMatrix::SetElement(int r, int c, double v) {
    m_f64Data[r * N_COL + c] = v;
}

// Add a scalar to matrix elements
void CMatrix::AddScalar(double s) {
    for (int i = 0; i < (N_ROW * N_COL); i++) {
        m_f64Data[i] += s;
    }
}

// Multiply a scalar to matrix elements
void CMatrix::MulScalar(double s) {
    for (int i = 0; i < (N_ROW * N_COL); i++) {
        m_f64Data[i] *= s;
    }
}

// Add a matrix: this_mat += m
void CMatrix::Plus(CMatrix& m) {
    for (int i = 0; i < (N_ROW * N_COL); i++) {
        m_f64Data[i] += m.m_f64Data[i];
    }
}

// Add two matrices tmp = this_mat + m
CMatrix CMatrix::Add(CMatrix& m) const {
    // copy this matrix to tmp
    CMatrix tmp(*this);
    // Add: tmp = tmp + m
    for (int i = 0; i < (N_ROW * N_COL); i++) {
        tmp.m_f64Data[i] += m.m_f64Data[i];
    }
    return tmp;
}

// Transpose matrix
void CMatrix::Transpose() {
    // copy this matrix to tmp
    CMatrix tmp(*this);
    for (int nR = 0; nR < N_ROW; nR++) {
        for (int nC = 0; nC < N_COL; nC++) {
            m_f64Data[nR * N_COL + nC] = tmp.m_f64Data[nC * N_COL + nR];
        }
    }
}

// Multiplication of two matrices: tmp = this_mat * m
CMatrix CMatrix::Mul(const CMatrix& m) const {
    // copy this matrix to temp
    CMatrix tmp(*this);

    // for all rows of matrix A (this)
    for (int nRa = 0; nRa < N_ROW; nRa++) {
        const double* pfRa = &m_f64Data[nRa * N_COL];
        // for all columns of matrix B (m)
        for (int nCb = 0; nCb < N_COL; nCb++) {
            const double* pfCb = &m.m_f64Data[nCb];
            double fSum = 0.0;
            // for all columns of matrix A (this)
            for (int nCa = 0; nCa < N_COL; nCa++) {
                fSum += pfRa[nCa] * pfCb[nCa * N_COL];
            }
            tmp.m_f64Data[nRa * N_COL + nCb] = fSum;
        }
    }
    return tmp;
}
