// ... (Previous test function definitions) ...

// ========== calculateChange Tests (Hypothetical Function) ========== //
// Assume a function: float calculateChange(float price, float money_inserted)

void test_calculateChange_positive_change(void) {
    // Price: $1.50, Money: $2.00. Expected Change: $0.50
    TEST_ASSERT_EQUAL_FLOAT(0.50, calculateChange(1.50, 2.00));
}

void test_calculateChange_no_change(void) {
    // Price: $1.25, Money: $1.25. Expected Change: $0.00
    TEST_ASSERT_EQUAL_FLOAT(0.00, calculateChange(1.25, 1.25));
}

void test_calculateChange_larger_change(void) {
    // Price: $1.00, Money: $5.00. Expected Change: $4.00
    TEST_ASSERT_EQUAL_FLOAT(4.00, calculateChange(1.00, 5.00));
}

void test_calculateChange_insufficient_money(void) {
    // Price: $2.00, Money: $1.50. Expected Change: $-0.50 (Negative change indicates insufficient funds)
    TEST_ASSERT_EQUAL_FLOAT(-0.50, calculateChange(2.00, 1.50));
}

// ========== checkLabel Tests (Additional Edge Case) ========== //

void test_checkLabel_invalid_upper_bound(void) {
    // Assuming A19 is the last valid index, 20 should be invalid.
    // This is similar to test_checkLabel_invalid_20 but clarifies the boundary.
    TEST_ASSERT_EQUAL(0, checkLabel(20));
}

// ========== purchase Tests (Additional Edge Cases) ========== //

void test_purchase_money_rounding_issue(void) {
    // Test for potential floating point comparison issues, e.g., $1.50 vs $1.499999
    int original_qty = vendingMachine[A0].quantity;
    
    // Exact change, but provided with a slight rounding error (e.g., from input conversion)
    item purchased = purchase(A0, 1.500001);
    
    TEST_ASSERT_EQUAL_STRING("Chips", purchased.name);
    // Quantity should decrease even with tiny excess money
    TEST_ASSERT_EQUAL(original_qty - 1, vendingMachine[A0].quantity);
    
    // Restore quantity (important for test isolation)
    vendingMachine[A0].quantity = original_qty; 
}

void test_purchase_maximum_index(void) {
    // Assuming A19 is the maximum valid label
    int original_qty = vendingMachine[A19].quantity;
    
    // Make sure A19 is stocked for this test
    if (original_qty == 0) {
        vendingMachine[A19].quantity = 1;
        original_qty = 1;
    }
    
    item purchased = purchase(A19, 5.00);
    
    // We expect a successful purchase if A19 is valid and stocked
    TEST_ASSERT_EQUAL(original_qty - 1, vendingMachine[A19].quantity);

    // Restore original quantity
    vendingMachine[A19].quantity = original_qty; 
}

// ========== restock Tests (Additional Edge Case) ========== //

void test_restock_add_zero(void) {
    item original_item = vendingMachine[A0].product;
    int original_qty = vendingMachine[A0].quantity;
    
    int result = restock(A0, original_item, 0); // Should add 0 items
    
    TEST_ASSERT_EQUAL(0, result); // 0 items were excess
    TEST_ASSERT_EQUAL(original_qty, vendingMachine[A0].quantity); // Quantity should be unchanged
}

void test_restock_negative_amount(void) {
    // This is an invalid operation but should be handled gracefully, likely adding 0 and returning the absolute value as "excess" or 0 as "added."
    // Assuming the function handles it by not subtracting, and treating the request as adding 0 or as an error.
    item original_item = vendingMachine[A1].product;
    int original_qty = vendingMachine[A1].quantity;

    // Assuming restock only handles positive additions and prevents subtraction.
    int result = restock(A1, original_item, -5); 
    
    // Expect: The machine is unchanged, and 0 items were added, or all 5 were "excess" if the function design implies requested - actual_added = excess
    TEST_ASSERT_TRUE(result == 5 || result == 0); // Depends on implementation: 5 (all excess) or 0 (no change)
    TEST_ASSERT_EQUAL(original_qty, vendingMachine[A1].quantity);
}

void test_restock_updates_product_details_on_full_slot(void) {
    // The slot is already full, but the product details should still be updated.
    item new_gum = {"New Gum", 0.75};
    vendingMachine[A10].quantity = MAX_QUANTITY; // Set to full
    
    // Try to restock 1 item
    int result = restock(A10, new_gum, 1);
    
    TEST_ASSERT_EQUAL(1, result); // 1 item excess
    // Product details should update even if no items were added
    TEST_ASSERT_EQUAL_STRING("New Gum", vendingMachine[A10].product.name);
    TEST_ASSERT_EQUAL_FLOAT(0.75, vendingMachine[A10].product.price);
    TEST_ASSERT_EQUAL(MAX_QUANTITY, vendingMachine[A10].quantity); // Quantity remains full
}
