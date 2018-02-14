# ImageRescaler

Applies a linear transformation to the intensity levels of the input Image.

It uses ITK's C++ [RescaleIntensityImageFilter](https://itk.org/Doxygen/html/classitk_1_1RescaleIntensityImageFilter.html) to apply pixel-wise linear transformation to the intensity values of input image pixels. The linear transformation is defined by the user in terms of the minimum and maximum values that the output image should have.

The following equation gives the mapping of the intensity values:

![equation](http://mathurl.com/y7eppsyj.png)


