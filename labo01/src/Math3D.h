#pragma once

/**
 * @file Math3D.h
 *
 * @brief Fonctions pour l'intinialisation et la manipulation de matrices de
 * rotation, de matrices de transformations en coordonnées homogènes et de
 * vecteurs 3D.
 *
 * Nom:Sébastien Charbonneau
 * Code permanent : CHAS01049805
 * Email :sebastien.charbonneau.1@ens.etsmtl.ca
 *
 */

#include "Matrix.h"
#include "Vector.h"
#include "Operators.h"

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <math.h>

namespace gti320
{

    // Deux types de vecteurs 3D considérés ici
    typedef Vector<double, 3> Vector3d;
    typedef Vector<float, 3> Vector3f;
    typedef Matrix<double, 3, Dynamic, ColumnStorage> Points3d;

    // Dans le cadre de ce projet, nous considérons seulement deux
    // cas :
    //
    //  - les rotations
    //  - les translations
    //
    // Deux types de matrices en coordonnées homogèes :
    typedef Matrix<double, 4, 4, ColumnStorage> Matrix4d;
    typedef Matrix<float, 4, 4, ColumnStorage> Matrix4f;
    //
    // Deux types de matrices pour les rotations
    typedef Matrix<double, 3, 3, ColumnStorage> Matrix3d;
    typedef Matrix<float, 3, 3, ColumnStorage> Matrix3f;

    /** Initialise et retourne la matrice identité */
    template <>
    inline void Matrix4d::setIdentity()
    {
        (*this).setZero();
        (*this)(0,0)=1;
        (*this)(1,1)=1;
        (*this)(2,2)=1;
        (*this)(3, 3) = 1;

    }

    /**
     * Calcul de la matrice inverse SPÉCIALISÉ pour le cas
     * d'une matrice de rotation.
     */
    template <>
    inline Matrix3d Matrix3d::inverse() const
    {

        Matrix3d Temp;

        for(int i=0; i < 3; i++){
            for(int j=0; j < 3; j++){
                Temp(j,i) = (*this)(i , j);
            }
        }

        return Temp;
    }

    /**
     * Multiplication d'une matrice 4x4 avec un vecteur 3D où la matrice
     * représente une transformation en coordonnées homogène.
     */
    template <typename _Scalar>
    Vector<_Scalar, 3> operator*(const Matrix<_Scalar, 4, 4, ColumnStorage>& A, const Vector<_Scalar, 3>& v)
    {

        Vector<_Scalar, 3> res(3);
        Matrix<_Scalar, 3, 3, ColumnStorage> Arot(3,3);
        Arot = A.block(0, 0, 3, 3);
        res = Arot * v;
        for (int i = 0; i < 3;i++) {
            res(i) += A(i, 3);
        }
        return res;
    }
    //Nouveau
    /**
     * combinaison de deux matrice 4x4 
     * représente une transformation en coordonnées homogène.
     */
    template <typename _Scalar>
    Matrix<_Scalar, 4, 4, ColumnStorage> combineMatrix(const Matrix<_Scalar, 4, 4, ColumnStorage>& A, const Matrix<_Scalar, 4, 4, ColumnStorage>& B)
    {
        //Les matrices de rotations se combinent en les multipliant entre elles. Attention à l'ordre dans lequel vous les multipliez ! Sinon…
        Matrix<_Scalar, 3, 3, ColumnStorage> RotationA;
        Matrix<_Scalar, 3, 3, ColumnStorage> RotationB;
        Matrix<_Scalar, 4, 4, ColumnStorage> TCHResult;
        TCHResult.setZero();
        for (int i = 0; i < 3;i++) {
            for (int j = 0; j < 3;j++) {
                RotationA(i, j) = A(i, j);
                RotationB(i, j) = B(i, j);
            }
        }
        TCHResult.block(0, 0, 3, 3) = RotationA * RotationB;

        TCHResult(0, 3) = A(0, 3) + B(0, 3);
        TCHResult(1, 3) = A(1, 3) + B(1, 3);
        TCHResult(2, 3) = A(2, 3) + B(2, 3);

        return TCHResult;
    }

    /**
     * Créer et retourne une matrice de rotation définie par les angles
     * d'Euler XYZ exprimés en radians.
     *
     * La matrice doit correspondre au produit : Rz * Ry * Rx.
     */
    template <typename _Scalar>
    static Matrix<_Scalar, 3, 3> makeRotation(_Scalar x, _Scalar y, _Scalar z)
    {
        /** TODO: Implémenter. */
        _Scalar cosRx = cos(x);
        _Scalar sinRx = sin(x);
        _Scalar cosRy = cos(y);
        _Scalar sinRy = sin(y);
        _Scalar cosRz = cos(z);
        _Scalar sinRz = sin(z);
        Matrix<_Scalar, 3, 3> Rz(3,3);
        Rz.setZero();
        Rz(0,0)=cosRz;
        Rz(0,1)=-sinRz;
        Rz(1,0)=sinRz;
        Rz(1,1)=cosRz;
        Rz(2,2)=1;
        Matrix<_Scalar, 3, 3> Ry(3,3);
        Ry.setZero();
        Ry(0,0)=cosRy;
        Ry(0,2)=sinRy;
        Ry(1,1)=1;
        Ry(2,0)=-sinRy;
        Ry(2,2)=cosRy;
        Matrix<_Scalar, 3, 3> Rx(3,3);
        Rx.setZero();
        Rx(0,0)=1;
        Rx(1,1)=cosRx;
        Rx(1,2)=-sinRx;
        Rx(2,1)=sinRx;
        Rx(2,2)=cosRx;

        // souce: http://web.mit.edu/2.05/www/Handout/HO2.PDF
        // eulerXYZ(0,0) = round(cosRx*cosRy * 1000.0)/1000.0;
        // eulerXYZ(0,1) = round(cosRx*sinRy*sinRz-sinRx*cosRz * 1000.0)/1000.0;
        // eulerXYZ(0,2) = round(cosRx*sinRy*cosRz+sinRx*sinRz * 1000.0)/1000.0;
        // eulerXYZ(1,0) = round(sinRx*cosRy* 1000.0)/1000.0;
        // eulerXYZ(1,1) = round(sinRx*sinRy*sinRz+cosRx*cosRz * 1000.0)/1000.0;
        // eulerXYZ(1,2) = round(sinRx*sinRy*cosRz-cosRx*sinRz * 1000.0)/1000.0;
        // eulerXYZ(2,0) = round(-sinRy * 1000.0)/1000.0;
        // eulerXYZ(2,1) = round(-cosRy*sinRz * 1000.0)/1000.0;
        // eulerXYZ(2,2) = round(cosRy*cosRz * 1000.0)/1000.0;
        Matrix<_Scalar, 3, 3> eulerZYX(3,3);
        eulerZYX.setZero();
        eulerZYX = Rz * Ry * Rx;
        //for (int i = 0; i < 3;i++) {
        //    for (int j = 0;j < 3;j++) {
        //        eulerZYX(i, j) = round(eulerZYX(i, j) * 1000.0) / 1000.0;
        //    }
        //}
        return eulerZYX;
    }

    /**
     * Calcul de la matrice inverse SPÉCIALISÉ pour le cas
     * d'une matrice de transformation en coordonnées homogènes.
     */
    template <>
    inline Matrix4d Matrix4d::inverse() const
    {   
        Matrix3d mRotation;
        Vector3d vTranslationEchelle;
        //Vector3d u;
        //Vector3d v;
        //Vector3d w;

        Matrix4d res;
        res.setZero();

        Matrix4d mTranslation;
        mTranslation.setIdentity();

        // Copie de matrice Rotation
        mRotation = (*this).block(0, 0, 3, 3);
        mRotation = mRotation.inverse();


        // Copie du vecteur Translation Echelle originale
        for(int i=0; i<3;i++){
            vTranslationEchelle(i) = -1*(*this)(i,3);
        }
        mTranslation(0, 3) = vTranslationEchelle(0);
        mTranslation(1, 3) = vTranslationEchelle(1);
        mTranslation(2, 3) = vTranslationEchelle(2);

        // Garder bit direction ou position
        //res(3,3)=(*this)(3,3);
        res(3, 3) = 1.0;
        // Copie de la Matrice rotation transpose dans res
        for(int i =0; i<3;i++){
            for(int j=0;j<3;j++){
                res(i,j) = mRotation(i,j);
            }
        }

        // faite le dot product 
 /*     res(0,3) = u.dot(vTranslationEchelle);
        res(1,3) = v.dot(vTranslationEchelle);
        res(2,3) = w.dot(vTranslationEchelle);*/
        res = res * mTranslation;
        return res;
    }

    //NOUVEAU
     /**
     * retourne la matrice avec la translation changé
     */
    inline Matrix4d Matrix4d::changeTranslation(double x, double y, double z ) const
    {
        //J'aurais prefere pouvoir assigner les valeurs mais je n'ai pas trouve comment
        //(*this)(0, 3) = x;
        //(*this)(0, 3) = x;
        //(*this)(0, 3) = x;
        Matrix4d temp = (*this);
        temp(0, 3) = x;
        temp(1, 3) = y;
        temp(2, 3) = z;

        return temp;
    }


    //NOUVEAU
    /** permet d'assigner les éléments d'une collonne pour une matrice */
    inline Points3d Points3d::assignPoint3d(int colonne, double x, double y, double z) const
    {

        Points3d temp = (*this);
        temp(0, colonne) = x;
        temp(1, colonne) = y;
        temp(2, colonne) = z;
        return temp;
    }

}
