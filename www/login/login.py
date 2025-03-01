#!/usr/bin/env python3

import os
import cgitb
import uuid
import cgi
import time
import urllib.parse

isNewClient = False

cgitb.enable()

print("Content-Type: text/html; charset=utf-8")

# ========= CREATE =========
def generateId():
    return str(uuid.uuid4())

def generateExpirationDate():
    expiration_time = time.time() + 60 * 60 * 24 * 30
    formatted_time = time.strftime("%a, %d-%b-%Y %H:%M:%S GMT", time.gmtime(expiration_time))
    return formatted_time

def createNewCookie():
    global isNewClient
    isNewClient = True
    form = cgi.FieldStorage()
    name = form.getvalue("username")
    password = form.getvalue("password")

    if name is None or password is None:
        return None

    isNewClient = False
    user_id = generateId()
    expiration_date = generateExpirationDate()
    print(f"Set-Cookie: id={user_id}; Expires={expiration_date}; Path=/\r\n")
    if not os.path.exists("./www/login/database"):
        os.makedirs("./www/login/database")
    with open(f"./www/login/database/{user_id}.txt", "w") as file:
        file.write(f"{name}\n{password}")
    return user_id

# ========= READ =========

def saveNote():
    form = cgi.FieldStorage()
    note = form.getvalue("note")
    
    if note is None:
        return
    
    user_id = getUserIdFromCookie()
    if user_id is None:
        return
    
    file_path = f"./www/login/database/{user_id}.txt"
    if not os.path.exists(file_path):
        return
    
    with open(file_path, "r") as file:
        lines = file.readlines()
        if len(lines) < 2:
            return
        username = lines[0].strip()
        password = lines[1].strip()
    
    with open(file_path, "w") as file:
        file.write(f"{username}\n{password}\n{note}")

def getUserIdFromCookie():
    cookies = os.environ.get('HTTP_COOKIE', '')
    user_id = None
    if cookies:
        for cookie in cookies.split(';'):
            parts = cookie.strip().split('=', 1)
            if len(parts) == 2:
                name, value = parts
                if name == "id":
                    user_id = value
                    break
    return user_id

def getUserInfo(user_id):
    saveNote()
    file_path = f"./www/login/database/{user_id}.txt"
    
    if not os.path.exists(file_path):
        print("<html><body><h1>Erreur: utilisateur non trouvé</h1></body></html>")
        return None
    
    with open(file_path, "r") as file:
        lines = file.readlines()
        if len(lines) < 2:
            print("<html><body><h1>Erreur: données utilisateur incorrectes</h1></body></html>")
            return None
        username = lines[0].strip()
        password = lines[1].strip()
        if len(lines) > 2:
            note = lines[2].strip()
        else:
            note = ""
    return {"username": username, "password": password, "note": note}

# Code principal
user_id = getUserIdFromCookie()
userInfo = {"username": "", "password": "", "note": ""}
if user_id is None:
    user_id = createNewCookie()
else:
    userInfo = getUserInfo(user_id)
    if userInfo is None:
        isNewClient = True


loginPage = f"""
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login Page</title>
    <style>
        @import url('https://fonts.googleapis.com/css2?family=Inter:ital,opsz,wght@0,14..32,100..900;1,14..32,100..900&display=swap');

        body {{
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            background: linear-gradient(135deg, #0a1f2c, #0f2e45);
            margin: 0;
            font-family: 'Inter', sans-serif;
            color: #e3f2fd;
        }}
        
        .container {{
            background: rgba(0, 0, 0, 0.7);
            border-radius: 20px;
            box-shadow: 0 8px 16px rgba(0, 0, 0, 0.3);
            padding: 2rem;
            width: 100%;
            max-width: 400px;
            text-align: center;
            animation: pulse 1s infinite alternate;
        }}

        h1 {{
            font-size: 2.5rem;
            margin-bottom: 1.5rem;
            color: #4dd0e1;
        }}

        input[type="text"], input[type="password"] {{
            padding: 1rem;
            margin: 0.8rem 0;
            border: none;
            border-radius: 10px;
            font-size: 1.2rem;
            background: #1c2b38;
            color: #f0f0f0;
            transition: transform 0.2s ease-in-out;
        }}

        input[type="text"]:focus, input[type="password"]:focus {{
            transform: scale(1.05);
            outline: none;
            box-shadow: 0 0 10px #4dd0e1;
        }}

        .button {{
            padding: 1rem;
            font-size: 1.1rem;
            background-color: #4dd0e1;
            border: none;
            border-radius: 10px;
            color: #fff;
            cursor: pointer;
            margin-top: 1rem;
            transition: all 0.3s ease;
        }}
        .button:hover {{
            background-color: #00838f;
            transform: scale(1.1);
        }}

        @keyframes pulse {{
            0% {{ opacity: 1; }}
            100% {{ opacity: 0.7; }}
        }}
    </style>
</head>
<body>
    <div class="container">
        <h1>Login</h1>
        <form action="./" method="post">
            <input type="text" id="username" name="username" placeholder="Username" required>
            <input type="password" id="password" name="password" placeholder="Password" required>
            <button class="button" type="submit">Submit</button>
        </form>
    </div>
</body>
</html>
"""

resultPage = f"""
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Dashboard</title>
    <style>
        @import url('https://fonts.googleapis.com/css2?family=Inter:ital,opsz,wght@0,14..32,100..900;1,14..32,100..900&display=swap');

        body {{
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            background: linear-gradient(135deg, #2c3e50, #34495e);
            margin: 0;
            font-family: 'Inter', sans-serif;
            color: #e3f2fd;
        }}

        .container {{
            background: rgba(0, 0, 0, 0.7);
            border-radius: 20px;
            box-shadow: 0 8px 16px rgba(0, 0, 0, 0.3);
            padding: 2rem;
            width: 100%;
            max-width: 400px;
            text-align: center;
        }}

        h1 {{
            font-size: 2.5rem;
            margin-bottom: 1.5rem;
            color: #4dd0e1;
        }}

        p {{
            font-size: 1.1rem;
            margin-bottom: 1rem;
        }}

        textarea {{
            width: 100%;
            padding: 1rem;
            border-radius: 10px;
            margin-bottom: 1rem;
            font-size: 1.1rem;
            color: #000;
            background-color: #fff;
        }}

        .button {{
            padding: 1rem;
            font-size: 1.1rem;
            background-color: #4dd0e1;
            border: none;
            border-radius: 10px;
            color: #fff;
            cursor: pointer;
            transition: all 0.3s ease;
            width: 100%;
        }}
        
        .button:hover {{
            background-color: #00838f;
            transform: scale(1.1);
        }}

        .delete {{
            background-color: #e74c3c;
        }}

        .buttons {{
            display: flex;
            justify-content: space-between;
            gap: 1rem;
            margin-top: 1rem;
        }}
    </style>
</head>
<body>
    <div class="container">
        <h1>Welcome {userInfo['username']}</h1>
        <p>Your password is: {userInfo['password']}</p>
        <textarea id="note" name="note" rows="4" cols="50">{userInfo['note']}</textarea>
        <div class="buttons">
            <button class="button" onclick="saveNote()">Save notes</button>
            <a href="/" class="button">Home</a>
            <button class="button delete" onclick="window.location.href = './logout.py'">Delete Account</button>
        </div>
    </div>
</body>
<script>
function saveNote() {{
    let note = document.getElementById("note").value;
    
    fetch("./login.py", {{
        method: "POST",
        headers: {{
            'Content-Type': 'application/x-www-form-urlencoded'
        }},
        body: new URLSearchParams({{
            'note': note
        }})
    }})
    .then(response => response.text())
    .then(data => {{
        console.log("Note saved:", data);
        alert("Note saved successfully!");
    }})
    .catch(error => {{
        console.error("Error saving note:", error);
        alert("Failed to save note.");
    }});
}}
</script>
</html>
"""

if (isNewClient == True):
    print("\r\n")
    print(loginPage)
else:
    print(resultPage)
