#ifndef __WFN_ANIM_IOUTIL_HPP__
#define __WFN_ANIM_IOUTIL_HPP__

namespace wfn_eng::anim::ioutil {
  /**
   * Writes out a type T, based on its size, serialized as bytes. Must not be
   * a pointer, or it will only write out the pointer value.
   */
  template<typename T>
  size_t write(std::ostream& output, T value) {
    output.write(reinterpret_cast<char *>(&value), sizeof(T));
    return sizeof(T);
  }

  /**
   * Reads in a type T, based on its size, deserialized from bytes. Must not be
   * a pointer, or it will only read in the pointer value.
   */
  template<typename T>
  size_t read(std::istream& input, T& value) {
    input.read(reinterpret_cast<char *>(&value), sizeof(T));
    return sizeof(T);
  }
}

#endif
