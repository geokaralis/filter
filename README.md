![Filter](docs/filter_logo.svg)

# Filter

Filter is a c++ project for simple image processing. It consists of a library that reads .ppm files and several image filtering implementations, such as linear, gamma etc.

## Filtering an image

In order to filter an image, create an instance of it and then apply the necessary filter using the << operator.

```c++
Image* image = new Image();
Filter* gamma_filter = new FilterGamma(2.0); // specify the gamma value inside the constructor, here 2.0

*image = *gamma_filter << *image;
```

### Contributors
George Kavalieros\
George Karalis
