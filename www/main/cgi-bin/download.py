#!/usr/bin/env python3

import os
import cgi
import cgitb
import sys

# Enable debugging
cgitb.enable()

# Define the path where files are located
FILE_DIRECTORY = "./www/main/cgi-bin/uploads/"

def generate_html_message(message):
    return f"""
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <title>File Download</title>
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
            <h2>{message}</h2>
            <p>Feel free to try again or contact support if the issue persists.</p>
            <a href="/" class="button">Return to Homepage</a>
        </div>
    </body>
    </html>
    """

def main():
    # Parse form data
    form = cgi.FieldStorage()

    # Get the 'resource' parameter from the form
    resource = form.getvalue('resource')

    # Construct the full file path
    file_path = os.path.join(FILE_DIRECTORY, resource)

    # Check if the file exists
    if resource and os.path.isfile(file_path):
        # Send response headers to initiate a file download
        print(f"Content-Type: application/octet-stream")
        print(f"Content-Disposition: attachment; filename=\"{resource}\"")
        print(f"Content-Length: {os.path.getsize(file_path)}")  # Optional
        print()  # End of headers
        sys.stdout.flush()

        # Read and send the file in chunks
        with open(file_path, 'rb') as file:
            chunk_size = 8192  # 8KB per chunk
            while chunk := file.read(chunk_size):
                sys.stdout.buffer.write(chunk)
                sys.stdout.buffer.flush()  # Ensure the data is sent immediately
    else:
        # If file does not exist, send an error message in HTML format
        print("Content-Type: text/html")
        print()  # End of headers
        print(generate_html_message("Error: The requested file does not exist."))

if __name__ == "__main__":
    main()
