#include "splashkit.h"
#include "utilities.h"
#include "cheese-shop.h"
#include <format>
using std::format;

// Initialise cheese struct
cheese_data new_cheese(string name, double weight, int price_per_kg)
{
    cheese_data cheese;
    cheese.name = name;
    cheese.weight = weight;
    cheese.price_per_kg = price_per_kg;
    return cheese;
}

// Format cheese as string
string cheese_to_string(const cheese_data &cheese, bool full_details)
{
    if (full_details)
    {
        return cheese.name + ": " 
            + to_string(cheese.weight) + " kg, $" 
            + to_string(cheese.price_per_kg / 100.0) + "/kg, Total: $" 
            + to_string(total_cost(cheese) / 100.0);
    }
    else
    {
        return cheese.name;
    }
}

// Calculate total cost in cents
int total_cost(const cheese_data &cheese)
{
    return static_cast<int>(cheese.weight * cheese.price_per_kg);
}

// Subtract weight, return real amount removed
double reduce_weight(cheese_data &cheese, double reduce_kg)
{
    if(reduce_kg <= 0)
    {
        return 0.0;
    }
    double actual_remove;
    if(reduce_kg >= cheese.weight)
    {
        actual_remove = cheese.weight;
        cheese.weight = 0.0;
    }
    else
    {
        actual_remove = reduce_kg;
        cheese.weight -= reduce_kg;
    }
    return actual_remove;
}

// Add weight to stock
void increase_weight(cheese_data &cheese, double add_kg)
{
    if(add_kg > 0)
    {
        cheese.weight += add_kg;
    }
}

// Add cheese into shop dynamic array
void add_cheese(shop_data &shop, const cheese_data &new_cheese)
{
    shop.cheeses.add(new_cheese);
}

// Delete cheese at index
void delete_cheese(shop_data &shop, int index)
{
    if(index >= 0 && index < shop.cheeses.length())
    {
        shop.cheeses.remove_at(index);
    }
}

// Check cheese validity
bool cheese_valid(const cheese_data &cheese)
{
    bool valid = true;

    if (cheese.name.empty())
    {
        write_line("Name is empty");
        valid = false;
    }
    if (cheese.weight < 0)
    {
        write_line("Weight cannot be negative");
        valid = false;
    }
    if (cheese.price_per_kg < 0)
    {
        write_line("Price cannot be negative");
        valid = false;
    }
    return valid;
}

// REQUIREMENT 2: Add additional features to the model
// Create new empty order
order_data new_order(string customer)
{
    order_data order; //variables declaration
    order.customer_name = customer;
    order.total_cents = 0;
    return order;
}

// Add cheese item to order
void add_cheese_to_order(order_data &order, const cheese_data &cheese)
{
    order.items.add(cheese);
}

// Calculate order total sum
int calculate_order_total(order_data &order)
{
    int sum = 0;
    for(int i = 0; i < order.items.length(); i++)
    {
        sum += total_cost(order.items[i]);
    }
    order.total_cents = sum;
    return sum;
}