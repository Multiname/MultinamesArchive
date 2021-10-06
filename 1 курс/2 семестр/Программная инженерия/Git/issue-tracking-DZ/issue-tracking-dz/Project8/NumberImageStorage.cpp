#include "NumberImageStorage.h"
#include <fstream>
#include <msclr\marshal_cppstd.h>

namespace BlackLine
{
	NumberImageStorage::NumberImageStorage() : m_numberIDs(), m_storagePath() {}
	NumberImageStorage::NumberImageStorage(std::string storagePath) : m_storagePath(storagePath) { Load(); }

	System::String^ NumberImageStorage::GetPathById(unsigned long id)
	{
		for (size_t i{}; i < m_numberIDs.size(); ++i)
		{
			if (m_numberIDs[i] == id)
			{
				return gcnew System::String(System::IO::Path::Combine(System::AppDomain::CurrentDomain->BaseDirectory,
					gcnew System::String((std::to_string(id) + ".numPic").c_str())));
			}
		}

		return "";
	}

	void NumberImageStorage::Add(unsigned long id, System::String^ sourcePath)
	{
		System::IO::File::Copy(sourcePath, System::IO::Path::Combine(System::AppDomain::CurrentDomain->BaseDirectory,
			gcnew System::String((std::to_string(id) + ".numPic").c_str())));
		m_numberIDs.push_back(id);

		Save();
	}

	void NumberImageStorage::Remove(unsigned long id)
	{
		for (std::vector<unsigned long>::iterator it = m_numberIDs.begin(); it != m_numberIDs.end(); ++it)
		{
			if (*it == id)
			{
				System::IO::File::Delete(System::IO::Path::Combine(System::AppDomain::CurrentDomain->BaseDirectory,
					gcnew System::String((std::to_string(id) + ".numPic").c_str())));

				m_numberIDs.erase(it);
				break;
			}
		}

		Save();
	}

	void NumberImageStorage::Save()
	{
		std::ofstream fileSave(m_storagePath, std::ios::binary);

		size_t size = m_numberIDs.size();
		fileSave.write((char*)&size, sizeof(size_t));
		for (size_t i{}; i < size; ++i)
		{
			fileSave.write((char*)&m_numberIDs[i], sizeof(unsigned long));
		}

		fileSave.close();
	}

	void NumberImageStorage::Load()
	{
		std::ifstream fileLoad(m_storagePath, std::ios::binary);

		size_t size{};
		fileLoad.read((char*)&size, sizeof(size_t));
		for (size_t i{}; i < size; ++i)
		{
			unsigned long id{};
			fileLoad.read((char*)&id, sizeof(unsigned long));
			m_numberIDs.push_back(id);
		}

		fileLoad.close();
	}
}