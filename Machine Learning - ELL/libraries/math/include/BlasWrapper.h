/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/math/include/BlasWrapper.h
 *
 *  Created on: Feb 27, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#pragma once 

#include <cstddef>

namespace ell 
{
    namespace math 
    {
        enum class MatrixLayout;
        enum class MatrixTranspose;

        namespace Blas
        {  
            // Map the given enum value to OpenBLAS's definition
            int GetCBlasMatrixOrder(MatrixLayout order);
            int GetCBlasMatrixTranspose(MatrixTranspose transpose);

            int SetNumThreads(int numThreads);

            void Copy(int n, const float* x, int incx, float* y, int incy);
            void Copy(int n, const double* x, int incx, double* y, int incy);

            float Asum(int n, const float* x, int incx);
            double Asum(int n, const double* x, int incx);

            float Nrm2(int n, const float* x, int incx);
            double Nrm2(int n, const double* x, int incx);

            void Scal(int n, float alpha, float* x, int incx);
            void Scal(int n, double alpha, double* x, int incx);

            void Axpy(int n, float alpha, const float* x, int incx, float* y, int incy);
            void Axpy(int n, double alpha, const float* x, int incx, double* y, int incy);

            float Dot(int n, const float* x, int incx, const float* y, int incy);
            double Dot(int n, const double* x, int incx, const double* y, int incy);

            void Ger(MatrixLayout order, int m, int n, float alpha, const float* x, int incx,
                        const float* y, int incy, float* M, int lda);
            void Ger(MatrixLayout order, int m, int n, double alpha, const double* x, int incx,
                        const double* y, int incy, double *M, int lda);
            
            void Gemv(MatrixLayout order, MatrixTranspose transpose, int m, int n, float alpha, const float* M, 
                        int lda, const float* x, int incx, float beta, float* y, int incy);
            void Gemv(MatrixLayout order, MatrixTranspose transpose, int m, int n, double alpha, const double* M,
                        int lda, const double* x, int incx, double beta, double* y, int incy);

            void Gemm(MatrixLayout order, MatrixTranspose transposeA, MatrixTranspose transposeB, int m, int n, int k, 
                        float alpha, const float* A, int lda, const float* B, int ldb, float beta, float* C, int ldc);
            void Gemm(MatrixLayout order, MatrixTranspose transposeA, MatrixTranspose transposeB, int m, int n, int k, 
                        double alpha, const double* A, int lda, const double* B, int ldb, double beta, double* C, int ldc);
        } 
    }
}
