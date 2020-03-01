#pragma once
#include <exception>

namespace Json
{
struct JsonParserError : std::invalid_argument
{
    JsonParserError() : std::invalid_argument("")
    {}

    using std::invalid_argument::invalid_argument;
};

#define ADD_EXCEPTION(NAME) struct Json##NAME : JsonParserError\
{\
    using JsonParserError::JsonParserError;\
};

ADD_EXCEPTION(MissingEntry);
ADD_EXCEPTION(InvalidEntry);

ADD_EXCEPTION(MismatchedEndBrackets);
ADD_EXCEPTION(MismatchedCurlyBrackets);
ADD_EXCEPTION(MismatchedSquareBrackets);

ADD_EXCEPTION(ExtraComma);
ADD_EXCEPTION(MissingRightQuotes);
ADD_EXCEPTION(MissingColon);

}