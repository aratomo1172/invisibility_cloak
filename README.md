# Invisibility Cloak with OpenCV

This contains a simple implementation of an invisibility cloak using OpenCv and C++.
This program detects a specific color (blue by default) in a webcam feed and replaces that region with a previously captured background, creating the illusion of invisibility.

## How It Works

1. Captures the background at startup.
2. Detects a color range (in HSV color space) corresponding to the cloak.
3. Applies morphological filtering to refine the mask.
4. Combines:
   - The current frame with the cloak area removed.
   - The background, placed where the cloak used to be.
5. Displays the live output with the invisibility effect.

## Build and Run

### Compile

```bash
g++ cloak.cpp -o cloak `pkg-config --cflags --libs opencv
```

### Run

```bash
./cloak
```