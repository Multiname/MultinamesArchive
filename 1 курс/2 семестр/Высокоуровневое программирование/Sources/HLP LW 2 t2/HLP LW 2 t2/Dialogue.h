#ifndef DIALOGUE_H
#define DIALOGUE_H
#include "TextEntity.h"

namespace KMK
{
	class Dialogue : public TextEntity
	{
	public:
		Dialogue(Id id, Date date, std::string message, Id senderId, Id adresseeId);
		Dialogue(Dialogue* dialogue);
		virtual ~Dialogue() {}

		Id GetAdresseeId();

		void SetAdresseeId(Id adresseeId);

	private:
		Id m_adresseeId{};
	};
}

#endif // !DIALOGUE_H