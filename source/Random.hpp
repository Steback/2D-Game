#ifndef RANDOM_HPP
#define RANDOM_HPP


#include <random>

class Random {
    public:
        static void init() {
            s_randomEngine.seed(std::random_device()());
        }

        static float Float() {
            return static_cast<float>(s_distribution(s_randomEngine)) / static_cast<float>(std::numeric_limits<uint32_t>::max());
        }

    private:
        static std::mt19937 s_randomEngine;
        static std::uniform_int_distribution<std::mt19937::result_type> s_distribution;
};


#endif
