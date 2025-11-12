# AI Agent Instructions for JUCE Development

## Project Overview
JUCE is a cross-platform C++ application framework primarily focused on audio applications and plugins. This codebase follows specific patterns and conventions that you should be aware of when assisting with development.

## Key Architecture Concepts

### Module System
- Modules are self-contained units in `/modules` with a specific structure:
  - Each module has a master header (e.g., `juce_core.h`) that includes all public headers
  - All internal includes must use relative paths within the module
  - Dependencies between modules are explicitly declared
- Example module structure from `juce_core`:
  ```
  juce_core/
    juce_core.h       # Master header
    juce_core.cpp     # Main source file
    containers/       # Implementation subcategories
    files/
    misc/
    ...
  ```

### Build System Conventions
- CMake (3.22+) is the primary build system
- Two ways to integrate JUCE:
  1. Via `add_subdirectory(JUCE)` for in-tree builds
  2. Via `find_package(JUCE)` for installed JUCE
- Projucer tool in `/extras/Projucer` provides alternative project management

### Plugin Architecture
- Plugin formats: VST3, AU, AUv3, AAX, LV2
- Key integration points:
  - `juce::AudioProcessor` - base class for all audio plugins
  - `juce::AudioProcessorEditor` - GUI component base class
  - `juce::AudioProcessorParameter` - parameter management

## Development Workflows

### Building the Project
```bash
# Configure build
cmake -B build
# Build specific target
cmake --build build --target <target_name>
# Build and install JUCE
cmake -B cmake-build-install -DCMAKE_INSTALL_PREFIX=/path/to/install
cmake --build cmake-build-install --target install
```

### Testing
- Unit tests are in `/extras/UnitTestRunner`
- Audio plugin validation in `/extras/AudioPluginHost`

### Common Patterns
1. RAII and smart pointer usage (prefer `std::unique_ptr` and `juce::Component` ownership)
2. Event dispatch via `juce::MessageManager` for thread-safe UI updates
3. Audio buffer management using `juce::AudioBuffer` and zero-copy techniques

## Key Files/Directories
- `/modules` - Core JUCE modules
- `/examples` - Reference implementations and demos
- `/docs` - API documentation and guides
- `/extras` - Tools and utilities
- `CMakeLists.txt` - Main build configuration

## Integration Points
- Audio: `juce_audio_*` modules for device I/O, formats, and processing
- GUI: `juce_gui_*` modules for cross-platform interface components
- DSP: `juce_dsp` module for audio processing algorithms
- Plugin formats: `juce_audio_processors` for host/plugin communication