#include <gtest/gtest.h>
#include "TypeManager.hpp"

// NO necesitas 'class TypeManagerTest : public ::testing::Test' 
// ni Setup() porque no hay objetos que instanciar.

TEST(TypeManagerTest, MaxTypeTest) {
    // Usamos TypeManager:: (cuatro puntos) en lugar de tm.
    EXPECT_EQ(TypeManager::maxType(0, 1), 1);
    EXPECT_EQ(TypeManager::maxType(5, 2), 5);
}

TEST(TypeManagerTest, MinTypeTest) {
    EXPECT_EQ(TypeManager::minType(0, 1), 0);
    EXPECT_EQ(TypeManager::minType(5, 2), 2);
}

TEST(TypeManagerTest, AmplifyTest) {
    // Argumentos dummy para dir (0)
    EXPECT_EQ(TypeManager::amplify(0, 5, 5), 5); 
    EXPECT_EQ(TypeManager::amplify(0, 1, 2), 2);
}

TEST(TypeManagerTest, ReduceTest) {
    EXPECT_EQ(TypeManager::reduce(0, 5, 5), 5);
    EXPECT_EQ(TypeManager::reduce(0, 1, 0), 0);
}