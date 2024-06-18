#pragma once
#include "CComponent.h"

class CState;

class CStateMachine :
    public CComponent
{
private:
    class StateData {
        CState* State;
        int Layer;
        int Priority;

        StateData(CState* state, int layer, int priority)
            : State(state), Layer(layer), Priority(priority) {}

        friend CStateMachine;
    };

    map<int, vector<StateData*>>   stateDatasByLayer;
    map<int, StateData*>   currentStateDatasByLayer;
    set<int> layers;


public:
    virtual CStateMachine* Clone() = 0;
    CStateMachine();
    CStateMachine(const CStateMachine& _Other);
    ~CStateMachine();

    void AddState(const wstring& stateName, CState* state, int layer);
    StateData* FindState(const wstring& stateName, int layer);
    void ChangeState(const wstring& stateName, int layer);
    void SetLayer();

    virtual void FinalTick() override;
    virtual void AddStates() = 0;
};

