#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>  // Added for stringstream

using namespace std;

// Item structure representing a product
struct Item
{
    string name;
    double price;
};

// ShoppingCart class to manage the items in the cart
class ShoppingCart 
{
public:
    void addItem(const Item& item) 
    {
        items.push_back(item);
    }

    void displayCart() const 
    {
        if (items.empty()) 
        {
            cout << "Your shopping cart is empty." << endl;
        } 
        else 
        {
            cout << "Shopping Cart Contents:" << endl;
            cout << setw(20) << "Item" << setw(10) << "Price" << endl;
            cout << setfill('-') << setw(30) << "" << setfill(' ') << endl;
            for (const auto& item : items) 
            {
                cout << setw(20) << item.name << setw(10) << item.price << endl;
            }
            double total = calculateTotal();
            cout << setfill('-') << setw(30) << "" << setfill(' ') << endl;
            cout << setw(20) << "Total" << setw(10) << total << endl;
        }
    }

private:
    vector<Item> items;

    double calculateTotal() const 
    {
        double total = 0.0;
        for (const auto& item : items) 
        {
            total += item.price;
        }
        return total;
    }
};

// ECommerceWebsite class to manage the list of items and user interaction
class ECommerceWebsite 
{
public:
    void displayItems() const 
    {
        cout << "Available Items:" << endl;
        cout << setw(20) << "Item" << setw(10) << "Price" << endl;
        cout << setfill('-') << setw(30) << "" << setfill(' ') << endl;

        // Display items from the file
        int index = 1;  // Initialize index
        for (const auto& item : itemsFromFile) 
        {
            cout << index << ". " << setw(20) << item.name << setw(10) << item.price << endl;
            ++index;  // Increment index
        }
    }

    void startShopping() 
    {
        int choice;
        do 
        {
            displayItems();
            cout << "Enter the item number you want to add to your cart\n";
            cout << "Enter 0 to check your shopping cart\n";
            cin >> choice;

            if (choice > 0 && choice <= itemsFromFile.size()) 
            {
                shoppingCart.addItem(itemsFromFile[choice - 1]);
                cout << "Item added to your cart." << endl;
            } 
            else if (choice != 0) 
            {
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 0);

        cout << "Thank you for shopping with us!" << endl;
        shoppingCart.displayCart();
    }

    void loadItemsFromFile(const string& filename)
    {
        ifstream inputFile(filename);
        if (!inputFile.is_open())
        {
            cerr << "Error opening file: " << filename << endl;
            cerr << "Make sure the file exists and the path is correct." << endl;
            return;
        }
        itemsFromFile.clear();
        cout << "Reading items from file..." << endl; // Debug statement
        string line;
        while (getline(inputFile, line))
        {
            // Parse each line to extract item number and name
            stringstream ss(line);
            string itemNumber, itemName;
            double itemPrice;
            ss >> itemNumber;  // Read item number
            // Check if the read is successful and the item number ends with a dot
            if (!ss.fail() && itemNumber.back() == '.')
            {
                ss >> itemName >> itemPrice;  // Read item name and price
                // Remove the dot from the item number
                itemNumber.pop_back();
                itemsFromFile.push_back({itemName, itemPrice});
            }
        }
        inputFile.close();

        // Debug statement to check the number of items loaded
        cout << "Number of items loaded: " << itemsFromFile.size() << endl;
    }

private:
    vector<Item> itemsFromFile;  // Items loaded from the file
    ShoppingCart shoppingCart;
};

int main() 
{
    ECommerceWebsite ecommerce;
    ecommerce.loadItemsFromFile("/Users/saivarun/Desktop/Assignments/2nd Year/C++/c++.txt");
    ecommerce.startShopping();
    return 0;
}
