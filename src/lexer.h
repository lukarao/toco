#pragma once

#include <string>
#include <vector>

enum TokenType {
    Operator,
    OpenParen,
    CloseParen,
    OpenBrace,
    CloseBrace,
    End,
    String,
    Keyword,
    Identifier,
    Eof
};

struct Token {
    std::string value;
    TokenType type;
    int start;
    int end;
};

class Lexer {
    std::string text;
    int pos = 0;
    Token getToken();

    public:
        Token currentToken;
        Token nextToken;
        void next();
        Lexer(std::string _text);
};