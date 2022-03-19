#include "Vector.h"
#include <cmath>

Vector::Vector(const Value* rawArray, const size_t size, float coef):
    _size(size), _multiplicativeCoef(coef) {

    _capacity = std::ceil(float(_size) * _multiplicativeCoef);
    _data = new Value[_capacity];

    for (size_t i = 0; i < _size; ++i) {
        _data[i] = rawArray[i];
    }
}

Vector:: Vector(const Vector& other):
    Vector(other._data, other._size, other._multiplicativeCoef) {}

Vector::~Vector() {
    delete[] _data;
}

Vector& Vector::operator=(const Vector& other) {
    if (this == &other) {
        return *this;
    }

    Vector vectorCopy(other);
    classObjectsSwap(*this, vectorCopy);

    return *this;
}

Vector::Vector(Vector&& other) noexcept {
    classObjectsSwap(*this, other);
}

Vector& Vector::operator=(Vector&& other) noexcept {
    classObjectsSwap(*this, other);
    return *this;
}

Value& Vector::operator[](size_t idx) {
    return _data[idx];
}

const Value& Vector::operator[](size_t idx) const {
    return _data[idx];
}

void Vector::pushBack(const Value& value) {
    if (_size == _capacity) {
        Vector vectorCopy(*this);
        *this = std::move(vectorCopy);
    }

    ++_size;
    _data[_size - 1] = value;
}

void Vector::pushFront(const Value& value) {
    if (_size == _capacity) {
        Vector vectorCopy(*this);
        *this = std::move(vectorCopy);
    }

    for (size_t i = 1; i < _size + 1; ++i) {
        std::swap(_data[0], _data[i]);
    }

    ++_size;
    _data[0] = value;
}

void Vector::insert(const Value& value, size_t pos) {
    for (size_t i = pos + 1; i < _size + 1; ++i) {
        std::swap(_data[pos], _data[i]);
    }

    _data[pos] = value;
    ++_size;
}

void Vector::insert(const Value* values, size_t size, size_t pos) {
    for (size_t i = 0; i < size; ++i) {
        insert(values[i], pos);
        ++pos;
    }
}

void Vector::insert(const Vector& vector, size_t pos) {
    insert(vector._data, vector.size(), pos);
}

void Vector::popBack() {
    --_size;
}

void Vector::popFront() {
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = _data[i + 1];
    }
    --_size;
}

void Vector::erase(size_t pos, size_t count) {
    size_t end = pos + count;
    size_t k = 0;

    if (pos + count > _size) {
        end = _size;
    }

    for (size_t i = end; i < _size; ++i) {
        _data[pos + k] = _data[i];
        ++k;
    }

    _size -= count;
}

void Vector::eraseBetween(size_t beginPos, size_t endPos) {
    erase(beginPos, endPos - beginPos);
}

size_t Vector::size() const {
    return _size;
}

size_t Vector::capacity() const {
    return _capacity;
}

double Vector::loadFactor() const {
    return double(_size) / double(_capacity);
}

long long Vector::find(const Value& value) const {
    for (size_t i = 0; i < _size; ++i) {
        if (_data[i] == value) {
            return i;
        }
    }
    return -1;
}

void Vector::reserve(size_t capacity) {
    if (capacity > _capacity) {
        _multiplicativeCoef = float(capacity) / float(this->_size);
        Vector vectorCopy(this->_data, _size, _multiplicativeCoef);
        *this = std::move(vectorCopy);
    }
}

void Vector::shrinkToFit() {
    float copyCoefficient = 1;
    Vector vectorCopy(_data, _size, copyCoefficient);
    copyCoefficient = this->_multiplicativeCoef;
    *this = std::move(vectorCopy);
    this->_multiplicativeCoef = copyCoefficient;
}

void Vector::classObjectsSwap(Vector& base, Vector& copy) {
    std::swap(base._data, copy._data);
    base._size = copy._size;
    base._capacity = copy._capacity;
    base._multiplicativeCoef = copy._multiplicativeCoef;
}