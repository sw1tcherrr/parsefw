#pragma once

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include <cerrno>
#include <cstring>
#include <string_view>
#include <system_error>
#include <tl/expected.hpp>

struct MmapBuffer {
    using value_type = char;             // NOLINT
    using iterator = value_type const*;  // NOLINT
    using const_iterator = iterator;     // NOLINT

    MmapBuffer(MmapBuffer const&) = delete;
    MmapBuffer& operator=(MmapBuffer const&) = delete;
    MmapBuffer& operator=(MmapBuffer&& other) = delete;

    MmapBuffer(MmapBuffer&& other) : m_ptr(other.m_ptr), m_size(other.m_size) {
        other.Reset();
    }

    bool TryDeallocate() {
        int res = munmap(reinterpret_cast<void*>(m_ptr), m_size);
        if (res != 0) {
            // user can retry
            return false;
        }
        Reset();
        return true;
    }

    void Reset() {
        m_ptr = nullptr;
        m_size = 0;
    }

    iterator begin() const {  // NOLINT
        return m_ptr;
    }

    iterator end() const {  // NOLINT
        return begin() + m_size;
    }

    value_type const& operator[](size_t idx) const {
        return *(m_ptr + idx);
    }

    ~MmapBuffer() {
        TryDeallocate();  // ignore result, can't throw in destructor
    }

private:
    friend tl::expected<MmapBuffer, std::string> MakeMmap(std::string_view path);

    MmapBuffer(char* ptr, size_t size) : m_ptr{ptr}, m_size{size} {
    }

    char* m_ptr;
    size_t m_size;
};

inline tl::expected<MmapBuffer, std::string> MakeMmap(std::string_view path) {
    int fd = ::open(path.data(), O_RDONLY);
    if (fd == -1) {
        return tl::unexpected(strerror(errno));
    }

    struct stat s;
    int res = fstat(fd, &s);
    if (res != 0) {
        return tl::unexpected("Can't fstat");
    }
    auto len = s.st_size;
    auto ptr = static_cast<char*>(::mmap64(nullptr, len, PROT_READ, MAP_PRIVATE, fd, 0));
    if (ptr == nullptr) {
        return tl::unexpected("Can't mmap");
    }

    return {MmapBuffer(ptr, len)};
}