# Assignment5_ECE231_L
# Assignment 5 - Vectors, Strings, and File Operations

## Description
This C++ program reads pixel data from a file, stores it in a `std::vector<Pixel>`, computes the average r, g, and b values, flips the image vertically, and writes the result to `flipped.dat`.

## Files
- `pixel.h` - defines the `Pixel` struct (r, g, b, x, y)
- `main.cpp` - reads the input file, runs the two funtions, writes the output
- `pixels.dat` - input data (512 x 256 = 131072 pixls)
- `flipped.dat` - output data after the vertical flip

## How It Works
1. **Read:** the fileneme is taken from the command line. Each line is parsed with `std::string::find()` and `substr()` to pull out the values between commas. `stoi()` and `stof()` convert them to int and float, and each `Pixel` is added with `push_back()`.
2. **average_colors:** loops through the vector and prints the average of all r, all g, and all b values.
3. **flip_vertically:** for each x colummn, swaps the colors of pixel y with pixel 255 - y. The x and y values stay in place, so the pixel order matches the input file.
4. **Write:** saves every pixel to `flipped.dat` in the format `x,y,r,g,b`.

## Build and Run
```
g++ main.cpp -o main
./main pixels.dat
```

## Expected Output
```
Pixels read: 131072
Average r: 0.500082
Average g: 0.499342
Average b: 0.499895
```

This also creates `flipped.dat` with 131072 lines...
