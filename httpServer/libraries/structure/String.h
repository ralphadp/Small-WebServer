//
// Created by root on 08-02-20.
//

#ifndef STRUCTURE_STRING_H
#define STRUCTURE_STRING_H


#include <iostream>
#include <string.h>

namespace Structure {

/**
 * Design pattern for data, following the rule of the three.
 */
    class String {

    protected:
        char *m_value;

        inline void assign(const char* value) {
            if (value) {
                m_value = new char[strlen(value) + 1]();
                strcpy(m_value, value);
                m_value[strlen(value)] = 0;
            }
        }

    public:
        String();

        String(const char *);

        String(const String &);

        ~String();

        String &operator=(const char *);

        String &operator=(const String &);

        friend std::ostream &operator<<(std::ostream &, const String &);

        void clear();

        const char *value() const;

        bool operator==(const char *);

        bool operator==(const String &);

        unsigned int getHash(unsigned int MAX = 100) const;

        String& operator+=(const char *);

        String& operator+=(const String &);
    };

}

#endif //TESTMAP_STRING_H
