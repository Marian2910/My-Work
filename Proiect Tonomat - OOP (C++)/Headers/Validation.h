//
// Created by Marian Mutu on 14.05.2022.
//

#ifndef LAB9_10_VALIDATION_H
#define LAB9_10_VALIDATION_H

class Validation
{
private:
    const char* message;
public:
    explicit Validation(const char* m) : message(m) {
    }
    const char* getMessage() {
        return message;
    }
};

#endif //LAB9_10_VALIDATION_H
