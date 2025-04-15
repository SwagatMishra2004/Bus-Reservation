# 🚌 Bus Reservation System (with Email Notifications)

A terminal-based **C program** for booking and canceling bus tickets. It features basic bus and passenger management, along with email notifications powered by **Node.js (Nodemailer)**.

---

## 📁 Files

- `bus_reservation.c`: Main C program to run the reservation system.
- `sendEmail.js`: Node.js script to send booking/cancellation emails using Gmail.

---

## ⚙️ Features

- ✅ Book tickets with passenger details (name, age, email)
- ❌ Cancel tickets by passenger name
- 🚌 View all buses and their status
- 📧 Email notification on ticket **booking** and **cancellation**
- 🔄 Dynamic memory allocation for passengers

---

## 🛠 Requirements

### C Environment
- GCC compiler

### Node.js Environment
- Node.js v14 or later
- Nodemailer package

```bash
npm install nodemailer
