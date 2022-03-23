#ifndef __RBUFFER_H
#define __RBUFFER_H

template <typename T, int SIZE>
class RingBuffer
{
public:
    RingBuffer() : in(0), out(0) {}
    int put(T *data, int count);
    int get(T *data, int count);
    int count();
    int rest();

private:
    T buf[SIZE];
    int in;
    int out;
};

template <typename T, int SIZE>
int RingBuffer<T, SIZE>::count()
{
    if (in >= out)
    {
        return in - out;
    }
    else
    {
        return SIZE + in - out;
    }
}

template <typename T, int SIZE>
int RingBuffer<T, SIZE>::rest()
{
    return SIZE - 1 - count();
}

template <typename T, int SIZE>
int RingBuffer<T, SIZE>::put(T *data, int cnt)
{
    if (rest() < cnt)
    {
        return 0;
    }

    int i = 0;
    while (i < cnt && in < SIZE)
    {
        buf[in++] = data[i++];
    }
    if (in == SIZE)
    {
        in = 0;
    }
    while (i < cnt)
    {
        buf[in++] = data[i++];
    }
    return cnt;
}

template <typename T, int SIZE>
int RingBuffer<T, SIZE>::get(T *data, int cnt)
{
    if (count() < cnt)
    {
        return 0;
    }

    int i = 0;
    while (i < cnt && out < SIZE)
    {
        data[i++] = buf[out++];
    }
    if (out == SIZE)
    {
        out = 0;
    }
    while (i < cnt)
    {
        data[i++] = buf[out++];
    }
    return cnt;
}

#endif
