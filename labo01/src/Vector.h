#pragma once

/**
 * @file Vector.h
 *
 * @brief Implémentation de vecteurs simples
 *
 * Nom:Sébastien charbonneau
 * Code permanent CHAS01049805:
 * Email :sebastien.charbonneau.1@ens.etsmtl.ca
 *
 */

#include "MatrixBase.h"

namespace gti320
{

    /**
     * Classe vecteur générique.
     *
     * Cette classe réutilise la classe `MatrixBase` et ses spécialisations de
     * templates pour les manipulation bas niveau.
     */
    template <typename _Scalar = double, int _Rows = Dynamic>
    class Vector : public MatrixBase<_Scalar, _Rows, 1>
    {
    public:
        /** Constructeur par défaut */
        Vector() : MatrixBase<_Scalar, _Rows, 1>() {}

        /** Contructeur à partir d'un taille (rows). */
        explicit Vector(int rows) : MatrixBase<_Scalar, _Rows, 1>(rows, 1) {}

        //NOUVEAU
        /** Contructeur à partir de trois scalaire. */
        explicit Vector(_Scalar scal1, _Scalar scal2, _Scalar scal3) : MatrixBase<_Scalar, _Rows, 1>(3, 1) {
            (*this)(0) = scal1;
            (*this)(1) = scal2;
            (*this)(2) = scal3;
        }


        /** Constructeur de copie */
        Vector(const Vector& other) : MatrixBase<_Scalar, _Rows, 1>(other) {}

        /** Destructeur */
        ~Vector() {}

        /** Opérateur de copie */
        Vector& operator=(const Vector& other)
        {
            if (this != &other)
            {
                // assert(other.m_size == m_size);
             (*this).m_storage = other.m_storage;

            }
            return *this;
        }

        /** Accesseur à une entrée du vecteur (lecture seule) */
        _Scalar operator()(int i) const
        {
            assert((*this).size() > i && 0 <= i);
            return (*this).m_storage.data()[i];
        }

        /** Accesseur à une entrée du vecteur (lecture et écriture) */
        _Scalar& operator()(int i)
        {
            assert((*this).size() > i && 0 <= i);
            return (*this).m_storage.data()[i];
        }

        /** Modifie le nombre de lignes du vecteur */
        void resize(int _rows)
        {
            MatrixBase<_Scalar, _Rows, 1>::resize(_rows, 1);
        }

        /** Produit scalaire de *this et other */
        inline _Scalar dot(const Vector& other) const
        {
            _Scalar result=0;
            assert((*this).size() == other.size());
            for(int i =0; i < (*this).size();i++){
                result += (*this)(i) * other(i);
            }
            return result;
        }

        /** Retourne la norme euclidienne du vecteur */
        inline _Scalar norm() const
        {
            _Scalar result=0;
            for(int i =0; i < (*this).size();i++){
                result += (*this)(i) * (*this)(i);
            }
            return sqrt(result);
        }
    };
}
