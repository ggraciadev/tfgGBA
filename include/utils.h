#ifndef BF_UTILS_H
#define BF_UTILS_H

#include <bn_fixed_point.h>

class Utils {
public:
    static int Min(const int x, const int y) {
        if(x < y) {
            return x;
        }
        else {
            return y;
        }
    }

    static int Max(const int x, const int y) {
        if(x > y) {
            return x;
        }
        else {
            return y;
        }
    }

    static float Min(const float x, const float y) {
        if(x < y) {
            return x;
        }
        else {
            return y;
        }
    }

    static float Max(const float x, const float y) {
        if(x > y) {
            return x;
        }
        else {
            return y;
        }
    }

    static bn::fixed Min(const bn::fixed x, const bn::fixed y) {
        if(x < y) {
            return x;
        }
        else {
            return y;
        }
    }

    static bn::fixed Max(const bn::fixed x, const bn::fixed y) {
        if(x > y) {
            return x;
        }
        else {
            return y;
        }
    }

    static int Clamp(const int x, const int min, const int max) {
        if(x < min) {
            return min;
        }
        else if(x > max) {
            return max;
        }
        return x;
    }

    static float Clamp(const float x, const float min, const float max) {
        if(x < min) {
            return min;
        }
        else if(x > max) {
            return max;
        }
        return x;
    }

    static bn::fixed Clamp(const bn::fixed x, const bn::fixed min, const bn::fixed max) {
        if(x < min) {
            return min;
        }
        else if(x > max) {
            return max;
        }
        return x;
    }

    static int GetSign(const int x) {
        if(x < 0) return -1;
        else { return 1; }
    }
    static int GetSign(const float x) {
        if(x < 0) return -1;
        else { return 1; }
    }
    static int GetSign(const bn::fixed x) {
        if(x < 0) return -1;
        else { return 1; }
    }
    static int GetSignZero(const int x) {
        if(x < 0) return -1;
        else if (x < 0) return 1;
        else { return 0; }
    }
    static int GetSignZero(const float x) {
        if(x < 0) return -1;
        else if (x < 0) return 1;
        else { return 0; }
    }
    static int GetSignZero(const bn::fixed x) {
        if(x < 0) return -1;
        else if (x < 0) return 1;
        else { return 0; }
    }
};

#endif