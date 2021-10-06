#include "Interest.h"

using namespace KMK;

Interest::Interest(Id id, Date date, std::string interest, Id ownerId) :
	TextEntity(id, date, interest, ownerId) {}

Interest::Interest(Interest* interest) :
	TextEntity(interest->GetId(), interest->GetDate(), interest->GetContent(), interest->GetOwnerId()) {}