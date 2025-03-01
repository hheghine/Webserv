#!/usr/bin/env python3

import cgi
import time

# Required HTTP headers
print("Content-Type: text/html\r\n\r\n")

# Retrieve form data
form = cgi.FieldStorage()
name = form.getvalue("name")
age = form.getvalue("age")

# Simulate long processing
# time.sleep(10)

# Generate HTML content with user information
html_content = f"""
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>User Information</title>
    <style>
        @import url('https://fonts.googleapis.com/css2?family=Inter:ital,opsz,wght@0,14..32,100..900;1,14..32,100..900&display=swap');

        body {{
            font-family: 'Inter', sans-serif;
            background-color: #0a0a0a;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
            padding: 0;
            color: #fff;
            text-align: center;
            background-image: url('https://www.transparenttextures.com/patterns/starry-night.png');
            background-size: cover;
            background-attachment: fixed;
            overflow: hidden;
        }}

        .container {{
            background-color: rgba(0, 0, 0, 0.7);
            padding: 2rem;
            border-radius: 15px;
            box-shadow: 0 0 25px rgba(255, 75, 92, 0.7);
            width: 90%;
            max-width: 600px;
        }}

        h1 {{
            font-size: 2.5rem;
            color: #ff4b5c;
            text-shadow: 0 0 15px rgba(255, 75, 92, 0.7);
            margin-bottom: 1.5rem;
        }}

        p {{
            font-size: 1.5rem;
            color: #00ff99;
            text-shadow: 0 0 10px rgba(0, 255, 153, 0.6);
        }}
    </style>
</head>
<body>
    <div class="container">
        <h1>Welcome, {name}!</h1>
        <p>Your age is {age} years old.</p>
    </div>
</body>
</html>
"""

print(html_content)
