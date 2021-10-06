#ifndef HUMAN_H
#define HUMAN_H

namespace KMK
{
	class Human
	{
	public:
		struct Date
		{
			unsigned short day{};
			unsigned short month{};
			unsigned short year{};
		};
		
		Human(unsigned long int id, Date date);

	private:
		unsigned long int m_id{};
		Date m_date;
	};
}

#endif // !HUMAN_H