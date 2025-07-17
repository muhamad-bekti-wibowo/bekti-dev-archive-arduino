const char Configuration[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>WiFi Configuration</title>
    <!-- Link to Bootstrap CSS -->
    <link href="https://maxcdn.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css" rel="stylesheet">
</head>
<body>
    <div class="container">
        <div class="row justify-content-center">
            <div class="col-md-6">
                <h3 class="text-center mt-5">WiFi Configuration</h3>
                <form action="/ssid_password" method="POST">
                    <div class="form-group">
                        <label for="ssid">SSID:</label>
                        <input type="text" class="form-control" id="ssid" name="ssid" placeholder="Enter SSID" required>
                    </div>
                    <div class="form-group">
                        <label for="password">Password:</label>
                        <input type="password" class="form-control" id="password" name="pass" placeholder="Enter Password" >
                    </div>
                    <button type="submit" class="btn btn-primary btn-block">Submit</button>
                </form>
            </div>
        </div>
    </div>

   </body>
</html>

)rawliteral";
