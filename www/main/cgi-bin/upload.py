#!/usr/bin/env python3

import cgi
import os
import cgitb

cgitb.enable()

upload_dir = "./www/main/cgi-bin/uploads/"

form = cgi.FieldStorage()

file_item = form['file']

print("Content-Type: text/html; charset=utf-8")
print()

if file_item.filename:
    filename = os.path.basename(file_item.filename)
    filepath = os.path.join(upload_dir, filename)

    try:
        with open(filepath, 'wb') as output_file:
            while True:
                chunk = file_item.file.read(1024)
                if not chunk:
                    break
                output_file.write(chunk)

        value = f"'{filename}' has been uploaded successfully and saved to '{upload_dir}'"
    except Exception as e:
        value = f"Error while saving the file: {e}"
else:
    value = "No file has been uploaded."

html_content = f"""
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Upload</title>
    <style>
        @import url('https://fonts.googleapis.com/css2?family=Inter:ital,opsz,wght@0,14..32,100..900;1,14..32,100..900&display=swap');

        body {{
            font-family: 'Inter', sans-serif;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            background-color: #0a0a0a;
            color: #fff;
            margin: 0;
            padding: 0;
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
            font-size: 2rem;
            color: #ff4b5c;
            text-shadow: 0 0 15px rgba(255, 75, 92, 0.7);
            margin-bottom: 1.5rem;
        }}

        a {{
            color: #00ff99;
            text-decoration: none;
            font-size: 1.2rem;
            letter-spacing: 1px;
            transition: color 0.3s;
        }}

        a:hover {{
            color: #ff4b5c;
        }}
    </style>
</head>
<body>
    <div class="container">
        <h2>{value}</h2>
        <a href="/">Back home</a>
    </div>
</body>
</html>
"""

print(html_content)
