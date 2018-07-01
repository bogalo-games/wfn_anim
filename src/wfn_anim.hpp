#ifndef __WFN_ANIM_HPP__
#define __WFN_ANIM_HPP__

#include <functional>
#include <cstring>
#include <vector>

#include "ioutil.hpp"

namespace wfn_eng::anim {
  /**
   * struct AnimFrame
   *
   * Provides the information for an individual frame of the animation.
   */
  template<typename T>
  struct AnimFrame {
    uint8_t duration;
    T frame;
  };

  /**
   * struct Anim
   *
   * Provides information for the entirety of an animation.
   *
   * As of right now, effectively just a typedef for a std::vector<AnimFrame<T>>
   */
  template<typename T>
  struct Anim {
    std::vector<AnimFrame<T>> frames;
  };

  /**
   * class AnimManager
   *
   * A manager for animations that handles the loading and saving logic of
   * animations. Intended to be used with ifstreams & ofstreams (saving and
   * loading from disk), but it's stream agnostic.
   */
  template<typename T>
  class AnimManager {
  public:
    /**
     * Given a function that can deserialize the frame type, deserialize an
     * entire animation from an istream.
     */
    static size_t load(
        std::function<size_t(std::istream&, T&)> fn,
        std::istream& input,
        Anim<T>& anim) {
      size_t bytesIn = 0;

      // Checking that the file starts with "ANIM".
      char header[4] { 0, 0, 0, 0 };
      input.read(header, 4);
      bytesIn += 4;

      if (strncmp(header, "ANIM", 4) != 0) {
        std::cerr << "Haaa" << std::endl;
        // TODO: Raise error?
      }

      // Reading in and resizing to the number of frames
      size_t frameCount;
      bytesIn += ioutil::read<size_t>(input, frameCount);
      anim.frames.resize(frameCount);

      // Populating the frames
      for (auto& frame : anim.frames) {
        bytesIn += ioutil::read<uint8_t>(input, frame.duration);
        bytesIn += fn(input, frame.frame);
      }

      return bytesIn;
    }

    /**
     * Given a function that can serialize the frame type, serialize an entire
     * animation to an ostream.
     */
    static size_t save(
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
      bytesOut += ioutil::write<size_t>(output, anim.frames.size());

      // For each frame, write out its duration, followed by the output from fn
      for (const auto& frame : anim.frames) {
        bytesOut += ioutil::write<uint8_t>(output, frame.duration);
        bytesOut += fn(output, frame.frame);
      }

      return bytesOut;
    }
  };
}

#endif
