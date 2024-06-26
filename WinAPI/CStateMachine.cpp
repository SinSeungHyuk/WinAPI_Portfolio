#include "pch.h"

#include "CStateMachine.h"
#include "CState.h"

class StateData;

CStateMachine::CStateMachine()
	: CComponent(COMPONENT_TYPE::STATE_MACHINE)
{

}

CStateMachine::CStateMachine(const CStateMachine& _Other)
	: CComponent(_Other)
{
	stateDatasByLayer = _Other.stateDatasByLayer;
	currentStateDatasByLayer = _Other.currentStateDatasByLayer;
	layers = _Other.layers;
}

CStateMachine::~CStateMachine()
{
	for (auto stateDatas : stateDatasByLayer)
		Release_Vector(stateDatas.second);
}


void CStateMachine::FinalTick()
{
	for (int layer : layers) {
		StateData* currentData = currentStateDatasByLayer[layer];

		if (currentData != nullptr)
			currentData->State->FinalTick();
	}
}

void CStateMachine::AddState(const wstring& stateName, CState* state, int layer)
{
	state->SetName(stateName);
	state->owner = this;

	if (layers.find(layer) == layers.end()) layers.insert(layer);

	stateDatasByLayer[layer].push_back(new StateData(
		state, layer, stateDatasByLayer[layer].size()
	));
}

CStateMachine::StateData* CStateMachine::FindState(const wstring& stateName, int layer)
{
	assert(layers.find(layer) != layers.end());

	for (StateData* iter : stateDatasByLayer[layer]) {
		if (iter->State->GetName() == stateName)
			return iter;
	}

	return nullptr;
}

void CStateMachine::ChangeState(const wstring& stateName, int layer)
{
	StateData* changeState = FindState(stateName, layer);

	if (changeState == currentStateDatasByLayer[layer]) return;

	// ���� ���¸� ����������(Exit)
	if (nullptr != currentStateDatasByLayer[layer])
	{
		currentStateDatasByLayer[layer]->State->Exit();
	}

	// ���ο� ���¸� ����Ű��
	currentStateDatasByLayer[layer] = changeState;
	// ���ο� ���·� ����(Enter) �Ѵ�.
	changeState->State->Enter();
}

void CStateMachine::SetLayer()
{
	for (auto stateDatas : stateDatasByLayer) {
		StateData* firstStateData = stateDatas.second.front();
		ChangeState(firstStateData->State->GetName(), stateDatas.first);
	}
}
