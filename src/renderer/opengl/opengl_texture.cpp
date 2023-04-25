#include "opengl_texture.h"
#include "opengl_headers.h"
#include "stb_image.h"
namespace SPG
{
    OpenGLTexture::OpenGLTexture(const TextureSpecs& specs)
    {
        _specs = specs;
        GLenum internalFormat;
        if(_specs.format == TextureFormat::RGB)
            internalFormat = GL_RGB;
        else if (_specs.format == TextureFormat::RGBA)
            internalFormat = GL_RGBA;
        _textureData = new uint32_t[_specs.width * _specs.height];
        glGenTextures(1, &_id);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _id);
        if(strcmp(specs.filepath, "") == 0)
        {
            if(_specs.data)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, _specs.width, _specs.height, 0, internalFormat, GL_UNSIGNED_BYTE, _specs.data);      
            }
            else
            {
                glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, _specs.width, _specs.height, 0, internalFormat, GL_UNSIGNED_BYTE, 0);      
            }
        }
        else
        {
            int32_t channelsInFile = 0;
            uint8_t* data = stbi_load(_specs.filepath, &_specs.width, &_specs.height, &channelsInFile, NULL);
            GLenum imageFormat = channelsInFile == 3? GL_RGB : GL_RGBA;
            glTexImage2D(GL_TEXTURE_2D, 0, imageFormat, _specs.width, _specs.height, 0, internalFormat, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    
    OpenGLTexture::~OpenGLTexture()
    {
		glDeleteTextures(1, &_id);
        delete _textureData;
    }
    
    void OpenGLTexture::Bind()
    {
        glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _id);
    }
    
    void OpenGLTexture::Unbind()
    {
		glBindTexture(GL_TEXTURE_2D, 0);
    }
    const uint32_t OpenGLTexture::GetID() const 
    {
        return _id;
    }
    
    void OpenGLTexture::UpdateData(void* data, int32_t width, int32_t height)
    {
        delete _textureData;
        _textureData = new uint32_t[width * height];
        glDeleteTextures(1, &_id);
        glGenTextures(1, &_id);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _id);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);      

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    
    const void* OpenGLTexture::GetTextureData()
    {
        glBindTexture(GL_TEXTURE_2D, _id);
        glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, _textureData);
        return _textureData;
    }
    
    const Vector2i OpenGLTexture::GetSize() const 
    {
        return _size;
    }
}