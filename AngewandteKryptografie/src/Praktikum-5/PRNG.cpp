#include "PRNG.h"


byte PRNG::getByte()
{
	byte b = 0;
	for(int i = 0; i < 8; i++)
	{
		b = 2 * b + getBit();
	}
	return b;
}

void PRNG::getBlock(byte* buffer, unsigned int n)
{
	for(int i = 0; i < n; i++)
	{
		buffer[i] = getByte();
	}
}

Integer PRNG::getInteger(unsigned int size)
{
	byte  buffer[size];
	getBlock(buffer, size);
	Integer var(buffer, size);

	return var;
}

Integer PRNG::getInteger(const Integer& m)
{
	int var = m.ByteCount();
	Integer var2 = m;

	while(var2 > (m - 1) || var2 < 1)
	{
		var2 = getInteger(var);
	}
	return var2;
}

