#include "Vector.h"
#include <cmath>

Vector::Vector(const Value* rawArray, const size_t size, float coef):
        _size(size), _multiplicativeCoef(coef) {

    if (_multiplicativeCoef < 1) _multiplicativeCoef = 2;

    if (size == 0) {
        _capacity = int(coef);
    }
    else {
        _capacity = int(float(_size) * _multiplicativeCoef);
    }

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
    reverseFieldsDestructCopy(*this, vectorCopy);

    return *this;
}

Vector::Vector(Vector&& other) noexcept {
    reverseFieldsDestructCopy(*this, other);
}

Vector& Vector::operator=(Vector&& other) noexcept {
    reverseFieldsDestructCopy(*this, other);
    return *this;
}

Value& Vector::operator[](size_t idx) {
    return _data[idx];
}

const Value& Vector::operator[](size_t idx) const {
    return _data[idx];
}

void Vector::pushBack(const Value& value) {
    insert(value, _size);
}

void Vector::pushFront(const Value& value) {
    insert(value, 0);
}

void Vector::insert(const Value& value, size_t pos) {
    sizeControl();

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
    erase(size() - 1, 1);
}

void Vector::popFront() {
    erase(0, 1);
}

void Vector::erase(size_t pos, size_t count) {
    errorShow();

    size_t end = pos + count;
    size_t k = 0;

    if (end > _size) {
        end = _size;
    }

    for (size_t i = end; i < _size; ++i) {
        _data[pos + k] = _data[i];
        ++k;
    }

    _size -= end - pos;
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
    float copyCoefficient;
    Vector vectorCopy;

    if (capacity > _capacity) {
        if (_size != 0) {
            copyCoefficient = float(capacity) / float(this->_size);
            vectorCopy = Vector(this->_data, _size, copyCoefficient);
        }
        else {
            vectorCopy = Vector(this->_data, _size, capacity);
        }

        copyCoefficient = this->_multiplicativeCoef;

        *this = std::move(vectorCopy);
        vectorCopy.cleanVector();

        this->_multiplicativeCoef = copyCoefficient;
    }
}

void Vector::shrinkToFit() {
    float copyCoefficient = this->_multiplicativeCoef;

    if (_size != 0) {
        Vector vectorCopy(_data, _size, 1);
        *this = std::move(vectorCopy);
        this->_multiplicativeCoef = copyCoefficient;

        vectorCopy.cleanVector();
    }
    else {
        delete this->_data;
        _data = new Value(0);
        _capacity = 0;
    }
}

void Vector::reverseFieldsDestructCopy(Vector& base, Vector& copy) {
    std::swap(base._data, copy._data);
    base._size = copy._size;
    base._capacity = copy._capacity;
    base._multiplicativeCoef = copy._multiplicativeCoef;
    copy.cleanVector();
}

void Vector::sizeControl() {
    if (_size == _capacity) {
        Vector vectorCopy(*this);
        *this = std::move(vectorCopy);
        vectorCopy.cleanVector();
    }
}

void Vector::cleanVector() {
    this->_data = nullptr;
    this->_size = 0;
    this->_multiplicativeCoef = 0;
    this->_capacity = 0;
}

void Vector::errorShow() const {
    if (_size == 0) {
        throw std::out_of_range("Removal from empty vector");
    }
}