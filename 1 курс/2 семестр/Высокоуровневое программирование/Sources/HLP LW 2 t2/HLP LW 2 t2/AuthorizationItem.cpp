#include "AuthorizationItem.h"
#include <iostream>
#include <Windows.h>
#include "TypeDefinitions.h"
#include "Sort.h"
#include "Add.h"
#include "Remove.h"
#include "Filter.h"
#include <vector>
#include <string>
#include "UserInput.h"

namespace KMK
{
	AuthorizstionItem::AuthorizstionItem(std::string itemName, Storage* storage) : MenuItem(itemName)
	{
		m_storage = storage;
	}

	int AuthorizstionItem::Run()
	{
		unsigned short command = 0;

		while (command != 2)
		{
			UserInput input{};
			system("cls");
			std::cout << "0. Log in\n";
			std::cout << "1. Sign in\n";
			std::cout << "2. Exit\n";
			std::cout << ">>> ";
			std::cin >> input;
			try
			{
				command = input.GetUInt16(0, 2);
			}
			catch (StringToUInt16Exception& exception)
			{
				std::cout << exception.GetError() << "\n";
				std::cin >> input;
				continue;
			}

			if (command == 0)
			{
				std::string login{};
				std::cout << "\nLogin: ";
				std::getline(std::cin, login);

				std::string password{};
				std::cout << "Password: ";
				std::getline(std::cin, password);

				Id userId = 0;
				for (size_t i{}; i < m_storage->GetUserListSize(); i++)
				{
					if (login == m_storage->m_userList[i]->GetLogin() &&
						password == m_storage->m_userList[i]->GetPassword())
					{
						userId = m_storage->m_userList[i]->GetId();
						break;
					}
				}

				if (userId != 0)
				{
					unsigned short userCommand = 0;
					std::string userNickname{};
					for (size_t i{}; i < m_storage->GetUserListSize(); ++i)
					{
						if (m_storage->m_userList[i]->GetId() == userId)
						{
							userNickname = m_storage->m_userList[i]->GetName();
							break;
						}
					}

					while (userCommand != 4)
					{
						system("cls");
						std::cout << "Your nickname: " << userNickname << "\n\n";
						std::cout << "0. Dialogs\n";
						std::cout << "1. Interests\n";
						std::cout << "2. Reminders\n";
						std::cout << "3. Themes\n";
						std::cout << "4. Exit\n";
						std::cout << ">>> ";
						std::cin >> input;
						try
						{
							userCommand = input.GetUInt16(0, 4);
						}
						catch (StringToUInt16Exception& exception)
						{
							std::cout << exception.GetError() << "\n";
							std::cin >> input;
							continue;
						}

						if (userCommand == 0)
						{
							unsigned short dialogCommand = 0;

							while (dialogCommand != 2)
							{
								system("cls");
								Sort((Entity**&)m_storage->m_dialogueList, m_storage->GetDialogueListSize(),
									OrderMode::ASCENDING, FieldMode::DATE);

								struct UserDialog
								{
									Id dialogUserId{};
									std::string dialogUserNickname{};
									std::string lastMessage{};
								};

								std::vector<UserDialog> userDialogs{};
								for (size_t i{}; i < m_storage->GetDialogueListSize(); ++i)
								{
									if (m_storage->m_dialogueList[i]->GetOwnerId() == userId ||
										m_storage->m_dialogueList[i]->GetAdresseeId() == userId)
									{
										size_t userDialogIndex = 0;
										for (size_t j{}; j < userDialogs.size(); ++j)
										{
											if (m_storage->m_dialogueList[i]->GetOwnerId() == userId &&
												m_storage->m_dialogueList[i]->GetAdresseeId() == userId &&
												userDialogs[j].dialogUserId == userId)
											{
												break;
											}
											else if (m_storage->m_dialogueList[i]->GetOwnerId() == userDialogs[j].dialogUserId &&
												m_storage->m_dialogueList[i]->GetOwnerId() != userId ||
												m_storage->m_dialogueList[i]->GetAdresseeId() == userDialogs[j].dialogUserId &&
												m_storage->m_dialogueList[i]->GetAdresseeId() != userId)
											{
												break;
											}
											++userDialogIndex;
										}
										if (userDialogIndex < userDialogs.size())
										{
											if (m_storage->m_dialogueList[i]->GetOwnerId() == userId)
											{
												userDialogs[userDialogIndex].lastMessage = "You";
											}
											else
											{
												for (size_t j{}; j < m_storage->GetUserListSize(); j++)
												{
													if (m_storage->m_dialogueList[i]->GetOwnerId() ==
														m_storage->m_userList[j]->GetId())
													{
														userDialogs[userDialogIndex].lastMessage = m_storage->m_userList[j]->GetName();
														break;
													}
												}
											}

											userDialogs[userDialogIndex].lastMessage += ": ";
											userDialogs[userDialogIndex].lastMessage += m_storage->m_dialogueList[i]->GetContent();
										}
										else
										{
											if (m_storage->m_dialogueList[i]->GetOwnerId() == userId &&
												m_storage->m_dialogueList[i]->GetAdresseeId() == userId)
											{
												std::string message = userNickname;
												message += ": ";
												message += m_storage->m_dialogueList[i]->GetContent();
												userDialogs.push_back({ userId, userNickname, message });
											}
											else if (m_storage->m_dialogueList[i]->GetOwnerId() != userId)
											{
												std::string dialogUserNickname = "";
												for (size_t j{}; j < m_storage->GetUserListSize(); j++)
												{
													if (m_storage->m_dialogueList[i]->GetOwnerId() ==
														m_storage->m_userList[j]->GetId())
													{
														dialogUserNickname = m_storage->m_userList[j]->GetName();
														break;
													}
												}
												if (dialogUserNickname == "") { continue; }

												std::string message = dialogUserNickname;
												message += ": ";
												message += m_storage->m_dialogueList[i]->GetContent();
												userDialogs.push_back({ m_storage->m_dialogueList[i]->GetOwnerId(),
													dialogUserNickname, message });
											}
											else if (m_storage->m_dialogueList[i]->GetAdresseeId() != userId)
											{
												std::string dialogUserNickname = "";
												for (size_t j{}; j < m_storage->GetUserListSize(); j++)
												{
													if (m_storage->m_dialogueList[i]->GetAdresseeId() ==
														m_storage->m_userList[j]->GetId())
													{
														dialogUserNickname = m_storage->m_userList[j]->GetName();
														break;
													}
												}
												if (dialogUserNickname == "") { continue; }

												std::string message = "You";
												message += ": ";
												message += m_storage->m_dialogueList[i]->GetContent();
												userDialogs.push_back({ m_storage->m_dialogueList[i]->GetAdresseeId(),
													dialogUserNickname, message });
											}
										}
									}
								}

								std::cout << "Your dialogs:\n";
								for (size_t i{}; i < userDialogs.size(); ++i)
								{
									std::cout << userDialogs[i].dialogUserNickname << "\n";
									std::cout << "\t" << userDialogs[i].lastMessage << "\n\n";
								}

								std::cout << "0. Open dialog\n";
								std::cout << "1. Find user\n";
								std::cout << "2. Exit\n";
								std::cout << ">>> ";
								std::cin >> input;
								try
								{
									dialogCommand = input.GetUInt16(0, 2);
								}
								catch (StringToUInt16Exception& exception)
								{
									std::cout << exception.GetError() << "\n";
									std::cin >> input;
									continue;
								}

								if (dialogCommand == 0)
								{

									std::string nickname{};
									std::cout << "\nInput nickname: ";
									std::getline(std::cin, nickname);

									Id dialogueUserId = 0;
									for (size_t i{}; i < m_storage->GetUserListSize(); i++)
									{
										if (nickname == m_storage->m_userList[i]->GetName())
										{
											dialogueUserId = m_storage->m_userList[i]->GetId();
											break;
										}
									}

									if (dialogueUserId != 0)
									{
										unsigned short dialogWithUserCommand = 0;

										while (dialogWithUserCommand != 1)
										{
											system("cls");
											for (size_t i{}; i < m_storage->GetDialogueListSize(); i++)
											{
												if (m_storage->m_dialogueList[i]->GetOwnerId() == userId &&
													m_storage->m_dialogueList[i]->GetAdresseeId() == dialogueUserId)
												{
													std::cout << "You: " << m_storage->m_dialogueList[i]->GetContent() << "\n";
												}
												else if (m_storage->m_dialogueList[i]->GetOwnerId() == dialogueUserId &&
													m_storage->m_dialogueList[i]->GetAdresseeId() == userId)
												{
													std::cout << nickname << ": " << m_storage->m_dialogueList[i]->GetContent() << "\n";
												}
											}
											std::cout << "\n";
											std::cout << "\n0. Write a message\n";
											std::cout << "1. Exit\n";
											std::cout << ">>> ";
											std::cin >> input;
											try
											{
												dialogWithUserCommand = input.GetUInt16(0, 1);
											}
											catch (StringToUInt16Exception& exception)
											{
												std::cout << exception.GetError() << "\n";
												std::cin >> input;
												continue;
											}

											if (dialogWithUserCommand == 0)
											{
												std::string message{};
												std::cout << "Message: ";
												std::getline(std::cin, message);

												SYSTEMTIME systemTime;
												GetLocalTime(&systemTime);
												m_storage->LoadDialogueList();
												size_t size = m_storage->GetDialogueListSize();
												Add<Dialogue>(m_storage->m_dialogueList, size,
													new Dialogue{ m_storage->GetNextDialogueId(),
													{systemTime.wDay, systemTime.wMonth, systemTime.wYear},
													message, userId, dialogueUserId });
												m_storage->SetDialogueListSize(size);
												m_storage->SaveDialogueList();
											}
										}
									}
									else
									{
										std::cout << "User wasn's found\n";
										std::cin >> input;
									}
								}
								else if (dialogCommand == 1)
								{
									system("cls");
									std::string nickname{};
									std::cout << "Input nickname: ";
									std::getline(std::cin, nickname);
									
									size_t size = m_storage->GetUserListSize();
									Filter((Entity**&)m_storage->m_userList, size, nickname, FieldMode::NAME);
									m_storage->SetUserListSize(size);

									std::cout << "\nFound users:\n";
									for (size_t i{}; i < m_storage->GetUserListSize(); ++i)
									{
										std::cout << m_storage->m_userList[i]->GetName() << "\n";
									}
									m_storage->LoadUserList();

									std::cout << "\nPress enter to return\n";
									std::cin >> input;
								}

								m_storage->LoadDialogueList();
							}
						}
						else if (userCommand == 1)
						{
							unsigned short interestCommand = 0;

							while (interestCommand != 3)
							{
								system("cls");
								std::vector<size_t> indexes{};
								std::cout << "Your interests:\n";
								for (size_t i{}; i < m_storage->GetInterestListSize(); ++i)
								{
									if (m_storage->m_interestList[i]->GetOwnerId() == userId)
									{
										std::cout << indexes.size() << ". " << m_storage->m_interestList[i]->GetContent() << "\n";
										indexes.push_back(i);
									}
								}
								std::cout << "\n0. Create new interest\n";
								std::cout << "1. Delete interest\n";
								std::cout << "2. Find by interest\n";
								std::cout << "3. Exit\n";
								std::cout << ">>> ";
								std::cin >> input;
								try
								{
									interestCommand = input.GetUInt16(0, 3);
								}
								catch (StringToUInt16Exception& exception)
								{
									std::cout << exception.GetError() << "\n";
									std::cin >> input;
									continue;
								}

								if (interestCommand == 0)
								{
									std::cout << "\nInput interest: ";
									std::string interest{};
									std::getline(std::cin, interest);

									SYSTEMTIME systemTime;
									GetLocalTime(&systemTime);
									size_t size = m_storage->GetInterestListSize();
									Add<Interest>(m_storage->m_interestList, size,
										new Interest{ m_storage->GetNextInterestId(),
										{systemTime.wDay, systemTime.wMonth, systemTime.wYear},
										interest, userId });
									m_storage->SetInterestListSize(size);
									m_storage->SaveInterestList();
								}
								else if (interestCommand == 1)
								{
									std::cout << "\nInput interest number: ";
									size_t interestNumber{};
									std::cin >> input;
									try
									{
										interestNumber = input.GetUInt32(0, indexes.size() - 1);
									}
									catch (StringToUInt32Exception& exception)
									{
										std::cout << exception.GetError() << "\n";
										std::cin >> input;
										continue;
									}

									size_t size = m_storage->GetInterestListSize();
									Remove((Entity**&)m_storage->m_interestList, size,
										m_storage->m_interestList[indexes[interestNumber]]->GetId());
									m_storage->SetInterestListSize(size);
									m_storage->SaveInterestList();
								}
								else if (interestCommand == 2)
								{
									std::cout << "\nInput interest: ";
									std::string interest{};
									std::getline(std::cin, interest);

									size_t size = m_storage->GetInterestListSize();
									Filter((Entity**&)m_storage->m_interestList, size, interest, FieldMode::CONTENT);
									m_storage->SetInterestListSize(size);

									std::cout << "\nUsers with similar interest:\n";
									for (size_t i{}; i < m_storage->GetInterestListSize(); ++i)
									{
										for (size_t j{}; j < m_storage->GetUserListSize(); ++j)
										{
											if (m_storage->m_interestList[i]->GetOwnerId() ==
												m_storage->m_userList[j]->GetId())
											{
												std::cout << m_storage->m_userList[j]->GetName() << ": " <<
													m_storage->m_interestList[i]->GetContent() << "\n";
												break;
											}
										}
									}
									m_storage->LoadInterestList();
									std::cout << "\nPress enter to return\n";
									std::cin >> input;
								}
							}
						}
						else if (userCommand == 2)
						{
							unsigned short reminderCommand = 0;

							while (reminderCommand != 2)
							{
								system("cls");
								Sort((Entity**&)m_storage->m_reminderList, m_storage->GetReminderListSize(),
									OrderMode::ASCENDING, FieldMode::REMINDER_TIME);

								std::cout << "Today's reminders:\n";
								SYSTEMTIME systemTime;
								GetLocalTime(&systemTime);
								for (size_t i{}; i < m_storage->GetReminderListSize(); ++i)
								{
									if (m_storage->m_reminderList[i]->GetOwnerId() == userId &&
										m_storage->m_reminderList[i]->GetReminderTime().day == systemTime.wDay &&
										m_storage->m_reminderList[i]->GetReminderTime().month == systemTime.wMonth &&
										m_storage->m_reminderList[i]->GetReminderTime().year == systemTime.wYear)
									{
										std::cout << m_storage->m_reminderList[i]->GetReminderTime().day << "/" <<
											m_storage->m_reminderList[i]->GetReminderTime().month << "/" <<
											m_storage->m_reminderList[i]->GetReminderTime().year << ": " <<
											m_storage->m_reminderList[i]->GetContent() << "\n";
									}
								}

								std::cout << "\nAll reminders:\n";
								std::vector<size_t> indexes{};
								for (size_t i{}; i < m_storage->GetReminderListSize(); ++i)
								{
									if (m_storage->m_reminderList[i]->GetOwnerId() == userId)
									{
										std::cout << indexes.size() << ") " <<
											m_storage->m_reminderList[i]->GetReminderTime().day << "/" <<
											m_storage->m_reminderList[i]->GetReminderTime().month << "/" <<
											m_storage->m_reminderList[i]->GetReminderTime().year << ": " <<
											m_storage->m_reminderList[i]->GetContent() << "\n";
										indexes.push_back(i);
									}
								}

								std::cout << "\n0. Create new reminder\n";
								std::cout << "1. Delete reminder\n";
								std::cout << "2. Exit\n";
								std::cout << ">>> ";
								std::cin >> input;
								try
								{
									reminderCommand = input.GetUInt16(0, 2);
								}
								catch (StringToUInt16Exception& exception)
								{
									std::cout << exception.GetError() << "\n";
									std::cin >> input;
									continue;
								}

								if (reminderCommand == 0)
								{
									Entity::Date newDate{};
									std::cout << "\nInput day: ";
									std::cin >> input;
									try
									{
										newDate.day = input.GetUInt16(1, 31);
									}
									catch (StringToUInt16Exception& exception)
									{
										std::cout << exception.GetError() << "\n";
										std::cin >> input;
										continue;
									}
									std::cout << "Input month: ";
									std::cin >> input;
									try
									{
										newDate.month = input.GetUInt16(1, 12);
									}
									catch (StringToUInt16Exception& exception)
									{
										std::cout << exception.GetError() << "\n";
										std::cin >> input;
										continue;
									}
									std::cout << "Input year: ";
									std::cin >> input;
									try
									{
										newDate.year = input.GetUInt16();
									}
									catch (StringToUInt16Exception& exception)
									{
										std::cout << exception.GetError() << "\n";
										std::cin >> input;
										continue;
									}
									std::cout << "Input text: ";
									std::string text{};
									std::getline(std::cin, text);

									SYSTEMTIME systemTime;
									GetLocalTime(&systemTime);
									size_t size = m_storage->GetReminderListSize();
									m_storage->LoadReminderList();
									Add<Reminder>(m_storage->m_reminderList, size,
										new Reminder{ m_storage->GetNextReminderId(),
										{ systemTime.wDay, systemTime.wMonth, systemTime.wYear},
										text, userId, newDate });
									m_storage->SetReminderListSize(size);
									m_storage->SaveReminderList();
								}
								else if (reminderCommand == 1)
								{
									std::cout << "\nInput reminder number: ";
									size_t reminderNumber{};
									std::cin >> input;
									try
									{
										reminderNumber = input.GetUInt32(0, indexes.size() - 1);
									}
									catch (StringToUInt32Exception& exception)
									{
										std::cout << exception.GetError() << "\n";
										std::cin >> input;
										continue;
									}

									size_t size = m_storage->GetReminderListSize();
									m_storage->LoadReminderList();
									Remove((Entity**&)m_storage->m_reminderList, size,
										m_storage->m_reminderList[indexes[reminderNumber]]->GetId());
									m_storage->SetReminderListSize(size);
									m_storage->SaveReminderList();
								}

								m_storage->LoadReminderList();
							}
						}
						else if (userCommand == 3)
						{
							unsigned short themeCommand = 0;

							while (themeCommand != 2)
							{
								system("cls");
								for (size_t i{}; i < m_storage->GetThemeListSize(); ++i)
								{
									std::cout << i << ") " << m_storage->m_themeList[i]->GetContent() << "\n";
								}

								std::cout << "\n0. Open theme\n";
								std::cout << "1. Create theme\n";
								std::cout << "2. Exit\n";
								std::cout << ">>> ";
								std::cin >> input;
								try
								{
									themeCommand = input.GetUInt16(0, 2);
								}
								catch (StringToUInt16Exception& exception)
								{
									std::cout << exception.GetError() << "\n";
									std::cin >> input;
									continue;
								}

								if (themeCommand == 0)
								{
									std::cout << "\nInput theme number: ";
									size_t themeNumber{};
									std::cin >> input;
									try
									{
										themeNumber = input.GetUInt32(0, m_storage->GetThemeListSize() - 1);
									}
									catch (StringToUInt32Exception& exception)
									{
										std::cout << exception.GetError() << "\n";
										std::cin >> input;
										continue;
									}

									unsigned short themeDialogCommand = 0;
									while (themeDialogCommand != 1)
									{
										system("cls");
										std::cout << "\t" << m_storage->m_themeList[themeNumber]->GetContent() << "\n\n";
										Sort((Entity**&)m_storage->m_dialogueList, m_storage->GetDialogueListSize(),
											OrderMode::ASCENDING, FieldMode::DATE);
										for (size_t i{}; i < m_storage->GetDialogueListSize(); ++i)
										{
											if (m_storage->m_dialogueList[i]->GetAdresseeId() ==
												m_storage->m_themeList[themeNumber]->GetId())
											{
												if (m_storage->m_dialogueList[i]->GetOwnerId() == userId)
												{
													std::cout << "You: " << m_storage->m_dialogueList[i]->GetContent() << "\n";
												}
												else
												{
													std::string themeUserNickname{};
													for (size_t j{}; j < m_storage->GetUserListSize(); ++j)
													{
														if (m_storage->m_dialogueList[i]->GetOwnerId() ==
															m_storage->m_userList[j]->GetId())
														{
															themeUserNickname = m_storage->m_userList[j]->GetName();
															break;
														}
													}
													std::cout << themeUserNickname << ": " << m_storage->m_dialogueList[i]->GetContent() << "\n";
												}
											}
										}

										std::cout << "\n0. Write a message\n";
										std::cout << "1. Exit\n";
										std::cout << ">>> ";
										std::cin >> input;
										try
										{
											themeDialogCommand = input.GetUInt16(0, 1);
										}
										catch (StringToUInt16Exception& exception)
										{
											std::cout << exception.GetError() << "\n";
											std::cin >> input;
											continue;
										}

										if (themeDialogCommand == 0)
										{
											std::cout << "\nInput message: ";
											std::string message{};
											std::getline(std::cin, message);

											SYSTEMTIME systemTime;
											GetLocalTime(&systemTime);
											size_t size = m_storage->GetDialogueListSize();
											m_storage->LoadDialogueList();
											Add<Dialogue>(m_storage->m_dialogueList, size,
												new Dialogue{ m_storage->GetNextDialogueId(),
												{ systemTime.wDay, systemTime.wMonth, systemTime.wYear },
												message, userId, m_storage->m_themeList[themeNumber]->GetId() });
											m_storage->SetDialogueListSize(size);
											m_storage->SaveDialogueList();
										}

										m_storage->LoadDialogueList();
									}
								}
								else if (themeCommand == 1)
								{
									std::cout << "\nInput theme: ";
									std::string theme{};
									std::getline(std::cin, theme);

									SYSTEMTIME systemTime;
									GetLocalTime(&systemTime);
									size_t size = m_storage->GetThemeListSize();
									Add<Theme>(m_storage->m_themeList, size,
										new Theme{ m_storage->GetNextThemeId(),
										{ systemTime.wDay, systemTime.wMonth, systemTime.wYear},
										theme, userId });
									m_storage->SetThemeListSize(size);
									m_storage->SaveThemeList();
								}
							}
						}
					}
				}
				else
				{
					std::cout << "Wrong login or password\n";
					std::cin >> input;
				}
			}
			else if (command == 1)
			{
				std::string nickname{};
				std::cout << "\nNickname: ";
				std::getline(std::cin, nickname);

				bool isTaken = false;
				for (size_t i{}; i < m_storage->GetUserListSize(); i++)
				{
					if (nickname == m_storage->m_userList[i]->GetName())
					{
						isTaken = true;
						std::cout << "This nickname is already taken\n";
						std::cin >> input;
					}
				}

				if (isTaken) { continue; }

				std::string login{};
				std::cout << "Login: ";
				std::getline(std::cin, login);

				for (size_t i{}; i < m_storage->GetUserListSize(); i++)
				{
					if (login == m_storage->m_userList[i]->GetLogin())
					{
						isTaken = true;
						std::cout << "This login is already taken\n";
						std::cin >> input;
					}
				}

				if (isTaken) { continue; }

				std::string password{};
				std::cout << "Password: ";
				std::getline(std::cin, password);

				SYSTEMTIME systemTime;
				GetLocalTime(&systemTime);
				size_t size = m_storage->GetUserListSize();
				Add<User>(m_storage->m_userList, size,
					new User{ m_storage->GetNextUserId(),
					{ systemTime.wDay, systemTime.wMonth, systemTime.wYear },
					nickname, login, password });
				m_storage->SetUserListSize(size);
				m_storage->SaveUserList();

				std::cout << "Account has been created\n";
				std::cin >> input;
			}
		}

		return 0;
	}
}