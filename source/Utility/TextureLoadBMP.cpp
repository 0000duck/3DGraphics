#include "StdAfx.h"
#include "Primitives/Texture.h"
#include "TextureLoadBMP.h"

#if 0
bool CTextureLoadBMP::LoadTexture( const CString &filename, CTexture *texture )
{
	// Open file
	FILE *fptr;
	CStringA filenameA( filename );
	if ( fopen_s( &fptr, filenameA, "r" ) != 0 )
	{
		return false;
	}

	// Read and check the header
	HEADER header;
	if ( fread( &header, sizeof(HEADER), 1, fptr ) != 1 )
	{
		fclose(fptr);
		return false;
	}

	// Read and check the information header
	INFOHEADER infoheader;
	if ( fread( &infoheader, sizeof(INFOHEADER), 1, fptr) != 1)
	{
		fclose(fptr);
		return false;
	}

	// Read the lookup table if there is one
	bool gotindex = false;
	COLOURINDEX colourindex[256];
	for ( unsigned int i = 0; i < 255; i++ )
	{
		colourindex[i].r = rand() % 256;
		colourindex[i].g = rand() % 256;
		colourindex[i].b = rand() % 256;
		colourindex[i].junk = rand() % 256;
	}
	if ( infoheader.ncolours > 0 )
	{
		for ( unsigned int i = 0; i < infoheader.ncolours; i++ )
		{
			if ( fread( &colourindex[i].b, sizeof(unsigned char), 1, fptr ) != 1 )
			{
				fclose(fptr);
				return false;
			}
			if ( fread( &colourindex[i].g, sizeof(unsigned char), 1, fptr ) != 1 )
			{
				fclose(fptr);
				return false;
			}
			if ( fread( &colourindex[i].r, sizeof(unsigned char), 1, fptr ) != 1 )
			{
				fclose(fptr);
				return false;
			}
			if ( fread( &colourindex[i].junk, sizeof(unsigned char), 1, fptr ) != 1 )
			{
				fclose(fptr);
				return false;
			}
		}
		gotindex = true;
	}

	// Seek to the start of the image data
	fseek( fptr, header.offset, SEEK_SET );

	// Read the image
	unsigned int width = (unsigned int) infoheader.width;
	unsigned int height = (unsigned int) infoheader.height;
	texture->SetDimensions( width, height );
	unsigned char grey, r, g, b;
	CColor color;
	
	for ( unsigned int j = 0; j < height; j++ )
	{
		for ( unsigned int i = 0; i < width; i++ )
		{
	        switch (infoheader.bits)
			{
				case 1:
					break;
				case 4:
					break;
				case 8:
					if ( fread( &grey, sizeof(unsigned char), 1, fptr ) != 1 )
					{
						fclose(fptr);
						return false;
					}
					if (gotindex)
					{
						color.r = colourindex[grey].r / 255.0f;
						color.g = colourindex[grey].g / 255.0f;
						color.b = colourindex[grey].b / 255.0f;
					}
					else
					{
						color.r = grey / 255.0f;
						color.g = grey / 255.0f;
						color.b = grey / 255.0f;
					}
					break;
				case 24:
					if ( fread( &b, sizeof(unsigned char), 1, fptr ) != 1 )
					{
						fclose(fptr);
						return false;
					}
					if ( fread( &g, sizeof(unsigned char), 1, fptr ) != 1 )
					{
						fclose(fptr);
						return false;
					}
					if ( fread( &r, sizeof(unsigned char), 1, fptr ) != 1 )
					{
						fclose(fptr);
						return false;
					}
					color.r = r / 255.0f;
					color.g = g / 255.0f;
					color.b = b / 255.0f;
					break;
			} // switch

			// Set texel color
			texture->SetTexel( i, j, color );
      } // i
   } // j

   fclose(fptr);
   return true;
}

#endif

bool CTextureLoadBMP::LoadTexture( const CString &filename, CTexture *texture )
{
    // Try opening the file; use "rb" mode to read this *binary* file
	FILE *fp;
	CStringA filenameA( filename );
    if ( fopen_s( &fp, filenameA, "rb" ) != 0 )
	{
		return false;
	}

    // Read the file header and any following bitmap information...
	BITMAPFILEHEADER header;
    if ( fread( &header, sizeof(BITMAPFILEHEADER), 1, fp) < 1 )
    {
		// Couldn't read the file header
		fclose(fp);
        return false;
    }

	// Check for BM reversed...
    if ( header.bfType != 'MB')
    {
        // Not a bitmap file
        fclose(fp);
        return false;
	}

	BITMAPINFO *info;
    int infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
    if ( (info = (BITMAPINFO *)malloc(infosize)) == NULL )
    {
        // Couldn't allocate memory for bitmap info
        fclose(fp);
        return false;
    }

    if ( (int) fread( info, 1, infosize, fp ) < infosize )
    {
        // Couldn't read the bitmap header
        free(info);
        fclose(fp);
        return false;
    }

    // Now that we have all the header info read in, allocate memory for
    // the bitmap and read *it* in...
	int bitsize;
	if ( (bitsize = info->bmiHeader.biSizeImage) == 0 )
	{
        bitsize = (info->bmiHeader.biWidth * info->bmiHeader.biBitCount + 7) / 8 * abs(info->bmiHeader.biHeight);
	}

	void *bits;
	if ( (bits = malloc(bitsize)) == NULL )
    {
        // Couldn't allocate memory
        free(info);
        fclose(fp);
        return false;
    }

    if ( (int) fread(bits, 1, bitsize, fp) < bitsize )
	{
        // Couldn't read bitmap
        free(info);
        free(bits);
        fclose(fp);
        return false;
    }

	// OK, everything went fine
	unsigned int width = info->bmiHeader.biWidth;
	unsigned int height = info->bmiHeader.biHeight;
	texture->SetDimensions( width, height );
	CColor color;
	unsigned bitIdx = 0;
	unsigned char *bitChars = (unsigned char *)bits;
	for ( unsigned int y = 0; y < height; y++ )
	{
		for ( unsigned int x = 0; x < width; x++ )
		{
			color.b = bitChars[bitIdx++] / 255.0f;
			color.g = bitChars[bitIdx++] / 255.0f;
			color.r = bitChars[bitIdx++] / 255.0f;
			texture->SetTexel( x, y, color );
		}
	}
	
	free(info);
    free(bits);
    fclose(fp);
    return true;
}
