#!/usr/bin/env python3

import cgitb
import os

# Enable debugging to show errors on the page
cgitb.enable()

# HTTP header to indicate the content is HTML
print("Content-Type: text/html; charset=utf-8")

def get_client_id():
    cookies = os.environ.get('HTTP_COOKIE', '')
    client_id = None

    for cookie in cookies.split(';'):
        parts = cookie.strip().split('=', 1)
        if len(parts) == 2:
            name, value = parts
            if name == "id":
                client_id = value
                break
    return client_id

client_id = get_client_id()

if client_id is not None:
    # Remove the user's data file if it exists
    user_data_file = f"./www/login/database/{client_id}.txt"
    if os.path.exists(user_data_file):
        os.remove(user_data_file)
    
    # Expire the cookie to log out
    print("Set-Cookie: id=; Expires=Thu, 01 Jan 1970 00:00:00 GMT; Path=/\r\n")
    message = "Your account has been successfully deleted."
else:
    message = "An error occurred while logging out."

# HTML page structure
page = f"""
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Logout Page</title>
    <style>
        @import url('https://fonts.googleapis.com/css2?family=Inter:wght@400;600;800&display=swap');

        * {{
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }}
        body {{
            font-family: 'Inter', sans-serif;
            background-color: #F4F6F9;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            padding: 20px;
        }}
        .container {{
            background-color: #ffffff;
            border-radius: 12px;
            box-shadow: 0 8px 24px rgba(0, 0, 0, 0.1);
            width: 100%;
            max-width: 480px;
            padding: 40px;
            text-align: center;
            display: flex;
            flex-direction: column;
            justify-content: center;
            align-items: center;
            box-sizing: border-box;
        }}
        h1 {{
            font-size: 24px;
            font-weight: 600;
            color: #333;
            margin-bottom: 24px;
            line-height: 1.4;
        }}
        .message {{
            font-size: 18px;
            color: #555;
            margin-bottom: 32px;
            line-height: 1.6;
        }}
        .button {{
            background-color: #007BFF;
            color: #fff;
            padding: 14px 28px;
            border-radius: 8px;
            text-decoration: none;
            font-size: 18px;
            font-weight: 600;
            transition: background-color 0.3s ease;
        }}
        .button:hover {{
            background-color: #0056b3;
        }}
    </style>
</head>
<body>
    <div class="container">
        <h1>{message}</h1>
        <p class="message">You can return to the homepage by clicking the button below.</p>
        <a href="/" class="button">Home</a>
    </div>
</body>
</html>
"""

print(page)
