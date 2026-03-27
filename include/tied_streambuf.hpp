#ifndef TIED_STREAMBUF_HPP
#define TIED_STREAMBUF_HPP

#include <streambuf>

template<typename CharT, std::size_t N>
class tied_streambuf final : public std::basic_streambuf<CharT> {
    using traits_type = std::char_traits<CharT>;
    using char_type = traits_type::char_type;
    using int_type = traits_type::int_type;

    std::basic_streambuf<char_type> *buffers_[N];

public:
    template<typename... Streambuf>
        requires (... && std::is_convertible_v<Streambuf *, std::basic_streambuf<char_type> *>)
    explicit tied_streambuf(Streambuf *... buffers) noexcept;

private:
    std::streamsize xsputn(const char_type *s, std::streamsize n);

    int_type overflow(int_type c);

    int sync();
};

template<typename First, typename... Other>
tied_streambuf(First *, Other *...) -> tied_streambuf<typename First::char_type, 1 + sizeof...(Other)>;

#include "tied_streambuf.tcc"

#endif
