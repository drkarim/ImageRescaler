# ImageRescaler

Applies a linear transformation to the intensity levels of the input Image. It can also be used for converting between file types NRRD, NiFTII and GIPL

It uses ITK's C++ [RescaleIntensityImageFilter](https://itk.org/Doxygen/html/classitk_1_1RescaleIntensityImageFilter.html) to apply pixel-wise linear transformation to the intensity values of input image pixels. The linear transformation is defined by the user in terms of the minimum and maximum values that the output image should have.

The following equation gives the mapping of the intensity values:


![equation](http://mathurl.com/y7eppsyj.png)


Note that this repository demonstrates a simple usage of ITK's rescale filters. Similar examples can be found in [ITK examples Wiki](https://itk.org/Wiki/ITK/Examples/ImageProcessing/RescaleIntensityImageFilter).

The code also has other rescaling options through ITK's filters such as [Cast Image Filter](https://itk.org/Doxygen/html/classitk_1_1CastImageFilter.html), [Shift Scale Filter](https://itk.org/Doxygen/html/classitk_1_1ShiftScaleImageFilter.html) and [Normalise Filter](https://itk.org/Doxygen/html/classitk_1_1NormalizeImageFilter.html). And, these can be activated by using the command line switches described below. 

For converting between file types NRRD, NiFTII and GIPL simply use the (https://itk.org/Doxygen/html/classitk_1_1CastImageFilter.html), [Shift Scale Filter] option within the code (switch: -s 3). 

## Usage
```
 irescale (followed with the these switches)
   -i <input 3D Image> 
   -o <output image> 

   (optional) 
   -s <which rescaler 1-4 below> 
      1 = itk::itkRescaleIntensityImageFilter (0-255)
      2 = itk::CastImageFilter (Window=0-255, please within modify code)
      3 = itk::ShiftScaleImageFilter (scale=1, shift=0) - useful for conversion between NRRD, NiFTII and GIPL
      4 = itk::NormalizeImageFilter
```

## Dependencies
This code has to be built from source using [CMake](https://cmake.org/). It has some dependencies as it requires to perform 3D medical image processing. For these purposes, it depends on the [Image Registration Toolkit (ITK)](https://itk.org/) 


## Platforms 
This code has been tested on Windows 7 on Visual Studio 2015 and MacOS Sierra 10.12 running native g++ compilers. 


## Author 

```
Dr. Rashed Karim 
Department of Biomedical Engineering 
King's College London 
```
