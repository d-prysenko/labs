#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

// Для работы с целыми числами из 64 бит




namespace com
{
	#define inttype long
	#define halfint short
	#define HALF_TYPE_MASK 0xffff

	class LongLong
	{
	private:
		

		static halfint get_high_bits(inttype value);
		static halfint get_low_bits(inttype value);

		enum sgn { MINUS = -1, ZERO = 0, PLUS = 1 };
		sgn get_sign() const
		{
			if (minor == 0 && major == 0)
				return ZERO;
			else if (major >> (sizeof(inttype) * 8 - 1))
				return MINUS;
			else
				return PLUS;
		}

	public:
		unsigned inttype minor;
		inttype major;


		LongLong();
		LongLong(inttype number);
		//LongLong(const uint8_t* bytes, uint16_t size);
		//LongLong(unsigned long long num);
		std::string toString() const;
		std::string toSignString() const;

		static void print_bits(const void* buffer, int size);

		static LongLong abs(const LongLong& src);
		LongLong abs() const;

		LongLong operator+(const LongLong& right) const;
		LongLong operator-(const LongLong& right) const;
		LongLong operator*(const LongLong& right) const;
		LongLong operator/(const LongLong& right) const;
		
		bool operator<(const LongLong& other) const;
		bool operator>(const LongLong& other) const;
		bool operator==(const LongLong& other) const;
		bool operator>=(const LongLong& other) const;
		bool operator<=(const LongLong& other) const;

		LongLong& operator-();

		//LongLong operator/(const LongLong& r);
		LongLong operator%(const LongLong& r);

		long long toLL() const;


		bool overflow = false;
	};
}


