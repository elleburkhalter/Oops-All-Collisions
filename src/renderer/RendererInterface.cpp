#include <renderer/RendererInterface.h>
    //note, these functions will need to be run during the RaylibRenderer main update loop. 
    bool RendererInterface::is_open() const {
        return true;
    }
    void RendererInterface::start_frame(){

    }
    void RendererInterface::finish_frame(){

    }

    // ----- Entities -----
    void RendererInterface::draw_agent(const AgentInterface& agent){
        Point newSpot = agent.get_location();
        //radius set to 100 by default, we don't have a getradius function yet so that will need to be implemented
        DrawCircleGradient(newSpot.x, newSpot.y, 100, PINK, RED);
        
    }
    void RendererInterface::draw_projectile(const ProjectileInterface& projectile){
        Point newSpot = projectile.get_location();
        //radius set to 100 by default, we don't have a getradius function yet so that will need to be implemented
        DrawCircleGradient(newSpot.x, newSpot.y, 100, YELLOW, ORANGE);
    }
    // virtual void draw_terrain(const Terrain& terrain) = 0;  // Comes later probably? Haven't thought through this.

    // ----- Debug visualization -----
    void RendererInterface::draw_bounding_box(const BoundingBox& bounding_box){
        int width = bounding_box.max.x - bounding_box.min.x;
        int height = bounding_box.max.y - bounding_box.min.y;
        DrawRectangle(bounding_box.min.x, bounding_box.min.y, width, height, GREEN);

    }
    void RendererInterface::draw_text(const Text& text){

    }
