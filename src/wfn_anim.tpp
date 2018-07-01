namespace wfn_eng::anim {
  template<typename T>
  size_t AnimManager<T>::load(
      std::function<size_t(std::istream&, T&)> fn,
      std::istream& input,
      Anim<T>& anim) {
    return 0;
  }

  template<typename T>
  size_t AnimManager<T>::save(
      std::function<size_t(std::ostream&, const T&)> fn,
      std::ostream& output,
      const Anim<T>& anim) {
    size_t bytesOut = 0;

    // "ANIM", but not in string literal form because we don't want to append
    // the null character.
    char header[4] = { 65, 78, 73, 77 };
    output.write(header, 4);
    bytesOut += 4;

    // Writing out the number of frames.
    output.write(anim.frames.size(), sizeof(size_t));
    bytesOut += sizeof(size_t);

    // For each frame, write out its duration, followed by the output from fn
    for (const auto& frame : anim.frames) {
      output.write(frame.duration, sizeof(uint8_t));
      bytesOut += sizeof(uint8_t);

      bytesOut += fn(output, frame.frame);
    }

    return bytesOut;
  }
}
