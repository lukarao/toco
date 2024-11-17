#include "lexer.h"

#include <iostream> // debug

Lexer::Lexer(std::string _text) {
    text = _text;
    currentToken = getToken();
    pos++;
    nextToken = getToken();
}

void Lexer::next() {
    currentToken = nextToken;
    pos++;
    nextToken = getToken();
}

Token Lexer::getToken() {
    while (pos != text.length()) {
        switch (text[pos]) {
            case '.': return {std::string(1, text[pos]), TokenType::Dot, pos, pos};
            case '(': return {"(", TokenType::OpenParen, pos, pos};
            case ')': return {")", TokenType::CloseParen, pos, pos};
            case '{': return {"{", TokenType::OpenBrace, pos, pos};
            case '}': return {"}", TokenType::CloseBrace, pos, pos};
            case ';':
            case '\n':
                return {"", TokenType::End, pos, pos};
            case '\'':
            case '"': {
                std::string value;
                int start = pos;
                pos++;
                while (pos != text.length() && text[pos] != text[start]) {
                    value += text[pos];
                    pos++;
                }
                return {value, TokenType::String, start, pos};
            }
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
            case 'G':
            case 'H':
            case 'I':
            case 'J':
            case 'K':
            case 'L':
            case 'M':
            case 'N':
            case 'O':
            case 'P':
            case 'Q':
            case 'R':
            case 'S':
            case 'T':
            case 'U':
            case 'V':
            case 'W':
            case 'X':
            case 'Y':
            case 'Z':
            case '_': {
                std::string value;
                int start = pos;
                while (pos != text.length() && ((text[pos] >= 'a' && text[pos] <= 'z') || (text[pos] >= 'A' && text[pos] <= 'Z') || (text[pos] >= '0' && text[pos] <= '9') || text[pos] == '_')) {
                    value += text[pos];
                    pos++;
                }
                pos--; // there should be a better way to fix this
                if (value == "func") {
                    return {"func", TokenType::Func, start, pos};
                } else if (value == "import") {
                    return {"import", TokenType::Import, start, pos};
                } else {
                    return {value, TokenType::Identifier, start, pos};
                }
            }
            default:
                pos++;
                break;
        }
    }
    return {"", TokenType::Eof, pos, pos};
}