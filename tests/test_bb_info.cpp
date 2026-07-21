/**
 * Copyright 2026 Stephan Lipp
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>

#include <code_inspector/bb_info.h>
#include <code_inspector/types.h>

using namespace testing;
using namespace code_inspector;

TEST(BBInfoTestSuite, ConstructorAndGettersTest) {
    // Arrange & act
    BBId id = 42;
    Lines lineNumbers = {1, 2, 3};
    LineRange lineRange = {1, 3};
    BBInfo bbInfo(id, lineNumbers, lineRange);

    // Assert
    ASSERT_EQ(bbInfo.getId(), id);
    ASSERT_EQ(bbInfo.getLineNumbers(), lineNumbers);
    ASSERT_EQ(bbInfo.getLineRange(), lineRange);
}

TEST(BBInfoTestSuite, EqualityOperatorTest) {
    // Arrange & act
    BBId id1 = 42;
    Lines lineNumbers1 = {1, 2, 3};
    LineRange lineRange1 = {1, 3};
    BBInfo bbInfo1(id1, lineNumbers1, lineRange1);

    BBId id2 = 42;
    Lines lineNumbers2 = {1, 2, 3};
    LineRange lineRange2 = {1, 3};
    BBInfo bbInfo2(id2, lineNumbers2, lineRange2);

    // Assert
    ASSERT_EQ(bbInfo1, bbInfo2);
}

TEST(BBInfoTestSuite, InequalityOperatorTest) {
    // Arrange & act
    BBId id1 = 42;
    Lines lineNumbers1 = {1, 2, 3};
    LineRange lineRange1 = {1, 3};
    BBInfo bbInfo1(id1, lineNumbers1, lineRange1);

    BBId id2 = 43;
    Lines lineNumbers2 = {1, 2, 3};
    LineRange lineRange2 = {1, 3};
    BBInfo bbInfo2(id2, lineNumbers2, lineRange2);

    // Assert
    ASSERT_NE(bbInfo1, bbInfo2);
}

TEST(BBInfoTestSuite, LessThanOperatorTest) {
    // Arrange & act
    BBId id1 = 42;
    Lines lineNumbers1 = {1, 2, 3};
    LineRange lineRange1 = {1, 3};
    BBInfo bbInfo1(id1, lineNumbers1, lineRange1);

    BBId id2 = 43;
    Lines lineNumbers2 = {1, 2, 3};
    LineRange lineRange2 = {1, 3};
    BBInfo bbInfo2(id2, lineNumbers2, lineRange2);

    // Assert
    ASSERT_LT(bbInfo1, bbInfo2);
}