/********************************************************************************************************************/
/*  CMatrix.h                                                                                                       */
/*                                                                                                                  */
/*  Modul "Steuergeraete/Software/Vernetzung - Embedded Systems II"                                                 */
/*  Uebung 3-03: C++-Programmierung–Klassendeﬁnition                                                                */
/*                                                                                                                  */
/*  Hochschule Mittweida, INW                                                                                       */
/*  Prof. J. Thomanek                                                                                               */
/*                                                                                                                  */
/********************************************************************************************************************/

#ifndef CMATRIX_HPP
#define CMATRIX_HPP

/*********************************************************************************************************************/
/*-----------------------------------------------------Constants-----------------------------------------------------*/
/*********************************************************************************************************************/

// Dimension of the matrix
const int N_ROW = 3;
const int N_COL = 3;

/*********************************************************************************************************************/
/*-----------------------------------------------------Class Declaration---------------------------------------------*/
/*********************************************************************************************************************/

class CMatrix
{
    public:
        /*********************************************************************************************************************/
        /*-----------------------------------------------------Constructors Declarations-------------------------------------*/
        /*********************************************************************************************************************/
        CMatrix ();
        CMatrix (double s);
        CMatrix (const double *a);
        CMatrix (const CMatrix &m);

        /*********************************************************************************************************************/
        /*-----------------------------------------------------Public Methods Declarations-----------------------------------*/
        /*********************************************************************************************************************/

        // Matrix element access
        double GetElement (int r, int c) const;
        void SetElement (int r, int c, double v);

        // Scalar operations
        void AddScalar (double s);
        void MulScalar (double s);

        // Matrix operations
        void Plus (CMatrix &m); // m1 = m1 + m
        CMatrix Add (CMatrix &m) const; // m2 = m1 + m
        CMatrix Mul (const CMatrix &m) const; // m2 = m1 * m

        // Transpose Matrix
        void Transpose ();

    private:

        // Matrix Data Array
        double m_f64Data[N_ROW * N_COL];
};

#endif // CMATRIX_HPP
