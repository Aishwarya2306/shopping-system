#include <iostream>
#include <string>
using namespace std;

struct Product {
    string name;
    float price;
    int quantity;
};

class BobBank {
    float balance;
public:
    BobBank(float bal = 1000.0f) : balance(bal) {}
    float getBalance() { return balance; }

    bool withdraw(float amt) {
        if (amt <= balance) {
            balance -= amt;
            return true;
        }
        return false;
    }
};

class Shopping {
    Product cart[10], wishlist[10];
    int cartCount = 0, wishlistCount = 0;
    float totalAmount = 0;

    void safeInput() {
        cin.clear();
        cin.ignore(10000, '\n');
    }

public:
    void addToCart() {
        if (cartCount >= 10) {
            cout << "Cart is full.\n";
            return;
        }
        Product p;
        cout << "Enter product name: ";
        cin >> p.name;
        cout << "Enter price: ";
        while (!(cin >> p.price)) {
            cout << "Invalid input. Enter a valid price: ";
            safeInput();
        }
        cout << "Enter quantity: ";
        while (!(cin >> p.quantity)) {
            cout << "Invalid input. Enter a valid quantity: ";
            safeInput();
        }

        cart[cartCount++] = p;
        totalAmount += p.price * p.quantity;
        cout << "Added to cart.\n";
    }

    void viewCart() {
        if (cartCount == 0) {
            cout << "Cart is empty.\n";
            return;
        }
        cout << "\nYour Cart:\n";
        for (int i = 0; i < cartCount; ++i) {
            cout << i+1 << ". " << cart[i].name << " - ₹" << cart[i].price << " x " << cart[i].quantity << endl;
        }
        cout << "Total: ₹" << totalAmount << "\n";
    }

    void deleteFromCart() {
        if (cartCount == 0) {
            cout << "Cart is empty.\n";
            return;
        }
        int idx;
        cout << "Enter item number to delete: ";
        while (!(cin >> idx)) {
            cout << "Invalid input. Enter a valid number: ";
            safeInput();
        }
        if (idx < 1 || idx > cartCount) {
            cout << "Invalid index.\n";
            return;
        }
        totalAmount -= cart[idx-1].price * cart[idx-1].quantity;
        for (int i = idx-1; i < cartCount-1; ++i) {
            cart[i] = cart[i+1];
        }
        cartCount--;
        cout << "Deleted from cart.\n";
    }

    void addToWishlist() {
        if (wishlistCount >= 10) {
            cout << "Wishlist is full.\n";
            return;
        }
        Product p;
        cout << "Enter product name: ";
        cin >> p.name;
        cout << "Enter price: ";
        while (!(cin >> p.price)) {
            cout << "Invalid input. Enter a valid price: ";
            safeInput();
        }
        cout << "Enter quantity: ";
        while (!(cin >> p.quantity)) {
            cout << "Invalid input. Enter a valid quantity: ";
            safeInput();
        }

        wishlist[wishlistCount++] = p;
        cout << "Added to wishlist.\n";
    }

    void viewWishlist() {
        if (wishlistCount == 0) {
            cout << "Wishlist is empty.\n";
            return;
        }
        cout << "\nYour Wishlist:\n";
        for (int i = 0; i < wishlistCount; ++i) {
            cout << i+1 << ". " << wishlist[i].name << " - ₹" << wishlist[i].price << " x " << wishlist[i].quantity << endl;
        }
    }

    void deleteFromWishlist() {
        if (wishlistCount == 0) {
            cout << "Wishlist is empty.\n";
            return;
        }
        int idx;
        cout << "Enter item number to delete: ";
        while (!(cin >> idx)) {
            cout << "Invalid input. Enter a valid number: ";
            safeInput();
        }
        if (idx < 1 || idx > wishlistCount) {
            cout << "Invalid index.\n";
            return;
        }
        for (int i = idx-1; i < wishlistCount-1; ++i) {
            wishlist[i] = wishlist[i+1];
        }
        wishlistCount--;
        cout << "Deleted from wishlist.\n";
    }

    void pay(BobBank &bank) {
        if (cartCount == 0) {
            cout << "Cart is empty.\n";
            return;
        }
        cout << "Select Payment Mode:\n";
        cout << "1. Paytm\n2. PhonePe\n3. GPay\n4. Card\nChoice: ";
        int mode;
        while (!(cin >> mode)) {
            cout << "Invalid input. Enter a number: ";
            safeInput();
        }

        if (mode < 1 || mode > 4) {
            cout << "Invalid payment mode.\n";
            return;
        }

        if (mode == 4) {
            string cardNum, exp, cvv;
            cout << "Enter card number: ";
            cin >> cardNum;
            cout << "Enter expiry (MM/YY): ";
            cin >> exp;
            cout << "Enter CVV: ";
            cin >> cvv;
        }

        if (bank.withdraw(totalAmount)) {
            cout << "Payment successful! ₹" << totalAmount << " deducted.\n";
            cartCount = 0;
            totalAmount = 0;
        } else {
            cout << "Payment failed. Insufficient balance.\n";
        }
    }
};

int main() {
    BobBank bank;
    Shopping shop;
    int choice;

    while (true) {
        cout << "\n--- Shopping Menu ---\n";
        cout << "1. Add to Cart\n2. View Cart\n3. Delete from Cart\n";
        cout << "4. Add to Wishlist\n5. View Wishlist\n6. Delete from Wishlist\n";
        cout << "7. Pay Bill\n8. Exit\nEnter choice: ";
        while (!(cin >> choice)) {
            cout << "Invalid input. Enter a number between 1–8: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        switch (choice) {
            case 1: shop.addToCart(); break;
            case 2: shop.viewCart(); break;
            case 3: shop.deleteFromCart(); break;
            case 4: shop.addToWishlist(); break;
            case 5: shop.viewWishlist(); break;
            case 6: shop.deleteFromWishlist(); break;
            case 7: shop.pay(bank); break;
            case 8: cout << "Thanks for shopping!\n"; return 0;
            default: cout << "Invalid choice.\n";
        }
    }
}