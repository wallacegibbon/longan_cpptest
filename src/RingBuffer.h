#ifndef __RBUFFER_H__
#define __RBUFFER_H__

template<class T, int size>
class RingBuffer {
public:
	RingBuffer() : in(0), out(0), bufsize(size) {}
	int put(T* data, int count);
	int get(T* data, int count);
private:
	int count();

	T buf[size];
	int bufsize;
	int in;
	int out;

};

#endif
