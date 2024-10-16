#include<iostream>
#include<string>
#include<map>
#include<set>
#include<sstream>
#include<conio.h>
#include <cstdlib>
#include<windows.h>
using namespace std;


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

void setColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, color);
}


void setCursorPosition(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(hConsole, coord);
}


template<class T>
T getInput(int toColor)
{
    setColor(toColor);

    T s;  cin >> s;

    setColor(15);

    return s;
}

void clearConsole()
{
    system("cls");
}

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

////////////////////////my Order/////////////////////////////////////////////////////
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



/////////my product/////////////////////////////////////////////////////////////////////////////////////////
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




////////////////////////my category////////////////////////////////////////////////////////////////////
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

    void addProduct(string productName, int productQuantity, double productPrice)
    {
        productsOfCategory[productName] = new Product();

        productsOfCategory[productName]->setProductName(productName);

        productsOfCategory[productName]->setProductQuantity(productQuantity);

        productsOfCategory[productName]->setProductPrice(productPrice);

    }

    void modifyProduct(string productName, double productPrice, int productQuantity)
    {
        productsOfCategory[productName]->setProductPrice(productPrice);

        productsOfCategory[productName]->setProductQuantity(productQuantity);
    }

    void deleteProduct(string productName)
    {

        productsOfCategory[productName]->setProductQuantity(0);

    }

    Product* getProduct(string productName)
    {
        return productsOfCategory[productName];
    }

private:

    string categoryName;

};



////////////////////my market////////////////////////////////////////////////////////////////
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

    void addProduct(string categoryName, string productName, double productPrice, int productQuantity)
    {
        marketCategory[categoryName]->addProduct(productName, productQuantity, productPrice);
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

    bool checkCategory(string categoryName)
    {
        if (marketCategory.find(categoryName) == marketCategory.end())
            return false;

        return true;
    }

    bool checkProduct(string categoryName, string productName)
    {
        if (marketCategory[categoryName]->productsOfCategory.find(productName) == marketCategory[categoryName]->productsOfCategory.end())
            return false;

        return true;
    }

    bool checkQuantity(string categoryName, string productName, int productQuantity)
    {
        if (marketCategory[categoryName]->getProductQuantity(productName) >= productQuantity)
            return true;

        return false;
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
    void deleteCategory()
    {
        string categoryName = "-1";
        categoryName = inputCategoryNameFromUser();
        if (categoryName != "-1")
        {
            delete marketCategory[categoryName];
            marketCategory.erase(categoryName);
            cout << "          Successful Delete \n";
        }
        char a = _getch();
    }


    void deleteProduct(string categoryName, string productName)
    {
        marketCategory[categoryName]->deleteProduct(productName);
    }

    void addNewProduct()
    {

    again:;
        string categoryName = "-1";
        categoryName = inputCategoryNameFromUser();

        if (categoryName != "-1")
        {
            cout << "PLZ Enter Product Name : ";
            string productName = getInput<string>(Red);
            cout << '\n';
            if (checkProduct(categoryName, productName))
            {
                cout << "This Product Already Added\n Do You Want To Add To It ? YES:NO => ";
                string option = getInput<string>(Red);
                convertStringToLower(option);
                if (option == "yes")
                {
                    cout << "PLZ Enter The Quantity You Want To Add It To The Current Quantity =>";
                    int productQuantity = getInput<int>(Red);

                    marketCategory[categoryName]->modifyProduct(productName
                        , marketCategory[categoryName]->getProductPrice(productName)
                        , marketCategory[categoryName]->getProductQuantity(productName) + productQuantity);
                }
            }
            else
            {

            quantityAgain:;
                cout << "PLZ Enter Quantity You Want To Add  =>  ";
                int productQuantity = getInput<int>(Red);
                cout << '\n';

                if (productQuantity < 0)
                {
                    cout << "Not Valid Number /n   ";
                    if (tryAgain())
                        goto quantityAgain;
                    else
                        return;
                }

            priceAgain:;
                cout << "PLZ Enter The Price Of The This Product  =>  ";
                double productPrice = getInput<double>(Red);
                cout << '\n';

                if (productPrice < 0)
                {
                    if (tryAgain())
                    {
                        goto priceAgain;
                    }
                    else
                        return;
                }

                addProduct(categoryName, productName, productPrice, productQuantity);

                cout << "          Successful Add \n";

                if (tryAgain())
                    goto again;

            }
        }

    }

    void deleteProductFromCategory()
    {
        string categoryName = "-1";
        categoryName = inputCategoryNameFromUser();

        string product = "-1";

        if (categoryName != "-1")
            product = inputProductFromUser(categoryName);

        if (product != "-1")
        {
            deleteProduct(categoryName, product);
            cout << "          Successful Delete\n";
        }
        else
            cout << "          Failed\n";
        char a = _getch();
    }


    void MoveProductToAnotherCategory()
    {

    Again:;

        string currentCategory = "-1";

        currentCategory = inputCategoryNameFromUser();

        string productName = "-1";

        if (currentCategory != "-1")
        {
            productName = inputProductFromUser(currentCategory);
        }

        string newCategory;

        if (currentCategory != "-1")
        {
            newCategory = inputCategoryNameFromUser();
        }

        if (newCategory != "-1")
        {
            Product* product = marketCategory[currentCategory]->getProduct(productName);

            deleteProduct(currentCategory, productName);

            marketCategory[newCategory]->productsOfCategory[productName] = product;
            marketCategory[newCategory]->setProductName(productName, product->getProductName());
            marketCategory[newCategory]->setProductPrice(productName, product->getProductPrice());
            marketCategory[newCategory]->setProductQuantity(productName, product->getProductQuantity());

            cout << "          Successful Move\n";
        }

        if (tryAgain())
        {
            goto Again;
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
////////my main////////////////////////////////////////////////////////////////////////////////////////




void printMenue(map<int, string>& mp, int cnt)
{
    setCursorPosition(40, 3);
    setColor(Light_Green);
    cout << "      Ahmed's Market\n";
    setColor(Bright_White);

    for (int i = 0;i <= 7;i++)
    {
        if (i == cnt)
        {
            setColor(Light_Green);
            setCursorPosition(36, i + 5);
            cout << "=>>" << i + 1 << ' ' << mp[i];
            setColor(Bright_White);
        }
        else
        {
            setCursorPosition(40, i + 5);
            cout << i + 1 << ' ' << mp[i];
        }
    }
}
string inputPassword(string password)
{
    int s = password.size();
    string ss;

    int cnt = 0;
    while (true)
    {
        cnt++;
        char a = _getch();

        if (a == 8)
        {
            ss.pop_back();
            continue;
        }
        if (a == 13)
        {
            break;
        }

        ss.push_back(a);
        cout << "*";
        if (cnt == s)
            break;
    }

    return ss;
}


bool checkUserNameAndPassword()
{
    string userName = "ahmedsalah";
    string password = "1234";
    bool T = true;
    int cnt = 3;

again:;

    if (!T) {
        setCursorPosition(36, 3);
        cout << "   UserName or Password is Wrong  \n";
    }
    if (cnt == 0)
    {
        cout << "try again after 30 second XDDDD\n";
        return false;
    }
    setCursorPosition(40, 5);
    cout << "Please Enter User Name  : ";
    setColor(Green);
    string userInput;
    getline(cin, userInput);
    setColor(Bright_White);
    cout << '\n';

    setCursorPosition(40, 6);
    cout << "please Enter Password  : ";
    setColor(Green);
    string passwordInput = inputPassword(password);
    setColor(Bright_White);
    cout << '\n';

    if (userName != userInput || password != passwordInput)
    {
        cnt--;
        T = false;
        clearConsole();
        goto again;
    }

    return true;
}


void ControlConsole()
{
    int cnt = 0;
    map<int, string> myData;
    myData[0] = "Display Market Categories And Products\n";
    myData[1] = "Add Category\n";
    myData[2] = "Delete Category\n";
    myData[3] = "Add Or Modify Product\n";
    myData[4] = "Remove Product\n";
    myData[5] = "Move Product To Another Category\n";
    myData[6] = "Sell Product\n";
    myData[7] = "EXIST";

    Market* market = new Market();
    if (checkUserNameAndPassword())
    {
        while (true)
        {

        loop:;

            clearConsole();
            printMenue(myData, cnt);
            char a = _getch();
            switch (a)
            {
            case 49:
                cnt = 0;
                break;

            case 50:
                cnt = 1;
                break;

            case 51:
                cnt = 2;
                break;

            case 52:
                cnt = 3;
                break;

            case 53:
                cnt = 4;
                break;

            case 54:
                cnt = 5;
                break;

            case 55:
                cnt = 6;
                break;

            case 56:
                cnt = 7;
                break;

            case 72:
                if (cnt == 0)
                    cnt = 7;
                else
                    cnt--;
                break;

            case 80:

                if (cnt == 7)
                    cnt = 0;
                else
                    cnt++;
                break;
            case 13:
                clearConsole();
                if (cnt == 0)
                {
                    cout << "this is our our categories and products \n";
                    market->printCategoriesAndProducts();
                    a = _getch();
                }
                else if (cnt == 1)
                {

                    market->addNewCategory();
                }
                else if (cnt == 2)
                {
                    market->deleteCategory();
                }
                else if (cnt == 3)
                {
                    market->addNewProduct();
                }
                else if (cnt == 4)
                {
                    market->deleteProductFromCategory();
                }
                else if (cnt == 5)
                {
                    market->MoveProductToAnotherCategory();
                }
                else if (cnt == 6)
                {
                    market->makeOrder();
                }
                else if (cnt == 7)
                    return;

            default:
                goto loop;
            }

        }
    }
}

int main()
{

    ControlConsole();



    return 0;
}
