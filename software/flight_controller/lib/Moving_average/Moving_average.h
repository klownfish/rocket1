#include <stdint.h>

template <typename T>
class Moving_average {
public:
    Moving_average(int16_t length);
    T insert(T value);
    T get_value();
private:
    int16_t index;
    int16_t length;
    T current;
    T* values;
};

template <typename T>
Moving_average<T>::Moving_average(int16_t len) {
    length = len;
}

template <typename T>
T Moving_average<T>::insert(T value) {
    int16_t new_index = (index + 1) % length;
    current = (current - values[new_index]) / length;
    values[new_index] = value;
    index = new_index;
}

template <typename T>
T Moving_average<T>::get_value() {
    return current;
}