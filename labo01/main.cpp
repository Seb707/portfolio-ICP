/**
 * @file main.cpp
 *
 * @brief Point d'entrée pour exécuter les tests de la librairie d'algèbre linéaire.
 *
 * Nom:
 * Code permanent :
 * Email :
 *
 */

#include <gtest/gtest.h>

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    //::testing::GTEST_FLAG(filter) = "TestsTP1_Etudiant.Supplementaire1*";
    //::testing::GTEST_FLAG(filter) = "TestsTP1.Math3D*";
    const int ret = RUN_ALL_TESTS();
    return ret;
}
