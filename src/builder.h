#pragma once

#include <vector>

class BlockRecord {}; // idk what else to name this

class Block : public BlockRecord {};

class Record : public BlockRecord {};

class Builder {
    std::vector<BlockRecord> stream;
    public:
        Builder();
};