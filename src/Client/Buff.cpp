    //
// Created by nicetwice on 10/05/16.
//

#include "Buff.h"

IND::Buff::Buff() {
    _duration = 1;
    _isEnded = false;
}

IND::Buff::~Buff() {

}

bool IND::Buff::isEnded(void) const {
    return _isEnded;
}






