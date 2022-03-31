#include "ExpressionTree.h"
#include <iostream>

namespace DTAS
{
	ExpressionTree::ExpressionTree() : _root(nullptr) {}

	ExpressionTree::~ExpressionTree() { Clear(); }

	bool ExpressionTree::IsEmpty() { return _root == nullptr; }

	void ExpressionTree::Create()
	{
		std::cout << "Input root: ";
		int input{};
		std::cin >> input;
		_root = new Number{ input, nullptr, nullptr };

		std::vector<int> branch{};
		branch.push_back(input);

		Place(_root, branch);
	}

	void ExpressionTree::Place(Number* pointer, std::vector<int> branch)
	{
		int input{};

		std::string branchStr{};
		for (size_t i{}; i < branch.size() - 1; ++i)
		{
			branchStr += std::to_string(branch[i]);
			branchStr += " - ";
		}
		branchStr += std::to_string(branch[branch.size() - 1]);
		branchStr += "\n";

		system("cls");
		Print(pointer, Left);

		std::cout << "\nBranch: " << branchStr << "\n";
		std::cout << "Place left? (1 = yes)\n";
		std::cout << ">>> ";
		std::cin >> input;

		if (input == 1)
		{
			std::cout << "Input number: ";
			std::cin >> input;

			pointer->left = new Number{ input, nullptr, nullptr };

			branch.push_back(input);
			Place(pointer->left, branch);
			branch.pop_back();
		}

		system("cls");
		Print(pointer, Right);

		std::cout << "\nBranch: " << branchStr << "\n";
		std::cout << "Place right? (1 = yes)\n";
		std::cout << ">>> ";
		std::cin >> input;

		if (input == 1)
		{
			std::cout << "Input number: ";
			std::cin >> input;

			pointer->right = new Number{ input, nullptr, nullptr };

			branch.push_back(input);
			Place(pointer->right, branch);
			branch.pop_back();
		}
	}

	void ExpressionTree::Create(std::ifstream& stream)
	{
		int number{};
		stream >> number;
		_root = new Number{ number, nullptr, nullptr };

		Place(_root, stream);
	}

	void ExpressionTree::Place(Number* pointer, std::ifstream& stream)
	{
		int input{};
		stream >> input;

		if (input == 1)
		{
			stream >> input;
			pointer->left = new Number{ input, nullptr, nullptr };
			Place(pointer->left, stream);
		}

		stream >> input;

		if (input == 1)
		{
			stream >> input;
			pointer->right = new Number{ input, nullptr, nullptr };
			Place(pointer->right, stream);
		}
	}

	std::string ExpressionTree::GetExpression()
	{
		if (_root != nullptr)
			return MakeString(_root);
		return "";
	}

	std::string ExpressionTree::MakeString(Number* pointer)
	{
		std::string str = "";

		if (pointer->left != nullptr && pointer->right != nullptr)
			str += "( " + std::to_string(pointer->number) + " + " +
			MakeString(pointer->left) + " ) * " + MakeString(pointer->right);
		else if (pointer->left != nullptr)
			str += std::to_string(pointer->number) + " + " +
			MakeString(pointer->left);
		else if (pointer->right != nullptr)
			str += std::to_string(pointer->number) + " * " +
			MakeString(pointer->right);
		else
			str += std::to_string(pointer->number);

		return str;
	}

	void ExpressionTree::CreateFromExpression(std::ifstream& stream)
	{
		_root =  MakeNumber(stream);
	}

	ExpressionTree::Number* ExpressionTree::MakeNumber(std::ifstream& stream, bool bracketMet)
	{
		std::string input{};
		if (!bracketMet)
			stream >> input;

		if (input == "(" || bracketMet)
		{
			Number* number = new Number{ 0, nullptr, new Number{1, nullptr, nullptr} };

			stream >> input;

			if (input == "(")
				number->left = MakeNumber(stream, true);
			else
			{
				int n = std::stoi(input);

				stream >> input;

				if (input == "+")
				{
					number->number = n;
					number->left = MakeNumber(stream);
				}
				else if (input == "*")
					number->left = new Number{ n, nullptr, MakeNumber(stream) };
			}

			std::string temp = "";
			stream >> temp;
			input = temp;
			if (input.size())
			{
				if (input == ")")
					return number;
				else if (input == "+")
				{
					number->right->left = MakeNumber(stream);
					return number;
				}
				else if (input == "*")
				{
					number->right = MakeNumber(stream);
					return number;
				}
			}
			else
				return number;
		}
		else
		{
			Number* number = new Number{ std::stoi(input), nullptr, nullptr };

			std::string temp = "";
			stream >> temp;
			input = temp;

			if (input.size())
			{
				if (input == "+")
				{
					number->left = MakeNumber(stream);
					return number;
				}
				else if (input == "*")
				{
					number->right = MakeNumber(stream);
					return number;
				}
				else if (input == ")")
					return number;
			}
			else
				return number;
		}
	}

	void ExpressionTree::Print()
	{
		if (!IsEmpty())
		{
			std::set<unsigned short> columnsToDraw{};
			DrawElement(_root, columnsToDraw, 0);
		}
		else
			std::cout << "The tree is empty\n";
	}

	void ExpressionTree::Print(Number* elementToHighlight, Selection selection)
	{
		if (!IsEmpty())
		{
			std::set<unsigned short> columnsToDraw{};
			DrawElement(_root, columnsToDraw, 0, elementToHighlight, selection);
		}
	}

	void ExpressionTree::DrawElement(Number* pointer,
		std::set<unsigned short> columnsToDraw, unsigned short numberPosition,
		Number* elementToHighlight, Selection selection)
	{
		std::cout << pointer->number;
		if (pointer == elementToHighlight)
			std::cout << " <=====";
		std::cout << "\n";

		for (unsigned short i{}; i < numberPosition; ++i)
			if (columnsToDraw.find(i) != columnsToDraw.end())
				std::cout << "|";
			else
				std::cout << " ";

		std::cout << "|";
		if (pointer->left != nullptr)
		{
			std::cout << ">";

			columnsToDraw.insert(numberPosition);
			DrawElement(pointer->left, columnsToDraw,
				numberPosition + 2, elementToHighlight, selection);
			columnsToDraw.erase(numberPosition);
		}
		else
			if (pointer == elementToHighlight && selection == Left)
				std::cout << "#\n";
			else
				std::cout << ">\n";

		for (unsigned short i{}; i < numberPosition; ++i)
			if (columnsToDraw.find(i) != columnsToDraw.end())
				std::cout << "|";
			else
				std::cout << " ";

		std::cout << "|";
		if (pointer->right != nullptr)
		{
			std::cout << ">";

			DrawElement(pointer->right, columnsToDraw,
				numberPosition + 2, elementToHighlight, selection);
		}
		else
			if (pointer == elementToHighlight && selection == Right)
				std::cout << "#\n";
			else
				std::cout << ">\n";
	}

	unsigned short ExpressionTree::Select(Number* pointer, Number*& selected)
	{
		unsigned short code = 1;
		while (code != 0 && code != 4)
		{
			system("cls");
			Print(pointer);

			std::cout << "\n1. Move left\n";
			std::cout << "2. Move right\n";
			std::cout << "3. Return\n";
			std::cout << "4. Select\n";
			std::cout << "0. Cancel\n";
			std::cout << ">>> ";
			std::cin >> code;

			if (code == 1)
			{
				if (pointer->left != nullptr)
					code = Select(pointer->left, selected);
			}
			else if (code == 2)
			{
				if (pointer->right != nullptr)
					code = Select(pointer->right, selected);
			}
			else if (code == 3)
			{
				if (pointer != _root)
					return 3;
			}
			else if (code == 4)
			{
				selected = pointer;
				return 4;
			}
			else if (code == 0)
			{
				return 0;
			}
		}
	}

	void ExpressionTree::Change()
	{
		if (!IsEmpty())
		{
			Number* selected{};
			if (Select(_root, selected) == 4)
			{
				std::cout << "\nInput number: ";
				int number{};
				std::cin >> number;

				selected->number = number;
			}
		}
	}

	void ExpressionTree::Insert()
	{
		if (!IsEmpty())
		{
			Number* selected{};
			if (Select(_root, selected) == 4)
			{
				std::cout << "\n1. Place subtree left\n";
				std::cout << "2. Place subtree right\n";
				std::cout << ">>> ";
				unsigned short placement{};
				std::cin >> placement;

				std::cout << "\nInput number: ";
				int number{};
				std::cin >> number;

				Number* moved = new Number{selected->number,
					selected->left, selected->right};

				selected->number = number;

				if (placement == 1)
				{
					selected->left = moved;
					selected->right = nullptr;
				}
				else if (placement == 2)
				{
					selected->left = nullptr;
					selected->right = moved;
				}
			}
		}
	}

	void ExpressionTree::Remove()
	{
		if (!IsEmpty())
		{
			Number* selected{};
			if (Select(_root, selected) == 4)
			{
				Number* parent = GoUp(selected, _root);

				if (selected->left == nullptr && selected->right == nullptr)
				{
					if (parent == nullptr)
					{
						delete _root;
						_root = nullptr;
					}
					else
					{
						if (parent->left == selected)
						{
							delete parent->left;
							parent->left = nullptr;
						}
						else
						{
							delete parent->right;
							parent->right = nullptr;
						}
					}
				}
				else if (selected->left != nullptr && selected->right != nullptr)
				{
					Number* numberToSwap = selected->left;
					Number* numberToSwapParent = selected;

					while (numberToSwap->right != nullptr)
					{
						numberToSwapParent = numberToSwap;
						numberToSwap = numberToSwap->right;
					}

					numberToSwap->right = selected->right;
					if (numberToSwapParent != selected)
					{
						numberToSwap->left = selected->left;
						if (numberToSwapParent->left == numberToSwap)
							numberToSwapParent->left = nullptr;
						else
							numberToSwapParent->right = nullptr;
					}

					if (parent != nullptr)
					{
						if (parent->left == selected)
						{
							delete parent->left;
							parent->left = numberToSwap;
						}
						else
						{
							delete parent->right;
							parent->right = numberToSwap;
						}
					}
					else
					{
						delete _root;
						_root = numberToSwap;
					}
				}
				else
				{
					if (parent == nullptr)
					{
						if (_root->left != nullptr)
						{
							Number* temp = _root->left;
							delete _root;
							_root = temp;
						}
						else
						{
							Number* temp = _root->right;
							delete _root;
							_root = temp;
						}
					}
					else
					{
						Number* numberToSet{};
						if (selected->left != nullptr)
							numberToSet = selected->left;
						else
							numberToSet = selected->right;

						if (parent->left == selected)
						{
							delete parent->left;
							parent->left = numberToSet;
						}
						else
						{
							delete parent->right;
							parent->right = numberToSet;
						}
					}
				}
			}
		}
	}

	ExpressionTree::Number* ExpressionTree::GoUp(Number* target, Number* current)
	{
		if (current->left == target || current->right == target)
			return current;

		Number* numberToFind = nullptr;

		if (current->left != nullptr)
			numberToFind = GoUp(target, current->left);

		if (numberToFind == nullptr && current->right != nullptr)
			numberToFind = GoUp(target, current->right);

		return numberToFind;
	}

	void ExpressionTree::Clear()
	{
		if (!IsEmpty())
		{
			Clear(_root);
			_root = nullptr;
		}
	}

	void ExpressionTree::Clear(Number* target)
	{
		if (target->left != nullptr)
			Clear(target->left);
		if (target->right != nullptr)
			Clear(target->right);

		delete target;
	}

	void ExpressionTree::BypassDirectly()
	{
		if (!IsEmpty())
			BypassDirectly(_root);
	}

	void ExpressionTree::BypassDirectly(Number* number)
	{
		std::cout << number->number << " ";

		if (number->left != nullptr)
			BypassDirectly(number->left);
		if (number->right != nullptr)
			BypassDirectly(number->right);
	}

	void ExpressionTree::BypassSymmetrical()
	{
		if (!IsEmpty())
			BypassSymmetrical(_root);
	}

	void ExpressionTree::BypassSymmetrical(Number* number)
	{
		if (number->left != nullptr)
			BypassSymmetrical(number->left);

		std::cout << number->number << " ";

		if (number->right != nullptr)
			BypassSymmetrical(number->right);
	}

	void ExpressionTree::BypassConversely()
	{
		if (!IsEmpty())
			BypassConversely(_root);
	}

	void ExpressionTree::BypassConversely(Number* number)
	{
		if (number->left != nullptr)
			BypassConversely(number->left);

		if (number->right != nullptr)
			BypassConversely(number->right);

		std::cout << number->number << " ";
	}

	std::string ExpressionTree::GetExpressionDirectly()
	{
		if (!IsEmpty())
		{
			std::string result = std::to_string(_root->number);

			if (_root->left != nullptr || _root->right != nullptr)
			{
				result += " + ";
				if (_root->left != nullptr)
					AddMemberDirectly(_root->left, result);

				if (_root->left != nullptr && _root->right != nullptr)
					result += " * ";

				if (_root->right != nullptr)
					AddMemberDirectly(_root->right, result);
			}

			return result;
		}

		return "";
	}

	void ExpressionTree::AddMemberDirectly(Number* pointer, std::string& destination)
	{
		if (pointer->left != nullptr || pointer->right != nullptr)
		{
			destination += "(";

			destination += std::to_string(pointer->number);
			destination += " + ";

			if (pointer->left != nullptr)
				AddMemberDirectly(pointer->left, destination);

			if (pointer->left != nullptr && pointer->right != nullptr)
				destination += " * ";

			if (pointer->right != nullptr)
				AddMemberDirectly(pointer->right, destination);

			destination += ")";
		}
		else
			destination += std::to_string(pointer->number);
	}

	std::string ExpressionTree::GetExpressionSymmetrical()
	{
		if (!IsEmpty())
		{
			std::string result = "";
			AddMemberSymmetrical(_root, result);

			return result;
		}

		return "";
	}

	void ExpressionTree::AddMemberSymmetrical(Number* pointer, std::string& destination)
	{
		if (pointer->left != nullptr)
		{
			AddMemberSymmetrical(pointer->left, destination);
			destination += " + ";
		}

		destination += std::to_string(pointer->number);

		if (pointer->right != nullptr)
		{
			destination += " * ";

			if (pointer->right->left != nullptr)
			{
				destination += "(";
				AddMemberSymmetrical(pointer->right, destination);
				destination += ")";
			}
			else
				AddMemberSymmetrical(pointer->right, destination);
		}
	}

	std::string ExpressionTree::GetExpressionConversely()
	{
		if (!IsEmpty())
		{
			std::string result = "";
			AddMemberConversely(_root, result);

			return result;
		}

		return "";
	}

	void ExpressionTree::AddMemberConversely(Number* pointer, std::string& destination)
	{
		if (pointer->left != nullptr || pointer->right != nullptr)
		{
			if (pointer->left != nullptr)
			{
				if ((pointer->left->left != nullptr || pointer->left->right != nullptr)
					&& pointer->right != nullptr)
				{
					destination += "(";
					AddMemberConversely(pointer->left, destination);
					destination += ")";
				}
				else
					AddMemberConversely(pointer->left, destination);
			}

			if (pointer->left != nullptr && pointer->right != nullptr)
				destination += " * ";

			if (pointer->right != nullptr)
			{
				if ((pointer->right->left != nullptr || pointer->right->right != nullptr)
					&& pointer->left != nullptr)
				{
					destination += "(";
					AddMemberConversely(pointer->right, destination);
					destination += ")";
				}
				else
					AddMemberConversely(pointer->right, destination);
			}

			destination += " + ";
		}

		destination += std::to_string(pointer->number);
	}
}