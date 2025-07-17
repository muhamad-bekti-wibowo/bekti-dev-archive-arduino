const char KWH[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.1/jquery.min.js"></script>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
    <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.5.0/Chart.min.js"></script>
    <script src="https://cdn.plot.ly/plotly-latest.min.js"></script>
    <script src="https://code.highcharts.com/highcharts.js"></script>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Pengukur Listrik</title>
    <style>
        .center {
            display: flex;
            align-items: center;
            justify-content: center;
            flex-direction: column;
            width: 100vw;
            height: 100vh;
        }

        td {
            font-size: 2vw;
            border: 0px solid black;
            margin: 10px;
            padding: 10px;
            box-shadow: 0px 20px 20px 0px rgba(0, 0, 0, 0.2);
            text-align: center;
            width: 300px;
            height: 50px;
        }

        button {
            padding: 10px;
            margin: 40px 10px 10px 10px;
            box-shadow: 0px 20px 20px 0px rgba(0, 0, 0, 0.2);
            width: 100px;
            height: 40px;
            border: 0px solid green;
            border-radius: 40px;
        }
    </style>
</head>

<body>
    <div class="center">
        <div style="padding: 100px;"></div>
        <div style="display: flex; justify-content: center;align-items: center; width: 100vw;">
            <div id="chartvoltage" class="container" style="margin-top: 40px; width: 80vw;"></div>
            <div id="chartcurrent" class="container" style="margin-top: 40px; width: 80vw;"></div>
            <div id="chartpower" class="container" style="margin-top: 40px; width: 80vw;"></div>
        </div>
        <div style="display: flex; justify-content: center;align-items: center; width: 100vw;">
            <div id="chartenergi" class="container" style="margin-top: 40px; width: 80vw;"></div>
            <div id="chartfrequensi" class="container" style="margin-top: 40px; width: 80vw;"></div>
            <div id="chartfactordaya" class="container" style="margin-top: 40px; width: 80vw;"></div>

        </div>
        <table>
            <tr>
                <td>
                    Tegangan
                </td>
                <td style="width: 10px;">
                    :
                </td>
                <td>
                    <span class="Voltage">100</span> V
                </td>

            </tr>
            <tr>
                <td>
                    Current
                </td>
                <td style="width: 10px;">
                    :
                </td>
                <td>
                    <span class="Current">100</span> A
                </td>

            </tr>
            <tr>
                <td>
                    Daya
                </td>
                <td style="width: 10px;">
                    :
                </td>
                <td>
                    <span class="Power">100</span> W
                </td>

            </tr>
            <tr>
                <td>
                    Energi
                </td>
                <td style="width: 10px;">
                    :
                </td>
                <td>
                    <span class="Energy">100</span> Kwh
                </td>

            </tr>
            <tr>
                <td>
                    Frekuensi
                </td>
                <td style="width: 10px;">
                    :
                </td>
                <td>
                    <span class="Frequensi">100</span> Hz
                </td>

            </tr>
            <tr>
                <td>
                    Faktor Daya / Efisiensi
                </td>
                <td style="width: 10px;">
                    :
                </td>
                <td>
                    <span class="Efisiensi">100</span> %
                </td>
            </tr>
        </table>
        <div>
        <button onclick="reset()"> Reset </button>
         <button onclick="state()"> State </button>
</div>
    </div>


    <script>
        var chartA = new Highcharts.Chart({
            chart: { renderTo: 'chartvoltage' },
            title: { text: 'Voltage' },
            series: [{
                showInLegend: false,
                data: []
            }],
            plotOptions: {
                line: {
                    animation: false,
                    dataLabels: { enabled: true }
                },
                series: { color: '#059e8a' }
            },
            xAxis: {
                type: 'datetime',
                dateTimeLabelFormats: { second: '%H:%M:%S' }
            },
            yAxis: {
                title: { text: 'V' }
            },
            credits: { enabled: false }
        });
        var chartB = new Highcharts.Chart({
            chart: { renderTo: 'chartcurrent' },
            title: { text: 'Current' },
            series: [{
                showInLegend: false,
                data: []
            }],
            plotOptions: {
                line: {
                    animation: false,
                    dataLabels: { enabled: true }
                },
                series: { color: '#059e8a' }
            },
            xAxis: {
                type: 'datetime',
                dateTimeLabelFormats: { second: '%H:%M:%S' }
            },
            yAxis: {
                title: { text: 'A' }
                //title: { text: 'Temperature (Fahrenheit)' }
            },
            credits: { enabled: false }
        }); var chartC = new Highcharts.Chart({
            chart: { renderTo: 'chartpower' },
            title: { text: 'Daya Listrik' },
            series: [{
                showInLegend: false,
                data: []
            }],
            plotOptions: {
                line: {
                    animation: false,
                    dataLabels: { enabled: true }
                },
                series: { color: '#059e8a' }
            },
            xAxis: {
                type: 'datetime',
                dateTimeLabelFormats: { second: '%H:%M:%S' }
            },
            yAxis: {
                title: { text: 'daya' }
                //title: { text: 'Temperature (Fahrenheit)' }
            },
            credits: { enabled: false }
        }); var chartD = new Highcharts.Chart({
            chart: { renderTo: 'chartenergi' },
            title: { text: 'Energi' },
            series: [{
                showInLegend: false,
                data: []
            }],
            plotOptions: {
                line: {
                    animation: false,
                    dataLabels: { enabled: true }
                },
                series: { color: '#059e8a' }
            },
            xAxis: {
                type: 'datetime',
                dateTimeLabelFormats: { second: '%H:%M:%S' }
            },
            yAxis: {
                title: { text: 'Kwh' }
                //title: { text: 'Temperature (Fahrenheit)' }
            },
            credits: { enabled: false }
        }); var chartE = new Highcharts.Chart({
            chart: { renderTo: 'chartfrequensi' },
            title: { text: 'Frequensi' },
            series: [{
                showInLegend: false,
                data: []
            }],
            plotOptions: {
                line: {
                    animation: false,
                    dataLabels: { enabled: true }
                },
                series: { color: '#059e8a' }
            },
            xAxis: {
                type: 'datetime',
                dateTimeLabelFormats: { second: '%H:%M:%S' }
            },
            yAxis: {
                title: { text: 'Hz' }
                //title: { text: 'Temperature (Fahrenheit)' }
            },
            credits: { enabled: false }
        }); var chartF = new Highcharts.Chart({
            chart: { renderTo: 'chartfactordaya' },
            title: { text: 'Faktor Daya' },
            series: [{
                showInLegend: false,
                data: []
            }],
            plotOptions: {
                line: {
                    animation: false,
                    dataLabels: { enabled: true }
                },
                series: { color: '#059e8a' }
            },
            xAxis: {
                type: 'datetime',
                dateTimeLabelFormats: { second: '%H:%M:%S' }
            },
            yAxis: {
                title: { text: 'COS Q' }
                //title: { text: 'Temperature (Fahrenheit)' }
            },
            credits: { enabled: false }
        });
    </script>
</body>
<script>
    function load() {
        $.get("/data", function (data_, status) {
            const data = data_.split('~');
            $(".Voltage").text(data[0]);
            $(".Current").text(data[1]);
            $(".Power").text(data[2]);
            $(".Energy").text(data[3]);
            $(".Frequensi").text(data[4]);
            $(".Efisiensi").text(data[5]);
        });
    }
    $(document).ready(function () {
        load();
    });
    setInterval(function () {
        load();
    }, 1000);

    function send() {
        $.get("/reset", function (data_, status) {

        });
    }
function state() {
        $.get("/state", function (data_, status) {

        });
    }
</script>
<script>
    setInterval(function () { //Load Data
        var xhttpDataLine1 = new XMLHttpRequest();
        xhttpDataLine1.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                const All_Array = this.responseText.split("~");
                var x = (new Date()).getTime(),
                    y = parseFloat(All_Array[0]);
                if (chartA.series[0].data.length > 40) {
                    chartA.series[0].addPoint([x, y], true, true, true);
                } else {
                    chartA.series[0].addPoint([x, y], true, false, true);
                }
                var x = (new Date()).getTime(),
                    y = parseFloat(All_Array[1]);
                if (chartB.series[0].data.length > 40) {
                    chartB.series[0].addPoint([x, y], true, true, true);
                } else {
                    chartB.series[0].addPoint([x, y], true, false, true);
                }var x = (new Date()).getTime(),
                    y = parseFloat(All_Array[2]);
                if (chartC.series[0].data.length > 40) {
                    chartC.series[0].addPoint([x, y], true, true, true);
                } else {
                    chartC.series[0].addPoint([x, y], true, false, true);
                }var x = (new Date()).getTime(),
                    y = parseFloat(All_Array[3]);
                if (chartD.series[0].data.length > 40) {
                    chartD.series[0].addPoint([x, y], true, true, true);
                } else {
                    chartD.series[0].addPoint([x, y], true, false, true);
                }var x = (new Date()).getTime(),
                    y = parseFloat(All_Array[4]);
                if (chartE.series[0].data.length > 40) {
                    chartE.series[0].addPoint([x, y], true, true, true);
                } else {
                    chartE.series[0].addPoint([x, y], true, false, true);
                }var x = (new Date()).getTime(),
                    y = parseFloat(All_Array[5]);
                if (chartF.series[0].data.length > 40) {
                    chartF.series[0].addPoint([x, y], true, true, true);
                } else {
                    chartF.series[0].addPoint([x, y], true, false, true);
                }
            }
        };
        xhttpDataLine1.open("GET", "/data", true);
        xhttpDataLine1.send();
    }, 1000);
</script>

</html>
)=====";
