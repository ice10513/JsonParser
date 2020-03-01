#include <iostream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "JsonParser.hpp"

namespace Josn
{
using namespace ::testing;
using namespace std::literals::string_literals;

class JsonParserTestSuite : public Test
{
public:

protected:
    Parser m_sut;
};

class BasicDictJsonParserTestSuite : public JsonParserTestSuite
{};

TEST_F(BasicDictJsonParserTestSuite, parseWithEmptyDict_shouldSucceed)
{
    auto l_content = R"(
        {}
    )"s;

    ASSERT_TRUE(m_sut.parse(l_content));
}

TEST(test, test1)
{
    std::cout << R"("key\"":"value")" << std::endl;
}
}
