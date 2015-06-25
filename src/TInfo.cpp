#include "TInfo.h"

TInfo::TInfo() {
    for (int i = 0; i < tamVectorPerceptron; i++) {
        wPerceptron.push_back(0);
    }
}