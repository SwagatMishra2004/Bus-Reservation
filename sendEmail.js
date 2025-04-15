const nodemailer = require('nodemailer');
const action = process.argv[2];
const passengerName = process.argv[3];
const busNumber = process.argv[4];
const seatNumber = process.argv[5];
const email = process.argv[6]; // Added email argument
async function sendMail() {
    const transporter = nodemailer.createTransport({
        service: 'gmail',
        auth: {
            user: '*******************@gmail.com', //Enter your gmail
            pass: '#############' //Enter your Gmail Pass key 
        }
    });
    const mailOption = {
        from: 'swagatmishra888@gmail.com',
        to: email, 
        subject: `Ticket ${action}`,
        text: `Dear ${passengerName},\n\nYour ticket for Bus ${busNumber}, Seat ${seatNumber} has been ${action === "Booking" ? "booked" : "cancelled"}.\n\nThank you!`
    };
    try {
        await transporter.sendMail(mailOption);
        console.log('Email sent');
    } catch (error) {
        console.log('Email sent failed:', error);
    }
}

sendMail();
