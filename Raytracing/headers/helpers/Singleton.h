#ifndef RT_SINGLETON_H
#define RT_SINGLETON_H

template<typename T>
class Singleton {
protected:
    struct token {};
    Singleton() = default;
public:
    static T& getInstance();

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

#endif
