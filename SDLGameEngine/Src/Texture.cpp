//
// Created by chenyifei on 2022/2/28.
//

#include "Texture.h"

bool FTextureTGA::Load(const char *Filename) {
    bool bLoad = Img.read_tga_file(Filename);
    if (bLoad) {
        Width = Img.get_width();
        Height = Img.get_height();
    }
    return bLoad;
}

void FTextureTGA::UnLoad() {

}

const FColor FTextureTGA::Sampler(int X, int Y) {
    TGAColor c = Img.get(X, Y);
    return FColor(c[2], c[1], c[0], c[3]);
}

IRenderTexture* FTextureFactory::LoadTexture(const char *Filename, ETextureResourceType TextureResourceType) {
    IRenderTexture* Texture = nullptr;
    if (TextureResourceType == ETextureResourceType::Unknown) {
        std::cerr << "Unknown Texture Type" << std::endl;
    }else if (TextureResourceType == ETextureResourceType::TGA) {
        Texture = new FTextureTGA();
        bool bLoad = Texture->Load(Filename);
        if (!bLoad) {
            free(Texture);
            Texture = nullptr;
        }
    }
    return Texture;
}
