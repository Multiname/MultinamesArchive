#include "IdCounter.h"
#include <iostream>
#include <fstream>

using namespace KMK;

IdCounter::IdCounter()
{
	m_id = 0;
	m_storageFile = {};
}

IdCounter::IdCounter(std::string storageFile){ SetIdCounter(storageFile); }

void IdCounter::SetIdCounter(std::string storageFile)
{
	m_storageFile = storageFile;

	std::ifstream fileRead(m_storageFile, std::ios::binary);
	fileRead.read((char*)&m_id, sizeof(m_id));
	fileRead.close();
}

Id IdCounter::operator() ()
{
	std::ifstream fileRead(m_storageFile, std::ios::binary);
	fileRead.read((char*)&m_id, sizeof(m_id));
	fileRead.close();

	++m_id;
	std::ofstream fileWrite(m_storageFile, std::ios::binary);
	fileWrite.write((char*)&m_id, sizeof(m_id));
	fileWrite.close();
	return m_id;
}