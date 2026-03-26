#ifndef TIED_STREAMBUF_TCC
#define TIED_STREAMBUF_TCC

#define CLASS tied_streambuf<CharT, N>

template<typename CharT, std::size_t N>
template<typename... Streambuf>
    requires (... && std::is_convertible_v<Streambuf *, std::basic_streambuf<typename std::char_traits<CharT>::char_type> *>)
CLASS::tied_streambuf(Streambuf *... buffers) noexcept : buffers_{buffers...} {}

template<typename CharT, std::size_t N>
std::streamsize CLASS::xsputn(const char_type *const s, const std::streamsize n) {
    if (n == 0) return 0;

    std::streamsize min_size = n;
    for (std::basic_streambuf<char_type> *const buffer : buffers_)
        min_size = std::min(min_size, buffer->sputn(s, n));

    return min_size;
}

template<typename CharT, std::size_t N>
auto CLASS::overflow(const int_type c) -> int_type {
    if (traits_type::eq_int_type(c, traits_type::eof()))
        return traits_type::not_eof(c);

    bool failed = false;
    for (const char_type ch = traits_type::to_char_type(c); std::basic_streambuf<char_type> *const buffer : buffers_)
        if (traits_type::eq_int_type(buffer->sputc(ch), traits_type::eof()))
            failed = true;

    return failed ? traits_type::eof() : traits_type::not_eof(c);
}

template<typename CharT, std::size_t N>
int CLASS::sync() {
    bool failed = false;
    for (std::basic_streambuf<char_type> *const buffer : buffers_)
        if (buffer->pubsync() == -1)
            failed = true;

    return failed ? -1 : 0;
}

#endif
