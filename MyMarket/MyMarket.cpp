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


	map<string, Category*> marketCategory;

private:

};


int main()
{
	Market* market = new Market();
	market->addNewCategory();
	return 0;
}
