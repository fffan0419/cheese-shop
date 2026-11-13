#include "splashkit.h"
#include "utilities.h"
#include "cheese-shop.h"

#include <format>
using std::format;

/**
 * The list of options in the main menu.
 */
enum main_menu_option
{
    EXIT_MAIN_MENU,
    ADD_CHEESE_MENU,
    EDIT_CHEESE_MENU,
    PRINT_STOCK_LIST_MENU,
    DELETE_CHEESE_MENU,
    // REQUIREMENT 3: Extend CLI to use new model
    CREATE_ORDER_MENU
};

/**
 * Output the cheese data to the terminal – on a single line.
 */
void print_cheese(const cheese_data &cheese, bool with_full_details)
{
    write_line(cheese_to_string(cheese, with_full_details));
}

/**
 * Read data from the user and populate and return the cheese
 * data to the caller. Uses cheese_valid to validate input.
 */
cheese_data read_cheese()
{
    cheese_data result;
    do
    {
        result.name = read_string("Enter cheese name: ");
        result.weight = read_double("Enter weight in stock (kg): ");
        result.price_per_kg = read_integer("Enter price per kg (cents): ");
    } while (!cheese_valid(result));

    return result;
}

/**
 * Allow the user to edit the passed in cheese.
 */
void edit_cheese(cheese_data &cheese)
{
    write_line("Editing cheese: " + cheese_to_string(cheese, true));

    if ( read_integer("Do you want to edit the name? (1 for yes, 0 for no): ", 0, 1) == 1 )
    {
        cheese.name = read_string("Enter new cheese name: ");
    }
    if ( read_integer("Do you want to edit the weight? (1 for yes, 0 for no): ", 0, 1) == 1 )
    {
        cheese.weight = read_double("Enter new weight in stock (kg): ");
    }
    if ( read_integer("Do you want to edit the price? (1 for yes, 0 for no): ", 0, 1) == 1 )
    {
        cheese.price_per_kg = read_integer("Enter new price per kg (cents): ");
    }
}

/**
 * Output these cheeses – optionally with the index.
 */
void print_cheese_list(const dynamic_array<cheese_data> &cheeses, bool with_ids)
{
    for (int i = 0; i < cheeses.length(); i++)
    {
        cheese_data cheese = cheeses[i];
        if (with_ids)
        {
            write(to_string(i + 1) + ": ");
        }
        print_cheese(cheese, true);
    }
}
/**
 * Ask the user to select a cheese from the supplied list.
 * Return user‑entered number (1‑based view number, 0 = cancel)
 */
int select_cheese(const dynamic_array<cheese_data> &cheeses)
{
    if (cheeses.length() == 0)
    {
        write_line("No cheese in stock.");
        return -1;
    }

    write_line("0: Select none");
    print_cheese_list(cheeses, true);

    return read_integer("Select cheese (0 - " + to_string(cheeses.length()) + "): ");
}

/**
 * Perform the steps needed to add a cheese to the shop.
 */
void handle_add_cheese(shop_data &shop)
{
    cheese_data new_cheese = read_cheese();
    add_cheese(shop, new_cheese);
}

/**
 * Perform the steps to allow the user to edit a cheese in the shop.
 */
void handle_edit_cheese(shop_data &shop)
{
    int choice_num = select_cheese(shop.cheeses);
    if (choice_num <= 0) return;
    int array_index = choice_num - 1;
    edit_cheese(shop.cheeses[array_index]);
}

/**
 * Handle deleting a cheese from shop
 */
void handle_delete_cheese(shop_data &shop)
{
    int choice_num = select_cheese(shop.cheeses);
    if (choice_num <= 0)
    {
        write_line("Delete cancelled.");
        return;
    }
    int array_index = choice_num - 1;
    delete_cheese(shop, array_index);
    write_line("Cheese deleted successfully!");
}

// REQUIREMENT 3: Extend CLI to use new model
/**
 * Handle create new order user workflow
 */
void handle_create_order(shop_data &shop)
{
    string cust_name = read_string("Enter customer name: ");
    order_data order = new_order(cust_name); //local variables declaration

    write_line("\nSelect cheese to add to this order:");
    int choice_num = select_cheese(shop.cheeses);
    if(choice_num > 0)
    {
        int idx = choice_num - 1;
        add_cheese_to_order(order, shop.cheeses[idx]);
        calculate_order_total(order);
        write_line("Added cheese to order!");
    }

    write_line("\nOrder for " + order.customer_name);
    write_line("Order total: $" + to_string(order.total_cents / 100.0));
}

/**
 * Show the main menu and get the chosen option from the user.
 */
main_menu_option read_main_menu_option()
{
    write_line("\n0. Exit");
    write_line("1. Add cheese");
    write_line("2. Edit cheese");
    write_line("3. Print cheese list");
    write_line("4. Delete cheese");
    // REQUIREMENT 3: Extend CLI to use new model
    write_line("5. Create new order");

    return (main_menu_option)read_integer("Select an option (0–5): ", 0, 5);
}

void print_stock_list(const shop_data &shop)
{
    if (shop.cheeses.length() == 0)
    {
        write_line("No cheese");
        return;
    }

    write_line();
    write_line("========================================");
    write_line("Cheese stock list:");
    write_line("========================================");

    print_cheese_list(shop.cheeses, false);

    write_line("========================================");
    write_line();
}

int main()
{
    shop_data shop;
    main_menu_option choice;

    do
    {
        choice = read_main_menu_option();

        switch (choice)
        {
            case EXIT_MAIN_MENU:
                write_line("Exiting...");
                break;
            case ADD_CHEESE_MENU:
                handle_add_cheese(shop);
                break;
            case EDIT_CHEESE_MENU:
                handle_edit_cheese(shop);
                break;
            case PRINT_STOCK_LIST_MENU:
                print_stock_list(shop);
                break;
            case DELETE_CHEESE_MENU:
                handle_delete_cheese(shop);
                break;
            // REQUIREMENT 3: Extend CLI to use new model
            case CREATE_ORDER_MENU:
                handle_create_order(shop);
                break;
        }
    } while (choice != EXIT_MAIN_MENU);

    return 0;
}