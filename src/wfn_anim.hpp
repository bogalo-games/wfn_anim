#ifndef __WFN_ANIM_HPP__
#define __WFN_ANIM_HPP__

#include <functional>
#include <vector>

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
    static size_t load(
        std::function<size_t(std::istream&, T&)>, std::istream&, Anim<T>&);

    static size_t save(
        std::function<size_t(std::ostream&, const T&)>,
        std::ostream&,
        const Anim<T>&);
  };
}

#include "wfn_anim.tpp"

#endif
