#include <vtf.h>

VTF_H::VTF_H(const char *fileAddress)
{
    this->Header = new tagVTFHEADER();

    ifstream *fileReader = new ifstream(fileAddress, ios::binary);
    fileReader->read((char *)this->Header, sizeof(tagVTFHEADER));

    fileReader->seekg(0, ios::end);
    this->FileSize = fileReader->tellg();

    int *UiBytesPerPixels = new int[27]
        {
            4, 4, 3, 3, 2, 1,
            2, 1, 1, 3, 3, 4,
            4, 1, 1, 1, 4, 2,
            2, 2, 1, 2, 2, 4,
            8, 8, 4
    };

    this->ImageSize = this->Header->Width * this->Header->Height * UiBytesPerPixels[this->Header->HighResImageFormat];
    int ThumbnailBufferSize = ((this->Header->LowResImageWidth + 3) / 4) * ((this->Header->LowResImageHeight + 3) / 4) * 8;

    switch (this->Header->HighResImageFormat)
    {
    case VTFImageFormat::IMAGE_FORMAT_DXT1:
    case VTFImageFormat::IMAGE_FORMAT_DXT1_ONEBITALPHA:
        this->ImageSize = ((this->Header->Width + 3) / 4) * ((this->Header->Height + 3) / 4) * 8;
        this->InternalFormat = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        break;

    case VTFImageFormat::IMAGE_FORMAT_DXT3:
    case VTFImageFormat::IMAGE_FORMAT_DXT5:
        this->ImageSize = ((this->Header->Width + 3) / 4) * ((this->Header->Height + 3) / 4) * 16;
        this->InternalFormat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        break;

    case VTFImageFormat::IMAGE_FORMAT_RGB888:
    case VTFImageFormat::IMAGE_FORMAT_RGB888_BLUESCREEN:
        this->InternalFormat = GL_COMPRESSED_RGB;
        break;

    case VTFImageFormat::IMAGE_FORMAT_RGBA8888:
        this->InternalFormat = GL_COMPRESSED_RGBA;
        break;

    default:
        // TODO: Доделать остальные форматы.
        return;
    }

    this->CompressedImage = new char[this->ImageSize];

    fileReader->seekg(this->FileSize - this->ImageSize, ios::beg);
    fileReader->read((char *)this->CompressedImage, this->ImageSize);
    fileReader->close();

    delete [] UiBytesPerPixels;
}

void VTF_H::OGL_CreateImage()
{
    GLuint texId;

    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    switch (this->Header->Flags)
    {
    case VTFImageFlags::TEXTUREFLAGS_CLAMPS:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        break;

    case VTFImageFlags::TEXTUREFLAGS_CLAMPT:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        break;
    }

    glCompressedTexImage2D(GL_TEXTURE_2D, 0, this->InternalFormat, this->Header->Width, this->Header->Height, 0, this->ImageSize, this->CompressedImage);
}
