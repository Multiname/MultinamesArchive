#ifndef THEME_H
#define THEME_H
#include "TextEntity.h"

namespace KMK
{
	class Theme : public TextEntity
	{
	public:
		Theme(Id id, Date date, std::string theme, Id ownerId);
		Theme(Theme* theme);
		virtual ~Theme() {}
	};
}

#endif // !THEME_H