//
// Created by Marian Mutu on 14.05.2022.
//

#ifndef LAB9_10_EXCEPTION_H
#define LAB9_10_EXCEPTION_H
class Exception
{
private:
    const char* message;
public:
    explicit Exception(const char* m) : message(m) {
    }
    const char* getMessage() {
        return message;
    }
};
#endif //LAB9_10_EXCEPTION_H
