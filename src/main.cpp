#include "builder.h"
#include "lexer.h"
#include "parser.h"

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
    
        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(buffer.str());
        std::unique_ptr<Builder> builder;
        Parser parser(std::move(lexer), std::move(builder));
        parser.parse();
    }

    return 0;
}