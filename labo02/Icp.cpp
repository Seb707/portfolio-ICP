#include "Icp.h"

#include "Matrix.h"
#include "Vector.h"
#include "Operators.h"
#include "SVD.h"

using namespace gti320;

/**
 * Calcul du déterminant 3x3
 * TODO
 */
double gti320::determinant(const Matrix3d& M)
{
    double result = M(0, 0)*((M(1, 1) * M(2, 2)) - (M(1, 2) * M(2, 1))) - (M(0, 1)*((M(1,0)*M(2,2))-(M(1,2)*M(2,0)))) + (M(0,2)*((M(1,0)*M(2,1))-(M(1,1)*M(2,0))));
    return result;
}

/**
 * Calcul de l'erreur entre deux nuages de points
 * somme des distances entre les points des nuages de points A et B
 */
double Icp::error(const Points3d& A, const Points3d& B)
{
    assert(A.cols() == B.cols());
    double error = 0;
    double deltaX = 0;
    double deltaY = 0;
    double deltaZ = 0;
    for (int i = 0; i < A.cols(); i++) {
        deltaX = abs(A(0, i) - B(0, i));
        deltaY = abs(A(1, i) - B(1, i));
        deltaZ = abs(A(2, i) - B(2, i));
        error += sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
    }
    return error;
}


/**
 * Index du point de A qui minimise la distance à p
 * TODO
 */
int Icp::nearestNeighbor(const Vector3d& p, const Points3d& A)
{
    assert(A.cols() >= 1);
    double deltaX = abs(A(0, 0) - p(0));
    double deltaY = abs(A(1, 0) - p(1));
    double deltaZ = abs(A(2, 0) - p(2));
    double currentNearestNeighbor = sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
    double tempNearestNeighbor = 0;
    int positionNearestNeighbor = 0;
    for (int i = 1; i < A.cols(); i++) {
        deltaX = abs(A(0, i) - p(0));
        deltaY = abs(A(1, i) - p(1));
        deltaZ = abs(A(2, i) - p(2));
        tempNearestNeighbor = sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
        if (tempNearestNeighbor < currentNearestNeighbor) {
            currentNearestNeighbor = tempNearestNeighbor;
            positionNearestNeighbor = i;
        }
    }

    return positionNearestNeighbor;
}

/**
 * Meilleure transformation rigide pour amener les points de B sur ceux A
 * TODO
 */
Matrix4d Icp::bestFitTransform(const Points3d& A, const Points3d& B)
{
    Matrix4d T;
    T.setIdentity();

    // Calculer le centre géométrique des nuages de points
    double sumAX=0;
    double sumAY=0;
    double sumAZ=0;
    double sumBX=0;
    double sumBY=0;
    double sumBZ=0;
    for (int i = 0;i < A.cols();i++) {
        sumAX += A(0, i);
        sumAY += A(1, i);
        sumAZ += A(2, i);
    }
    for (int i = 0;i < B.cols();i++) {
        sumBX += B(0, i);
        sumBY += B(1, i);
        sumBZ += B(2, i);
    }

    // Calculer les matrices pour obtenir X et Y
    Points3d X(3,A.cols());
    Points3d Y(3,B.cols());

    Vector3d CentreA;
    CentreA(0) = sumAX / A.cols();
    CentreA(1) = sumAY / A.cols();
    CentreA(2) = sumAZ / A.cols();

    Vector3d CentreB;
    CentreB(0) = sumBX / B.cols();
    CentreB(1) = sumBY / B.cols();
    CentreB(2) = sumBZ / B.cols();
    for (int i = 0;i < A.cols();i++) {

        X = X.assignPoint3d(i, A(0, i) - CentreA(0), A(1, i) - CentreA(1), A(2, i) - CentreA(2));
        //AA(0, i) = A(0, i)- CentreA(0);
        //AA(1, i) = A(1, i) - CentreA(1);
        //AA(2, i) = A(2, i) - CentreA(2);
    }
    for (int i = 0;i < B.cols();i++) {
        Y = Y.assignPoint3d(i, B(0, i) - CentreB(0), B(1, i) - CentreB(1), B(2, i) - CentreB(2));
        //BB(0, i) = B(0, i) - CentreB(0);
        //BB(1, i) = B(1, i) - CentreB(1);
        //BB(2, i) = B(2, i) - CentreB(2);
    }


    Matrix3d result = X * Y.transpose<double, Dynamic, 3, ColumnStorage>();
    SVD<double, 3, 3, ColumnStorage> svd(result);
    svd.decompose();
    Matrix3d U = svd.getU();
    Matrix3d V = svd.getV();

    Matrix3d R = V * U.transpose<double,3,3,ColumnStorage>();

    double detR = determinant(R);
    if (detR < 0) {
        V(0, 3) = -V(0, 3);
        V(1, 3) = -V(1, 3);
        V(2, 3) = -V(2, 3);
        R = V * U.transpose<double, 3, 3, ColumnStorage>();
    }
    gti320::Matrix4d BestRotationTranslation;
    BestRotationTranslation.setIdentity();
    BestRotationTranslation.block(0, 0, 3, 3) = R;
    Vector3d t = CentreB - (R * CentreA);

    BestRotationTranslation = BestRotationTranslation.changeTranslation(t(0), t(1), t(2));

    return BestRotationTranslation;
}
