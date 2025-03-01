#!/usr/bin/env python3

import cgi
import os
from pathlib import Path

# Create an instance of FieldStorage
form = cgi.FieldStorage()

# Get the form data
filename = form.getvalue("filename")
content = form.getvalue("content")

# Path where the file will be created
directory = "./www/main/cgi-bin/uploads/"
filepath = os.path.join(directory, filename)

file = Path(filepath)

print("Content-Type: text/html; charset=utf-8\r\n\r\n")  # HTTP header

# if the file already exists
if file.exists():
    value = f"The file '{filename}' already exists."
else:
    # Initialize the HTML content variable
    value = ""

    # Check if the directory exists, if not, create it
    if not os.path.exists(directory):
        os.makedirs(directory)

    try:
        with open(filepath, "w") as file:
            file.write(content)
        value = f"The file '{filename}' has been successfully created."

    except Exception as e:
        value = f"Failed to create the file '{filename}'"

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
            background-color: #000000;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            color: #fff;
            margin: 0;
            padding: 0;
            text-align: center;
            background-image: url('https://www.transparenttextures.com/patterns/starry-night.png'); /* Spacey background */
            background-size: cover;
            background-attachment: fixed;
            overflow: hidden;
        }}

        .container {{
            background-color: rgba(0, 0, 0, 0.6);
            padding: 2rem;
            border-radius: 15px;
            box-shadow: 0 0 20px rgba(255, 75, 92, 0.7);
            text-align: center;
        }}

        h2 {{
            color: #ff4b5c;
            font-size: 2rem;
            text-shadow: 0 0 20px rgba(255, 75, 92, 0.7);
        }}

        p {{
            font-size: 1.2rem;
            color: #00ff99;
            text-shadow: 0 0 15px rgba(0, 255, 153, 0.7);
            margin-top: 20px;
        }}

        .button {{
            padding: 12px 30px;
            background-color: #ff4b5c;
            border: none;
            border-radius: 30px;
            font-size: 1rem;
            color: #fff;
            cursor: pointer;
            transition: all 0.3s ease;
            margin-top: 20px;
        }}

        .button:hover {{
            background-color: #ff1f2a;
            transform: scale(1.1);
        }}

        .button:active {{
            transform: scale(0.98);
        }}
    </style>
</head>
<body>
    <div class="container">
        <h2>{value}</h2>
        <p>If you would like to create another file, try again or contact support.</p>
        <a href="/" class="button">Return to Homepage</a>
    </div>
</body>
</html>
"""

print(html_content)
