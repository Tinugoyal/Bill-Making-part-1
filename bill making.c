#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 26
#define MAX_CART  50

typedef struct {
    int id;
    char name[30];
    float gstRate;   // GST % for this category
} ItemType;

typedef struct {
    char name[30];
    float price;
    float gstRate;
    int qty;
} CartLine;

int main() {
    // Categories WITHOUT fixed price
    ItemType types[MAX_ITEMS] = {
    {1,  "Fresh Veggies",   0.0},
    {2,  "Fresh Fruits",    0.0},
    {3,  "Milk",            0.0},
    {4,  "Curd",            0.0},
    {5,  "Eggs",            0.0},
    {6,  "Unpacked Rice",   0.0},
    {7,  "Unpacked Wheat",  0.0},
    {8,  "Unpacked toffee", 0.0},
    {9, "Gold Jewellery",   3.0},
    {10,  "Branded Rice",   5.0},
    {11, "Branded Atta",    5.0},
    {12, "Cooking Oil",     5.0},
    {13, "Tea (packed)",    5.0},
    {14, "Coffee (packed)", 5.0},
    {15, "Biscuits",        12.0},
    {16, "Packed Chips",    12.0},
    {17, "Soft Drink",      28.0},
    {18, "Cold Drink",      28.0},
    {19, "Shampoo",         18.0},
    {20, "Soap",            18.0},
    {21, "Toothpaste",      18.0},
    {22, "Detergent",       18.0},
    {23, "Face Cream",      18.0},
    {24, "Mobile Phone",    18.0},
    {25, "Laptop",          18.0},
    {26, "Headphones",      18.0},
        
    };

    CartLine cart[MAX_CART];
    int cartCount = 0;

    char more = 'y';
    int choice, qty;
    float price;

    printf("===== GENERIC MART BILLING (NO FIXED PRICES) =====\n");

    while (more == 'y' || more == 'Y') {
        printf("\nItem Categories:\n");
        printf("ID  %-15s   GST%%\n", "Name");
        for (int i = 0; i < MAX_ITEMS; i++) {
            printf("%-3d %-15s   %5.1f%%\n", types[i].id, types[i].name, types[i].gstRate);
        }

        printf("\nEnter Item ID (category): ");
        scanf("%d", &choice);

        // Find category
        ItemType *sel = NULL;
        for (int i = 0; i < MAX_ITEMS; i++) {
            if (types[i].id == choice) {
                sel = &types[i];
                break;
            }
        }

        if (sel == NULL) {
            printf("Invalid Item ID!\n");
        } else {
            printf("Enter quantity: ");
            scanf("%d", &qty);
            printf("Enter price per unit (Rs): ");
            scanf("%f", &price);

            if (cartCount < MAX_CART) {
                strcpy(cart[cartCount].name, sel->name);
                cart[cartCount].price = price;
                cart[cartCount].gstRate = sel->gstRate;
                cart[cartCount].qty = qty;
                cartCount++;
                printf("Added %d x %s (%.2f each) to cart.\n", qty, sel->name, price);
            } else {
                printf("Cart is full!\n");
            }
        }

        printf("\nAdd another item? (y/n): ");
        scanf(" %c", &more);
    }

    // Generate bill
    float grandSubTotal = 0.0, grandGST = 0.0, grandTotal = 0.0;

    printf("\n========== FINAL BILL ==========\n");
    printf("%-15s %5s %10s %8s %10s %10s\n",
           "Item", "Qty", "Price", "GST%", "Amount", "Total");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < cartCount; i++) {
        CartLine cl = cart[i];
        qty = cl.qty;

        float amount = cl.price * qty;
        float gstAmt = amount * cl.gstRate / 100.0f;
        float total = amount + gstAmt;

        grandSubTotal += amount;
        grandGST += gstAmt;
        grandTotal += total;

        printf("%-15s %5d %10.2f %8.1f %10.2f %10.2f\n",
               cl.name, qty, cl.price, cl.gstRate, amount, total);
    }

    printf("-------------------------------------------------------------\n");
    printf("%-31s %10.2f %10.2f\n", "Sub-total (before GST):", grandSubTotal, grandSubTotal);
    printf("%-31s %10.2f\n", "Total GST:", grandGST);
    printf("%-31s %10.2f\n", "GRAND TOTAL:", grandTotal);
    printf("=============================================\n");

    return 0;
}
