# Joshi-card

# 💳 Credit Card Validator & Manager — C++ Project

A C++ Object-Oriented program that validates, classifies, and manages credit card data like a pro! Built with full-fledged features including card number verification using the **Luhn algorithm**, card type detection, expiry alerts, CVV validation, file logging, and even a mock AI risk score. 🔐🧠

---

## 🚀 Features

✔️ **Card Number Validation**  
- Uses Luhn’s Algorithm to check if the card is structurally valid.

✔️ **Card Type Detection**  
- Identifies if the card is **Visa**, **MasterCard**, **American Express**, or Unknown.

✔️ **Masked Card Number**  
- Displays only the last 4 digits for privacy (e.g., `XXXX-XXXX-XXXX-1234`).

✔️ **Expiry Date Check**  
- Warns if the card is expired, valid, or close to expiry with visual indicators (🟢🟡🔴).

✔️ **CVV Validation**  
- Ensures 3-digit for most cards, 4-digit for AmEx.

✔️ **AI Risk Score (Mocked)**  
- Random score (0–1) showing a fake “risk level” for demo/testing/fun.

✔️ **Exception Handling**  
- Handles input errors like incorrect lengths or formatting.

✔️ **File I/O Logging**  
- Stores processed card details in a `card_log.txt` file.

✔️ **OOP Best Practices**  
- Fully modular using `CreditCard` & `EnhancedCard` classes.

---

## 📁 File Structure

```bash
📦 credit-card-validator/
├── main.cpp            # Main application code
├── card_log.txt        # Output log file (generated after run)
├── README.md           # This file!
