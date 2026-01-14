 
#pragma once

template <typename BitType, typename FlagType, typename SignedType>
class BitFlagIterator
{
private:
  FlagType flags;

public:
  inline BitFlagIterator() : flags(0) {}
  inline BitFlagIterator(FlagType mask) : flags(mask) {}
  inline BitFlagIterator(FlagType mask, BitType bit) : flags(mask & ~(bit - 1)) {}
  inline BitFlagIterator(const BitFlagIterator &o) : flags(o.flags) {}
  static inline BitFlagIterator begin(FlagType mask) { return BitFlagIterator(mask); }
  static inline BitFlagIterator end() { return BitFlagIterator(0); }
  inline BitType operator*() const { return (BitType)(flags & (FlagType)(-(SignedType)flags)); }
  inline BitFlagIterator &operator++()
  {
    flags ^= **this;
    return *this;
  }
  inline bool operator==(const BitFlagIterator &rhs) const { return flags == rhs.flags; }
  inline bool operator!=(const BitFlagIterator &rhs) const { return flags != rhs.flags; }
  inline BitFlagIterator &operator=(const BitFlagIterator &rhs)
  {
    flags = rhs.flags;
    return *this;
  }
};
