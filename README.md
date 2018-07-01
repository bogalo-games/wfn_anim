# wfn_anim

Library for saving and loading animations of arbitrary image types, so long as
images can be loaded and saved.

Provides the following API:

* `AnimFrame` &mdash; Contains information on frame durations and frame content.
* `Anim` &mdash; A series of `AnimFrames` in sequence.
* `AnimManager::load` &mdash; Animation loader, requires a function that loads
  in a frame from a `std::istream`. Returns an `Anim`.
* `AnimManager::save` &mdash; Animation saver, requires a function that
  serializes a frame such that it can be written out with an `std::ostream`.
  Takes an `Anim`.
