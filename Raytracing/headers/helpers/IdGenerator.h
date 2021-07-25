#ifndef RT_IDGENERATOR_H
#define RT_IDGENERATOR_H


class IdGenerator {
private:
    int _count = 0;
public:
    IdGenerator() = default;
    IdGenerator(const IdGenerator& copy) = delete;
    void operator=(const IdGenerator& copy) = delete;

    int getId();
};

#endif
