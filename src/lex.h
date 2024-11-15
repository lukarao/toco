#pragma once

#include <string>
#include <vector>

enum TokenType {
    Import,
    Func,
    Identifier,
    Dot,
    OpenParen,
    CloseParen,
    OpenBrace,
    CloseBrace,
    String
};

struct Token {
    TokenType type;
    int start;
    int end;
    int line;
};

std::vector<Token> Lex(std::string text);