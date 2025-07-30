
#ifndef ENTITYABC_H
#define ENTITYABC_H

#include "raylib.h"
#include <collision/ColliderInterface.h>
#include <collision/ColliderFlags.h>

class EntityABC
{
private:
    /* data */
    Rectangle inputRec;
    Rectangle outputRec;
    Vector2 origin;
    float rotation = 0;
    ColliderInterface& collider;
public:
    //explicit EntityABC(ColliderInterface& collider): collider(collider) {}
    int health;
    Texture2D sprite = LoadTexture("graphics/Guy1.png");
    EntityABC(float startingX, float startingY, int startingHealth) : collider(collider)
    {
        health = startingHealth;
        inputRec = { 0.0f, 0.0f, (float)sprite.width, (float)sprite.height };
        outputRec = { startingX, startingY, sprite.width*2.0f, sprite.height*2.0f };
        origin = {(float)sprite.width, (float)sprite.height};
    }
    void changePos(int xOffset, int yOffset){
        outputRec.x += xOffset;
        outputRec.y += yOffset;
    }
    void SetPos(int x, int y){
        outputRec.x = x;
        outputRec.y = y;
    }
    void playerControl()//only run this function if you want it playerControlled
    {
        if (IsKeyDown(KEY_RIGHT))
        {
            rotation = 0;
            changePos(2,0);
        } 
        if (IsKeyDown(KEY_LEFT))
        {
            rotation = 180;
            changePos(-2,0);
        } 
        if (IsKeyDown(KEY_UP))
        {
            rotation = -90;
            changePos(0,-2);
        } 
        if (IsKeyDown(KEY_DOWN))
        {
            rotation = 90;
            changePos(0,2);
        }
         
    }
    void drawEntity(){
        DrawTexturePro(sprite, inputRec, outputRec, origin, rotation, WHITE);
    }
    ~EntityABC()
    {
        UnloadTexture(sprite);
    }

    //virtual CollisionCode resolve_collision_with(EntityABC& other) = 0;
    //[[nodiscard]] Point get_centroid() const { return collider.get_centroid(); };
    //virtual void move(double dt) = 0;

};

#endif //ENTITYABC_H
