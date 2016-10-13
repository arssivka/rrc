/**
 *  @autor Nikita Somenkov
 *  @date 08/10/2016
 */
#pragma once

#include <memory>

namespace rrc {

    class IOBuffer
    {
    public:
        IOBuffer();
        IOBuffer(const IOBuffer &other);
        IOBuffer(const char *data, size_t size);
        IOBuffer(size_t size);

        IOBuffer &operator=(const IOBuffer &other);

        size_t size() const;
        char * data();
        const char * data() const;

        ~IOBuffer();

    private:
        void copyBuffer(const char *buffer);

        char *mData;
        size_t mSize;
    };

    typedef std::shared_ptr<IOBuffer> IOBufferPtr;
}



