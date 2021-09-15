#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    // Task 1
    // Define variables here
    int balance = 0;

    int coin_5_left = 3;
    int coin_2_left = 3;
    int coin_1_left = 3;

    int item_A_left = 3;
    int item_B_left = 3;

    const int ITEM_A_PRICE = 6;
    const int ITEM_B_PRICE = 4;

    int actionChoice = 0;
    int coinInsertChoice = 0;
    int purchaseChoice = 0;

    while (1)
    {
        // Task 2
        cout << "The balance is $" << balance << endl;
        cout << "Please choose an action:" << endl;
        cout << "1. Insert coin" << endl;
        cout << "2. Purchase" << endl;
        cout << "3. Return coins" << endl;
        cout << "4. Leave" << endl;
        cout << "Please enter 1-4: ";

        cin >> actionChoice;

        if (actionChoice != 1 && actionChoice != 2 && actionChoice != 3 && actionChoice != 4) // user input an invalid action choice
        {
            cout << "Invalid choice" << endl;
            continue;
        }

        // Task 3
        else if (actionChoice == 1) // user decide to insert coin
        {
            cout << "Please insert a coin: $";
            cin >> coinInsertChoice;

            while (coinInsertChoice != 5 && coinInsertChoice != 2 && coinInsertChoice != 1)
            {
                cout << "Only $5, $2 and $1 coins are accepted" << endl;
                cout << "Please insert a coin: $";
                cin >> coinInsertChoice;
            }

            balance += coinInsertChoice;
            if (coinInsertChoice == 5)
                coin_5_left++;
            if (coinInsertChoice == 2)
                coin_2_left++;
            if (coinInsertChoice == 1)
                coin_1_left++;
        }

        // Task 4
        else if (actionChoice == 2) // user decide to purchase item
        {
            while (1)
            {
                cout << "Please select an item:" << endl;
                if (item_A_left > 0)
                    cout << "1. Item A - $6" << endl;
                else
                    cout << "1. Item A - SOLD OUT" << endl;
                if (item_B_left > 0)
                    cout << "2. Item B - $4" << endl;
                else
                    cout << "2. Item B - SOLD OUT" << endl;
                cout << "3. Go back" << endl;
                cout << "Please enter 1-3: ";
                cin >> purchaseChoice;

                if (purchaseChoice == 3)
                {
                    break;
                }

                if (purchaseChoice != 1 && purchaseChoice != 2 && purchaseChoice != 3)
                {
                    cout << "Invalid choice" << endl;
                    continue;
                }

                if (purchaseChoice == 1)
                {
                    if (item_A_left <= 0)
                    {
                        cout << "Item A has been sold out" << endl;
                        continue;
                    }
                    else if (balance < ITEM_A_PRICE)
                    {
                        cout << "Insufficient balance" << endl;
                        continue;
                    }
                    else
                    {
                        balance -= ITEM_A_PRICE;
                        item_A_left--;
                        cout << "Purchased item A" << endl;
                        break;
                    }
                }
                if (purchaseChoice == 2)
                {
                    if (item_B_left <= 0)
                    {
                        cout << "Item B has been sold out" << endl;
                        continue;
                    }
                    else if (balance < ITEM_B_PRICE)
                    {
                        cout << "Insufficient balance" << endl;
                        continue;
                    }
                    else
                    {
                        balance -= ITEM_B_PRICE;
                        item_B_left--;
                        cout << "Purchased item B" << endl;
                        break;
                    }
                }
            }
        }

        // Task 5
        else if (actionChoice == 3) // user decide to return coin
        {
            while (coin_5_left > 0 && balance >= 5)
            {
                coin_5_left--;
                balance -= 5;
                cout << "Returned a $5 coin" << endl;
            }
            while (coin_2_left > 0 && balance >= 2)
            {
                coin_2_left--;
                balance -= 2;
                cout << "Returned a $2 coin" << endl;
            }
            while (coin_1_left > 0 && balance >= 1)
            {
                coin_1_left--;
                balance -= 1;
                cout << "Returned a $1 coin" << endl;
            }

            if (balance > 0)
                cout << "Oops... Not enough coins to return..." << endl;
        }
        
        // Task 6
        else if (actionChoice == 4) // user decide to leave
        {
            cout << "Bye" << endl;
            break;
        }
    }

    return 0;
}