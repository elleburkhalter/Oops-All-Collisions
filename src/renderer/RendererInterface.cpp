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
        
    }
    RendererInterface::draw_projectile(const ProjectileInterface& projectile){
        Point newSpot = projectile.get_location();
    }
    // virtual void draw_terrain(const Terrain& terrain) = 0;  // Comes later probably? Haven't thought through this.

    // ----- Debug visualization -----
    RendererInterface::draw_bounding_box(const BoundingBox& bounding_box){

    }
    RendererInterface::draw_text(const Text& text){

    }
