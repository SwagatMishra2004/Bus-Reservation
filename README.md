# 🚌 Bus Reservation System with Email Notifications

![C Language](https://img.shields.io/badge/Language-C-blue.svg)
![Node.js](https://img.shields.io/badge/Backend-Node.js-green.svg)
![License](https://img.shields.io/badge/License-MIT-lightgrey.svg)

A terminal-based **C application** that allows users to book and cancel bus tickets. On each transaction, an email notification is sent to the user using **Node.js (Nodemailer)**.

---

## 📸 Screenshots

### 🔹 Main Menu
![image](https://github.com/user-attachments/assets/7b139095-05c3-4f6f-b726-02e40a8c3b37)

### 🔹 Booking a Ticket
![screenshots](https://github.com/user-attachments/assets/33be4714-3b7b-409e-8a0e-4c9abcdf040b)

### 🔹 Booking Confirmation Email
![screenshots](https://github.com/user-attachments/assets/131b5948-f1fe-4fa5-9324-7dee5f0ad3a9)

### 🔹 Cancel a Ticket
![screenshots](https://github.com/user-attachments/assets/7a3f15cc-2fc7-496b-9428-1519cc5a40bf)

### 🔹 Cancellation Confirmation Email
![screenshot](https://github.com/user-attachments/assets/45f2979e-17a4-4581-9853-90fd10226e10)

---

## ✨ Features

- 📥 Book tickets with name, age, and email
- ❌ Cancel tickets using passenger name
- 📊 View bus status, available seats
- 📧 Automated email notifications for bookings & cancellations
- 🔄 Dynamic memory allocation for passenger list
- 💡 Easy-to-understand console UI

---

## 🛠 Prerequisites

### ✅ For C Code:
- GCC compiler (e.g. `gcc`)

### ✅ For Node.js:
- Node.js v14+
- Install Nodemailer via npm:

```bash
npm install nodemailer
```

---

## 🔧 Email Configuration

Edit the following section in `sendEmail.js`:

```javascript
auth: {
  user: 'your_email@gmail.com',
  pass: 'your_app_password' // use Gmail App Password
}
```

- Use Gmail App Password (https://myaccount.google.com/apppasswords)
- Enable 2-Step Verification if not already set up

---

## 🚀 How to Run

### 🔹 Step 1: Compile the C Code

```bash
gcc bus_reservation.c -o bus_reservation
```

### 🔹 Step 2: Run the Executable

```bash
./bus_reservation
```

### 🔹 Step 3: Node.js Script
No need to run separately — `sendEmail.js` is automatically called via `system()` from C.

---

## ✅ Sample Run

```text
=== Bus Reservation System ===
1. Book a Ticket
2. Cancel a Ticket
3. Check Bus Status
4. View All Buses
5. View Available Seats
6. Exit
Enter your choice: 1
Enter the bus number: 101
Enter number of tickets: 1
Enter passenger name: John
Enter passenger age: 28
Enter passenger email: john@example.com
Ticket booked successfully! Seat number: 1
```

> 📩 A confirmation email will be sent to `john@example.com`.

---

## 🧹 Limitations

- Data is not saved across sessions
- Email credentials are hardcoded (use environment variables or dotenv in real-world apps)
- No encryption or secure storage

---

## 💡 Future Enhancements

- Save data to file or database
- Admin dashboard (GUI or Web)
- Login system
- Print tickets as PDFs
