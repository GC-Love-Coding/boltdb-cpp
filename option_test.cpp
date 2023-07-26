#include "option.h"

#include <gtest/gtest.h>

TEST(Option, timeout) {
  boltdb::Option option;
  option.timeout(10);

  EXPECT_EQ(10, option.timeout());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
