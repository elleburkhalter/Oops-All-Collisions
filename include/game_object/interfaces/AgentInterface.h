#ifndef AGENTINTERFACE_H
#define AGENTINTERFACE_H

#include <game_object/interfaces/EntityInterface.h>

class AgentInterface
{
public:
    virtual ~AgentInterface() = default;

    // I originally had this for like path-finding or something, but this is just dangling now;
    // TODO: Add pathfinding eventually.
};

#endif //AGENTINTERFACE_H
