#include "ArduinoUtils.h"


template<int S>
void ArduinoUtils::setPinsMode(const short (& pins)[S], bool mode) {

    for (int i = 0; i < S; ++i)
        pinMode(pins[i], mode);
}
