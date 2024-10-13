#include <iostream>
#include <iomanip> // Spacing
#include <string> // String functions
#include <cstdio> // printf, scanf, etc.
#include <limits> // cin.ignore
using namespace std;

// Function to convert a string to lowercase
string toLowerCase(const string &str) {
    string lowerStr = str;
    for (int i = 0; i < str.length(); i++) {
        lowerStr[i] = tolower(str[i]);
    }
    return lowerStr;
}

// Function to check if a category is valid
bool isValidCategory(string category) {
    string lowerCategory = toLowerCase(category);
    return (lowerCategory == "clothing" || lowerCategory == "electronics" || lowerCategory == "entertainments");
}

// Function to input an integer
int inputInteger(const string &prompt) {
    int value;
    cout << prompt;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid integer: ";
    }
    return value;
}

// Function to input a double
double inputDouble(const string &prompt) {
    double value;
    cout << prompt;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid number: ";
    }
    return value;
}

// Abstract base class for inventory items
class inventoryItem {
public:
    virtual ~inventoryItem() {}
    virtual string getId() const = 0;
    virtual string getName() const = 0;
    virtual int getQuantity() const = 0;
    virtual double getPrice() const = 0;
    virtual string getCategory() const = 0;
    virtual void setQuantity(int quantity) = 0;
    virtual void setPrice(double price) = 0;
};

// Concrete implementation of an inventory item
class Item : public inventoryItem {
private:
    string id;
    string name;
    int quantity;
    double price;
    string category;

public:
    Item(string id, string name, int quantity, double price, string category)
        : id(id), name(name), quantity(quantity), price(price), category(category) {}

    string getId() const override {
        return id;
    }

    string getName() const override {
        return name;
    }

    int getQuantity() const override {
        return quantity;
    }

    double getPrice() const override {
        return price;
    }

    string getCategory() const override {
        return category;
    }

    void setQuantity(int quantity) override {
        this->quantity = quantity;
    }

    void setPrice(double price) override {
        this->price = price;
    }
};

// Abstract base class for the inventory manager
class inventoryManager {
public:
    virtual ~inventoryManager() {}

    virtual void addItem(inventoryItem* item) = 0;
    virtual void displayItemsByCategory(string category) = 0;
    virtual void updateItem(string id, string field, int newValue) = 0;
    virtual void updateItemPrice(string id, double newValue) = 0;
    virtual void removeItem(string id) = 0;
    virtual void displayAllItems() = 0;
    virtual void searchItem(string id) = 0;
    virtual void sortItems(string field, string order) = 0;
    virtual void displayLowStockItems() = 0;
};

// Concrete implementation of an inventory manager using dynamic arrays
class Inventory : public inventoryManager {
private:
    inventoryItem** items;
    int size;
    int capacity;

public:
    Inventory() {
        size = 0;
        capacity = 100; // Maximum of 100 items for now
        items = new inventoryItem*[capacity];
    }

    ~Inventory() {
        for (int i = 0; i < size; i++) {
            delete items[i];
        }
        delete[] items;
    }

    void addItem(inventoryItem* item) override {
        if (size >= capacity) {
            cout << "Inventory is full, cannot add more items." << endl;
            return;
        }
        items[size] = item;
        size++;
        cout << "Item added successfully!" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        cin.get();
    }

    void displayItemsByCategory(string category) override 
    {
        bool found = false;
        cout << "ID" << fixed
             << setw(15) << "Name"
             << setw(15) << "Quantity"
             << setw(15) << "Price"
             << endl;
        for (int i = 0; i < size; i++) {
            if (items[i]->getCategory() == toLowerCase(category)) {
                found = true;
                cout << items[i]->getId()
                     << setw(15) << items[i]->getName()
                     << setw(15) << items[i]->getQuantity()
                     << setw(15) << items[i]->getPrice()
                     << endl;
            }
        }
        if (!found) {
            cout << "Category " << category << " does not exist!" << endl;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        cin.get();
    }

    void updateItem(string id, string field, int newValue) override 
    {
        for (int i = 0; i < size; i++) {
            if (items[i]->getId() == id) {
                if (field == "quantity") {
                    int oldQuantity = items[i]->getQuantity();
                    items[i]->setQuantity(newValue);
                    cout << "Quantity of Item " << items[i]->getName() << " is updated from " << oldQuantity << " to " << newValue << endl;
                }
                return;
            }
        }
        cout << "Item not found!" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        cin.get();
    }

    void updateItemPrice(string id, double newValue) override 
    {
        for (int i = 0; i < size; i++) {
            if (items[i]->getId() == id) {
                double oldPrice = items[i]->getPrice();
                items[i]->setPrice(newValue);
                cout << "Price of Item " << items[i]->getName() << " is updated from " << oldPrice << " to " << newValue << endl;
                return;
            }
        }
        cout << "Item not found!" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        cin.get();
    }

    void removeItem(string id) override 
    {
        for (int i = 0; i < size; i++) {
            if (items[i]->getId() == id) {
                delete items[i];
                for (int j = i; j < size - 1; j++) {
                    items[j] = items[j + 1];
                }
                size--;
                cout << "Item removed successfully!" << endl;
                return;
            }
        }
        cout << "Item not found!" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        cin.get();
    }

    void displayAllItems() override {
        cout << "ID" << fixed
             << setw(15) << "Name"
             << setw(15) << "Quantity"
             << setw(15) << "Price"
             << setw(15) << "Category"
             << endl;
        for (int i = 0; i < size; i++) {
            cout << items[i]->getId()
                 << setw(15) << items[i]->getName()
                 << setw(15) << items[i]->getQuantity()
                 << setw(15) << items[i]->getPrice()
                 << setw(15) << items[i]->getCategory()
                 << endl;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        cin.get();
    }

    void searchItem(string id) override 
    {
        for (int i = 0; i < size; i++) {
            if (items[i]->getId() == id) {
                cout << "ID: " << items[i]->getId() << endl;
                cout << "Name: " << items[i]->getName() << endl;
                cout << "Quantity: " << items[i]->getQuantity() << endl;
                cout << "Price: " << items[i]->getPrice() << endl;
                cout << "Category: " << items[i]->getCategory() << endl;
                return;
            }
        }
        cout << "Item not found!" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        cin.get();
    }

    void sortItems(string field, string order) override 
    {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                bool condition = false;
                if (field == "quantity") {
                    if (order == "ascending") {
                        condition = items[j]->getQuantity() > items[j + 1]->getQuantity();
                    } else {
                        condition = items[j]->getQuantity() < items[j + 1]->getQuantity();
                    }
                } else if (field == "price") {
                    if (order == "ascending") {
                        condition = items[j]->getPrice() > items[j + 1]->getPrice();
                    } else {
                        condition = items[j]->getPrice() < items[j + 1]->getPrice();
                    }
                }

                if (condition) {
                    inventoryItem* temp = items[j];
                    items[j] = items[j + 1];
                    items[j + 1] = temp;
                }
            }
        }
        displayAllItems();

        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        cin.get();
    }

    void displayLowStockItems() override 
    {
        cout << "ID" << fixed
             << setw(15) << "Name"
             << setw(15) << "Quantity"
             << setw(15) << "Price"
             << setw(15) << "Category"
             << endl;
        for (int i = 0; i < size; i++) {
            if (items[i]->getQuantity() < 5) {
                cout << items[i]->getId()
                     << setw(15) << items[i]->getName()
                     << setw(15) << items[i]->getQuantity()
                     << setw(15) << items[i]->getPrice()
                     << setw(15) << items[i]->getCategory()
                     << endl;
            }
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        cin.get();
    }
};

int main() {
    Inventory inventory;
    bool repeat = true;
    do {
        int choices;
        printf(
            "\n M E N U \n"
            "1 - Add Item\n"
            "2 - Update Item\n"
            "3 - Remove Item\n"
            "4 - Display Items by Category\n"
            "5 - Display All Items\n"
            "6 - Search Item\n"
            "7 - Sort Items\n"
            "8 - Display Low Stock Items\n"
            "9 - Exit\n"
        );
        cout << endl;
        cout << "Your Choices: " << endl;
        cin >> choices;
        
        // Prevents looping if the user input letters instead of numbers
        while(1)
        {
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout<<"You have entered wrong input"<<endl;
                cin>>choices;
            }
            if(!cin.fail())
            break;
        }

        switch (choices)  
        {
        case 1:
        {
            printf("\n==================== Add Item ====================\n");
            printf(
                "\n O P T I O N S \n"
                "Clothing\n"
                "Electronics\n"
                "Entertainments\n"
            );
            cout << endl;
            string category;
            cout << "Enter Category: ";
            cin >> category;
            //This is to prevent  the user from entering wrong input mainly numbers so it will only accept letters. 
            if (isValidCategory(category)) 
            {
                string id;
                while(true)
                {
                        cout << "Enter ID: ";
                        cin >> id;
                        bool isValidId = true;
                    for (char c : id) 
                    {
                    //!isalpha() checks whether a character is an alphabet (a to z and A to Z) or not.
                    if (!isalpha(c)) 
                    {
                    isValidId = false;
                    break;
                    }
                    }
                    if (isValidId) 
                    {
                    break;
                    } 
                    else
                    {
                    cout << "Invalid ID. ID should only contain letters. Please try again." << endl;
                    }  
                }
                //The continuation of the add item
                string name;
                cout << "Enter Name: ";
                getline(cin,name);
                int quantity = inputInteger("Enter Quantity: ");
                double price = inputDouble("Enter Price: ");
                inventoryItem* item = new Item(id, name, quantity, price, category);
                inventory.addItem(item);
            }  else {
                cout << "Category "<< category <<" does not exist" << endl;
            }
            break;
        }

        case 2:
        {
            printf("\n==================== Update Item ====================\n");
            
            string id;
            cout << "Enter ID: ";
            cin >> id;
            string field;
            cout << "Enter Field (quantity/price): ";
            cin >> field;

            if (field == "price") 
            {
                double newValue = inputDouble("Enter New Value: ");
                inventory.updateItemPrice(id, newValue);
            } 
            else 
            {
                int newValue = inputInteger("Enter New Value: ");
                inventory.updateItem(id, field, newValue);
            }
            break;
        }

        case 3:
        {
            printf("\n==================== Remove Item ====================\n");
            string idRemove;
            cout << "Enter ID: ";
            cin >> idRemove;
            inventory.removeItem(idRemove);
            break;
        }

        case 4:
        {
            printf("\n==================== Display Items by Category ====================\n");
            string category;
            printf(
                "\n O P T I O N S \n"
                "Clothing\n"
                "Electronics\n"
                "Entertainments\n"
            );
            cout << endl;
            cout << "Enter Category: ";
            cin >> category;
            
            //This is for case sensitivity 
            if (isValidCategory(category)) 
            {
            inventory.displayItemsByCategory(category);
            } 
            else 
            {
                cout << "Category "<< category <<" does not exist!" << endl;
            }
            break;
        }

        case 5:
            printf("\n==================== Display All Items ====================\n");
            inventory.displayAllItems();
            break;

        case 6:
        {
            printf("\n==================== Search Item ====================\n");
            string idSearch;
            cout << "Enter ID: ";
            cin >> idSearch;
            inventory.searchItem(idSearch);            
            break;
        }

        case 7: 
        {
            printf("\n==================== Sort Items ====================\n");
            string field;
            cout << "Enter Field (quantity/price): ";
            cin >> field;
            string order;
            cout << "Enter Order (ascending/descending): ";
            cin >> order;
            inventory.sortItems(field, order);
            break;
        }

        case 8:
            printf("\n==================== Display Low Stock Items ====================\n");
            inventory.displayLowStockItems();
            break;

        case 9:
            repeat = false;
            break;

        default:
            cout << "Invalid Choice!" << endl;
        }
    } while (repeat);
    return 0;
} 