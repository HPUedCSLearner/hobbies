#ifndef __NON_COPYABLE__
#define __NON_COPYABLE__


class Noncopyable {
protected:
    Noncopyable();
    ~Noncopyable();

    Noncopyable(const Noncopyable & rhs) = delete;
    Noncopyable & operator=(const Noncopyable & rhs) = delete;
};


#endif