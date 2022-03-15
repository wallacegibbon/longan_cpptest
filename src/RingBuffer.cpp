#include <stdio.h>
#include <stdlib.h>
#include "RingBuffer.h"

template<class T>
int RingBuffer::count() {
	if (in >= out)
		return in - out;
	else
		return bufsize + in - out;
}

template<class T>
int RingBuffer::rest() {
	return bufsize - 1 - count();
}

template<class T>
int RingBuffer::put(T* data, int count) {
	if (rest() < count)
		return 0;

	int i = 0;
	while (i < count && in < bufsize)
		buf[in++] = data[i++];

	if (in == bufsize)
		in = 0;

	while (i < count)
		buf[in++] = data[i++];

	return count;
}

template<class T>
int RingBuffer::get(T* data, int count) {
	if (count() < count)
		return 0;

	int i = 0;
	while (i < count && out < bufsize)
		data[i++] = buf[out++];

	if (out == bufsize)
		out = 0;

	while (i < count)
		data[i++] = buf[out++];

	return count;
}

