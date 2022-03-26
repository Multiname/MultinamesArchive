#pragma once
#include <set>
#include <vector>
#include <string>
#include <fstream>

namespace DTAS
{
	class ExpressionTree
	{
	public:
		ExpressionTree();
		~ExpressionTree();

		bool IsEmpty();
		void Create();
		void Create(std::ifstream& stream);
		void Print();
		void Change();
		void Insert();
		void Remove();
		void Clear();
		void BypassDirectly();
		void BypassSymmetrical();
		void BypassConversely();
		std::string GetExpressionDirectly();
		std::string GetExpressionSymmetrical();
		std::string GetExpressionConversely();

	private:
		struct Number
		{
			int number{};
			Number* left{};
			Number* right{};
		};

		enum Selection
		{
			None,
			Left,
			Right
		};

		void Print(Number* elementToHighlight,
			Selection selection = None);
		void Place(Number* pointer, std::vector<int> branch);
		void Place(Number* pointer, std::ifstream& stream);
		void DrawElement(Number* pointer,
			std::set<unsigned short> columnsToDraw,
			unsigned short numberPosition,
			Number* elementToHighlight = nullptr,
			Selection selection = None);
		unsigned short Select(Number* pointer,
			Number* &selected);
		Number* GoUp(Number* target, Number* current);
		void Clear(Number* target);
		void BypassDirectly(Number* number);
		void BypassSymmetrical(Number* number);
		void BypassConversely(Number* number);
		void AddMemberDirectly(Number* pointer, std::string& destination);
		void AddMemberSymmetrical(Number* pointer, std::string& destination);
		void AddMemberConversely(Number* pointer, std::string& destination);

		Number* _root{};
	};
}