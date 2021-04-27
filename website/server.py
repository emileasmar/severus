from flask import Flask, render_template
app = Flask(__name__, template_folder='main')


@app.route('/')
def home():
    return render_template('index.html')


@app.route('/controls')
def controls():
    return render_template('controls.html', methods=['GET', 'POST'])


@app.route('/data')
def data():
    return render_template('data.html', methods=['GET', 'POST'])


@app.route('/security')
def security():
    file = open("/home/pi/Severus/data/data.dtd")
    par = eval("(" + file.read().split(",\n")[-2].split("(")[1])
    dataTemperature = int(par[0])
    dataHumidity = int(par[1])
    return render_template('security.html', value=dataTemperature, value2=dataHumidity)


@app.route('/settings')
def settings():
    return render_template('settings.html', methods=['GET', 'POST'])


if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=8080)
