const char jadwal[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.1/jquery.min.js"></script>
    <title>Jadwal</title>
    <style>
        body {
            width: 100vw;
            height: 100vh;
            display: flex;
            flex-direction: column;
            justify-content: center;
            align-items: center;

        }

        button,
        input,
        .time {
            width: 200px;
            height: 40px;
            border-radius: 10px;
            border: 1px solid rgba(1, 1, 1, 0.1);
            box-shadow: 0px 1px 10px 1px rgba(1, 1, 1, 0.1);
            text-align: center;
        }

        .button {
            display: flex;
            flex-direction: column;
            justify-content: center;
            align-items: center;

        }
    </style>
</head>

<body>
    <form action="jadwal" method="get">
        <div class="times time button" style="padding: 20px;">
            00:00:00
        </div>
        <div style="padding: 20px;">
            <div class="time button">
                Time On :
            </div>
            <input type="text" name="on">
        </div>
        <div style="padding: 20px;">
            <div class="time button">
                Time Off :
            </div>
            <input type="text" name="off">
        </div>
        <div class="button">

            <button>Submit</button>
        </div>
    </form>
    <script>function load() {
            $.get("/time", function (data, status) {
                $(".times").text(data);
            });
        }
        $(document).ready(function () {
            load();
        });
        setInterval(function () {
            load();
        }, 1000);
    </script>
</body>

</html>
)=====";
