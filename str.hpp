
#ifndef STR_HPP
#define STR_HPP

#include <algorithm>
#include <cstring>
#include <vector>

class str
{
private:
    char *data;
    size_t length;

public:
    str() {
        data = new char[1];
        data[0] = '\0';
        length = 0;
    }

    str(const char &c) {
        data = new char[2];
        data[0] = c;
        data[1] = '\0';
        length = 1;
    }

    str(const char *&&s_) {
        if (s_) {
            length = std::strlen(s_);
            data = new char[length + 1];
            std::memcpy(data, s_, length + 1);
        } else {
            length = 0;
            data = new char[1];
            data[0] = '\0';
        }
    }

    str &operator=(const char *&&s_) {
        char* new_data;
        size_t new_length;
        if (s_) {
            new_length = std::strlen(s_);
            new_data = new char[new_length + 1];
            std::memcpy(new_data, s_, new_length + 1);
        } else {
            new_length = 0;
            new_data = new char[1];
            new_data[0] = '\0';
        }
        delete[] data;
        data = new_data;
        length = new_length;
        return *this;
    }

    str(const str &other) {
        length = other.length;
        data = new char[length + 1];
        std::memcpy(data, other.data, length + 1);
    }

    str &operator=(const str &other) {
        if (this != &other) {
            char* new_data = new char[other.length + 1];
            std::memcpy(new_data, other.data, other.length + 1);
            delete[] data;
            data = new_data;
            length = other.length;
        }
        return *this;
    }

    char &operator[](size_t pos) {
        return data[pos];
    }

    const char &operator[](size_t pos) const {
        return data[pos];
    }

    size_t len() const {
        return length;
    }

    str join(const std::vector<str> &strs) const {
        if (strs.empty()) {
            return str();
        }
        size_t total_len = 0;
        for (size_t i = 0; i < strs.size(); ++i) {
            total_len += strs[i].len();
        }
        total_len += (strs.size() - 1) * length;

        char *new_data = new char[total_len + 1];
        char *ptr = new_data;
        for (size_t i = 0; i < strs.size(); ++i) {
            size_t slen = strs[i].len();
            if (slen > 0) {
                std::memcpy(ptr, strs[i].data, slen);
                ptr += slen;
            }
            if (i < strs.size() - 1 && length > 0) {
                std::memcpy(ptr, data, length);
                ptr += length;
            }
        }
        *ptr = '\0';
        
        str res;
        delete[] res.data;
        res.data = new_data;
        res.length = total_len;
        return res;
    }

    str slice(size_t l, size_t r) const {
        if (l >= r || l >= length) {
            return str();
        }
        if (r > length) r = length;
        size_t new_len = r - l;
        char *new_data = new char[new_len + 1];
        std::memcpy(new_data, data + l, new_len);
        new_data[new_len] = '\0';

        str res;
        delete[] res.data;
        res.data = new_data;
        res.length = new_len;
        return res;
    }

    ~str() {
        delete[] data;
    }
};

#endif
