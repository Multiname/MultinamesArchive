#include "Dialogue.h"

using namespace KMK;

Dialogue::Dialogue(Id id, Date date, std::string message, Id senderId, Id adresseeId) :
	TextEntity(id, date, message, senderId)
{
	m_adresseeId = adresseeId;
}

Dialogue::Dialogue(Dialogue* dialogue) :
	TextEntity(dialogue->GetId(), dialogue->GetDate(), dialogue->GetContent(), dialogue->GetOwnerId())
{
	m_adresseeId = dialogue->m_adresseeId;
}

Id Dialogue::GetAdresseeId() { return m_adresseeId; }

void Dialogue::SetAdresseeId(Id adresseeId) { m_adresseeId = adresseeId; }