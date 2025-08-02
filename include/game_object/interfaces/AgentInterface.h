#ifndef AGENTINTERFACE_H
#define AGENTINTERFACE_H

#include <game_object/interfaces/EntityInterface.h>

class AgentInterface : public EntityInterface
{
public:
    AgentInterface() = default;
    virtual ~AgentInterface() = default;

    // TODO: Figure out what all an Agent needs to be able to do.
    // I don't know what special methods an Agent might need.

};

#endif //AGENTINTERFACE_H
