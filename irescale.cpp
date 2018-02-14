#include "itkImage.h"
#include "itkImageFileReader.h"

#include "itkCastImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkNormalizeImageFilter.h"
#include "itkImageFileWriter.h"
#include "itkIntensityWindowingImageFilter.h"
#include "itkImageDuplicator.h"
#include "itkImageIterator.h"

int main(int argc, char * argv[])
{
	if (argc < 2)
	{
		std::cerr << "Usage: " << std::endl;
		std::cerr << argv[0] << "   inputImageFile " << std::endl;
		return EXIT_FAILURE;
	}

	typedef   double   InputPixelType;
	typedef   unsigned char            OutputPixelType;

	typedef itk::Image< InputPixelType, 3 >   InputImageType;
	typedef itk::Image< OutputPixelType, 3 >   OutputImageType;
	// Software Guide : EndCodeSnippet
	typedef itk::ImageFileReader< InputImageType >  ReaderType;
	typedef itk::ImageFileReader< InputImageType >  ReaderType;

	// Different Rescalers available
	typedef itk::CastImageFilter<InputImageType, OutputImageType >  CastFilterType;
	typedef itk::RescaleIntensityImageFilter<InputImageType, OutputImageType >  RescaleFilterType;
	typedef itk::ShiftScaleImageFilter<InputImageType, OutputImageType >  ShiftScaleFilterType;
	typedef itk::NormalizeImageFilter<InputImageType, OutputImageType >  NormalizeFilterType;
	

	ReaderType::Pointer reader = ReaderType::New();
	 
	CastFilterType::Pointer       castFilter = CastFilterType::New();
	RescaleFilterType::Pointer    rescaleFilter = RescaleFilterType::New();
	ShiftScaleFilterType::Pointer shiftFilter = ShiftScaleFilterType::New();
	NormalizeFilterType::Pointer  normalizeFilter = NormalizeFilterType::New();
	 
	reader->SetFileName(argv[1]);
	double offset = atof(argv[3]); 

	InputImageType::Pointer input_image = reader->GetOutput(); 
	InputImageType::RegionType region = input_image->GetLargestPossibleRegion();

	int size_x = region.GetSize()[0];
	int size_y = region.GetSize()[1];
	int size_z = region.GetSize()[2];
	
	InputImageType::IndexType pixelIndex;
	for (int x = 0; x < size_x; x++)
	{
		for (int y = 0; y < size_y; y++)
		{
			for (int z = 0; z < size_z; z++) {

				pixelIndex[0] = x;      // x position of the pixel
				pixelIndex[1] = y;      // y position of the pixel
				pixelIndex[2] = z;

				int pixelValue = input_image->GetPixel(pixelIndex); 
				input_image->SetPixel(pixelIndex, pixelValue+offset);
			}
		}
	}


	castFilter->SetInput(input_image);
	shiftFilter->SetInput(input_image);
	rescaleFilter->SetInput(input_image);
	normalizeFilter->SetInput(input_image);
	
	rescaleFilter->SetOutputMinimum(0);
	rescaleFilter->SetOutputMaximum(255);
	
	shiftFilter->SetScale(255);
	shiftFilter->SetShift(32770);
	
	castFilter->Update();
	shiftFilter->Update();
	rescaleFilter->Update();
	normalizeFilter->Update();

	typedef itk::IntensityWindowingImageFilter <InputImageType, OutputImageType> IntensityWindowingImageFilterType;
	IntensityWindowingImageFilterType::Pointer filter = IntensityWindowingImageFilterType::New();
	filter->SetInput(reader->GetOutput());
	filter->SetWindowMinimum(0);
	filter->SetWindowMaximum(65354);
	filter->SetOutputMinimum(0);
	filter->SetOutputMaximum(255);
	filter->Update();
	
	typedef  itk::ImageFileWriter< OutputImageType  > WriterType;
	WriterType::Pointer writer = WriterType::New();
	char* outputFilename = argv[2]; 
	writer->SetFileName(outputFilename);
	writer->SetInput(rescaleFilter->GetOutput());
	writer->Update();
}