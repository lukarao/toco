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
    
        Lexer lexer(buffer.str());
        Builder builder;
        Parser parser(&lexer, &builder);
        parser.parse();
    }

    return 0;
}