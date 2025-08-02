#include <renderer/RendererInterface.h>
    //note, these functions will need to be run during the RaylibRenderer main update loop. 
    RendererInterface::is_open(){
        
    }
    RendererInterface::start_frame(){

    }
    RendererInterface::finish_frame(){

    }

    // ----- Entities -----
    RendererInterface::draw_agent(const AgentInterface& agent){
        Point newSpot = agent.get_location();
        //radius set to 100 by default, we don't have a getradius function yet so that will need to be implemented
        DrawCircleGradient(newSpot.x, newSpot.y, 100, PINK, RED);
        
    }
    RendererInterface::draw_projectile(const ProjectileInterface& projectile){
        Point newSpot = projectile.get_location();
        //radius set to 100 by default, we don't have a getradius function yet so that will need to be implemented
        DrawCircleGradient(newSpot.x, newSpot.y, 100, YELLLOW, ORANGE);
    }
    // virtual void draw_terrain(const Terrain& terrain) = 0;  // Comes later probably? Haven't thought through this.

    // ----- Debug visualization -----
    RendererInterface::draw_bounding_box(const BoundingBox& bounding_box){
        int width = bounding_box.max.x - bounding_box.min.x;
        int height = bounding_box.max.y - bounding_box.min.y;
        DrawRectangle(bounding_box.min.x, bounding_box.min.y, width, height, GREEN);

    }
    RendererInterface::draw_text(const Text& text){

    }
