#ifndef SDLGAMEENGINE_TEXTURE_H
#define SDLGAMEENGINE_TEXTURE_H

#include "SoftWarePCH.h"
#include "GraphicMath.h"
#include "tgaimage.h"

enum class ETextureResourceType {
    Unknown = 0,
    TGA = 1,
    RenderTarget = 2,
};

class IRenderTexture
{
protected:
    int Width, Height;
    uint32* Buffer;
public:
    int GetWidth() const { return Width; }
    int GetHeight() const { return  Height; }
public:
    virtual bool Load(const char *Filename) = 0;
    virtual void UnLoad() = 0;
    virtual const FColor Sampler(int X, int Y) = 0;
};

class FTextureTGA : public IRenderTexture
{
public:
    bool Load(const char *Filename) override;
    void UnLoad() override;
    const FColor Sampler(int X, int Y) override;

private:
    TGAImage Img;
};

class FTextureFactory{
public:
    static IRenderTexture* LoadTexture(const char* Filename, ETextureResourceType TextureResourceType);
};

#endif