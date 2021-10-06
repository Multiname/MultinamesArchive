#include "IdCounter.h"
#include <fstream>

namespace BlackLine
{
	IdCounter::IdCounter()
	{
		m_id = 0;
		m_storageFile = {};
	}

	IdCounter::IdCounter(std::string storageFile)
	{
		m_storageFile = storageFile;

		std::ifstream fileRead(m_storageFile, std::ios::binary);
		fileRead.read((char*)&m_id, sizeof(m_id));
		fileRead.close();
	}

	unsigned long IdCounter::operator() ()
	{
		++m_id;

		std::ofstream fileWrite(m_storageFile, std::ios::binary);
		fileWrite.write((char*)&m_id, sizeof(m_id));
		fileWrite.close();

		return m_id;
	}}