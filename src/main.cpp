#include "lexer.h"

#include <fstream>
#include <sstream>

#include <iostream> // debug

int main(int argc, char *argv[]) {
    if (argc == 1) {
        std::cerr << "error: missing input file" << std::endl;
    } else if (argc > 2) {
        std::cerr << "error: too many arguments" << std::endl;
    } else {
        std::ifstream file(argv[1]);
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();

        Lexer lexer(buffer.str());
        while (lexer.currentToken.type != TokenType::Eof) {
            std::cout << lexer.currentToken.value << " " << lexer.currentToken.type << std::endl;
            lexer.next();
        }
    }

    return 0;
}