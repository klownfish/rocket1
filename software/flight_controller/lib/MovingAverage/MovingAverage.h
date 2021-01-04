#include <stdint.h>

template <typename T>
class MovingAverage {
public:
    MovingAverage(int16_t length);
    void insert(T value);
    T get_value();
private:
    int16_t index_ = 0;
    int16_t length_ = 0;
    T current_ = 0;
    T* values_;
};

template <typename T>
MovingAverage<T>::MovingAverage(int16_t len) {
    length_ = len;
    values_ = malloc(sizeof(T) * len);
}

template <typename T>
void MovingAverage<T>::insert(T value) {
    int16_t new_index = (index_ + 1) % length_;
    current_ = (current_ - values_[new_index]) / length_;
    values_[new_index] = value;
    index_ = new_index;
}

template <typename T>
T MovingAverage<T>::get_value() {
    return current_;
}