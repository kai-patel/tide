# Tide

_Torrenting_

---

## Features

- [x] BEncode Parsing
  - [x] Integers
  - [x] Strings
  - [x] Lists
  - [x] Dictionaries
- [ ] BitTorrent Protocol Implementation
- [ ] Command-line Client
- [ ] GUI Client

## Dependencies

- **C++ 17**
- **Boost**
  - Spirit
  - Phoenix
  - Fusion
  - Variant
- _Google Test_ (only if building tests)
- _Doxygen_ (if building documentation)

## Building

See [the build scripts](/tools/) to get an overall idea of how to build.

### Build Definitions

- **BUILD_TESTS** => Toggle test building
- **BOOST_ROOT** => Path to the root directory of your local Boost insallation
