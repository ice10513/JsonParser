#include <iostream>
#include <string_view>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "JsonParser.hpp"

namespace Json
{
using namespace ::testing;
using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;

class JsonParserTestSuite : public Test
{
public:

protected:
    Parser m_sut;
};

class BasicDictJsonParserTestSuite : public JsonParserTestSuite
{};

struct BasicDictParam
{
    std::string_view content;
};

class BasicDictJsonParserSucceedParameterTestSuite : public BasicDictJsonParserTestSuite, public WithParamInterface<BasicDictParam>
{};

TEST_P(BasicDictJsonParserSucceedParameterTestSuite, shouldOk)
{
    ASSERT_NO_THROW(m_sut.parse(GetParam().content.data()));
}

const std::vector<BasicDictParam> g_succeedDictParam = {
    {
        .content = R"(
            {}
        )"sv
    },

    {
        .content = R"(
            {"key":"value"}
        )"sv
    },

    {
        .content = R"(
            {
                "key1":"value1",
                "key2":"value2"
            }
        )"sv
    },

    {
        .content = R"(
            {
                "key1":"value1",
                "key2":null,
                "key2":234,
                "key2":3.1415
            }
        )"sv
    }
};

INSTANTIATE_TEST_SUITE_P(
    Succeed,
    BasicDictJsonParserSucceedParameterTestSuite,
    ValuesIn(g_succeedDictParam)
);

}
