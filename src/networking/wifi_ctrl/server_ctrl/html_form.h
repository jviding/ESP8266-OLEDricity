#pragma once

inline const char* HTML_FORM = R"(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>WiFi Logon</title>
  <style>
    * {
      margin: 0;
      padding: 0;
      box-sizing: border-box;
    }
    body {
      font-family: Arial, sans-serif;
      background: linear-gradient(135deg, #74b9ff, #a29bfe);
      height: 100vh;
      display: flex;
      justify-content: center;
      align-items: center;
      color: #2d3436;
    }
    .container {
      background: #ffffff;
      padding: 20px 30px;
      border-radius: 8px;
      box-shadow: 0 8px 16px rgba(0, 0, 0, 0.2);
      width: 300px;
      text-align: center;
    }
    .container h1 {
      font-size: 1.5rem;
      margin-bottom: 15px;
      color: #0984e3;
    }

    .form-group {
      margin-bottom: 15px;
      text-align: left;
    }
    .form-group label {
      font-size: 0.9rem;
      color: #636e72;
      margin-bottom: 5px;
      display: block;
    }
    .form-group input {
      width: 100%;
      padding: 8px 10px;
      border: 1px solid #dfe6e9;
      border-radius: 4px;
      font-size: 0.9rem;
    }
    .form-group input:focus {
      outline: none;
      border-color: #0984e3;
      box-shadow: 0 0 4px rgba(9, 132, 227, 0.5);
    }
    .form-group input:placeholder {
      color: #d3d3d3;
    }
    .submit-btn {
      background: #0984e3;
      color: #fff;
      border: none;
      padding: 10px 15px;
      border-radius: 4px;
      font-size: 1rem;
      cursor: pointer;
      width: 100%;
    }
    .submit-btn:hover {
      background: #74b9ff;
    }
    .footer {
      margin-top: 15px;
      font-size: 0.8rem;
      color: #b2bec3;
    }
  </style>
</head>
<body>
  <div class="container">
    <h1>WiFi Logon</h1>
    <form action="/" method="POST">
      <div class="form-group">
        <label for="ssid">SSID</label>
        <input type="text" id="ssid" name="ssid" placeholder="Enter WiFi SSID" required>
      </div>
      <div class="form-group">
        <label for="pwd">Password</label>
        <input type="text" id="pwd" name="pwd" placeholder="Enter WiFi Password" required>
      </div>
      <button type="submit" class="submit-btn">Connect</button>
    </form>
    <div class="footer">
        © 2024 Jasu Viding tmi
    </div>
  </div>
</body>
</html>
)";
