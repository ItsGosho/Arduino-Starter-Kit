#ifndef KNOCK_LOCK_ARDUINOUTILS_H
#define KNOCK_LOCK_ARDUINOUTILS_H


namespace ArduinoUtils {

    template<int S>
    void setPinsMode(const short (& pins)[S], bool mode);
};


#endif //KNOCK_LOCK_ARDUINOUTILS_H
