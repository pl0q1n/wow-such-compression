#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <algorithm>
#include <iostream>
#include <iterator>
#include <type_traits>

namespace lzw {

template <class Iter>
class UnescapeIterator
    : public std::iterator<std::forward_iterator_tag,
                           typename std::remove_reference<decltype(
                               *std::declval<Iter>())>::type> {
  Iter _inner;

public:
  UnescapeIterator(Iter it) : _inner(it) {}
  UnescapeIterator() = default;
  UnescapeIterator(const UnescapeIterator &) = default;
  UnescapeIterator(UnescapeIterator &&) = default;
  UnescapeIterator &operator=(const UnescapeIterator &) = default;
  UnescapeIterator &operator=(UnescapeIterator &&) = default;
  ~UnescapeIterator() = default;

  // TODO: Fix if frst character is backslash
  UnescapeIterator operator++() {
    ++_inner;
    if (*_inner == '\\') {
      ++_inner;
    }
    return *this;
  }

  typename std::remove_reference<decltype(*std::declval<Iter>())>::type
  operator*() {
    return *_inner;
  }

  bool operator!=(const UnescapeIterator &rhs) const {
    return _inner != rhs._inner;
  }
  bool operator==(const UnescapeIterator &rhs) const {
    return _inner == rhs._inner;
  }

  std::ptrdiff_t operator-(const UnescapeIterator &rhs) const {
    return _inner - rhs._inner;
  }
};

template <class Iter> UnescapeIterator<Iter> unescape(Iter &&it) {
  return UnescapeIterator<Iter>(std::forward<Iter>(it));
}

const uint16_t *find_unescaped(const uint16_t *begin, const uint16_t *end,
                               const uint16_t &what_to_find);

} // namespace lzw

#endif // UTILITIES_HPP
