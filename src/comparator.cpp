#include "comparator.hpp"

bool comparator::cmpfi(float A, float B, float epsilon) {
    return (std::fabs(A - B) < epsilon);
}

bool nothing() {

    
}