# ImageRescaler

Applies a linear transformation to the intensity levels of the input Image.

It uses ITK's C++ [RescaleIntensityImageFilter](https://itk.org/Doxygen/html/classitk_1_1RescaleIntensityImageFilter.html) to apply pixel-wise linear transformation to the intensity values of input image pixels. The linear transformation is defined by the user in terms of the minimum and maximum values that the output image should have.

The following equation gives the mapping of the intensity values:

![equation](http://mathurl.com/y7eppsyj.png)

Note that this repository demonstrates a simple usage of ITK's rescale filters. Similar examples can be found in [ITK examples Wiki](https://itk.org/Wiki/ITK/Examples/ImageProcessing/RescaleIntensityImageFilter).

The code also has other rescaling options through ITK's filters such as [Cast Image Filter](https://itk.org/Doxygen/html/classitk_1_1CastImageFilter.html), [Shift Scale Filter](https://itk.org/Doxygen/html/classitk_1_1ShiftScaleImageFilter.html) and [Normalise Filter](https://itk.org/Doxygen/html/classitk_1_1NormalizeImageFilter.html). But, these to be activated within the code by changing the ImageFileWriter's code: 

    writer->SetInput(rescaleFilter->GetOutput());    // change filter name 


