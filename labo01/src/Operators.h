#pragma once

/**
 * @file Operators.h
 *
 * @brief Implémentation de divers opérateurs arithmétiques pour les matrices et les vecteurs.
 *
 * Nom: Sébastien Charbonneau
 * Code permanent : Chas01049805
 * Email : sebastien.charbonneau.1@ens.etsmtl.ca
 *
 */

#include "Matrix.h"
#include "Vector.h"

namespace gti320
{

    /** Multiplication : Matrice * Matrice (générique) */
    template <typename _Scalar, int RowsA, int ColsA, int StorageA, int RowsB, int ColsB, int StorageB>
    Matrix<_Scalar, RowsA, ColsB> operator*(const Matrix<_Scalar, RowsA, ColsA, StorageA>& A, const Matrix<_Scalar, RowsB, ColsB, StorageB>& B)
    {
        assert(A.cols() == B.rows());

        Matrix<_Scalar, RowsA, ColsB> M(A.rows(), B.cols());
        M.setZero();

        for(int i=0; i < A.rows(); i++){
            for(int j=0; j < B.cols(); j++){
                for(int a=0; a < B.rows(); a++){
                    //std::cout << "i: " << i << "\n";
                    //std::cout << "j: " << j << "\n";
                    //std::cout << "a: " << a << "\n";
                    M(i,j) += A(i,a)*B(a,j);
                }
            }
        }
        return M;
    }

    /**
     * Multiplication : Matrice (colonne) * Matrice (ligne)
     *
     * Spécialisation de l'opérateur de multiplication pour le cas où les matrices
     * ont un stockage à taille dynamique et où la matrice de gauche utilise un
     * stockage par colonnes et celle de droite un stockage par lignes.
     */
    template <typename _Scalar>
    Matrix<_Scalar, Dynamic, Dynamic> operator*(const Matrix<_Scalar, Dynamic, Dynamic, ColumnStorage>& A, const Matrix<_Scalar, Dynamic, Dynamic, RowStorage>& B)
    {

    //      j           A
    // i    1 2 3   -> [1,4,7,2,5,8,3,6,9]
    //      4 5 6
    //      7 8 9
    //      j           B
    // i    1 2 3   -> [1,2,3,4,5,6,7,8,9]
    //      4 5 6
    //      7 8 9
        assert(A.cols() == B.rows());

        Matrix<_Scalar, Dynamic, Dynamic> M(A.rows(), B.cols());
        M.setZero();

        for(int i=0; i < B.rows(); i++){
            for(int j=0; j < B.cols(); j++){
                for(int a=0; a < A.rows(); a++){
                    M(a,j) += A(a,i)*B(i,j);
                }
            }
        }
        return M;
    }

    /**
     * Multiplication : Matrice (ligne) * Matrice (colonne)
     *
     * Spécialisation de l'opérateur de multiplication pour le cas où les matrices
     * ont un stockage à taille dynamique et où la matrice de gauche utilise un
     * stockage par lignes et celle de droite un stockage par colonnes.
     */
    template <typename _Scalar>
    Matrix<_Scalar, Dynamic, Dynamic> operator*(const Matrix<_Scalar, Dynamic, Dynamic, RowStorage>& A, const Matrix<_Scalar, Dynamic, Dynamic, ColumnStorage>& B)
    {
        assert(A.cols() == B.rows());

        Matrix<_Scalar, Dynamic, Dynamic> M(A.rows(), B.cols());
        M.setZero();

        for(int i=0; i < A.rows(); i++){
            for(int j=0; j < B.cols(); j++){
                for(int a=0; a < B.rows(); a++){
                    M(i,j) += A(i,a)*B(a,j);
                }
            }
        }
        return M;
    }

    /** Addition : Matrice + Matrice (générique) */
    template <typename _Scalar, int Rows, int Cols, int StorageA, int StorageB>
    Matrix<_Scalar, Rows, Cols> operator+(const Matrix<_Scalar, Rows, Cols, StorageA>& A, const Matrix<_Scalar, Rows, Cols, StorageB>& B)
    {
        assert(A.rows() == B.rows());
        assert(A.cols() == B.cols());

        Matrix<double, Dynamic, Dynamic> M(A.rows(), B.cols());
        M.setZero();

        for(int i=0; i < A.rows(); i++){
            for(int j=0; j < A.cols(); j++){
                M(i,j) = A(i,j) + B(i,j);
            }
        }

        return M;
    }

    /**
     * Addition : Matrice (colonne) + Matrice (colonne)
     *
     * Spécialisation de l'opérateur d'addition pour le cas où les deux matrices
     * sont stockées par colonnes.
     */
    template <typename _Scalar>
    Matrix<_Scalar, Dynamic, Dynamic> operator+(const Matrix<_Scalar, Dynamic, Dynamic, ColumnStorage>& A, const Matrix<_Scalar, Dynamic, Dynamic, ColumnStorage>& B)
    {
        assert(A.rows() == B.rows());
        assert(A.cols() == B.cols());

        Matrix<double, Dynamic, Dynamic> M(A.rows(), B.cols());
        M.setZero();

        for(int j=0; j < A.cols(); j++){
            for(int i=0; i < A.rows(); i++){
                M(i,j) = A(i,j) + B(i,j);
            }
        }

        return M;
    }

    /**
     * Addition : Matrice (ligne) + Matrice (ligne)
     *
     * Spécialisation de l'opérateur d'addition pour le cas où les deux matrices
     * sont stockées par lignes.
     */
    template <typename _Scalar>
    Matrix<_Scalar, Dynamic, Dynamic, RowStorage> operator+(const Matrix<_Scalar, Dynamic, Dynamic, RowStorage>& A, const Matrix<_Scalar, Dynamic, Dynamic, RowStorage>& B)
    {
        assert(A.rows() == B.rows());
        assert(A.cols() == B.cols());

        Matrix<double, Dynamic, Dynamic, RowStorage> M(A.rows(), B.cols());
        M.setZero();

        for(int i=0; i < A.rows(); i++){
            for(int j=0; j < A.cols(); j++){
                M(i,j) = A(i,j) + B(i,j);
            }
        }

        return M;
    }

    /**
     * Multiplication  : Scalaire * Matrice (colonne)
     *
     * Spécialisation de l'opérateur de multiplication par un scalaire pour le
     * cas d'une matrice stockée par colonnes.
     */
    template <typename _Scalar, int _Rows, int _Cols>
    Matrix<_Scalar, _Rows, _Cols, ColumnStorage> operator*(const _Scalar& a, const Matrix<_Scalar, _Rows, _Cols, ColumnStorage>& A)
    {
        Matrix<double, Dynamic, Dynamic> M(A.rows(), A.cols());
        M.setZero();

        for(int j=0; j < A.cols(); j++){
            for(int i=0; i < A.rows(); i++){
                M(i,j) = a * A(i,j);
            }
        }

        return M;
    }

    /**
     * Multiplication  : Scalaire * Matrice (ligne)
     *
     * Spécialisation de l'opérateur de multiplication par un scalaire pour le
     * cas d'une matrice stockée par lignes.
     */
    template <typename _Scalar, int _Rows, int _Cols>
    Matrix<_Scalar, _Rows, _Cols, RowStorage> operator*(const _Scalar& a, const Matrix<_Scalar, _Rows, _Cols, RowStorage>& A)
    {
        Matrix<double, Dynamic, Dynamic, RowStorage> temp(A.rows(), A.cols());
        temp.setZero();

        for(int i=0; i < A.rows(); i++){
            for(int j=0; j < A.cols(); j++){
                temp(i,j) = a * A(i,j);
            }
        }

        return temp;
    }

    /**
     * Multiplication : Matrice (ligne) * Vecteur
     *
     * Spécialisation de l'opérateur de multiplication matrice*vecteur pour le
     * cas où la matrice est représentée par lignes.
     */
    template <typename _Scalar, int _Rows, int _Cols>
    Vector<_Scalar, _Rows> operator*(const Matrix<_Scalar, _Rows, _Cols, RowStorage>& A, const Vector<_Scalar, _Cols>& v)
    {
        assert(A.cols() == v.size());

        Vector<_Scalar, Dynamic>  Vres(A.rows());
        Vres.setZero();

        for(int i=0; i < A.rows(); i++){
            for(int j=0; j < A.cols(); j++){
                Vres(i) += A(i,j) * v(j);
            }
        }
        return Vres;
    }

    /**
     * Multiplication : Matrice (colonne) * Vecteur
     *
     * Spécialisation de l'opérateur de multiplication matrice*vecteur pour le
     * cas où la matrice est représentée par colonnes.
     */
    template <typename _Scalar, int _Rows, int _Cols>
    Vector<_Scalar, _Rows> operator*(const Matrix<_Scalar, _Rows, _Cols, ColumnStorage>& A, const Vector<_Scalar, _Cols>& v)
    {
        assert(A.cols() == v.size());

        Vector<_Scalar, _Rows> Vres(A.rows());
        Vres.setZero();

        for(int j=0; j < A.cols(); j++){
            for(int i=0; i < A.rows(); i++){
                Vres(i) += A(i,j) * v(j);
            }
        }
        return Vres;
    }

    /** Multiplication : Scalaire * Vecteur */
    template <typename _Scalar, int _Rows>
    Vector<_Scalar, _Rows> operator*(const _Scalar& a, const Vector<_Scalar, _Rows>& v)
    {
        Vector<_Scalar, Dynamic>  Vres(v.size());
        Vres.setZero();

        for(int j=0; j < v.size(); j++){
                Vres(j) += a * v(j);
            }

        return Vres;
    }

    /** Addition : Vecteur + Vecteur */
    template <typename _Scalar, int _RowsA, int _RowsB>
    Vector<_Scalar, _RowsA> operator+(const Vector<_Scalar, _RowsA>& a, const Vector<_Scalar, _RowsB>& b)
    {
        assert(a.size() == b.size());

        Vector<_Scalar, _RowsA>  Vres(a.size());
        Vres.setZero();

        for(int j=0; j < a.size(); j++){
                Vres(j) += a(j) + b(j);
            }
        return Vres;
    }

    /** Soustraction : Vecteur - Vecteur */
    template <typename _Scalar, int _RowsA, int _RowsB>
    Vector<_Scalar, _RowsA> operator-(const Vector<_Scalar, _RowsA>& a, const Vector<_Scalar, _RowsB>& b)
    {
        assert(a.size() == b.size());

        Vector<_Scalar, _RowsA> Vres(a.size());
        Vres.setZero();

        for(int j=0; j < a.size(); j++){
                Vres(j) += a(j) - b(j);
            }
        return Vres;
    }
}   
