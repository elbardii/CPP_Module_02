
#include "Fixed.hpp"
#include <cmath>

Fixed::Fixed(void) : _value(0) {}

Fixed::Fixed(const int n)
{
	this->_value = n << _fractionalBits;
}

Fixed::Fixed(const float n)
{
	this->_value = roundf(n * (1 << _fractionalBits));
}

Fixed::Fixed(const Fixed &src)
{
	*this = src;
}

Fixed &Fixed::operator=(const Fixed &rhs)
{
	if (this != &rhs)
		this->_value = rhs.getRawBits();
	return *this;
}

Fixed::~Fixed(void) {}

int Fixed::getRawBits(void) const
{
	return this->_value;
}

void Fixed::setRawBits(int const raw)
{
	this->_value = raw;
}

float Fixed::toFloat(void) const
{
	return (float)this->_value / (1 << _fractionalBits);
}

int Fixed::toInt(void) const
{
	return this->_value >> _fractionalBits;
}

// Comparison operators
bool Fixed::operator>(const Fixed &rhs) const
{
	return this->_value > rhs._value;
}

bool Fixed::operator<(const Fixed &rhs) const
{
	return this->_value < rhs._value;
}

bool Fixed::operator>=(const Fixed &rhs) const
{
	return this->_value >= rhs._value;
}

bool Fixed::operator<=(const Fixed &rhs) const
{
	return this->_value <= rhs._value;
}

bool Fixed::operator==(const Fixed &rhs) const
{
	return this->_value == rhs._value;
}

bool Fixed::operator!=(const Fixed &rhs) const
{
	return this->_value != rhs._value;
}

// Arithmetic operators
Fixed Fixed::operator+(const Fixed &rhs) const
{
	Fixed result;
	result.setRawBits(this->_value + rhs._value);
	return result;
}

Fixed Fixed::operator-(const Fixed &rhs) const
{
	Fixed result;
	result.setRawBits(this->_value - rhs._value);
	return result;
}

Fixed Fixed::operator*(const Fixed &rhs) const
{
	Fixed result;
	result.setRawBits((this->_value * rhs._value) >> _fractionalBits);
	return result;
}

Fixed Fixed::operator/(const Fixed &rhs) const
{
	Fixed result;
	result.setRawBits((this->_value << _fractionalBits) / rhs._value);
	return result;
}

// Pre-increment: ++a
Fixed &Fixed::operator++(void)
{
	this->_value++;
	return *this;
}

// Post-increment: a++
Fixed Fixed::operator++(int)
{
	Fixed temp(*this);
	this->_value++;
	return temp;
}

// Pre-decrement: --a
Fixed &Fixed::operator--(void)
{
	this->_value--;
	return *this;
}

// Post-decrement: a--
Fixed Fixed::operator--(int)
{
	Fixed temp(*this);
	this->_value--;
	return temp;
}

// Static min/max functions
Fixed &Fixed::min(Fixed &a, Fixed &b)
{
	return (a < b) ? a : b;
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b)
{
	return (a < b) ? a : b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b)
{
	return (a > b) ? a : b;
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b)
{
	return (a > b) ? a : b;
}

std::ostream &operator<<(std::ostream &out, const Fixed &fixed)
{
	out << fixed.toFloat();
	return out;
}
