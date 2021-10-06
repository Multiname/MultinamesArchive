#ifndef INTEREST_H
#define INTEREST_H
#include "TextEntity.h"

namespace KMK
{
	class Interest : public TextEntity
	{
	public:
		Interest(Id id, Date date, std::string interest, Id ownerId);
		Interest(Interest* interest);
		virtual ~Interest() {}
	};
}

#endif // !INTEREST_H