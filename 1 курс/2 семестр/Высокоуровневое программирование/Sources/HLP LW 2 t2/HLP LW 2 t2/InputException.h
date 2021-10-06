#ifndef INPUT_EXCEPTION_H
#define INPUT_EXCEPTION_H

namespace KMK
{
	class InputException
	{
	public:
		InputException(const char* error);

		const char* GetError();

	private:
		const char* m_error{};
	};

	class StringToUInt16Exception : public InputException
	{
	public:
		StringToUInt16Exception(const char* error);
	};

	class StringToUInt32Exception : public InputException
	{
	public:
		StringToUInt32Exception(const char* error);
	};
}

#endif // !INPUT_EXCEPTION_H