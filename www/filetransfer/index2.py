#!/usr/bin/env python3

import cgi
import time
import os

download_path = "./www/filetransfer/uploads/"
upload_url = "/filetransfer/uploads/"

# Function to load the file list
def load_files():
    links = ""
    for file in os.listdir(download_path):
        if os.path.isfile(os.path.join(download_path, file)):
            if file[0] != "." and file != "index.py":
                links += f"""
                    <div id="file-{file}" class="link">
                        <div>{file}</div>

                        <div class="link-buttons">
                            <a href={upload_url}{file} class="link-button" download>
                                Download
                            </a>
                            <form id="delete-{file}" onsubmit="deleteFile(event)">
                                <button type="submit" class="link-button">
                                    Delete
                                </button>
                            </form>
                        </div>
                    </div>
                """
    return links

def main():
    links = load_files()
    html_content = f"""
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <title>File Transfer</title>
        <style>
            @import url('https://fonts.googleapis.com/css2?family=Inter:ital,opsz,wght@0,14..32,100..900;1,14..32,100..900&display=swap');

            body {{
                font-family: 'Inter', sans-serif;
                background-color: #1d1f21;
                color: #f1f1f1;
                display: flex;
                justify-content: center;
                align-items: center;
                height: 100vh;
                margin: 0;
                overflow: hidden;
            }}
            .container {{
                max-width: 1000px;
                width: 90%;
                text-align: center;
                padding: 2rem;
                background-color: #2b2f35;
                border-radius: 15px;
                box-shadow: 0 4px 10px rgba(0, 0, 0, 0.1);
            }}
            h2 {{
                font-size: 2.5rem;
                color: #f0f0f0;
                margin-bottom: 1.5rem;
            }}
            .button {{
                padding: 1rem 3rem;
                background-color: #333;
                border-radius: 25px;
                color: #f0f0f0;
                font-weight: bold;
                cursor: pointer;
                transition: all 0.3s ease;
            }}
            .button:hover {{
                background-color: #555;
            }}
            .links {{
                margin-top: 2rem;
                display: flex;
                flex-wrap: wrap;
                justify-content: center;
            }}
            .link {{
                padding: 1rem;
                margin: 10px;
                background-color: #383d44;
                border-radius: 10px;
                transition: background-color 0.3s ease;
                width: 200px;
                display: flex;
                justify-content: space-between;
                align-items: center;
            }}
            .link:hover {{
                background-color: #484c55;
                cursor: pointer;
            }}
            .link-buttons {{
                display: flex;
                gap: 10px;
            }}
            .link-button {{
                padding: 5px 10px;
                background-color: #4e7dd4;
                color: white;
                text-decoration: none;
                border-radius: 5px;
                transition: background-color 0.3s ease;
            }}
            .link-button:hover {{
                background-color: #3a6cb5;
            }}
        </style>
        <script>
            function deleteFile(event) {{
                event.stopPropagation();
                event.preventDefault();

                var form = event.target;
                var file = form.id.replace('delete-', '');

                fetch('{upload_url}' + file, {{
                    method: 'DELETE'
                }})
                .then(response => {{
                    if (response.ok) {{
                        document.getElementById('file-' + file).remove();
                    }} else {{
                        alert('Failed to delete file');
                    }}
                }})
                .catch(error => {{
                    alert('Failed to delete file');
                }});
            }}

            function handleUpload(event) {{
                event.stopPropagation();
                event.preventDefault();

                var form = event.target;
                var fileInput = form.file;
                var filename = form.filename.value;
                var enctype = document.getElementById('enctypeSelect').value;

                if (filename) {{
                    filename = filename;
                }}

                if (!fileInput.files.length) {{
                    alert('Please select a file to upload');
                    return;
                }}

                fetch('{upload_url}' + filename, {{
                    method: 'POST',
                    headers: {{
                        'Filename': filename,
                        'Content-Type': 'application/octet-stream',
                    }},
                    body: fileInput.files[0]
                }})
                .then(response => {{
                    if (response.ok) {{
                        alert('File uploaded successfully');
                        window.location.reload();
                    }} else {{
                        alert('Failed to upload file');
                    }}
                }})
                .catch(error => {{
                    alert('Failed to upload file');
                }});
            }}
        </script>
    </head>
    <body>
        <div class="container">
            <h2>File Transfer</h2>
            <form id="uploadForm" onsubmit="handleUpload(event)">
                <label for="filenameInput">File Name:</label>
                <input id="filenameInput" type="text" name="filename">

                <label for="enctypeSelect">Select Encoding:</label>
                <select id="enctypeSelect">
                    <option value="application/octet-stream">application/octet-stream</option>
                    <option value="multipart/form-data">multipart/form-data</option>
                </select>

                <input id="fileInput" type="file" name="file" class="hidden-input">
                <button type="button" class="button" onclick="document.getElementById('fileInput').click();">Select File</button>
                <button type="submit" class="button">Upload File</button>
            </form>
            <div class="links">
                {links}
            </div>
        </div>
    </body>
    </html>
    """

    print("Content-Type: text/html\r\n\r\n")
    print(html_content)

if __name__ == "__main__":
    main()
