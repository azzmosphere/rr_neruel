#ifndef LAYER_HPP
#define LAYER_HPP

#include "Logger.hpp"

#define NODE_ARY_SZ 8

#define NN_INITIAL_WEIGHT 0.5


class Layer {

    static inline long random(long howbig)
    {
        if (howbig == 0) {
            return 0;
        }
        return arc4random() % howbig;
    }

    public:

        void initialize(size_t, size_t);

        float _nodes[NODE_ARY_SZ];
        float _weights[NODE_ARY_SZ][NODE_ARY_SZ];
        float _change_weights[NODE_ARY_SZ][NODE_ARY_SZ];
        float _delta[NODE_ARY_SZ];

        size_t _size = 0;
};

#endif