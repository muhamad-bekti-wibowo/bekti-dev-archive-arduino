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

        .Room-switch {
            position: relative;
            display: inline-block;
            width: 60px;
            height: 25px;
        }

        .Room-switch input {
            opacity: 0;
            width: 0;
            height: 0;
        }

        .Room-Toogle {

            position: absolute;
            cursor: pointer;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            background-color: #ccc;
            -webkit-transition: .4s;
            transition: .4s;
        }

        .Room-Toogle:before {
            position: absolute;
            content: "OFF";
            display: flex;
            align-items: center;
            justify-content: center;
            font-size: 10px;
            height: 20px;
            width: 20px;
            left: 3px;
            bottom: 2px;
            background-color: white;
            -webkit-transition: .4s;
            transition: .4s;
        }

        input:checked+.Room-Toogle {
            background-color: #2196F3;

        }

        input:focus+.Room-Toogle {
            box-shadow: 0 0 1px #2196F3;
        }

        input:checked+.Room-Toogle:before {
            transform: translateX(35px);
            content: "ON";
            transition: .4s;
        }

        .Room-Toogle.round {
            border-radius: 34px;
        }

        .Room-Toogle.round:before {
            border-radius: 50%;
        }  
        .flexwrap {
            display: flex;
            align-items: center;
            justify-content: center;
            flex-wrap: wrap;
        }
        .marginx{
 margin: 30px;
        }
    </style>
</head>

<body>
    <form action="#" >
        <div class="flexwrap "style="flex-direction: column;">
        <div class="times time button" style="padding: 20px;">
            00:00:00
        </div>
        <div style="padding: 20px;">
            <div class="time button">
                Time On :
            </div>
            <input type="number" name="on" value="5">
        </div>
        <div style="padding: 20px;">
            <div class="time button">
                Time Off :
            </div>
            <input type="number" name="off"value="18">
        </div>

    </div>
        <div class="flexwrap ">
            <div class="marginx flexwrap " style="flex-direction: column;">
                <div>IR</div>
                <label class="Room-switch ">
                    <input id="ir" type="checkbox" name="ir">
                    <span class="Room-Toogle round">
                    </span>
                </label>
            </div>
            <div class="marginx flexwrap " style="flex-direction: column;">
                <div>Lampu Ruang Tamu</div>
                <label class="Room-switch">
                    <input id="rt" type="checkbox" name="lrt">
                    <span class="Room-Toogle round">
                    </span>
                </label>
            </div>
            <div class="marginx flexwrap " style="flex-direction: column;">
                <div>Kipas Ruang Tamu</div>
                <label class="Room-switch">
                    <input id="kipas" type="checkbox" name="krt">
                    <span class="Room-Toogle round">
                    </span>
                </label>
            </div>
            <div class="marginx flexwrap " style="flex-direction: column;">
                <div>Lampu Ruang Makan</div>
                <label class="Room-switch">
                    <input id="rm" type="checkbox" name="rm">
                    <span class="Room-Toogle round">
                    </span>
                </label>
            </div>
<div class="marginx flexwrap " style="flex-direction: column;">
                <div>auto</div>
                <label class="Room-switch">
                    <input id="auto" type="checkbox" name="auto">
                    <span class="Room-Toogle round">
                    </span>
                </label>
            </div>
            <div class="marginx flexwrap " style="flex-direction: column;">
                <div>lampu3</div>
                <label class="Room-switch">
                    <input id="lampu3" type="checkbox" name="lampu3">
                    <span class="Room-Toogle round">
                    </span>
                </label>
            </div>
        </div>
    </form>        <div class="button">

            <button onclick="jadwal()">Submit</button>
        </div> 
    <script>
    function jadwal() {
            $.get("/jadwal?"+$("form").serialize(), function (data, status) {
                $(".times").text(data);
                console.log($("form").serialize());
            });
        }
    function load() {
            $.get("/time", function (data, status) {
                $(".times").text(data);
            });
            $.get("/data", function (data, status) {
                const datas = data.split('~');
                document.getElementById("ir").checked = datas[0] == 0 ? true : false;
                document.getElementById("rt").checked = datas[1] == 0 ? true : false;
                document.getElementById("rm").checked = datas[2] == 0 ? true : false;
                document.getElementById("kipas").checked = datas[3] == 0 ? true : false;
                document.getElementById("auto").checked = datas[4] == 1 ? true : false;
                 document.getElementById("lampu3").checked = datas[5] == 0 ? true : false;
            });
            
        }
        $(document).ready(function () {
            load();
        });
        setInterval(function () {
            load();
        }, 10000);
    </script>
</body>

</html>
)=====";
