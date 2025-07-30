#include <renderer/RendererInterface.h>
virtual bool is_open(){
        
    }
    virtual void start_frame(){

    }
    virtual void finish_frame(){

    }

    // ----- Entities -----
    virtual void draw_agent(const AgentInterface& agent){

    }
    virtual void draw_projectile(const ProjectileInterface& projectile){

    }
    // virtual void draw_terrain(const Terrain& terrain) = 0;  // Comes later probably? Haven't thought through this.

    // ----- Debug visualization -----
    virtual void draw_bounding_box(const BoundingBox& bounding_box){

    }
    virtual void draw_text(const Text& text){

    }
