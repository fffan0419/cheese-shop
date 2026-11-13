#include "splashkit.h"
#include "splashkit-arrays.h"
// Cheese stock data
struct cheese_data
{
    string name;
    double weight;
    int price_per_kg;
};
// Shop data with dynamic array of cheese
struct shop_data
{
    dynamic_array<cheese_data> cheeses;
};
// REQUIREMENT 1: Design a change to the program data (add new struct)
struct order_data
{
    string customer_name;
    dynamic_array<cheese_data> items;
    int total_cents;
};
// Create new cheese, parameters have default values
cheese_data new_cheese(string name = "", double weight = 0.0, int price_per_kg = 0);

// Convert cheese to string, full_details for complete info
string cheese_to_string(const cheese_data &cheese, bool full_details = false);

// Return total cost in cents
int total_cost(const cheese_data &cheese);

// Reduce cheese weight, return actual removed kg, ignore negative input
double reduce_weight(cheese_data &cheese, double reduce_kg);

// Add weight to cheese stock, ignore negative input
void increase_weight(cheese_data &cheese, double add_kg);

// Add a new cheese to the shop's cheese list
void add_cheese(shop_data &shop, const cheese_data &new_cheese);

// Remove cheese at given index from shop
void delete_cheese(shop_data &shop, int index);

// Check if cheese data is valid, print error messages
bool cheese_valid(const cheese_data &cheese);

// REQUIREMENT 2: Add additional features to the model
// Create empty new order(function declaration)
order_data new_order(string customer = "");

// Add cheese item into order
void add_cheese_to_order(order_data &order, const cheese_data &cheese);

// Calculate sum total of order in cents
int calculate_order_total(order_data &order);