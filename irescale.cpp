#include "itkImage.h"
#include "itkImageFileReader.h"

#include "itkCastImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkNormalizeImageFilter.h"
#include "itkImageFileWriter.h"
#include "itkIntensityWindowingImageFilter.h"
#include "itkImageDuplicator.h"
#include "itkImageIterator.h"



using namespace std;
int main(int argc, char * argv[])
{
	char* input_f1, *output_f; 
	int input_f2=1;		// by default use itkRescaleIntensityImageFilter
	
	double offset = 0;
	bool foundArgs1 = false, foundArgs2 = false, foundArgs3 = false;

	

	if (argc >= 1)
	{
		for (int i = 1; i < argc; i++) {
			if (i + 1 != argc) {
				if (string(argv[i]) == "-i") {
					input_f1 = argv[i + 1];
					foundArgs1 = true;
				}

				else if (string(argv[i]) == "-o") {
					output_f = argv[i + 1];
					foundArgs2 = true;
				}

				else if (string(argv[i]) == "-r") {
					input_f2 = atoi(argv[i + 1]);
					foundArgs3 = true;
				}
				
	

			}

		}
	}

	if (!(foundArgs1 && foundArgs2))
	{
		cerr << "Cheeck your parameters\n\nUsage:"
			"\nRescales 3D images to intensity range 0-255"
			"\n(Mandatory)\n\t-i <img> \n\t-o <output image>\n\n(Optional)\n\t-s <which rescaler 1-4>\n\n\tAvailable Rescalers:"
			"\n\t1 = itk::itkRescaleIntensityImageFilter (0-255)"
			"\n\t2 = itk::CastImageFilter (Window=0-255, please within modify code)"
			"\n\t3 = itk::ShiftScaleImageFilter (scale=1, shift=0)"
			"\n\t4 = itk::NormalizeImageFilter\n" << endl;
			

		exit(1);
	}
	else
	{


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

		reader->SetFileName(input_f1);
		

		InputImageType::Pointer input_image = reader->GetOutput();
		

		castFilter->SetInput(input_image);
		shiftFilter->SetInput(input_image);
		rescaleFilter->SetInput(input_image);
		normalizeFilter->SetInput(input_image);

		rescaleFilter->SetOutputMinimum(0);
		rescaleFilter->SetOutputMaximum(255);

		shiftFilter->SetScale(1);
		shiftFilter->SetShift(0);

		castFilter->Update();
		shiftFilter->Update();
		rescaleFilter->Update();
		normalizeFilter->Update();

		

		typedef  itk::ImageFileWriter< OutputImageType  > WriterType;
		WriterType::Pointer writer = WriterType::New();
		
		writer->SetFileName(output_f);

		switch (input_f2)
		{
			case 1: 
				writer->SetInput(rescaleFilter->GetOutput());; 
				break; 

			case 2: 
				writer->SetInput(castFilter->GetOutput());;
				break;

			case 3: 
				writer->SetInput(shiftFilter->GetOutput());;
				break;

			case 4: 
				writer->SetInput(normalizeFilter->GetOutput());;
				break;
		}
		
		writer->Update();
	}
}