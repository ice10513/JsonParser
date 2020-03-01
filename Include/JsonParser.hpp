#pragma once
#include <string>
#include <stack>
#include <optional>
#include <iostream>
#include <variant>

namespace Josn
{
class Parser
{
    using ValueType = std::variant<int, std::string>;
public:
    bool parse(std::string p_content)
    {
        m_content = std::move(p_content);

        auto l_entry = getJosnEntry();
        if (!l_entry)
        {
            std::cout << "Not include invalid entry char\n";
            return false;
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
                return parseDict();
                break;
            }
            default:
            {
                std::cout << "Not a valid entry with char: " << *l_entry << std::endl;
                return false;
            }
        }
    }

private:
    bool parseDict()
    {
        bool l_hasNextPair = false;
        while (!isEof())
        {
            auto l_ch = getNextChar();
            if (l_ch == '}')
            {
                if (l_hasNextPair)
                {
                    std::cout << "There has a extra comma" << std::endl;
                    return false;
                }

                return true;
            }
            
            if (l_ch != '"')
            {
                continue;
            }

            parseThePair();

            if (getLastChar() == '}')
            {
                l_hasNextPair = false;
                break;
            }
            l_hasNextPair = true;
        }

        return true;
    }


    bool parseThePair()
    {
        std::string l_key = getKey();
        skipColon();
        std::string l_value = getValue();
        std::cout << l_key << ":" << l_value << std::endl;
    }

    std::string getKey()
    {
        std::string l_key;
        char l_ch{};
        while (!isEof())
        {
            l_ch = getNextChar();
    
            //TODO 暂时跳过转义字符
            if (l_ch == '"')
            {
                break;
            }
            else
            {
                l_key += l_ch;
            }
        }

        if (l_ch != '"')
        {
            //TODO 异常处理
        }

        return l_key;
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

        //TODO 找不到冒号时，异常处理
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