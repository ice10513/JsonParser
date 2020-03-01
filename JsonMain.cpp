#include <iostream>
#include "JsonParser.hpp"

int main()
{
    Josn::Parser l_parser(R"(
        {
	        "abc": "abc"
        }
    )");

    l_parser.parse();
    return 0;
}