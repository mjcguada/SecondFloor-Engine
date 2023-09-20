#pragma once


class Texture2D 
{
public:
	Texture2D(unsigned int width, unsigned int height, unsigned char* data);
	void Bind() const;

	// texture image dimensions
	unsigned int Width = 0, Height = 0;
	// texture Format
	unsigned int Internal_Format; // format of texture object
	unsigned int Image_Format; // format of loaded image
	// texture configuration
	unsigned int Wrap_S; // wrapping mode on S axis
	unsigned int Wrap_T; // wrapping mode on T axis
	unsigned int Filter_Min; // filtering mode if texture pixels < screen pixels
	unsigned int Filter_Max; // filtering mode if texture pixels > screen pixels

private:
	unsigned char* imageData;

	// holds the ID of the texture object, used for all texture operations to reference to this particular texture
	unsigned int ID;
};
