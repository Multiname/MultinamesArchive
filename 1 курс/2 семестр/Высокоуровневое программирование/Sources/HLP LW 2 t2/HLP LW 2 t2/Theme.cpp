#include "Theme.h"

using namespace KMK;

Theme::Theme(Id id, Date date, std::string theme, Id ownerId) :
	TextEntity(id, date, theme, ownerId){}

Theme::Theme(Theme* theme) :
	TextEntity(theme->GetId(), theme->GetDate(), theme->GetContent(), theme->GetOwnerId()) {}