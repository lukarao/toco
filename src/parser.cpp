#include "parser.h"

#include <iostream> // debug

int getPrecedence(Token token) {
    switch (token.type) {
        default:
            return 0;
    }
}

Parser::Parser(std::unique_ptr<Lexer> _lexer, std::unique_ptr<Builder> _builder) {
    lexer = std::move(_lexer);
    builder = std::move(_builder);
}

std::string Parser::parseTerm() {
    while (lexer->currentToken.type != TokenType::Eof) {
        switch (lexer->currentToken.type) {
            case TokenType::Identifier:
            {
                std::string name = lexer->currentToken.value;
                lexer->next();
                if (lexer->currentToken.type == TokenType::OpenParen) { // function call
                    lexer->next();
                    // TODO: parse multiple arguments
                    std::string argument = parseExpression(0);
                    lexer->next();
                    if (lexer->currentToken.type != TokenType::CloseParen) {
                        std::cerr << "Expected closing ) after arguments, got \"" << lexer->currentToken.value << "\" instead." << std::endl;
                        std::exit(1);
                    }
                    return "(call, " + name + ", " + argument + ")";
                } else {
                    // parse other expressions starting with an identifier
                }
            }
            case TokenType::Func:
            {
                lexer->next();
                // function name
                std::string name;
                if (lexer->currentToken.type == TokenType::Identifier) {
                    name = lexer->currentToken.value;
                    lexer->next();
                } else {
                    std::cerr << "Expected Identifier after Func, got \"" << lexer->currentToken.value << "\" instead." << std::endl;
                    std::exit(1);
                }
                // (parse parameters)
                // function body
                std::string body = parseExpression(0);
                return "(funcdef, " + name + ", " + body + ")";
            }
            case TokenType::OpenBrace:
            {
                lexer->next();
                std::string content = "(block, ";
                while (lexer->currentToken.type != TokenType::CloseBrace) { // not sure if i can just use while(True)
                    if (lexer->currentToken.type == TokenType::Eof) {
                        std::cerr << "Missing closing } in block." << std::endl;
                        std::exit(1);
                    }
                    while (lexer->currentToken.type == TokenType::End) {
                        lexer->next();
                    }
                    if (lexer->currentToken.type == TokenType::CloseBrace) {
                        break;
                    }
                    content += parseExpression(0) + ", ";
                    lexer->next();
                }
                return content + ")";
            }
            case TokenType::Import:
            {
                lexer->next();
                std::string content = "(import, ";
                while (lexer->currentToken.type != TokenType::End) {
                    content += lexer->currentToken.value;
                    lexer->next();
                }
                return content + ")";
            }
            case TokenType::String:
                return "(string, " + lexer->currentToken.value + ")";
            case TokenType::End:
                lexer->next();
                break;
        }
    }
}

std::string Parser::parseExpression(int precedence) {
    std::string left = parseTerm();
    if (lexer->nextToken.type != TokenType::End && lexer->nextToken.type != TokenType::Eof && lexer->nextToken.type != TokenType::CloseParen &&
        lexer->nextToken.type != TokenType::CloseBrace) {
        lexer->next();
        Token op = lexer->currentToken;
        while (precedence < getPrecedence(op)) {
            lexer->next();
            std::string right = parseExpression(getPrecedence(op));
            left = "(" + op.value + ", " + left + ", " + right + ")";
        }
    }
    return left;
}

void Parser::parse() {
    while (lexer->currentToken.type != TokenType::Eof) {
        while (lexer->currentToken.type == TokenType::End) {
            lexer->next();
        }
        std::cout << parseExpression(0) << std::endl;
        lexer->next();
    }
}