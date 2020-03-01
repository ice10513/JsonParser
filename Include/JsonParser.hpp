#pragma once
#include <string>
#include <stack>
#include <optional>
#include <iostream>
#include <variant>
#include "JsonException.hpp"

namespace Json
{
class Parser
{
    using ValueType = std::variant<int, std::string>;
public:
    void parse(std::string p_content)
    {
        m_content = std::move(p_content);

        auto l_entry = getJosnEntry();
        if (!l_entry)  // TODO move this judge to method getJsonEntry
        {
            std::cout << "Not include invalid entry char\n";
            throw JsonMissingEntry();
        }

        switch (*l_entry)
        {
            case '[':
            {
                m_boundStack.push(*l_entry);
                break;
            }
            case '{':
            {
                m_boundStack.push(*l_entry);
                parseDict();
                break;
            }
            default:
            {
                throw JsonInvalidEntry();
            }
        }

        if (!m_boundStack.empty())
        {
            std::cout << "The [] or {} not matched" << std::endl;
            throw JsonMismatchedEndBrackets();
        }
    }

private:
    void parseDict()
    {
        bool l_hasNextPair = false;
        while (!isEof())
        {
            auto l_ch = getNextChar();   // TODO 这里的逻辑是否欠考虑？是否可以更平滑一些？
            if (l_ch == '}')
            {
                if (l_hasNextPair)
                {
                    std::cout << "There has a extra comma" << std::endl;
                    throw JsonExtraComma();
                }

                m_boundStack.pop();
                return;
            }
            
            if (l_ch != '"')
            {
                continue;
            }

            parseThePair();

            if (getLastChar() == '}')
            {
                m_boundStack.pop();
                return;
            }
            l_hasNextPair = true;
        }
    }

    void parseThePair()
    {
        std::string l_key = getKey();
        skipColon();
        std::string l_value = getValue();
        std::cout << l_key << ":" << l_value << std::endl;
    }

    std::string getKey()
    {
        std::string l_key;
        while (!isEof())
        {
            auto l_ch = getNextChar();
            if (l_ch == '"' && l_key.back() != '\\')
            {
                return l_key;
            }

            l_key += l_ch;
        }

        throw JsonMissingRightQuotes();
    }

    void skipColon()
    {
        char l_ch{};
        while (!isEof())
        {
            l_ch = getNextChar();
            if (l_ch == ':')
            {
                return;
            }
        }

        throw JsonMissingColon();
    }

    std::string getValue()
    {
        char l_ch{};
        bool l_hasDoubleQuotes = false;
    
        std::string l_value;
        while (!isEof())
        {
            l_ch = getNextChar();
            if (l_ch == ',' || l_ch == '}')
            {
                break;
            }

            l_value += l_ch;
        }

        return l_value;
    }

    std::optional<char> getJosnEntry()
    {
        while (!isEof())
        {
            auto l_ch = getNextChar();
            if (isBoundChar(l_ch))
            {
                return l_ch;
            }
        }

        return {};
    }

    char getNextChar()
    {
        return m_content[m_index++];
    }

    char getLastChar() const
    {
        return m_content[m_index - 1];
    }

    bool isEof() const
    {
        return m_index >= m_content.size();
    }

    bool isBoundChar(char p_ch) const
    {
        return p_ch == '[' 
            || p_ch == ']'
            || p_ch == '{'
            || p_ch == '}';
    }

    std::stack<char> m_boundStack;
    std::string m_content;
    size_t m_index = 0;
};
}