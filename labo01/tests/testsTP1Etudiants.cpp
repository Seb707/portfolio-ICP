/**
 * @file TestsEtudiants.cpp
 *
 * @brief Tests unitaires faits par l'étudiant pour la librairie d'algèbre linéaire.
 *
 * Nom:
 * Code permanent :
 * Email :
 *
 */

#include "../src/Matrix.h"
#include "../src/Vector.h"
#include "../src/Math3D.h"
#include "../src/Operators.h"

#include <gtest/gtest.h>
#include <chrono>

using namespace gti320;

// ===========================================================================================================
// ----- Tests supplémentaires évalués, à compléter! ---------------------------------------------------------
// ===========================================================================================================
#pragma region // Tests évalués

/**
 * TODO:
 * Écrivez trois tests supplémentaires pertinents, complets et bien commentés.
 * Seuls les trois tests de cette section seront évalués.
 *
 * Vous pouvez changer leurs noms, mais pas celui de la suite de tests.
 * Les tests évalués doivent être dans "TestsTP1_Evalue".
 *
 * Attention :
 * Le non-respect de ces consignes entraînera une note de zéro pour les tests.
 * 
 * Documentation :
 * https://google.github.io/googletest/primer.html
 */

TEST(TestsTP1_Evalue, TestEvalue1)
{
    // Vecteur à taille dynamique
    Vector<double> v(5);
    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 4.0;
    v(3) = 8.0;
    v(4) = 16.0;
 
    EXPECT_DOUBLE_EQ(v(0), 1.0);
    EXPECT_DOUBLE_EQ(v(1), 2.0);
    EXPECT_DOUBLE_EQ(v(2), 4.0);
    EXPECT_DOUBLE_EQ(v(3), 8.0);
    EXPECT_DOUBLE_EQ(v(4), 16.0);

    // Test : multiplication par une matrice à taille dynamique avec stockage par collone.
    Matrix<double, Dynamic, Dynamic, ColumnStorage> M(5, 5);
    M.setIdentity();
    M = 2.0 * M;

    EXPECT_DOUBLE_EQ(M(0, 0), 2);
    EXPECT_DOUBLE_EQ(M(1, 1), 2);
    EXPECT_DOUBLE_EQ(M(2, 2), 2);
    EXPECT_DOUBLE_EQ(M(3, 3), 2);
    EXPECT_DOUBLE_EQ(M(4, 4), 2);

    Vector<double> b2 = M * v;
    EXPECT_DOUBLE_EQ(b2(0), 2.0);  
    EXPECT_DOUBLE_EQ(b2(1), 4.0);
    EXPECT_DOUBLE_EQ(b2(2), 8.0);
    EXPECT_DOUBLE_EQ(b2(3), 16.0);
    EXPECT_DOUBLE_EQ(b2(4), 32.0);

}

TEST(TestsTP1_Evalue, TestEvalue2)
{

        // Création d'un matrice à stockage par lignes
        Matrix<double, Dynamic, Dynamic, RowStorage> A(5, 5);
        A(0, 0) = 0.8147;
        A(0, 1) = 0.0975;
        A(0, 2) = 0.1576;
        A(0, 3) = 0.1419;
        A(0, 4) = 0.6557;
        A(1, 0) = 0.9058;
        A(1, 1) = 0.2785;
        A(1, 2) = 0.9706;
        A(1, 3) = 0.4218;
        A(1, 4) = 0.0357;
        A(2, 0) = 0.1270;
        A(2, 1) = 0.5469;
        A(2, 2) = 0.9572;
        A(2, 3) = 0.9157;
        A(2, 4) = 0.8491;
        A(3, 0) = 0.9134;
        A(3, 1) = 0.9575;
        A(3, 2) = 0.4854;
        A(3, 3) = 0.7922;
        A(3, 4) = 0.9340;
        A(4, 0) = 0.6324;
        A(4, 1) = 0.9649;
        A(4, 2) = 0.8003;
        A(4, 3) = 0.9595;
        A(4, 4) = 0.6787;
        
        // Test : transposée (le résultat est une matrice à stockage par
        //        colonnes)
        Matrix<double, Dynamic, Dynamic, ColumnStorage> B = A.transpose();

        // Test : addition  matrice(ligne) + matrice(colonne)
        // Note : teste seulement la première et la dernière colonne
        const auto A_plus_B = A + B;
        EXPECT_DOUBLE_EQ(A_plus_B(0, 0), A(0, 0) + B(0, 0));
        EXPECT_DOUBLE_EQ(A_plus_B(0, 4), A(0, 4) + B(0, 4));
        EXPECT_DOUBLE_EQ(A_plus_B(1, 0), A(1, 0) + B(1, 0));
        EXPECT_DOUBLE_EQ(A_plus_B(1, 4), A(1, 4) + B(1, 4));
        EXPECT_DOUBLE_EQ(A_plus_B(2, 0), A(2, 0) + B(2, 0));
        EXPECT_DOUBLE_EQ(A_plus_B(2, 4), A(2, 4) + B(2, 4));
        EXPECT_DOUBLE_EQ(A_plus_B(3, 0), A(3, 0) + B(3, 0));
        EXPECT_DOUBLE_EQ(A_plus_B(3, 4), A(3, 4) + B(3, 4));
        EXPECT_DOUBLE_EQ(A_plus_B(4, 0), A(4, 0) + B(4, 0));
        EXPECT_DOUBLE_EQ(A_plus_B(4, 4), A(4, 4) + B(4, 4));
}

TEST(TestsTP1_Evalue, TestEvalue3)
{

    // Test : matrice identité 4x4
    Matrix4d M;

    Matrix<double, Dynamic, Dynamic, ColumnStorage> ColM(3, 3);
    ColM.setZero();

    ColM.setIdentity();

    M.block(0, 0, 3, 3) = ColM;

    EXPECT_DOUBLE_EQ(M(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(M(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(M(0, 2), 0.0);
    EXPECT_DOUBLE_EQ(M(1, 1), 1.0);
    EXPECT_DOUBLE_EQ(M(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(M(1, 2), 0.0);
    EXPECT_DOUBLE_EQ(M(2, 0), 0.0);
    EXPECT_DOUBLE_EQ(M(2, 1), 0.0);
    EXPECT_DOUBLE_EQ(M(2, 2), 1.0);


}

#pragma endregion // Tests évalués

// ===========================================================================================================
// ----- Tests supplémentaires (Facultatif) -----------------------------------------------------------------
// ===========================================================================================================
#pragma region // Tests supplémentaires

/**
 * TODO: (Facultatif)
 * Vous pouvez utiliser cette section pour créer des tests supplémentaires.
 * Aucun de ces tests ne seront évalués.
 *
 * Vous pouvez changer leurs noms, mais pas celui de la suite de tests.
 * Les tests supplémentaires doivent être dans "TestLabo1_Etudiant".
 * 
 * Documentation :
 * https://google.github.io/googletest/primer.html
 */

TEST(TestsTP1_Etudiant, Supplementaire1)
{

    //Points3d listePoints;
    //listePoints(0, 0) = 1;
    //listePoints(0, 0) = 0;
    //listePoints(0, 0) = 0;

    //listePoints(0, 0) = 0;
    //listePoints(0, 0) = 1;
    //listePoints(0, 0) = 0;

    //listePoints(0, 0) = 0;
    //listePoints(0, 0) = 0;
    //listePoints(0, 0) = 1;

    //gti320::Vector3d result;
    //result(0) = 0;
    //result(1) = 0;
    //result(2) = 0;

    //int position = nearestNeighbor(result, listePoints);

    //EXPECT_DOUBLE_EQ(position, 0);

}

#pragma endregion // Tests Supplémentaires
