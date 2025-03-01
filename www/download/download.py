#!/usr/bin/env python3

import cgi
import time
import os

# Required HTTP headers
print("Content-Type: text/html\r\n\r\n")

# Retrieve the file list for download
download_path = "./www/main/cgi-bin/uploads/"
path = "../cgi-bin/uploads/"
links = ""

for file in os.listdir(download_path):
    if os.path.isfile(os.path.join(download_path, file)):
        # If the file doesn't start with a dot, add it to the links
        if file[0] != ".":
            links += f'<a href={path}{file} download><div class="link">{file}</div></a>'

# Generate HTML content with the file links
html_content = f"""
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Download Files</title>
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

        h2 {{
            font-size: 2.5rem;
            color: #ff4b5c;
            text-shadow: 0 0 15px rgba(255, 75, 92, 0.7);
            margin-bottom: 1.5rem;
        }}

        .links a {{
            color: white;
            text-decoration: none;
            background-color: #121212;
        }}

        .link {{
            padding: 10px 20px;
            background-color: #121212;
            margin: 10px;
            border-radius: 10px;
            box-shadow: 0 0 15px rgba(0, 255, 153, 0.6);
            transition: transform 0.3s ease;
        }}

        .link:hover {{
            cursor: pointer;
            opacity: 0.9;
            transform: scale(1.05);
        }}
    </style>
</head>
<body>
    <div class="container">
        <h2>Choose and Download Your File</h2>
        <div class="links">
            {links}
        </div>
    </div>
</body>
</html>
"""

print(html_content)
