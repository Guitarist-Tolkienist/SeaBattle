#include "Texture.h"
#include "Renderer.h"

int load_texture(textureT* texture, char* filename) {
    SDL_Surface* tmpSurface = IMG_Load(filename);

    if(tmpSurface == NULL) {
        fprintf(stderr, "Texture Error; Could not load image %s! SDL_image Error: %d", filename, IMG_GetError);
        return 0;
    } else {
        texture->texture = SDL_CreateTextureFromSurface(get_renderer(), tmpSurface);

        if (texture->texture == NULL) {
            fprintf(stderr, "Texture Error; Could not load image %s! SDL_image Error: %d", filename, IMG_GetError());
            SDL_FreeSurface(tmpSurface);
            return 0;
        } else {
            texture->width = tmpSurface->w;
            texture->height = tmpSurface->h;
        }

        SDL_FreeSurface(tmpSurface);
        return 1;
    }
}

void texture_init(textureT* texture, int x, int y, double angle, SDL_Point* center, SDL_Rect* cliprect, SDL_RendererFlip fliptype) {
    texture->x = x;
    texture->y = y;

    texture->angle = angle;

    texture->center = center;

    texture->cliprect = cliprect;

    texture->fliptype = fliptype;
}

void texture_renderer_XY_clip(textureT* texture, int x, int y, SDL_Rect* cliprect) {
    if (texture == NULL) {
        fprintf(stderr, "Warning: passed texture eas null \n");
        return;
    }
    texture->x = x;
    texture->y = y;
    texture->cliprect = cliprect;

    SDL_Rect quad = {texture->x, texture->y, texture->width, texture->height};

    if (texture->cliprect != NULL) {
        quad.w = texture->cliprect->w;
        quad.h = texture->cliprect->h;
    }

    SDL_RenderCopyEx(get_renderer(), texture->texture, texture->cliprect, &quad, texture->angle, texture->center, texture->fliptype);
}

void setupRect(SDL_Rect* rect, int x, int y, int w, int h) {
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
}

void init_tile_clip(SDL_Rect* tiles_rect, textureT* tilesTex, int w, int h, int iso_size) {
    int x = 0;
    int y = 0;

    texture_init(tilesTex, 0, 0, 0, NULL, NULL, SDL_FLIP_NONE);

    for (int i = 0; i < iso_size; i++) {
        setupRect(&tiles_rect[i], x, y, w, h);
        x += w;
    }
}