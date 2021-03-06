//
// GameEngine - A cross platform game engine made using OpenGL and c++
// Copyright (C) 2016-2020 Matan Keren <xmakerenx@gmail.com>
//
// This file is part of GameEngine.
//
// GameEngine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// GameEngine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with GameEngine.  If not, see <http://www.gnu.org/licenses/>.
//

#include "AssetManager.h"
#include "MeshGenerator.h"
#include <sstream>

TextureInfo AssetManager::s_noTextureInfo(0,0);

//-----------------------------------------------------------------------------
// Name : AssetManager (constructor)
//-----------------------------------------------------------------------------
AssetManager::AssetManager()
{
}

//-----------------------------------------------------------------------------
// Name : AssetManager (destructor)
//-----------------------------------------------------------------------------
AssetManager::~AssetManager()
{

}

//-----------------------------------------------------------------------------
// Name : getTexture
//-----------------------------------------------------------------------------
GLuint AssetManager::getTexture(const std::string& filePath)
{
    // check if the texture is already loaded
    if (m_textureCache.count(filePath) != 0)
    {
        // return textrue id(name)
        return m_textureCache[filePath];
    }
    // else load the textrue
    else
    {
        std::string suffix;
        std::stringstream s(filePath);
        // gets the file name
        std::getline(s, suffix, '.');
        // gets the file suffix
        std::getline(s, suffix, '.');
        // load the texutre using the appropriate method
        if (suffix == "png")
            return loadPng(filePath);
        if (suffix == "jpg")
            return loadJPEG(filePath);
        if (suffix == "bmp")
            return loadBMP(filePath);

        std::cout << suffix << " is not a supported texture type\n";
        return 0;
    }
}

//-----------------------------------------------------------------------------
// Name : getTextureInfo
//-----------------------------------------------------------------------------
const TextureInfo& AssetManager::getTextureInfo(GLuint textureName)
{
    if (m_textureInfoCache.count(textureName) != 0)
        return m_textureInfoCache[textureName];
    else
        return s_noTextureInfo;
}

//-----------------------------------------------------------------------------
// Name : loadPng
//-----------------------------------------------------------------------------
GLuint AssetManager::loadPng(const std::string &filePath)
{
    int number_of_passes = 0;
    unsigned int format = 0;

    // header for testing if it is a png
    png_byte header[8];

    // open file as binary
    FILE* fp = fopen(filePath.c_str(), "rb");
    if (!fp)
    {
        std::cout << "Failed to open " << filePath << "\n";
        return 0;
    }

    // read header
    fread(header, 1, 8, fp);

    // test if png
    int is_png = !png_sig_cmp(header, 0, 8);
    if (!is_png)
    {
        fclose(fp);
        std::cout<<"The given file is not a valid png file\n";
        return 0;
    }

    // create png struct
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr,nullptr,nullptr);
    if (!png_ptr)
    {
        fclose(fp);
        std::cout << "Failed to create png struct\n";
        return 0;
    }

    // create png info struct
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        png_destroy_read_struct(&png_ptr, (png_infopp) nullptr, (png_infopp) nullptr);
        fclose(fp);
        return 0;
    }

    // create png info struct
    png_infop end_info = png_create_info_struct(png_ptr);
    if (!end_info)
    {
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)nullptr);
        fclose(fp);
        std::cout << "Failed to create png info struct\n";
        return 0;
    }

    // png error stuff, not sure libpng man suggests this.
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
        std::cout << "png error stuff\n";
        return 0;
    }

    // init png reading
    png_init_io(png_ptr, fp);

    // let libpng know you already read the first 8 bytes
    png_set_sig_bytes(png_ptr, 8);

    // read al the info up to the image data
    png_read_info(png_ptr, info_ptr);

    // variables to pass to get info
    int bit_depth, color_type;
    png_uint_32 width, height;

    number_of_passes = png_set_interlace_handling(png_ptr);

    //get info about png
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, nullptr, nullptr, nullptr);

    // set the correct image format
    if (color_type == PNG_COLOR_TYPE_RGB)
        format = GL_RGB;
    if (color_type == PNG_COLOR_TYPE_RGBA)
        format = GL_RGBA;

    // Update the png info struct
    png_read_update_info(png_ptr, info_ptr);

    // Row size in bytes
    int rowBytes = png_get_rowbytes(png_ptr, info_ptr);

    // Allocate the image_data as a big block, to be given to opengl
    png_byte* image_data = new png_byte[rowBytes * height];
    if (!image_data)
    {
        //clean up memory and close stuff
        std::cout << "Fail to allocate buffer for image\n";
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
        return 0;
    }

    // row_pointers is for the pointing to image_data for reading the png with libpng
    png_bytep* row_pointers = new png_bytep[height];
    if (!row_pointers)
    {
        //clean up memory and close stuff
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        delete[] image_data;
        fclose(fp);
        return 0;
    }

    // set the individual row_pointers to point at the correct offsets of image_data
    for (int i = 0; i < height; i++)
        row_pointers[height - 1 - i] = image_data + i * rowBytes;

    // read the png into image data through row_pointers
    png_read_image(png_ptr, row_pointers);


    // now generate the OpenGL texture
    GLuint textureID = createTexture(width, height, format, image_data);

    //clean up memory and close stuff
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    delete[] image_data;
    delete[] row_pointers;
    fclose(fp);

    // cached the loaded texture
    m_textureCache.insert(std::pair<std::string, GLuint>(filePath,textureID));
    m_textureInfoCache.insert(std::pair<GLuint, TextureInfo>(textureID, TextureInfo(width, height)));
    return textureID;
}

//-----------------------------------------------------------------------------
// Name : loadBMP
//-----------------------------------------------------------------------------
GLuint AssetManager::loadBMP(const std::string &filePath)
{
    // Each BMP file begins by a 54-bytes header
    unsigned char header[54];
    // Position in the file where the actual data begins
    unsigned int dataPos;
    unsigned int width, height;
    unsigned int imageSize;
    unsigned char* data;

    // open file
    std::ifstream file;
    file.open(filePath, std::ifstream::binary);
    if (!file.is_open())
    {
        std::cout << "Failed to open "<< filePath << "\n";
        return 0;
    }

    file.read((char*)header, 54);
    if (!file)
    {
        file.close();
        std::cout << "Not a correct BMP file\n";
        return 0;
    }

    if (header[0] != 'B' || header[1] != 'M' )
    {
        file.close();
        std::cout << "Not a correct BMP file\n";
        return 0;
    }

    if (header[28] != 24 && header[28] != 32)
    {
        file.close();
        std::cout << "Invalid file format. only 24 or 32 are supported \n";
        return 0;
    }

    // Read ints from the byte array
    dataPos   =   *(int*)&(header[0x0A]);
    imageSize =   *(int*)&(header[0x22]);
    width     =   *(int*)&(header[0x12]);
    height    =   *(int*)&(header[0x16]);
    unsigned int bitsPerPixel = header[28];
    //width     =   header[18] + (header[19] << 8);
    //height    =   header[22] + (header[23] << 8);
    //dataPos   = header[10] + (header[11] << 8);
    imageSize = ((width * bitsPerPixel + 31) /32)* 4 * height;


    // Some BMP files are misformatted, guess missing information
    if (imageSize == 0)
        imageSize = width * height * 3; // one byte per color RGB
    if (dataPos == 0)
        dataPos = 54;

    // create a buffer
    data = new unsigned char[imageSize];

    if (!data)
    {
        //clean up memory and close stuff
        std::cout << "Fail to allocate buffer for image\n";
        file.close();
        return 0;
    }

    // read the actual data from the file into the buffer
    file.seekg(dataPos, std::ifstream::beg);
    file.read((char*)data, imageSize);

    GLuint textureID = createTexture(width, height, GL_BGR, data);

    // clean up memory and close stuff
    file.close();
    delete[] data;

    // cache the loaded texture
    m_textureCache.insert(std::pair<std::string, GLuint>(filePath,textureID));
    m_textureInfoCache.insert(std::pair<GLuint, TextureInfo>(textureID, TextureInfo(width, height)));

    return textureID;
}

//-----------------------------------------------------------------------------
// Name : loadJPEG
//-----------------------------------------------------------------------------
GLuint AssetManager::loadJPEG(const std::string &filePath)
{
    unsigned int width, height;
    int channels; //  3 =>RGB   4 =>RGBA
    unsigned int format = 0;

    unsigned char * rowptr[1];    // pointer to an array
    unsigned char * jdata;        // data for the image
    struct jpeg_decompress_struct info; //for our jpeg info
    struct jpeg_error_mgr err;          //the error handler

    FILE* file = fopen(filePath.c_str(), "rb");  //open the file

    info.err = jpeg_std_error(&err);
    jpeg_create_decompress(&info);   //fills info structure

    //if the jpeg file doesn't load
    if(!file)
    {
        std::cout << "Falied to open " << filePath << "\n";
        return 0;
    }

    jpeg_stdio_src(&info, file);
    jpeg_read_header(&info, TRUE);

    //TODO: check jpeg size before starting decompressing
    jpeg_start_decompress(&info);

    width = info.output_width;
    height = info.output_height;

    channels = info.num_components;
    // set texture type
    if (channels < 3)
    {
        std::cout << "jpegs with less than 3 channels are not supported\n";
        return 0;
    }

    format = GL_RGB;
    if(channels == 4) format = GL_RGBA;

    unsigned long data_size = width * height * info.output_components;
    unsigned int rowStride = channels * info.output_width;

    // read scanlines one at a time into jdata[] array
    jdata = new unsigned char[data_size];
    while (info.output_scanline < info.output_height)
    {

        // point rowptr to the current row to be filled with data
        // libjpeg loads from end to start to rowptr starts from the end of jdata
        //          start +         end        -  current line  - line(to get to the start of the line)
        rowptr[0] = jdata + rowStride * height - rowStride * info.output_scanline - rowStride;

        // load data to the current line
        jpeg_read_scanlines(&info, rowptr, 1);

    }

    jpeg_finish_decompress(&info);
    GLuint textureID = createTexture(width, height, format, jdata);

    // free resources
    jpeg_destroy_decompress(&info);
    fclose(file);
    delete[] jdata;

    // cache the loaded texture
    m_textureCache.insert(std::pair<std::string, GLuint>(filePath,textureID));
    m_textureInfoCache.insert(std::pair<GLuint, TextureInfo>(textureID, TextureInfo(width, height)));

    return textureID;
}

//-----------------------------------------------------------------------------
// Name : createTexture
//-----------------------------------------------------------------------------
GLuint AssetManager::createTexture(GLsizei width, GLsizei height, GLenum format, unsigned char *data)
{
    // generate the OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);
    
    if (textureID != 0)
    {
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, (GLvoid*)data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
    else
        std::cout << "Failed to generate a texture name\n";
    
    return textureID;
}

//-----------------------------------------------------------------------------
// Name : getMesh
//-----------------------------------------------------------------------------
Mesh* AssetManager::getMesh(const std::string& meshPath)
{
    // check if the texture is already loaded
    if (m_meshCache.count(meshPath) != 0)
    {
        // return textrue id(name)
        return &m_meshCache[meshPath];
    }
    // else load the textrue
    else
    {
        std::string suffix;
        std::stringstream s(meshPath);
        // gets the file name
        std::getline(s, suffix, '.');
        // gets the file suffix
        std::getline(s, suffix, '.');
        Mesh* ret = nullptr;
        bool knowSuffix = false;
        // load the texutre using the appropriate method
        if (suffix == "obj")
        {
            ret = loadObjMesh(meshPath);
            knowSuffix = true;
        }
        if (suffix == "fbx")
        {
            #ifdef FBX
            ret = loadFBXMesh(meshPath);
            knowSuffix = true;
            #endif
        }
        if (suffix == "gen")
        {
            ret = generateMesh(meshPath);
            knowSuffix = true;
        }

        if (!knowSuffix)
            std::cout << suffix << " is not a supported mesh type\n";
        
        if (ret != nullptr)
            return ret;
        else
            return getMesh("cube.gen");
    }
}

//-----------------------------------------------------------------------------
// Name : loadObjMesh
//-----------------------------------------------------------------------------
Mesh* AssetManager::loadObjMesh(const std::string& meshPath)
{
    Model model(meshPath);
    std::ifstream in;
    
    in.open(meshPath);
    
    if (!in.is_open())
    {
        std::cout << "Failed to open "<< meshPath << "\n";
        return nullptr;
    }
    
    objFirstPass(*this, in, model);
    
    // return to start of file
    in.clear();
    in.seekg(0, std::ios::beg);
    
    objSecondPass(in, model);
    
    // convert obj groups to subMeshes
    std::vector<SubMesh> subMeshes;
    std::vector<GLuint> meshMaterials;
    for (Group& g : model.groups)
    {
        // ignore empty groups
        if (g.vertices.size() != 0)
        {
            subMeshes.emplace_back(g.vertices, g.indices);
            if (g.material != -1)
                meshMaterials.push_back(g.material);
        }
    }
    
    m_meshCache.insert(std::pair<std::string, Mesh>(meshPath, 
    Mesh(std::move(subMeshes), std::move(meshMaterials),std::vector<std::string>())) );
    
    return &m_meshCache[meshPath];
}

#ifdef FBX
//-----------------------------------------------------------------------------
// Name : loadFBXMesh
//-----------------------------------------------------------------------------
Mesh *AssetManager::loadFBXMesh(const std::string &meshPath)
{
    std::vector<GLuint> meshMaterials;
    std::vector<SubMesh> subMeshes;
    if (m_fbxLoader.LoadMesh(meshPath, subMeshes))
    {
        m_meshCache.insert(std::pair<std::string, Mesh>(meshPath,
                        Mesh(std::move(subMeshes), std::move(meshMaterials), std::vector<std::string>())) );

        return &m_meshCache[meshPath];
    }
    else
        return nullptr;
}
#endif

//-----------------------------------------------------------------------------
// Name : generateMesh
//-----------------------------------------------------------------------------
Mesh*  AssetManager::generateMesh(const std::string& meshString)
{
    if (meshString == "board.gen")
    {
        m_meshCache.insert(std::pair<std::string, Mesh>(meshString, MeshGenerator::createBoardMesh(*this, glm::vec2(10.0f, 10.0f))));
        
        return &m_meshCache[meshString];
    }
    
    if (meshString == "square.gen")
    {
        m_meshCache.insert(std::pair<std::string, Mesh>(meshString, MeshGenerator::createSquareMesh(*this, glm::vec2(10.0f, 10.0f))));
        
        return &m_meshCache[meshString];
    }
    
    if (meshString == "skybox.gen")
    {
        m_meshCache.insert(std::pair<std::string, Mesh>(meshString, MeshGenerator::createSkyBoxMesh()));
        
        return &m_meshCache[meshString];
    }
    
    if (meshString == "cube.gen")
    {
        m_meshCache.insert(std::pair<std::string, Mesh>(meshString, MeshGenerator::createCubeMesh()));
        
        return &m_meshCache[meshString];
    }
    
    return nullptr;
}

//-----------------------------------------------------------------------------
// Name : getShader
//-----------------------------------------------------------------------------
Shader* AssetManager::getShader(const std::string& shaderPath)
{
	// check if the shader is loaded in the cache
    if (m_shaderCache.count(shaderPath) != 0)
    {
        // return textrue id(name)
        return m_shaderCache[shaderPath];
    }

    // no such shader in cache , adding a new one 
    std::string vertexShader = shaderPath + ".vs";
    std::string fragmentShader = shaderPath + ".frag";
    
    Shader* shader = new Shader(vertexShader.c_str(), fragmentShader.c_str());
    
    m_shaderCache.insert(std::pair<std::string, Shader*>(shaderPath,shader));
    
    return shader;
}

//-----------------------------------------------------------------------------
// Name : getMaterialIndex
//-----------------------------------------------------------------------------
int AssetManager::getMaterialIndex(const Material& mat)
{
    for (unsigned int i = 0; i < m_materials.size(); i++)
    {
        if (m_materials[i] == mat)
            return i;
    }
    
    // no matching material found , adding a new one
    m_materials.push_back(mat);
    
    return m_materials.size() - 1;
}

//-----------------------------------------------------------------------------
// Name : getMaterial
//-----------------------------------------------------------------------------
Material& AssetManager::getMaterial(int materialIndex)
{
    return m_materials[materialIndex];
}

//-----------------------------------------------------------------------------
// Name : getAttribute
// Desc : returns the attribute index that correlate to the given properties
//-----------------------------------------------------------------------------
int AssetManager::getAttribute(const std::string& texPath, GLint wrapMode, const Material& mat,const std::string& shaderPath)
{
    unsigned int  matIndex = getMaterialIndex(mat);
    return getAttribute(texPath, wrapMode, matIndex, shaderPath);
}

//-----------------------------------------------------------------------------
// Name : getAttribute
// Desc : returns the attribute index that correlate to the given properties
// ****   Material property is given by index
//-----------------------------------------------------------------------------
int AssetManager::getAttribute(const std::string &texPath, GLint wrapMode, GLuint matIndex, const std::string &shaderPath)
{
    Attribute attrib = {texPath, wrapMode, matIndex, shaderPath};


    for (unsigned int i = 0; i < m_attributes.size(); i++)
    {
        if (attrib == m_attributes[i])
            return i;
    }

    // no matching Attribute found , adding a new one
    // TODO: to test if it is smart to force load unloaded attributes
    if (texPath != "")
        getTexture(texPath);
    if (shaderPath != "")
        getShader(shaderPath);

    m_attributes.push_back(attrib);

    return m_attributes.size() - 1;
}

//-----------------------------------------------------------------------------
// Name : getFont
//-----------------------------------------------------------------------------
mkFont* AssetManager::getFont(std::string fontName, int fontSize, bool isPath/* = false*/)
{
    std::string fontPath;
    if (isPath)
        fontPath = fontName;
    else
        fontPath = mkFont::getFontPath(fontName);


    std::string fontFileName = mkFont::getFontNameFromPath(fontPath);
    std::stringstream fontNameStream;
    fontNameStream << fontFileName << fontSize;

    // check if the font is loaded in the cache
    if (m_fontCache.count(fontNameStream.str()) != 0)
    {
        return &m_fontCache[fontNameStream.str()];
    }
    else
    {
        mkFont newFont(fontPath, true);
        if (newFont.init(fontSize, 96, 96) == 0)
        {
            m_fontCache.insert(std::pair<std::string, mkFont>(fontNameStream.str(), std::move(newFont)));
            return &m_fontCache[fontNameStream.str()];
        }
        else
            return nullptr;
    }
}
//-----------------------------------------------------------------------------
// Name : getAttributeVector
//-----------------------------------------------------------------------------
const std::vector<Attribute>& AssetManager::getAttributeVector()
{
    return m_attributes;
}
