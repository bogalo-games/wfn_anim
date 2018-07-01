#include <functional>
#include <iostream>
#include <fstream>
#include <string>

#include "wfn_anim.hpp"
#include "ioutil.hpp"

using namespace wfn_eng::anim;

/**
 * Loads a string in from disk.
 */
size_t loadFunction(std::istream& input, std::string& str) {
  size_t bytesIn = 0;

  size_t strSize;
  bytesIn += ioutil::read<size_t>(input, strSize);

  str.resize(strSize);
  for (size_t i = 0; i < strSize; i++) {
    str[i] = (char)input.get();
  }

  return bytesIn;
}

/**
 * Saves a string to disk.
 */
size_t saveFunction(std::ostream& output, const std::string& str) {
  size_t bytesOut = 0;

  bytesOut += ioutil::write<size_t>(output, str.size());
  for (const char& c : str) {
    output.put(c);
  }

  return bytesOut;
}

/**
 *
 */
int main(int argc, char** argv) {
  // Saving an animation
  Anim<std::string> saveAnimation;

  saveAnimation.frames.push_back(AnimFrame<std::string> { 8, "Hel" });
  saveAnimation.frames.push_back(AnimFrame<std::string> { 4, "lo" });
  saveAnimation.frames.push_back(AnimFrame<std::string> { 5, "Wor" });
  saveAnimation.frames.push_back(AnimFrame<std::string> { 3 , "ld" });

  std::ofstream output("out.anim");
  size_t saved =
    AnimManager<std::string>::save(saveFunction, output, saveAnimation);
  output.close();

  // Loading an animation
  Anim<std::string> loadAnimation;

  std::ifstream input("out.anim");
  size_t loaded =
    AnimManager<std::string>::load(loadFunction, input, loadAnimation);
  input.close();

  // Ensuring that both animations are the same
  if (saved != loaded) {
    std::cerr << "Byte count mismatch, save has: "
              << saved
              << ", but load has: "
              << loaded
              << std::endl;
    return 1;
  }

  if (saveAnimation.frames.size() != loadAnimation.frames.size()) {
    std::cerr << "Frame count mismatch, save has: "
              << saveAnimation.frames.size()
              << ", but load has: "
              << loadAnimation.frames.size()
              << std::endl;
    return 1;
  }

  bool errd = false;
  for (int i = 0; i < saveAnimation.frames.size(); i++) {
    const auto& saveFrame = saveAnimation.frames[i];
    const auto& loadFrame = loadAnimation.frames[i];

    if (saveFrame.duration != loadFrame.duration) {
      std::cerr << "(" << i << "): Duration mismatch, save has: "
                << saveFrame.duration
                << ", but load has: "
                << loadFrame.duration
                << std::endl;
      errd = true;
    }

    // Here we can compare against the frame, but we might not be able to
    // depending on the template used.
    if (saveFrame.frame != loadFrame.frame) {
      std::cerr << "(" << i << "): Frame mismatch, save has: \""
                << saveFrame.frame
                << "\", but load has: \""
                << loadFrame.frame
                << "\""
                << std::endl;
      errd = true;
    }
  }

  if (errd) return 1;
  else return 0;
}
