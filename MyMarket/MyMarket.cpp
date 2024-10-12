#include<iostream>
#include<string>
#include<map>
#include<set>
#include<sstream>
#include<conio.h>
#include <cstdlib>
#include<windows.h>
using namespace std;



void setColor(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, color);
}

template<class T>
T getInput(int toColor)
{
	setColor(toColor);

	T s;  cin >> s;

	setColor(15);

	return s;
}

enum Colors {
	Black = 0,
	Blue = 1,
	Green = 2,
	Red = 4,
	White = 7,
	Light_Blue = 9,
	Light_Green = 10,
	Light_Red = 12,
	Bright_White = 15
};

void convertStringToLower(string& s)
{

	for (auto& it : s)
		it = tolower(it);
}

bool tryAgain()
{
	cout << "Do You Want To Try Again ? Yes:NO => ";
	string option = getInput<string>(Red);
	cout << '\n';

	convertStringToLower(option);
	return option == "yes";
}

class Order
{
public:


	double getTotalPrice()
	{
		return totalPrice;
	}

	void setTotalPrice(double price)
	{
		totalPrice += price;
	}
	set<string> productSelled;

	string toString()
	{
		stringstream ss;

		ss << "total price = $" << totalPrice << "\n";

		ss << "products sold : \n";

		int counter = 0;

		for (auto& it : productSelled)
		{
			ss << ++counter << " " << it << '\n';
		}

		return ss.str();
	}

private:

	double totalPrice = 0;

};




class Product
{
public:


	void setProductName(string ProductName)
	{
		productName = ProductName;
	}

	void setProductQuantity(int Quantity)
	{
		productQuantity = Quantity;
	}

	void setProductPrice(double Price)
	{
		oneProductPrice = Price;
	}


	string getProductName()
	{
		return productName;
	}
	double getProductPrice()
	{
		return oneProductPrice;
	}
	int getProductQuantity()
	{
		return productQuantity;
	}

	double getTotalProductPrice()
	{
		return getProductPrice() * getProductQuantity();
	}

private:

	string productName;
	int productQuantity;
	double totalProductPrice = 0;
	double oneProductPrice;

};




class Category
{
public:
	map<string, Product*>productsOfCategory;


	string getCategoryName()
	{
		return categoryName;
	}

	int getProductQuantity(string productName)
	{
		return productsOfCategory[productName]->getProductQuantity();
	}

	double getProductPrice(string productName)
	{
		return productsOfCategory[productName]->getProductPrice();
	}

	string getProductName(string productName)
	{
		return productsOfCategory[productName]->getProductName();
	}

	double getTotalProductPrice(string productName)
	{
		return productsOfCategory[productName]->getTotalProductPrice();
	}


	void setProductName(string product, string ProductName)
	{
		productsOfCategory[product]->setProductName(ProductName);
	}

	void setProductQuantity(string productName, int Quantity)
	{
		productsOfCategory[productName]->setProductQuantity(Quantity);
	}

	void setProductPrice(string productName, double Price)
	{
		productsOfCategory[productName]->setProductPrice(Price);
	}

	Product* getProduct(string productName)
	{
		return productsOfCategory[productName];
	}

	void addProduct(string productName, int productQuantity, double productPrice)
	{
		productsOfCategory[productName] = new Product();

		productsOfCategory[productName]->setProductName(productName);

		productsOfCategory[productName]->setProductQuantity(productQuantity);

		productsOfCategory[productName]->setProductPrice(productPrice);

	}

	void modifyProduct(string productName, int productQuantity, double productPrice)
	{
		productsOfCategory[productName]->setProductPrice(productPrice);

		productsOfCategory[productName]->setProductQuantity(productQuantity);
	}


	void deleteProduct(string productName)
	{

		productsOfCategory[productName]->setProductQuantity(0);

	}


private:

	string categoryName;

};



class Market
{
public:


	int getProductQuantity(string categoryName, string ProductName)
	{
		return marketCategory[categoryName]->getProductQuantity(ProductName);
	}

	double getProductPrice(string categoryName, string productName)
	{
		return marketCategory[categoryName]->getProductPrice(productName);
	}

	string getProductName(string categoryName, string productName)
	{
		return marketCategory[categoryName]->getProductName(productName);
	}

	double getTotalProductPrice(string categoryName, string productName)
	{
		return marketCategory[categoryName]->getTotalProductPrice(productName);
	}

	void setProductName(string categoryName, string Product, string productName)
	{

		marketCategory[categoryName]->setProductName(Product, productName);
	}

	void setProductQuantity(string categoryName, string Product, int productQuantity)
	{
		marketCategory[categoryName]->setProductQuantity(Product, productQuantity);
	}

	void setProductPrice(string categoryName, string Product, double productPrice)
	{
		marketCategory[categoryName]->setProductPrice(Product, productPrice);
	}

	void addNewCategory()
	{
	categoryAgain:;
		cout << "PLZ Enter Category Name That You Want To Add : ";
		string categoryName = getInput<string>(4);
		cout << '\n';

		if (checkCategory(categoryName))
		{
			cout << "This Category Already Found\n";
			if (tryAgain())
			{
				goto categoryAgain;
			}
		}
		else
		{
			marketCategory[categoryName] = new Category();
			cout << "          Successful Add \n";

			if (tryAgain())
				goto categoryAgain;
		}
	}

	bool checkCategory(string categoryName)
	{
		if (marketCategory.find(categoryName) == marketCategory.end())
			return false;

		return true;
	}

	void printCategoryNotFounded(string categoryName)
	{
		cout << "This Category : ";

		setColor(Red);

		cout << categoryName;

		setColor(Bright_White);

		cout << " not founded\n";
	}

	void printProductNotFounded(string productName)
	{
		cout << "This Product : ";

		setColor(Red);

		cout << productName;

		setColor(Bright_White);

		cout << " not founded\n";
	}

	bool checkProduct(string categoryName, string productName)
	{
		if (marketCategory[categoryName]->productsOfCategory.find(productName) == marketCategory[categoryName]->productsOfCategory.end())
			return false;

		return true;
	}

	string inputCategoryNameFromUser()
	{
		string categoryName = "-1";

	categoryAgain:;
		cout << "PLZ Enter Category Name : ";
		categoryName = getInput<string>(Red);
		cout << '\n';
		if (!checkCategory(categoryName))
		{
			printCategoryNotFounded(categoryName);
			if (tryAgain())
			{
				goto categoryAgain;
			}
			else
				categoryName = "-1";
		}
		return categoryName;
	}


	bool checkQuantity(string categoryName, string productName, int productQuantity)
	{
		if (marketCategory[categoryName]->getProductQuantity(productName) >= productQuantity)
			return true;

		return false;
	}
	string inputProductFromUser(string categoryName)
	{

	productAgain:;
		cout << "PLZ Enter Product Name : ";
		string product = getInput<string>(Red);
		cout << "\n";

		if (!checkProduct(categoryName, product))
		{
			printProductNotFounded(product);
			if (tryAgain())
			{
				goto productAgain;
			}
			else
				product = "-1";
		}
		return product;
	}

	void makeOrder()
	{

		set<string>listOfOrder;

		double totalPrice = 0;

	again:;

		bool checkInput = true;
		string categoryName = "-1";

		categoryName = inputCategoryNameFromUser();
		if (categoryName != "-1")
			printSpecificMarketCategory(categoryName);

		string productName = "-1";

		if (categoryName != "-1") {
			productName = inputProductFromUser(categoryName);
		}

		if (productName != "-1")
		{
			if (marketCategory[categoryName]->getProductQuantity(productName) == 0)
			{
				cout << "This Product Found But There Is No Quantity Now\n";
				if (tryAgain())
				{
					goto again;
				}
				else
					productName = "-1";
			}
		}

		int productQuantity;
		if (productName != "-1") {
			cout << "PLZ Enter The Quantity : ";
			productQuantity = getInput<int>(4);
			cout << '\n';
		}
		Order* order = NULL;
		if (productName != "-1")
			order = makeOrder(categoryName, productName, productQuantity);

		if (order != NULL)
		{
			if (order->getTotalPrice())
				totalPrice += order->getTotalPrice();

			for (auto& it : order->productSelled)
				listOfOrder.insert(it);

			cout << "Do You Want to Continue ? Yes|No => ";
			string option;

			option = getInput<string>(Red);

			convertStringToLower(option);

			if (option == "yes") {
				goto again;
			}
		}
		else if (productName != "-1")
		{
			if (tryAgain()) {
				goto again;
			}
		}

		if (!totalPrice) {
			return;
		}
		cout << "\n\n   **Your Receipt.....\n";

		int cnt = 0;

		for (auto& it : listOfOrder)
		{
			cout << ++cnt << " => " << it << '\n';
		}

		cout << "And Your Total price = ";

		setColor(Red);

		cout << totalPrice;

		setColor(White);

		cout << "\n";

		char a = _getch();
	}

	Order* makeOrder(string CategoryName, string productName, int productQuantity)
	{

		if (!checkCategory(CategoryName))
		{

			printCategoryNotFounded(CategoryName);

		}
		else if (!checkProduct(CategoryName, productName))
		{

			printProductNotFounded(productName);

		}
		else if (!checkQuantity(CategoryName, productName, productQuantity))
		{

			cout << "This Product found but there is no quantity now\n";

		}
		else
		{
			Order* order = new Order();

			order = sellOrder(CategoryName, productName, productQuantity);

			return order;

		}

		Order* order = NULL;

		return order;
	}

	void printSpecificMarketCategory(string categoryName)
	{
		if (marketCategory[categoryName]->productsOfCategory.empty())
			cout << "No Products in This Category\n";
		else
		{
			cout << categoryName << "......\n";
			for (auto& it : marketCategory[categoryName]->productsOfCategory)
			{
				Product* product = it.second;
				if (product->getProductQuantity() == 0)
				{
					cout << " Product : ";
					setColor(Red);
					cout << product->getProductName();
					setColor(Bright_White);
					cout << " found but there is no quantity now\n";
					continue;
				}
				cout << "   Product Name : " << product->getProductName()
					<< "    Product Quantity : " << product->getProductQuantity()
					<< "    product Price : " << product->getProductPrice() << '\n';
			}
		}
	}

	void printCategoriesAndProducts()
	{
		for (auto& it : marketCategory)
		{
			string categoryName = it.first;

			printSpecificMarketCategory(categoryName);
		}
	}

	map<string, Category*> marketCategory;

private:

	Order* sellOrder(string categoryName, string productName, int productQuantity)
	{
		Order* order = new Order();

		order->productSelled.insert(productName);

		double totalProductPrice = marketCategory[categoryName]->getProductPrice(productName) * productQuantity;

		order->setTotalPrice(totalProductPrice);

		int remainQuantity = marketCategory[categoryName]->getProductQuantity(productName) - productQuantity;

		marketCategory[categoryName]->setProductQuantity(productName, remainQuantity);

		return order;
	}
};


int main()
{
	Market* market = new Market();
	market->addNewCategory();
	return 0;
}
