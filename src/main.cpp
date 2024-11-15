#include "lex.h"

#include <fstream>
#include <sstream>

#include <iostream> // debug

int main(int argc, char *argv[]) {
    std::ifstream file("helloworld.tc");
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    std::vector<Token> tokens = Lex(buffer.str());

    return 0;
}